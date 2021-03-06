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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml_to_cpp/io/relationships_io.hpp"
#include "dogen/sml_to_cpp/types/extraction_error.hpp"
#include "dogen/sml_to_cpp/types/extractor.hpp"

using dogen::sml::test::mock_model_factory;
using dogen::sml::string_converter;
typedef mock_model_factory::object_types object_types;
typedef mock_model_factory::property_types property_types;

namespace {

const std::string empty;
const std::string test_module("sml_to_cpp");
const std::string test_suite("extractor_spec");

const mock_model_factory::flags flags(false/*tagged*/, false/*resolved*/,
    false/*merged*/, false/*concepts_indexed*/, false/*properties_indexed*/,
    true/*associations_indexed*/);
const mock_model_factory factory(flags);

const std::string object_not_found("Could not find QName in object container");

}

using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(extractor)

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_no_properties_and_no_inheritance_has_no_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_no_properties_and_no_inheritance_has_no_names_in_relationships");

    const auto m(factory.make_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.objects().size() == 1);

    dogen::sml_to_cpp::extractor x;
    const auto r(x.extract_dependency_graph(m.objects().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_CHECK(r.names().empty());
    BOOST_CHECK(r.forward_decls().empty());
    BOOST_CHECK(r.keys().empty());
    BOOST_CHECK(r.leaves().empty());
    BOOST_CHECK(!r.has_std_string());
    BOOST_CHECK(!r.has_variant());
    BOOST_CHECK(!r.is_parent());
    BOOST_CHECK(!r.is_child());
    BOOST_CHECK(!r.requires_stream_manipulators());
    BOOST_CHECK(!r.has_std_pair());
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_parent_has_one_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_parent_has_one_name_in_relationships");

    const auto m(factory.object_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(!m.objects().empty());

    dogen::sml_to_cpp::extractor x;

    std::array<bool, 2> found({{ false, false }});
    for (const auto& pair : m.objects()) {
        if (factory.is_type_name_n(0, pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found child object: "
                                     << string_converter::convert(pair.first);

            found[0] = true;
            const auto r(x.extract_dependency_graph(pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_REQUIRE(factory.is_type_name_n(1, *r.names().begin()));
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        } else if (factory.is_type_name_n(1, pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found parent object: "
                                     << string_converter::convert(pair.first);

            found[1] = true;
            const auto r(x.extract_dependency_graph(pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().empty());
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().size() == 1);
            BOOST_REQUIRE(factory.is_type_name_n(0, *r.leaves().begin()));
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        }
    }
    BOOST_CHECK(found[0] && found[1]);
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_unsigned_int_property_has_expected_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_unsigned_int_property_has_expected_name_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::unsigned_int);
    const auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);
    BOOST_REQUIRE(m.objects().begin()->second.local_properties().size() == 1);

    dogen::sml_to_cpp::extractor x;
    const auto r(x.extract_dependency_graph(m.objects().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_REQUIRE(r.names().size() == 1);
    BOOST_CHECK(r.names().begin()->simple_name() == "unsigned int");
    BOOST_CHECK(r.forward_decls().empty());
    BOOST_CHECK(r.keys().empty());
    BOOST_CHECK(r.leaves().empty());
    BOOST_CHECK(!r.has_std_string());
    BOOST_CHECK(!r.has_variant());
    BOOST_CHECK(!r.is_parent());
    BOOST_CHECK(!r.is_child());
    BOOST_CHECK(!r.requires_stream_manipulators());
    BOOST_CHECK(!r.has_std_pair());
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_boolean_property_has_expected_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_boolean_property_has_expected_name_in_relationships");


    const auto ot(object_types::value_object);
    const auto pt(property_types::boolean);
    const auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);
    BOOST_REQUIRE(m.objects().begin()->second.local_properties().size() == 1);

    dogen::sml_to_cpp::extractor x;
    const auto r(x.extract_dependency_graph(m.objects().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

    BOOST_REQUIRE(r.names().size() == 1);
    BOOST_CHECK(r.names().begin()->simple_name() == "bool");
    BOOST_CHECK(r.forward_decls().empty());
    BOOST_CHECK(r.keys().empty());
    BOOST_CHECK(r.leaves().empty());
    BOOST_CHECK(!r.has_std_string());
    BOOST_CHECK(!r.has_variant());
    BOOST_CHECK(!r.is_parent());
    BOOST_CHECK(!r.is_child());
    BOOST_CHECK(r.requires_stream_manipulators());
    BOOST_CHECK(!r.has_std_pair());
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_other_object_property_has_expected_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_other_object_property_has_expected_names_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::value_object);
    const auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);

    dogen::sml_to_cpp::extractor x;
    bool found(false);
    for (const auto& pair : m.objects()) {
        if (factory.is_type_name_n(0, pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found child object: "
                                     << string_converter::convert(pair.first);
            BOOST_REQUIRE(pair.second.local_properties().size() == 1);
            const auto r(x.extract_dependency_graph(pair.second));

            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_CHECK(factory.is_type_name_n(1, *r.names().begin()));
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());

            found = true;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_pair_property_has_expected_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_pair_property_has_expected_names_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::std_pair);
    const auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);

    bool found(false);
    dogen::sml_to_cpp::extractor x;
    for (const auto& pair : m.objects()) {
        if (factory.is_type_name_n(0, pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found child object: "
                                     << string_converter::convert(pair.first);
            BOOST_REQUIRE(pair.second.local_properties().size() == 1);
            const auto r(x.extract_dependency_graph(pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;
            BOOST_REQUIRE(r.names().size() == 2);
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(r.requires_stream_manipulators());
            BOOST_CHECK(r.has_std_pair());
            found = true;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_variant_property_has_expected_names_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_variant_property_has_expected_names_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::boost_variant);
    const auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);
    BOOST_REQUIRE(m.primitives().size() == 2);

    bool found(false);
    dogen::sml_to_cpp::extractor x;
    for (const auto& pair : m.objects()) {
        if (factory.is_type_name_n(0, pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found object: "
                                     << string_converter::convert(pair.first);
            BOOST_REQUIRE(pair.second.local_properties().size() == 1);
            const auto r(x.extract_dependency_graph(pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 3);
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
            found = true;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_std_string_property_has_expected_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_std_string_property_has_expected_name_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::std_string);
    const auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);

    bool found(false);
    dogen::sml_to_cpp::extractor x;
    for (const auto& pair : m.objects()) {
        if (factory.is_type_name_n(0, pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found object: "
                                     << string_converter::convert(pair.first);
            BOOST_REQUIRE(pair.second.local_properties().size() == 1);
            const auto r(x.extract_dependency_graph(pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_CHECK(r.names().begin()->simple_name() == "string");
            BOOST_CHECK(r.forward_decls().empty());
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
            found = true;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(dependency_graph_of_object_with_boost_shared_ptr_property_has_expected_name_in_relationships) {
    SETUP_TEST_LOG_SOURCE("dependency_graph_of_object_with_boost_shared_ptr_property_has_expected_name_in_relationships");

    const auto ot(object_types::value_object);
    const auto pt(property_types::boost_shared_ptr);
    const auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 3);

    bool found(false);
    dogen::sml_to_cpp::extractor x;
    for (const auto& pair : m.objects()) {
        if (factory.is_type_name_n(0, pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found object: "
                                     << string_converter::convert(pair.first);
            BOOST_REQUIRE(pair.second.local_properties().size() == 1);

            found = true;
            const auto r(x.extract_dependency_graph(pair.second));
            BOOST_LOG_SEV(lg, debug) << "relationships: " << r;

            BOOST_REQUIRE(r.names().size() == 1);
            BOOST_CHECK(r.forward_decls().size() == 1);
            BOOST_CHECK(r.keys().empty());
            BOOST_CHECK(r.leaves().empty());
            BOOST_CHECK(!r.has_std_string());
            BOOST_CHECK(!r.has_variant());
            BOOST_CHECK(!r.is_parent());
            BOOST_CHECK(!r.is_child());
            BOOST_CHECK(!r.requires_stream_manipulators());
            BOOST_CHECK(!r.has_std_pair());
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_SUITE_END()
