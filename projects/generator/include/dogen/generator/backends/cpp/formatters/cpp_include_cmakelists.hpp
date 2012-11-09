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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_INCLUDE_CMAKELISTS_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_INCLUDE_CMAKELISTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/backends/cpp/view_models/cmakelists_view_model.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class cpp_include_cmakelists {
public:
    typedef view_models::cmakelists_view_model cmakelists_view_model;

public:
    cpp_include_cmakelists() = delete;
    cpp_include_cmakelists(const cpp_include_cmakelists&) = default;
    ~cpp_include_cmakelists() noexcept = default;
    cpp_include_cmakelists(cpp_include_cmakelists&&) = default;
    cpp_include_cmakelists& operator=(const cpp_include_cmakelists&) = default;

public:
    explicit cpp_include_cmakelists(std::ostream& stream);

public:
    void format(const cmakelists_view_model& vm);

private:
    std::ostream& stream_;
};

} } } } }

#endif
