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
#include "dogen/dia/test_data/color_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace dia {

color_generator::color_generator() : position_(0) { }

void color_generator::
populate(const unsigned int position, result_type& v) {
    v.value(create_std_string(position + 0));
}

color_generator::result_type
color_generator::create(const unsigned int position) {
    color r;
    color_generator::populate(position, r);
    return r;
}
color_generator::result_type*
color_generator::create_ptr(const unsigned int position) {
    color* p = new color();
    color_generator::populate(position, *p);
    return p;
}

color_generator::result_type
color_generator::operator()() {
    return create(position_++);
}

} }
