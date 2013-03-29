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
#include "dogen/cpp/test_data/view_models/nested_type_view_model_td.hpp"
#include "dogen/cpp/test_data/view_models/property_view_model_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::cpp::view_models::nested_type_view_model
create_dogen_cpp_view_models_nested_type_view_model(const unsigned int position) {
    return dogen::cpp::view_models::nested_type_view_model_generator::create(position);
}

std::pair<std::string, std::string>
create_std_pair_std_string_std_string(unsigned int position) {
    std::pair<std::string, std::string> r(
        create_std_string(position),
        create_std_string(position));
    return r;
}

std::vector<std::pair<std::string, std::string> > create_std_vector_std_pair_std_string_std_string_(unsigned int position) {
    std::vector<std::pair<std::string, std::string> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_pair_std_string_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace view_models {

property_view_model_generator::property_view_model_generator() : position_(0) { }

void property_view_model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.type(create_dogen_cpp_view_models_nested_type_view_model(position + 1));
    v.documentation(create_std_string(position + 2));
    v.implementation_specific_parameters(create_std_vector_std_pair_std_string_std_string_(position + 3));
}

property_view_model_generator::result_type
property_view_model_generator::create(const unsigned int position) {
    property_view_model r;
    property_view_model_generator::populate(position, r);
    return r;
}
property_view_model_generator::result_type*
property_view_model_generator::create_ptr(const unsigned int position) {
    property_view_model* p = new property_view_model();
    property_view_model_generator::populate(position, *p);
    return p;
}

property_view_model_generator::result_type
property_view_model_generator::operator()() {
    return create(position_++);
}

} } }