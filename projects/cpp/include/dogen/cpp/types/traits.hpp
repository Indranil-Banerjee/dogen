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
#ifndef DOGEN_CPP_TYPES_TRAITS_HPP
#define DOGEN_CPP_TYPES_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace cpp {

/**
 * @brief Constants for all the top-level meta-data keys for the C++
 * backend.
 */
struct traits {
    /**
     * @brief If set to false, no generation will occur.
     */
    static std::string enabled();

    /**
     * @brief If set to true, the facet is not supported.
     */
    static std::string supported();

    /**
     * @brief Directory in which to place files for this facet.
     */
    static std::string directory();

    /**
     * @brief Post-fix to apply to file names.
     */
    static std::string postfix();

    /**
     * @brief All facets that have been integrated with the present
     * facet.
     */
    static std::string integrated_facet();

    /**
     * @brief File extension to use.
     */
    static std::string extension();

    /**
     * @brief Include path to use for type.
     */
    static std::string inclusion_path();

    /**
     * @brief Type of notation to use in inclusion.
     */
    static std::string inclusion_delimiter_type();

    /**
     * @brief Name of the directory containing the include files.
     */
    static std::string include_directory_name();

    /**
     * @brief Name of the directory containing the source files.
     */
    static std::string source_directory_name();
};

} }

#endif
