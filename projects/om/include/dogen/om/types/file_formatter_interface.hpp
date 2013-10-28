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
#ifndef DOGEN_OM_TYPES_FILE_FORMATTER_INTERFACE_HPP
#define DOGEN_OM_TYPES_FILE_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace om {

/**
 * @brief Base formatter for all file formatters.
 *
 * The only reason we need it is because of the meta data path.
 */
class file_formatter_interface {
public:
    file_formatter_interface() = default;
    file_formatter_interface(const file_formatter_interface&) = default;
    file_formatter_interface(file_formatter_interface&&) = default;

public:
    virtual ~file_formatter_interface() noexcept { }

public:
    /**
     * @brief Path to the meta data for this formatter.
     */
    virtual const std::string& meta_data_path() const = 0;
};

} }

#endif