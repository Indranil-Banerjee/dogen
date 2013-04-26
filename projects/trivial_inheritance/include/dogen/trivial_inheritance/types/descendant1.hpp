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
#ifndef DOGEN_TRIVIAL_INHERITANCE_TYPES_DESCENDANT1_HPP
#define DOGEN_TRIVIAL_INHERITANCE_TYPES_DESCENDANT1_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/trivial_inheritance/serialization/descendant1_fwd_ser.hpp"
#include "dogen/trivial_inheritance/types/base.hpp"

namespace dogen {
namespace trivial_inheritance {

class descendant1 final : public dogen::trivial_inheritance::base {
public:
    descendant1() = default;
    descendant1(const descendant1&) = default;
    descendant1(descendant1&&) = default;
    descendant1& operator=(const descendant1&) = default;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const descendant1& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, descendant1& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const descendant1& rhs) const;
    bool operator!=(const descendant1& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::trivial_inheritance::base& other) const override;

};

} }

#endif