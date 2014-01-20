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
#ifndef DOGEN_FORMATTERS_HASH_MODELINE_GROUP_HASH_HPP
#define DOGEN_FORMATTERS_HASH_MODELINE_GROUP_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/formatters/types/modeline_group.hpp"

namespace dogen {
namespace formatters {

struct modeline_group_hasher {
public:
    static std::size_t hash(const modeline_group& v);
};

} }

namespace std {

template<>
struct hash<dogen::formatters::modeline_group> {
public:
    size_t operator()(const dogen::formatters::modeline_group& v) const {
        return dogen::formatters::modeline_group_hasher::hash(v);
    }
};

}
#endif