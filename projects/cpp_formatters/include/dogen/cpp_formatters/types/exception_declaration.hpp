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
#ifndef DOGEN_CPP_FORMATTERS_TYPES_EXCEPTION_DECLARATION_HPP
#define DOGEN_CPP_FORMATTERS_TYPES_EXCEPTION_DECLARATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include "dogen/cpp/types/formattables/exception_info.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"

namespace dogen {
namespace cpp_formatters {

class exception_declaration {
public:
    exception_declaration() = default;
    ~exception_declaration() = default;
    exception_declaration(const exception_declaration&) = default;
    exception_declaration(exception_declaration&&) = default;
    exception_declaration& operator=(
        const exception_declaration&) = default;

public:
    exception_declaration(std::ostream& stream);

public:
    void format(const cpp::formattables::exception_info& ei);

protected:
    std::ostream& stream_;
    indenter indenter_;
    utility utility_;
};

} }

#endif
