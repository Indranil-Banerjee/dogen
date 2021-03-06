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
#include "dogen/cpp/hash/formattables/class_info_hash.hpp"
#include "dogen/cpp/hash/formattables/enum_info_hash.hpp"
#include "dogen/cpp/hash/formattables/exception_info_hash.hpp"
#include "dogen/cpp/hash/formattables/namespace_info_hash.hpp"
#include "dogen/cpp/hash/formattables/registrar_info_hash.hpp"
#include "dogen/cpp/hash/formattables/visitor_info_hash.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml_to_cpp/hash/context_hash.hpp"
#include "dogen/sml_to_cpp/hash/relationships_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_shared_ptr_dogen_cpp_formattables_class_info(const boost::shared_ptr<dogen::cpp::formattables::class_info>& v){
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_class_info_(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::formattables::class_info> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_cpp_formattables_class_info(i.second));
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_dogen_sml_to_cpp_relationships(const std::unordered_map<dogen::sml::qname, dogen::sml_to_cpp::relationships>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_cpp_formattables_exception_info(const boost::shared_ptr<dogen::cpp::formattables::exception_info>& v){
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_exception_info_(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::formattables::exception_info> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_cpp_formattables_exception_info(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_cpp_formattables_enum_info(const boost::shared_ptr<dogen::cpp::formattables::enum_info>& v){
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_enum_info_(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::formattables::enum_info> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_cpp_formattables_enum_info(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_cpp_formattables_registrar_info(const boost::shared_ptr<dogen::cpp::formattables::registrar_info>& v){
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_registrar_info_(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::formattables::registrar_info> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_cpp_formattables_registrar_info(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_cpp_formattables_namespace_info(const boost::shared_ptr<dogen::cpp::formattables::namespace_info>& v){
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_namespace_info_(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::formattables::namespace_info> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_cpp_formattables_namespace_info(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_cpp_formattables_visitor_info(const boost::shared_ptr<dogen::cpp::formattables::visitor_info>& v){
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_visitor_info_(const std::unordered_map<dogen::sml::qname, boost::shared_ptr<dogen::cpp::formattables::visitor_info> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_cpp_formattables_visitor_info(i.second));
    }
    return seed;
}

}

namespace dogen {
namespace sml_to_cpp {

std::size_t context_hasher::hash(const context&v) {
    std::size_t seed(0);

    combine(seed, hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_class_info_(v.classes()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_dogen_sml_to_cpp_relationships(v.relationships()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_exception_info_(v.exceptions()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_enum_info_(v.enumerations()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_registrar_info_(v.registrars()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_namespace_info_(v.namespaces()));
    combine(seed, hash_std_unordered_map_dogen_sml_qname_boost_shared_ptr_dogen_cpp_formattables_visitor_info_(v.visitors()));

    return seed;
}

} }
