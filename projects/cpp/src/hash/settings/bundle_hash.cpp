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
#include "dogen/cpp/hash/settings/bundle_hash.hpp"
#include "dogen/cpp/hash/settings/formatter_settings_hash.hpp"
#include "dogen/cpp/hash/settings/opaque_settings_hash.hpp"
#include "dogen/cpp/hash/settings/type_settings_hash.hpp"
#include "dogen/formatters/hash/general_settings_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_optional_dogen_formatters_general_settings(const boost::optional<dogen::formatters::general_settings>& v){
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_boost_optional_dogen_cpp_settings_type_settings(const boost::optional<dogen::cpp::settings::type_settings>& v){
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_cpp_settings_formatter_settings(const std::unordered_map<std::string, dogen::cpp::settings::formatter_settings>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_cpp_settings_opaque_settings(const boost::shared_ptr<dogen::cpp::settings::opaque_settings>& v){
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_boost_shared_ptr_dogen_cpp_settings_opaque_settings_(const std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_cpp_settings_opaque_settings(i.second));
    }
    return seed;
}

}

namespace dogen {
namespace cpp {
namespace settings {

std::size_t bundle_hasher::hash(const bundle&v) {
    std::size_t seed(0);

    combine(seed, hash_boost_optional_dogen_formatters_general_settings(v.general_settings()));
    combine(seed, hash_boost_optional_dogen_cpp_settings_type_settings(v.type_settings()));
    combine(seed, hash_std_unordered_map_std_string_dogen_cpp_settings_formatter_settings(v.formatter_settings()));
    combine(seed, hash_std_unordered_map_std_string_boost_shared_ptr_dogen_cpp_settings_opaque_settings_(v.opaque_settings()));

    return seed;
}

} } }
