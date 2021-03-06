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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_CONTAINER_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_CONTAINER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include <unordered_map>
#include "dogen/cpp/types/formatters/formatter_interface.hpp"
#include "dogen/cpp/types/formatters/class_formatter_interface.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class registrar;

/**
 * @brief Simple container for all formatter types.
 */
class container final {
private:
    friend class registrar;

public:
    /**
     * @brief Returns all available class formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::class_formatter_interface>
    >&
    class_formatters() const;

public:
    /**
     * @brief Returns all available formatters.
     */
    const std::forward_list<std::shared_ptr<formatters::formatter_interface>>&
    all_formatters() const;

private:
    std::forward_list<std::shared_ptr<formatters::formatter_interface>>
    all_formatters_;
    std::forward_list<std::shared_ptr<formatters::class_formatter_interface>>
    class_formatters_;
};

} } }

#endif
