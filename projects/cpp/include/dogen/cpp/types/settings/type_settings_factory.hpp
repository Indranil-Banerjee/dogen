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
#ifndef DOGEN_CPP_TYPES_SETTINGS_TYPE_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_TYPE_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/cpp/types/formattables/family_types.hpp"
#include "dogen/cpp/types/settings/type_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Constructs the type settings for the supplied object.
 */
class type_settings_factory {
private:
    /**
     * @brief Converts a string to its corresponding family type.
     *
     * @pre string must be a valid family type.
     */
    formattables::family_types to_family_type(const std::string s) const;

public:
    /**
     * @brief Construct the type settings, if available.
     */
    boost::optional<type_settings> make(const dynamic::object& o) const;
};

} } }

#endif