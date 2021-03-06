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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUDES_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUDES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <list>
#include "dogen/cpp/serialization/formattables/includes_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Captures include dependencies.
 */
class includes final {
public:
    includes() = default;
    includes(const includes&) = default;
    includes(includes&&) = default;
    ~includes() = default;

public:
    includes(
        const std::list<boost::filesystem::path>& system,
        const std::list<boost::filesystem::path>& user);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const includes& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, includes& v, unsigned int version);

public:
    /**
     * @brief System includes.
     */
    /**@{*/
    const std::list<boost::filesystem::path>& system() const;
    std::list<boost::filesystem::path>& system();
    void system(const std::list<boost::filesystem::path>& v);
    void system(const std::list<boost::filesystem::path>&& v);
    /**@}*/

    /**
     * @brief User includes.
     */
    /**@{*/
    const std::list<boost::filesystem::path>& user() const;
    std::list<boost::filesystem::path>& user();
    void user(const std::list<boost::filesystem::path>& v);
    void user(const std::list<boost::filesystem::path>&& v);
    /**@}*/

public:
    bool operator==(const includes& rhs) const;
    bool operator!=(const includes& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(includes& other) noexcept;
    includes& operator=(includes other);

private:
    std::list<boost::filesystem::path> system_;
    std::list<boost::filesystem::path> user_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::includes& lhs,
    dogen::cpp::formattables::includes& rhs) {
    lhs.swap(rhs);
}

}

#endif
