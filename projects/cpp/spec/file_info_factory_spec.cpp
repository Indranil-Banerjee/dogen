/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/cpp/io/all_io.hpp"
#include "dogen/cpp/types/building_error.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/config/test/mock_settings_factory.hpp"
#include "dogen/cpp/types/transformer.hpp"
#include "dogen/cpp/types/file_info_factory.hpp"

using dogen::config::cpp_facet_types;
using dogen::sml::test::mock_model_factory;
using dogen::config::test::mock_settings_factory;

namespace {

const std::string test_module("cpp");
const std::string test_suite("file_info_factory_spec");
const std::string src_dir("__source_directory__");
const std::string inc_dir("__include_directory__");

}

using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(file_info_factory)

BOOST_AUTO_TEST_CASE(creating_file_info_for_enumeration_with_all_facets_enabled_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_enumeration_with_all_facets_enabled_produces_expected_results");

    const auto mt(dogen::sml::meta_types::enumeration);
    const auto m(mock_model_factory::build_single_type_model(0, mt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::transformer t(m);

    dogen::cpp::file_info_factory f(s.enabled_facets(), t, l, i);
    const auto en(m.enumerations().begin()->second);
    const auto infos(f.create(en));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.facet_type());
        BOOST_CHECK(fi.meta_type() == en.name().meta_type());
        BOOST_CHECK(fi.enumeration_info());
        BOOST_CHECK(!fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(!fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.file_type() == dogen::cpp::file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.file_type() == dogen::cpp::file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }
    BOOST_CHECK(found_facets == s.enabled_facets());
}

BOOST_AUTO_TEST_CASE(creating_file_info_for_enumeration_with_a_few_facets_enabled_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_enumeration_with_a_few_facets_enabled_produces_expected_results");

    const auto mt(dogen::sml::meta_types::enumeration);
    const auto m(mock_model_factory::build_single_type_model(0, mt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    std::set<cpp_facet_types> ft;
    ft.insert(cpp_facet_types::types);
    ft.insert(cpp_facet_types::io);
    s.enabled_facets(ft);

    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::transformer t(m);

    dogen::cpp::file_info_factory f(s.enabled_facets(), t, l, i);
    const auto en(m.enumerations().begin()->second);
    const auto infos(f.create(en));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.facet_type());
        BOOST_CHECK(fi.meta_type() == en.name().meta_type());
        BOOST_CHECK(fi.enumeration_info());
        BOOST_CHECK(!fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(!fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.file_type() == dogen::cpp::file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.file_type() == dogen::cpp::file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }
    BOOST_CHECK(found_facets == s.enabled_facets());
}

BOOST_AUTO_TEST_CASE(creating_file_info_for_exception_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_exception_produces_expected_results");

    const auto mt(dogen::sml::meta_types::exception);
    const auto m(mock_model_factory::build_single_type_model(0, mt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.exceptions().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::transformer t(m);

    dogen::cpp::file_info_factory f(s.enabled_facets(), t, l, i);
    const auto ex(m.exceptions().begin()->second);
    const auto infos(f.create(ex));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.facet_type());
        BOOST_CHECK(fi.meta_type() == ex.name().meta_type());
        BOOST_CHECK(!fi.enumeration_info());
        BOOST_CHECK(!fi.class_info());
        BOOST_CHECK(fi.exception_info());
        BOOST_CHECK(!fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.file_type() == dogen::cpp::file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.file_type() == dogen::cpp::file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }
    BOOST_CHECK(found_facets.size() == 1);
    BOOST_CHECK(*found_facets.begin() == dogen::config::cpp_facet_types::types);
}

BOOST_AUTO_TEST_CASE(creating_file_info_for_package_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_package_produces_expected_results");

    const auto mt(dogen::sml::meta_types::pod);
    const auto m(
        mock_model_factory::build_single_type_model_in_package(0, mt, 1));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.packages().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::transformer t(m);

    dogen::cpp::file_info_factory f(s.enabled_facets(), t, l, i);
    const auto p(m.packages().begin()->second);
    const auto infos(f.create(p));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.facet_type());
        BOOST_CHECK(fi.meta_type() == p.name().meta_type());
        BOOST_CHECK(!fi.enumeration_info());
        BOOST_CHECK(!fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.file_type() == dogen::cpp::file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.file_type() == dogen::cpp::file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }
    BOOST_CHECK(found_facets.size() == 1);
    BOOST_CHECK(*found_facets.begin() == dogen::config::cpp_facet_types::types);
}

BOOST_AUTO_TEST_CASE(creating_file_info_for_model_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_model_produces_expected_results");

    const auto mt(dogen::sml::meta_types::pod);
    const auto m(
        mock_model_factory::build_single_type_model_in_package(0, mt, 1));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::transformer t(m);

    dogen::cpp::file_info_factory f(s.enabled_facets(), t, l, i);
    const auto infos(f.create(m));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.facet_type());
        BOOST_CHECK(fi.meta_type() == dogen::sml::meta_types::package);
        BOOST_CHECK(!fi.enumeration_info());
        BOOST_CHECK(!fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.file_type() == dogen::cpp::file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.file_type() == dogen::cpp::file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }
    BOOST_CHECK(found_facets.size() == 1);
    BOOST_CHECK(*found_facets.begin() == dogen::config::cpp_facet_types::types);
}

BOOST_AUTO_TEST_CASE(creating_file_info_for_pod_with_all_facets_enabled_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_pod_with_all_facets_enabled_produces_expected_results");

    const auto m(mock_model_factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::transformer t(m);

    dogen::cpp::file_info_factory f(s.enabled_facets(), t, l, i);
    const auto p(m.pods().begin()->second);
    const auto infos(f.create(p));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.facet_type());
        BOOST_CHECK(fi.meta_type() == p.name().meta_type());
        BOOST_CHECK(!fi.enumeration_info());
        BOOST_CHECK(fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(!fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.file_type() == dogen::cpp::file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.file_type() == dogen::cpp::file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }
    BOOST_CHECK(found_facets == s.enabled_facets());
}

BOOST_AUTO_TEST_CASE(creating_file_info_for_pod_with_some_facets_enabled_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_pod_with_some_facets_enabled_produces_expected_results");

    const auto m(mock_model_factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);

    auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    std::set<cpp_facet_types> ft;
    ft.insert(cpp_facet_types::types);
    ft.insert(cpp_facet_types::io);
    s.enabled_facets(ft);

    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::transformer t(m);

    dogen::cpp::file_info_factory f(s.enabled_facets(), t, l, i);
    const auto p(m.pods().begin()->second);
    const auto infos(f.create(p));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.facet_type());
        BOOST_CHECK(fi.meta_type() == p.name().meta_type());
        BOOST_CHECK(!fi.enumeration_info());
        BOOST_CHECK(fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(!fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.file_type() == dogen::cpp::file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.file_type() == dogen::cpp::file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }
    BOOST_CHECK(found_facets.size() == 2);
    BOOST_CHECK(*found_facets.begin() == dogen::config::cpp_facet_types::types);
}

BOOST_AUTO_TEST_CASE(creating_includer_file_info_for_single_pod_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_includer_file_info_for_single_pod_produces_expected_results");

    const auto m(mock_model_factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::transformer t(m);

    dogen::cpp::file_info_factory f(s.enabled_facets(), t, l, i);
    const auto p(m.pods().begin()->second);
    const auto pod_infos(f.create(p));
    BOOST_LOG_SEV(lg, debug) << "pod file infos: " << pod_infos;

    const auto ft(dogen::config::cpp_facet_types::types);
    const auto includer_infos(f.create_includer(m.external_package_path(), ft));
    BOOST_LOG_SEV(lg, debug) << "includer file infos: " << includer_infos;

    BOOST_REQUIRE(includer_infos.size() == 1);
    const auto fi(includer_infos.front());

    BOOST_CHECK(fi.facet_type() == ft);
    BOOST_CHECK(fi.aspect_type() == dogen::cpp::aspect_types::includers);
    BOOST_CHECK(!fi.enumeration_info());
    BOOST_CHECK(!fi.class_info());
    BOOST_CHECK(!fi.exception_info());
    BOOST_CHECK(!fi.namespace_info());
    BOOST_CHECK(!fi.registrar_info());
    BOOST_CHECK(!fi.visitor_info());
    BOOST_CHECK(!fi.file_path().empty());
    BOOST_CHECK(fi.file_type() == dogen::cpp::file_types::header);

    bool found(false);
    for (const auto& ui : fi.user_includes()) {
        if (boost::contains(ui, p.name().type_name()))
            found = true;
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(creating_file_info_for_registrar_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_registrar_produces_expected_results");

    const auto m(mock_model_factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::transformer t(m);

    dogen::cpp::file_info_factory f(s.enabled_facets(), t, l, i);
    const auto infos(f.create_registrar(m));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    BOOST_REQUIRE(infos.size() == 1);
    const auto fi(infos.front());

    const auto ft(dogen::config::cpp_facet_types::serialization);
    BOOST_CHECK(fi.facet_type() == ft);
    BOOST_CHECK(fi.aspect_type() == dogen::cpp::aspect_types::registrar);
    BOOST_CHECK(!fi.enumeration_info());
    BOOST_CHECK(!fi.class_info());
    BOOST_CHECK(!fi.exception_info());
    BOOST_CHECK(!fi.namespace_info());
    BOOST_CHECK(fi.registrar_info());
    BOOST_CHECK(!fi.visitor_info());
    BOOST_CHECK(!fi.file_path().empty());
    BOOST_CHECK(fi.file_type() == dogen::cpp::file_types::header);
}

BOOST_AUTO_TEST_SUITE_END()