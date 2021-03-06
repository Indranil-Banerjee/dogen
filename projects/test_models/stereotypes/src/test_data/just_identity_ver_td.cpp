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
#include "dogen/test_models/stereotypes/test_data/just_identity_ver_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return position;
}

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

}

namespace dogen {
namespace test_models {
namespace stereotypes {

just_identity_ver_generator::just_identity_ver_generator() : position_(0) { }

void just_identity_ver_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_int(position + 0));
    v.version(create_unsigned_int(position + 1));
}

just_identity_ver_generator::result_type
just_identity_ver_generator::create(const unsigned int position) {
    just_identity_ver r;
    just_identity_ver_generator::populate(position, r);
    return r;
}
just_identity_ver_generator::result_type*
just_identity_ver_generator::create_ptr(const unsigned int position) {
    just_identity_ver* p = new just_identity_ver();
    just_identity_ver_generator::populate(position, *p);
    return p;
}

just_identity_ver_generator::result_type
just_identity_ver_generator::operator()() {
    return create(position_++);
}

} } }
