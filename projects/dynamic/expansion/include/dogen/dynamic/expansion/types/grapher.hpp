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
#ifndef DOGEN_DYNAMIC_EXPANSION_TYPES_GRAPHER_HPP
#define DOGEN_DYNAMIC_EXPANSION_TYPES_GRAPHER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "dogen/dynamic/expansion/types/expander_interface.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

/**
 * @brief Graph of expander dependencies.
 */
typedef boost::adjacency_list<
    boost::setS, boost::vecS, boost::directedS,
    boost::shared_ptr<expander_interface>
    > graph_type;

/**
 * @brief Builds a graph of expander dependencies.
 */
class grapher {
private:
    typedef boost::graph_traits<graph_type>::vertex_descriptor
    vertex_descriptor_type;

public:
    grapher();

private:
    /**
     * @brief Given a expander name, return its associated vertex.
     *
     * If the vertex does not yet exist, creates it.
     */
    vertex_descriptor_type vertex_for_expander(const std::string& n);

    /**
     * @brief Ensures the graph has not yet been built.
     */
    void require_not_built() const;

    /**
     * @brief Ensures the graph has been built.
     */
    void require_built() const;

public:
    /**
     * @brief Adds the expander to the graph.
     *
     * @pre The graph must not yet have been built.
     */
    void add(boost::shared_ptr<expander_interface> e);

    /**
     * @brief Returns true if the graph has been built, false
     * otherwise.
     */
    bool is_built() const { return built_; }

    /**
     * @brief Generate a DAG of all objects that have been added.
     *
     * @pre Graph must not yet have been built.
     */
    void generate();

    /**
     * @brief Returns the generated graph.
     *
     * @pre The graph must have already been built.
     */
    const graph_type& graph() const;

private:
    bool built_;
    graph_type graph_;
    vertex_descriptor_type root_vertex_;
    std::unordered_map<std::string, vertex_descriptor_type>
    expander_name_to_vertex_;
    std::unordered_map<std::string, vertex_descriptor_type>
    orphanage_;
    std::unordered_set<std::string> non_orphans_;
};

} } }

#endif
