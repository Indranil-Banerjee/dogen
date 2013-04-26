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
#include "dogen/trivial_inheritance/test_data/base_td.hpp"
#include "dogen/trivial_inheritance/test_data/descendant1_td.hpp"



namespace dogen {
namespace trivial_inheritance {

descendant1_generator::descendant1_generator() : position_(0) { }

void descendant1_generator::
populate(const unsigned int /*position*/, result_type& /*v*/) {
}

descendant1_generator::result_type
descendant1_generator::create(const unsigned int position) {
    descendant1 r;
    dogen::trivial_inheritance::base_generator::populate(position, r);
    return r;
}
descendant1_generator::result_type*
descendant1_generator::create_ptr(const unsigned int position) {
    descendant1* p = new descendant1();
    descendant1_generator::populate(position, *p);
    return p;
}

descendant1_generator::result_type
descendant1_generator::operator()() {
    return create(position_++);
}

} }