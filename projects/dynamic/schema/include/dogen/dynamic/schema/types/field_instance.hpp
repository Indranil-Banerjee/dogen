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
#ifndef DOGEN_DYNAMIC_SCHEMA_TYPES_FIELD_INSTANCE_HPP
#define DOGEN_DYNAMIC_SCHEMA_TYPES_FIELD_INSTANCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/dynamic/schema/serialization/field_instance_fwd_ser.hpp"
#include "dogen/dynamic/schema/types/value_fwd.hpp"

namespace dogen {
namespace dynamic {
namespace schema {

/**
 * @brief Represents an instance of a field in an object.
 */
class field_instance final {
public:
    field_instance() = default;
    field_instance(const field_instance&) = default;
    field_instance(field_instance&&) = default;
    ~field_instance() = default;

public:
    explicit field_instance(const boost::shared_ptr<dogen::dynamic::schema::value>& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const field_instance& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, field_instance& v, unsigned int version);

public:
    const boost::shared_ptr<dogen::dynamic::schema::value>& value() const;
    boost::shared_ptr<dogen::dynamic::schema::value>& value();
    void value(const boost::shared_ptr<dogen::dynamic::schema::value>& v);
    void value(const boost::shared_ptr<dogen::dynamic::schema::value>&& v);

public:
    bool operator==(const field_instance& rhs) const;
    bool operator!=(const field_instance& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(field_instance& other) noexcept;
    field_instance& operator=(field_instance other);

private:
    boost::shared_ptr<dogen::dynamic::schema::value> value_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::dynamic::schema::field_instance& lhs,
    dogen::dynamic::schema::field_instance& rhs) {
    lhs.swap(rhs);
}

}

#endif
