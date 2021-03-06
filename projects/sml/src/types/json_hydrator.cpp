/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <istream>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/primitive.hpp"
#include "dogen/sml/types/hydration_error.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/json_hydrator.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.json_hydrator"));

const std::string empty;
const std::string hardware_model_name("hardware");
const std::string model_name_key("model_name");
const std::string bool_true("true");
const std::string bool_false("false");

const std::string is_expandable_key("is_expandable");
const std::string documentation_key("documentation");
const std::string origin_key("origin");
const std::string origin_system_value("system");
const std::string origin_user_value("user");
const std::string elements_key("elements");

const std::string meta_type_key("meta_type");
const std::string meta_type_object_value("object");
const std::string meta_type_primitive_value("primitive");

const std::string simple_name_key("simple_name");
const std::string module_path_key("module_path");
const std::string extensions_key("extensions");

const std::string object_type_key("object_type");
const std::string object_type_smart_pointer_value("smart_pointer");
const std::string object_type_ordered_container_value("ordered_container");
const std::string object_type_hash_container_value("hash_container");
const std::string object_type_sequence_container_value("sequence_container");

const std::string invalid_json_file("Failed to parse JSON file");
const std::string invalid_option_in_json_file(
    "Failed to read option in JSON file: ");
const std::string invalid_path("Failed to find JSON path: ");
const std::string invalid_origin("Invalid value for origin: ");
const std::string invalid_meta_type("Invalid value for meta type: ");
const std::string invalid_is_expandable("Invalid value for is expandible: ");
const std::string model_has_no_types("Did not find any elements in model");
const std::string missing_module("Could not find module: ");
const std::string failed_to_open_file("Failed to open file: ");

}

namespace dogen {
namespace sml {

json_hydrator::json_hydrator(const dynamic::schema::workflow& w)
    : schema_workflow_(w) { }

boost::optional<qname> containing_module(model& m, const qname& qn) {
    if (qn.model_name().empty() || qn.simple_name() == m.name().model_name()) {
        BOOST_LOG_SEV(lg, debug) << "Type has no containing module: "
                                 << string_converter::convert(qn);
        return boost::optional<qname>();
    }

    qname module_qn;
    module_qn.model_name(qn.model_name());

    if (qn.module_path().empty()) {
        module_qn.simple_name(qn.model_name());
    } else {
        module_qn.simple_name(qn.module_path().back());
        module_qn.module_path(qn.module_path());
        module_qn.module_path().pop_back();
    }

    const auto i(m.modules().find(module_qn));
    if (i != m.modules().end())
        return module_qn;

    BOOST_LOG_SEV(lg, debug) << "Could not find containing module: "
                             << string_converter::convert(module_qn);
    return boost::optional<qname>();;
}

template<typename AssociativeContainerOfContainable>
inline void
update_containing_module(model& m, AssociativeContainerOfContainable& c) {
    for (auto& pair : c) {
        auto& s(pair.second);
        s.containing_module(containing_module(m, s.name()));

        if (!s.containing_module())
            continue;

        auto i(m.modules().find(*s.containing_module()));
        if (i == m.modules().end()) {
            const auto sn(s.containing_module()->simple_name());
            BOOST_LOG_SEV(lg, error) << missing_module << sn;
            BOOST_THROW_EXCEPTION(hydration_error(missing_module + sn));
        }

        BOOST_LOG_SEV(lg, debug) << "Adding type to module. Type: '"
                                 << string_converter::convert(s.name())
                                 << "' Module: '"
                                 << string_converter::convert(i->first);
        i->second.members().push_back(s.name());
    }
}

std::string json_hydrator::model_name(const model& m) const {
    if (m.name().model_name() == hardware_model_name)
        return empty;
    return m.name().model_name();
}

generation_types json_hydrator::generation_type(const bool is_target) const {
    if (is_target)
        return generation_types::full_generation;
    return generation_types::no_generation;
}

void json_hydrator::read_module_path(const boost::property_tree::ptree& pt,
    model& m, qname& qn) const {
    const auto i(pt.find(module_path_key));
    if (i == pt.not_found())
        return;

    for (auto j(i->second.begin()); j != i->second.end(); ++j) {
        const auto module_name(j->second.get_value<std::string>());
        qn.module_path().push_back(module_name);

        qname module_qn;
        module_qn.simple_name(module_name);
        module_qn.model_name(model_name(m));
        auto mp(qn.module_path());
        mp.pop_back();
        module_qn.module_path(mp);

        const auto i(m.modules().find(module_qn));
        if (i == m.modules().end()) {
            module mod;
            mod.name(module_qn);
            mod.origin_type(m.origin_type());
            mod.generation_type(m.generation_type());
            mod.type(module_types::regular);
            m.modules().insert(std::make_pair(module_qn, mod));
        }
    }
}

dynamic::schema::object json_hydrator::
create_dynamic_extensions(const boost::property_tree::ptree& pt,
    const dynamic::schema::scope_types st) const {
    const auto i(pt.find(extensions_key));
    if (i == pt.not_found())
        return dynamic::schema::object();

    dynamic::schema::object r;
    std::list<std::pair<std::string, std::string> > kvps;
    for (auto j(i->second.begin()); j != i->second.end(); ++j) {
        const auto field_name(j->first);
        const auto field_value(j->second.get_value<std::string>());
        kvps.push_back(std::make_pair(field_name, field_value));
    }
    return schema_workflow_.execute(st, kvps);
}

void json_hydrator::
read_element(const boost::property_tree::ptree& pt, model& m) const {
    qname qn;
    qn.model_name(model_name(m));
    read_module_path(pt, m, qn);

    const auto simple_name_value(pt.get<std::string>(simple_name_key));
    qn.simple_name(simple_name_value);

    const auto documentation(pt.get_optional<std::string>(documentation_key));

    const auto lambda([&](type& t) {
            BOOST_LOG_SEV(lg, debug) << "Processing type: "
                                     << sml::string_converter::convert(qn);
            t.name(qn);
            t.origin_type(m.origin_type());
            t.generation_type(m.generation_type());

            if (documentation)
                t.documentation(*documentation);

            const auto scope(dynamic::schema::scope_types::entity);
            t.extensions(create_dynamic_extensions(pt, scope));
        });

    const auto meta_type_value(pt.get<std::string>(meta_type_key));
    if (meta_type_value == meta_type_object_value) {
        object o;
        lambda(o);

        const auto ot(pt.get_optional<std::string>(object_type_key));
        if (ot) {
            // FIXME: we should read the number of type arguments from file
            if (*ot == object_type_smart_pointer_value) {
                o.object_type(object_types::smart_pointer);
                o.number_of_type_arguments(1);
            } else if (*ot == object_type_ordered_container_value) {
                o.object_type(object_types::ordered_container);
                o.number_of_type_arguments(2);
            } else if (*ot == object_type_hash_container_value) {
                o.object_type(object_types::hash_container);
                o.number_of_type_arguments(2);
            } else if (*ot == object_type_sequence_container_value) {
                o.object_type(object_types::sequence_container);
                o.number_of_type_arguments(1);
            }
        } else
            o.object_type(object_types::user_defined_value_object);

        m.objects().insert(std::make_pair(qn, o));
    } else if (meta_type_value == meta_type_primitive_value) {
        primitive p;
        lambda(p);
        m.primitives().insert(std::make_pair(qn, p));
    }
    else {
        BOOST_LOG_SEV(lg, error) << invalid_meta_type << meta_type_value;
        BOOST_THROW_EXCEPTION(
            hydration_error(invalid_meta_type + meta_type_value));
    }
}

model json_hydrator::read_stream(std::istream& s, const bool is_target) const {
    model r;
    r.generation_type(generation_type(is_target));

    using namespace boost::property_tree;
    ptree pt;
    read_json(s, pt);

    r.name().model_name(pt.get<std::string>(model_name_key));
    BOOST_LOG_SEV(lg, debug) << "Processing model: "
                             << sml::string_converter::convert(r.name());

    read_module_path(pt, r, r.name());
    const auto scope(dynamic::schema::scope_types::root_module);
    r.extensions(create_dynamic_extensions(pt, scope));

    const auto documentation(pt.get_optional<std::string>(documentation_key));
    if (documentation)
        r.documentation(*documentation);

    const auto is_expandable_value(pt.get<std::string>(is_expandable_key));
    if (is_expandable_value != bool_true && is_expandable_value != bool_false) {
        BOOST_LOG_SEV(lg, error) << invalid_is_expandable
                                 << is_expandable_value;

        BOOST_THROW_EXCEPTION(hydration_error(invalid_is_expandable +
                is_expandable_value));
    }
    r.is_expandable(is_expandable_value == bool_true);

    const auto origin_value(pt.get<std::string>(origin_key));
    if (origin_value == origin_system_value)
        r.origin_type(origin_types::system);
    else if (origin_value == origin_user_value)
        r.origin_type(origin_types::system);
    else {
        BOOST_LOG_SEV(lg, error) << invalid_origin << origin_value;
        BOOST_THROW_EXCEPTION(hydration_error(invalid_origin + origin_value));
    }

    if (!model_name(r).empty()) {
        module m;
        m.name().simple_name(r.name().model_name());
        m.name().model_name(r.name().model_name());
        m.origin_type(r.origin_type());
        m.type(module_types::model);
        m.generation_type(r.generation_type());
        r.modules().insert(std::make_pair(m.name(), m));
    }

    const auto i(pt.find(elements_key));
    if (i == pt.not_found() || i->second.empty()) {
        BOOST_LOG_SEV(lg, error) << model_has_no_types;
        BOOST_THROW_EXCEPTION(hydration_error(model_has_no_types));
    }

    for (auto j(i->second.begin()); j != i->second.end(); ++j)
        read_element(j->second, r);

    return r;
}

void json_hydrator::post_process(model& m) const {
    update_containing_module(m, m.objects());
    update_containing_module(m, m.primitives());
    update_containing_module(m, m.enumerations());
    update_containing_module(m, m.concepts());
    update_containing_module(m, m.modules());
}

model json_hydrator::hydrate(std::istream& s) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON stream.";
    using namespace boost::property_tree;
    try {
        const bool is_target(false);
        auto m(read_stream(s, is_target));
        post_process(m);
        BOOST_LOG_SEV(lg, debug) << "Parsed JSON stream successfully.";
        return m;
    } catch (const json_parser_error& e) {
        BOOST_LOG_SEV(lg, error) << invalid_json_file << ": " << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_json_file + e.what()));
    } catch (const ptree_bad_data& e) {
        BOOST_LOG_SEV(lg, error) << invalid_option_in_json_file << ": "
                                 << e.what();
        BOOST_THROW_EXCEPTION(
            hydration_error(invalid_option_in_json_file + e.what()));
    } catch (const ptree_bad_path& e) {
        BOOST_LOG_SEV(lg, error) << invalid_path << ": " << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_path + e.what()));
    }
}

model json_hydrator::hydrate(const boost::filesystem::path& p) const {
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON file: " << gs;
    boost::filesystem::ifstream s(p);

    if (s.fail()) {
        BOOST_LOG_SEV(lg, error) << failed_to_open_file << ": " << gs;
        BOOST_THROW_EXCEPTION(hydration_error(failed_to_open_file + gs));
    }

    const auto r(hydrate(s));
    BOOST_LOG_SEV(lg, debug) << "Parsed JSON file successfully.";
    return r;
}

} }
