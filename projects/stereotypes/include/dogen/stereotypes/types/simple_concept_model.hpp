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
#ifndef DOGEN_STEREOTYPES_TYPES_SIMPLE_CONCEPT_MODEL_HPP
#define DOGEN_STEREOTYPES_TYPES_SIMPLE_CONCEPT_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/stereotypes/serialization/simple_concept_model_fwd_ser.hpp"

namespace dogen {
namespace stereotypes {

/**
 * @brief This class models simple concept.
 */
class simple_concept_model final {
public:
    simple_concept_model(const simple_concept_model&) = default;
    simple_concept_model(simple_concept_model&&) = default;
    ~simple_concept_model() = default;

public:
    simple_concept_model();

public:
    simple_concept_model(
        const int prop_1,
        const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const simple_concept_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, simple_concept_model& v, unsigned int version);

public:
    /**
     * @brief Property that belongs to class.
     */
    /**@{*/
    int prop_1() const;
    void prop_1(const int v);
    /**@}*/

    /**
     * @brief This is a sample property in a concept.
     */
    /**@{*/
    int prop_0() const;
    void prop_0(const int v);
    /**@}*/

public:
    bool operator==(const simple_concept_model& rhs) const;
    bool operator!=(const simple_concept_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(simple_concept_model& other) noexcept;
    simple_concept_model& operator=(simple_concept_model other);

private:
    int prop_1_;
    int prop_0_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stereotypes::simple_concept_model& lhs,
    dogen::stereotypes::simple_concept_model& rhs) {
    lhs.swap(rhs);
}

}

#endif