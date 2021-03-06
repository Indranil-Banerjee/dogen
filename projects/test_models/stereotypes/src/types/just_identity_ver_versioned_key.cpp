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
#include "dogen/test_models/stereotypes/types/just_identity_ver_versioned_key.hpp"

namespace dogen {
namespace test_models {
namespace stereotypes {

just_identity_ver_versioned_key::just_identity_ver_versioned_key()
    : prop_0_(static_cast<int>(0)),
      version_(static_cast<unsigned int>(0)) { }

just_identity_ver_versioned_key::just_identity_ver_versioned_key(
    const int prop_0,
    const unsigned int version)
    : prop_0_(prop_0),
      version_(version) { }

void just_identity_ver_versioned_key::swap(just_identity_ver_versioned_key& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(version_, other.version_);
}

bool just_identity_ver_versioned_key::operator==(const just_identity_ver_versioned_key& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        version_ == rhs.version_;
}

just_identity_ver_versioned_key& just_identity_ver_versioned_key::operator=(just_identity_ver_versioned_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int just_identity_ver_versioned_key::prop_0() const {
    return prop_0_;
}

void just_identity_ver_versioned_key::prop_0(const int v) {
    prop_0_ = v;
}

unsigned int just_identity_ver_versioned_key::version() const {
    return version_;
}

void just_identity_ver_versioned_key::version(const unsigned int v) {
    version_ = v;
}

} } }