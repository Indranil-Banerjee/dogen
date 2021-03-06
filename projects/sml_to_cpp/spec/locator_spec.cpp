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
#include <iterator>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/config/io/cpp_options_io.hpp"
#include "dogen/cpp/types/formattables/content_descriptor.hpp"
#include "dogen/sml_to_cpp/types/locator.hpp"
#include "dogen/config/test/mock_options_factory.hpp"

using dogen::config::cpp_facet_types;

namespace {

const std::string empty;
const std::string test_module("sml_to_cpp");
const std::string test_suite("locator_spec");

const std::string test_model_name("test");
const boost::filesystem::path src_dir("source directory");
const boost::filesystem::path include_dir("include directory");
const boost::filesystem::path project_dir("project directory");
const std::string type_name("a_type");
const std::list<std::string> module_path_1({ "a", "b" });
const std::list<std::string> external_module_path_1({ "c", "d" });
const std::string unique_name("unique_name");
const std::string header_extension(".hxx");
const std::string source_extension(".cxx");

const std::vector<cpp_facet_types> facets =
{
    cpp_facet_types::types,
    cpp_facet_types::serialization,
    cpp_facet_types::hash,
    cpp_facet_types::io,
    cpp_facet_types::test_data
};

dogen::config::cpp_options non_split_project_options() {
    return dogen::config::test::mock_options_factory::
        make_cpp_options(project_dir);
}

dogen::config::cpp_options split_project_options() {
    return dogen::config::test::mock_options_factory::
        make_cpp_options(src_dir, include_dir);
}

dogen::cpp::formattables::content_descriptor
mock_descriptor(dogen::config::cpp_facet_types ft,
    dogen::cpp::formattables::file_types flt,
    std::string simple_name, std::list<std::string> module_path,
    std::list<std::string> external_module_path) {

    dogen::cpp::formattables::content_descriptor r;
    r.facet_type(ft);
    r.file_type(flt);
    r.aspect_type(dogen::cpp::formattables::aspect_types::main);
    r.name().model_name(test_model_name);
    r.name().module_path(module_path);
    r.name().simple_name(simple_name);
    r.name().external_module_path(external_module_path);

    return r;
}

dogen::cpp::formattables::content_descriptor
mock_descriptor(dogen::config::cpp_facet_types ft,
    dogen::cpp::formattables::file_types flt) {
    return mock_descriptor(
        ft, flt, type_name, module_path_1, external_module_path_1);
}

std::list<std::string>
generate_all_filenames(dogen::config::cpp_options s, bool with_path) {
    using dogen::sml_to_cpp::locator;
    locator lm(test_model_name, s);

    std::list<std::string> r;
    auto lambda([&](dogen::config::cpp_facet_types ft,
            dogen::cpp::formattables::file_types flt) {
            const auto cd(mock_descriptor(ft, flt));
            const auto p(lm.relative_logical_path(cd));
            r.push_back(with_path ?
                p.generic_string() :
                p.filename().generic_string());
        });

    auto pi([&](dogen::config::cpp_facet_types ft) {
            lambda(ft, dogen::cpp::formattables::file_types::header);
            lambda(ft, dogen::cpp::formattables::file_types::implementation);
        });

    boost::for_each(facets, pi);
    return r;
}

}

BOOST_AUTO_TEST_SUITE(locator)

BOOST_AUTO_TEST_CASE(split_project_configuration_results_in_expected_locations) {
    SETUP_TEST_LOG_SOURCE("split_project_configuration_results_in_expected_locations");
    using dogen::sml_to_cpp::locator;
    const auto s(split_project_options());
    BOOST_CHECK(s.split_project());

    locator lm(test_model_name, s);
    auto cd(mock_descriptor(dogen::config::cpp_facet_types::types,
            dogen::cpp::formattables::file_types::header));

    boost::filesystem::path e("c/d/test/types/a/b/a_type.hpp");
    boost::filesystem::path a(lm.relative_logical_path(cd));

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "test/types/a/b/a_type.hpp";
    a = lm.relative_physical_path(cd);
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "include directory/test/types/a/b/a_type.hpp";
    a = lm.absolute_path(cd);
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "source directory/test/a_type";
    a = lm.absolute_path_to_src(type_name);
    BOOST_CHECK(asserter::assert_equals(e, a));

    const auto md(lm.managed_directories());
    BOOST_CHECK(std::distance(md.begin(), md.end()) == 2);

    e = "include directory/test";
    auto i(md.begin());
    a = *i;
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "source directory/test";
    ++i;
    a = *i;
    BOOST_CHECK(asserter::assert_equals(e, a));

    cd = mock_descriptor(dogen::config::cpp_facet_types::io,
        dogen::cpp::formattables::file_types::implementation);
    e = "c/d/test/io/a/b/a_type_io.cpp";
    a = lm.relative_logical_path(cd);
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "test/io/a/b/a_type_io.cpp";
    a = lm.relative_physical_path(cd);
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "source directory/test/io/a/b/a_type_io.cpp";
    a = lm.absolute_path(cd);
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "source directory/test/a_type";
    a = lm.absolute_path_to_src(type_name);
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(non_split_project_configuration_results_in_expected_locations) {
    SETUP_TEST_LOG_SOURCE("non_split_project_configuration_results_in_expected_locations");
    using dogen::sml_to_cpp::locator;
    const auto s(non_split_project_options());
    BOOST_CHECK(!s.split_project());

    locator lm(test_model_name, s);
    auto cd(mock_descriptor(dogen::config::cpp_facet_types::types,
            dogen::cpp::formattables::file_types::header));

    boost::filesystem::path e("c/d/test/types/a/b/a_type.hpp");
    boost::filesystem::path a(lm.relative_logical_path(cd));

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "c/d/test/types/a/b/a_type.hpp";
    a = lm.relative_physical_path(cd);
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "project directory/test/include/c/d/test/types/a/b/a_type.hpp";
    a = lm.absolute_path(cd);
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "project directory/test/src/a_type";
    a = lm.absolute_path_to_src(type_name);
    BOOST_CHECK(asserter::assert_equals(e, a));

    const auto md(lm.managed_directories());
    BOOST_CHECK(std::distance(md.begin(), md.end()) == 1);

    e = "project directory/test";
    a = md.front();
    BOOST_CHECK(asserter::assert_equals(e, a));

    cd = mock_descriptor(dogen::config::cpp_facet_types::io,
        dogen::cpp::formattables::file_types::implementation);
    e = "io/a/b/a_type_io.cpp";
    a = lm.relative_logical_path(cd);
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "io/a/b/a_type_io.cpp";
    a = lm.relative_physical_path(cd);
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "project directory/test/src/io/a/b/a_type_io.cpp";
    a = lm.absolute_path(cd);
    BOOST_CHECK(asserter::assert_equals(e, a));

    e = "project directory/test/src/a_type";
    a = lm.absolute_path_to_src(type_name);
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(disabling_facet_folders_removes_facet_folders_from_locations) {
    SETUP_TEST_LOG_SOURCE("disabling_facet_folders_removes_facet_folders_from_locations");

    auto s(split_project_options());
    s.disable_facet_folders(true);
    BOOST_LOG_SEV(lg, debug) << "options: " << s;
    BOOST_CHECK(s.split_project());

    using dogen::sml_to_cpp::locator;
    locator lm(test_model_name, s);

    auto lambda([&](dogen::config::cpp_facet_types ft,
            dogen::cpp::formattables::file_types flt) {
            const auto cd(mock_descriptor(ft, flt));
            boost::filesystem::path e("c/d/test/a/b/a_type");
            boost::filesystem::path a(lm.relative_logical_path(cd));

            using dogen::utility::test::asserter;
            BOOST_CHECK(asserter::assert_starts_with(
                    e.generic_string(), a.generic_string()));

            e = "test/a/b/a_type";
            a = lm.relative_physical_path(cd);
            BOOST_CHECK(asserter::assert_starts_with(
                    e.generic_string(), a.generic_string()));

            if (flt == dogen::cpp::formattables::file_types::header)
                e = "include directory/test/a/b/a_type";
            else
                e = "source directory/test/a/b/a_type";
            a = lm.absolute_path(cd);
            BOOST_CHECK(asserter::assert_starts_with(
                    e.generic_string(), a.generic_string()));
        });

    auto pi([&](dogen::config::cpp_facet_types ft) {
            lambda(ft, dogen::cpp::formattables::file_types::header);
            lambda(ft, dogen::cpp::formattables::file_types::implementation);
        });
    boost::for_each(facets, pi);
}

BOOST_AUTO_TEST_CASE(enabling_unique_file_names_results_in_different_names_across_facets) {
    SETUP_TEST_LOG_SOURCE("enabling_unique_file_names_results_in_different_names_across_facets");

    auto s(split_project_options());
    s.disable_unique_file_names(true);
    BOOST_LOG_SEV(lg, debug) << "options: " << s;

    using dogen::sml_to_cpp::locator;
    locator lm(test_model_name, s);

    const bool with_path(false);
    std::list<std::string> files(generate_all_filenames(s, with_path));
    BOOST_LOG_SEV(lg, debug) << "before sorting: " << files;
    BOOST_CHECK(files.size() == facets.size() * 2);

    files.sort();
    files.unique();
    BOOST_LOG_SEV(lg, debug) << "after sorting: " << files;

    BOOST_CHECK(files.size() == 2);
    BOOST_CHECK(files.front() == "a_type.hpp" || files.front() == "a_type.cpp");
    BOOST_CHECK(files.back() == "a_type.hpp" || files.back() == "a_type.cpp");
}

BOOST_AUTO_TEST_CASE(disabling_unique_file_names_results_in_the_same_names_across_facets) {
    SETUP_TEST_LOG_SOURCE("disabling_unique_file_names_results_in_the_same_names_across_facets");

    auto s(split_project_options());
    s.disable_unique_file_names(false);
    BOOST_LOG_SEV(lg, debug) << "options: " << s;

    using dogen::sml_to_cpp::locator;
    locator lm(test_model_name, s);

    const bool with_path(false);
    std::list<std::string> files(generate_all_filenames(s, with_path));
    BOOST_LOG_SEV(lg, debug) << "before sorting: " << files;
    const std::size_t sz(files.size());
    BOOST_CHECK(sz == facets.size() * 2);

    files.sort();
    files.unique();
    BOOST_LOG_SEV(lg, debug) << "after sorting: " << files;
    BOOST_CHECK(sz == files.size());
}

BOOST_AUTO_TEST_CASE(changing_facet_folder_names_results_in_new_folder_names_in_location) {
    SETUP_TEST_LOG_SOURCE("changing_facet_folder_names_names_results_in_new_folder_names_in_location");

    auto s(split_project_options());
    s.disable_unique_file_names(false);
    s.domain_facet_folder(unique_name + "_1");
    s.hash_facet_folder(unique_name + "_2");
    s.io_facet_folder(unique_name + "_3");
    s.serialization_facet_folder(unique_name + "_4");
    s.test_data_facet_folder(unique_name + "_5");
    BOOST_LOG_SEV(lg, debug) << "options: " << s;

    using dogen::sml_to_cpp::locator;
    locator lm(test_model_name, s);

    const bool with_path(true);
    std::list<std::string> files(generate_all_filenames(s, with_path));
    BOOST_LOG_SEV(lg, debug) << "before removing: " << files;
    BOOST_CHECK(files.size() == facets.size() * 2);

    auto lambda([](const std::string& f) {
            return boost::contains(f, unique_name);
        });

    files.remove_if(lambda);
    BOOST_LOG_SEV(lg, debug) << "after removing: " << files;
    BOOST_CHECK(files.empty());
}

BOOST_AUTO_TEST_CASE(changing_file_extensions_results_expected_file_names) {
    SETUP_TEST_LOG_SOURCE("changing_file_extensions_results_expected_file_names");

    auto s(split_project_options());
    s.header_extension(header_extension);
    s.source_extension(source_extension);
    BOOST_LOG_SEV(lg, debug) << "options: " << s;

    using dogen::sml_to_cpp::locator;
    locator lm(test_model_name, s);

    const bool with_path(false);
    std::list<std::string> files(generate_all_filenames(s, with_path));
    BOOST_LOG_SEV(lg, debug) << "before removing: " << files;
    BOOST_CHECK(files.size() == facets.size() * 2);

    auto lambda([](const std::string& f) {
            return boost::contains(f, header_extension) ||
                boost::contains(f, source_extension);
        });

    files.remove_if(lambda);
    BOOST_LOG_SEV(lg, debug) << "after removing: " << files;
    BOOST_CHECK(files.empty());
}

BOOST_AUTO_TEST_SUITE_END()
