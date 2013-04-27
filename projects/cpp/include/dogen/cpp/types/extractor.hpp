/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2013 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_TYPES_EXTRACTOR_HPP
#define DOGEN_CPP_TYPES_EXTRACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include "dogen/sml/types/pod.hpp"
#include "dogen/cpp/types/boost_model_helper.hpp"
#include "dogen/cpp/types/std_model_helper.hpp"
#include "dogen/cpp/types/relationships.hpp"

namespace dogen {
namespace cpp {

class extractor {
public:
    extractor() = delete;
    extractor(const extractor&) = default;
    ~extractor() = default;
    extractor(extractor&&) = default;
    extractor& operator=(const extractor&) = delete;

public:
    typedef const std::unordered_map<sml::qname, sml::pod> pod_map;

public:
    extractor(const pod_map& pods,
        const boost_model_helper& boost,
        const std_model_helper& std) : pods_(pods), boost_(boost), std_(std) { }

private:
    /**
     * @brief Iterates through the nested qname recursively, picking
     * up dependencies as it goes along.
     */
    void recurse_nested_qnames(const dogen::sml::nested_qname& nqn,
        relationships& rel, bool& is_pointer) const;

public:
    /**
     * @brief Flattens the given pod into all qnames it is related to,
     * except itself.
     *
     * The qnames include all types used by the properties of the pod,
     * as well as its parent, if any.
     */
    relationships extract_dependency_graph(const sml::pod& p) const;

    /**
     * @brief Flattens the given qname into a object inheritance
     * graph, with the qname as the root.
     *
     * The qnames include all descendants of the originally supplied
     * type.
     */
    relationships extract_inheritance_graph(const sml::qname& qn) const;

private:
    const pod_map& pods_;
    const boost_model_helper& boost_;
    const std_model_helper& std_;
};

} }

#endif