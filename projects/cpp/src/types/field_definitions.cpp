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
#include "dogen/cpp/types/field_definitions.hpp"

namespace {

const std::string model_name("cpp");

dogen::dynamic::field_definition create_enabled() {
    dogen::dynamic::field_definition r;
    r.name().simple("enabled");
    r.name().qualified("cpp.enabled");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_split_project() {
    dogen::dynamic::field_definition r;
    r.name().simple("split_project");
    r.name().qualified("cpp.split_project");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_source_directory() {
    dogen::dynamic::field_definition r;
    r.name().simple("source_directory");
    r.name().qualified("cpp.source_directory");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_include_directory() {
    dogen::dynamic::field_definition r;
    r.name().simple("include_directory");
    r.name().qualified("cpp.include_directory");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_header_file_extension() {
    dogen::dynamic::field_definition r;
    r.name().simple("header_file_extension");
    r.name().qualified("cpp.header_file_extension");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_implementation_file_extension() {
    dogen::dynamic::field_definition r;
    r.name().simple("implementation_file_extension");
    r.name().qualified("cpp.implementation_file_extension");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::text);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_enable_facet_folders() {
    dogen::dynamic::field_definition r;
    r.name().simple("enable_facet_folders");
    r.name().qualified("cpp.enable_facet_folders");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

dogen::dynamic::field_definition create_enable_unique_file_names() {
    dogen::dynamic::field_definition r;
    r.name().simple("enable_unique_file_names");
    r.name().qualified("cpp.enable_unique_file_names");
    r.ownership_hierarchy().model(model_name);
    r.type(dogen::dynamic::value_types::boolean);
    r.scope(dogen::dynamic::scope_types::root_module);
    return r;
}

}

namespace dogen {
namespace cpp {

const dynamic::field_definition& field_definitions::enabled() {
    static auto r(create_enabled());
    return r;
}

const dynamic::field_definition& field_definitions::split_project() {
    static auto r(create_split_project());
    return r;
}

const dynamic::field_definition& field_definitions::source_directory() {
    static auto r(create_source_directory());
    return r;
}

const dynamic::field_definition& field_definitions::include_directory() {
    static auto r(create_include_directory());
    return r;
}

const dynamic::field_definition& field_definitions::header_file_extension() {
    static auto r(create_header_file_extension());
    return r;
}

const dynamic::field_definition&
field_definitions::implementation_file_extension() {
    static auto r(create_implementation_file_extension());
    return r;
}

const dynamic::field_definition& field_definitions::enable_facet_folders() {
    static auto r(create_enable_facet_folders());
    return r;
}

const dynamic::field_definition& field_definitions::enable_unique_file_names() {
    static auto r(create_enable_unique_file_names());
    return r;
}

} }