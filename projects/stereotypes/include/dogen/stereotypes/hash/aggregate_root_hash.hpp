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
#ifndef DOGEN_STEREOTYPES_HASH_AGGREGATE_ROOT_HASH_HPP
#define DOGEN_STEREOTYPES_HASH_AGGREGATE_ROOT_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/stereotypes/types/aggregate_root.hpp"

namespace dogen {
namespace stereotypes {

class aggregate_root_hasher {
public:
    static std::size_t hash(const aggregate_root& v);
};

} }

namespace std {

template<>
class hash<dogen::stereotypes::aggregate_root> {
public:
    size_t operator()(const dogen::stereotypes::aggregate_root& v) const {
        return dogen::stereotypes::aggregate_root_hasher::hash(v);
    }
};

}
#endif