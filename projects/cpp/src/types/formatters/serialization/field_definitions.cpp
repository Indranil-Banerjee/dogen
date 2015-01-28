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
#include <boost/make_shared.hpp>
#include "dogen/dynamic/types/text.hpp"
#include "dogen/dynamic/types/boolean.hpp"
#include "dogen/cpp/types/formatters/serialization/field_definitions.hpp"

namespace {

const std::string model_name("cpp");
const std::string facet_name("serialization");
const std::string class_header_formatter_name("class_header_formatter");
const std::string class_implementation_formatter_name(
    "class_implementation_formatter");
const std::string enumeration_header_formatter_name(
    "enumeration_header_formatter");
const std::string enumeration_implementation_formatter_name(
    "enumeration_implementation_formatter");

dogen::dynamic::field_definition create_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.serialization.enabled");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    r.default_value(boost::make_shared<dogen::dynamic::boolean>(true));
    return r;
}

dogen::dynamic::field_definition create_directory() {
    dogen::dynamic::field_definition r;
    r.name().simple("directory");
    r.name().qualified("cpp.serialization.directory");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    r.default_value(boost::make_shared<dogen::dynamic::text>("serialization"));
    return r;
}

dogen::dynamic::field_definition create_postfix() {
    dogen::dynamic::field_definition r;
    r.name().simple("postfix");
    r.name().qualified("cpp.serialization.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    r.default_value(boost::make_shared<dogen::dynamic::text>("ser"));
    return r;
}

dogen::dynamic::field_definition create_class_header_formatter_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.serialization.class_header_formatter.enabled");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_header_formatter_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    r.default_value(boost::make_shared<dogen::dynamic::boolean>(true));
    return r;
}

dogen::dynamic::field_definition create_class_header_formatter_postfix() {
    dogen::dynamic::field_definition r;
    r.name().simple("postfix");
    r.name().qualified("cpp.serialization.class_header_formatter.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_header_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_class_header_formatter_file_name() {
    dogen::dynamic::field_definition r;
    r.name().simple("file_name");
    r.name().qualified("cpp.serialization.class_header_formatter.file_name");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_header_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::entity);
    return r;
}

dogen::dynamic::field_definition create_class_header_formatter_is_system() {
    dogen::dynamic::field_definition r;
    r.name().simple("is_system");
    r.name().qualified("cpp.serialization.class_header_formatter.is_system");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_header_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::entity);
    return r;
}

dogen::dynamic::field_definition
create_class_implementation_formatter_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.serialization.class_implementation_formatter.enabled");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_implementation_formatter_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    r.default_value(boost::make_shared<dogen::dynamic::boolean>(true));
    return r;
}

dogen::dynamic::field_definition
create_class_implementation_formatter_postfix() {
    dogen::dynamic::field_definition r;
    r.name().simple("postfix");
    r.name().qualified("cpp.serialization.class_implementation_formatter.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(class_implementation_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition
create_enumeration_header_formatter_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.serialization.enumeration_header_formatter.enabled");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(enumeration_header_formatter_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    r.default_value(boost::make_shared<dogen::dynamic::boolean>(true));
    return r;
}

dogen::dynamic::field_definition
create_enumeration_header_formatter_postfix() {
    dogen::dynamic::field_definition r;
    r.name().simple("postfix");
    r.name().qualified("cpp.serialization.enumeration_header_formatter.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(enumeration_header_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition
create_enumeration_implementation_formatter_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.serialization.enumeration_implementation_formatter.enabled");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(
        enumeration_implementation_formatter_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    r.default_value(boost::make_shared<dogen::dynamic::boolean>(true));
    return r;
}

dogen::dynamic::field_definition
create_enumeration_implementation_formatter_postfix() {
    dogen::dynamic::field_definition r;
    r.name().simple("postfix");
    r.name().qualified("cpp.serialization.enumeration_implementation_formatter.postfix");
    r.ownership_hierarchy().model(model_name);
    r.ownership_hierarchy().facet(facet_name);
    r.ownership_hierarchy().formatter(
        enumeration_implementation_formatter_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

std::forward_list<dogen::dynamic::field_definition>
create_all_field_definitions() {
    using dogen::dynamic::field_definition;
    std::forward_list<field_definition> r;

    using fd = dogen::cpp::formatters::serialization::field_definitions;
    r.push_front(fd::enabled());
    r.push_front(fd::directory());
    r.push_front(fd::postfix());

    using chf = fd::class_header_formatter;
    r.push_front(chf::enabled());
    r.push_front(chf::postfix());
    r.push_front(chf::file_name());
    r.push_front(chf::is_system());

    using cif = fd::class_implementation_formatter;
    r.push_front(cif::postfix());
    r.push_front(cif::enabled());

    using ehf = fd::enumeration_header_formatter;
    r.push_front(ehf::postfix());
    r.push_front(ehf::enabled());

    using eif = fd::enumeration_implementation_formatter;
    r.push_front(eif::postfix());
    r.push_front(eif::enabled());

    return r;
}

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace serialization {

const std::forward_list<dynamic::field_definition>&
field_definitions::all_field_definitions() {
    static auto r(create_all_field_definitions());
    return r;
}

const dynamic::field_definition& field_definitions::enabled() {
    static auto r(create_enabled());
    return r;
}

const dynamic::field_definition& field_definitions::directory() {
    static auto r(create_directory());
    return r;
}

const dynamic::field_definition& field_definitions::postfix() {
    static auto r(create_postfix());
    return r;
}

const dynamic::field_definition&
field_definitions::class_header_formatter::enabled() {
    static auto r(create_class_header_formatter_enabled());
    return r;
}

const dynamic::field_definition&
field_definitions::class_header_formatter::postfix() {
    static auto r(create_class_header_formatter_postfix());
    return r;
}

const dynamic::field_definition&
field_definitions::class_header_formatter::file_name() {
    static auto r(create_class_header_formatter_file_name());
    return r;
}

const dynamic::field_definition&
field_definitions::class_header_formatter::is_system() {
    static auto r(create_class_header_formatter_is_system());
    return r;
}

const dynamic::field_definition&
field_definitions::class_implementation_formatter::enabled() {
    static auto r(create_class_implementation_formatter_enabled());
    return r;
}

const dynamic::field_definition&
field_definitions::class_implementation_formatter::postfix() {
    static auto r(create_class_implementation_formatter_postfix());
    return r;
}

const dynamic::field_definition&
field_definitions::enumeration_header_formatter::enabled() {
    static auto r(create_enumeration_header_formatter_enabled());
    return r;
}

const dynamic::field_definition&
field_definitions::enumeration_header_formatter::postfix() {
    static auto r(create_enumeration_header_formatter_postfix());
    return r;
}

const dynamic::field_definition&
field_definitions::enumeration_implementation_formatter::enabled() {
    static auto r(create_enumeration_implementation_formatter_enabled());
    return r;
}

const dynamic::field_definition&
field_definitions::enumeration_implementation_formatter::postfix() {
    static auto r(create_enumeration_implementation_formatter_postfix());
    return r;
}

} } } }
