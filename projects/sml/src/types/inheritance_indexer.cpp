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
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/indexing_error.hpp"
#include "dogen/sml/io/relationship_types_io.hpp"
#include "dogen/sml/types/inheritance_indexer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.inheritance_indexer"));

const std::string relationship_not_found(
    "Could not find relationship in object. Details: ");
const std::string object_not_found("Object not found in model: ");
const std::string concept_not_found("Concept not found in concept container: ");

}

namespace dogen {
namespace sml {

/**
 * @brief Add comparable support for qnames.
 *
 * This is required as part of the current (very sub-optimal)
 * implementation of concept processing.
 */
inline bool operator<(const qname& lhs, const qname& rhs) {
    return
        lhs.model_name() < rhs.model_name() ||
        (lhs.model_name() == rhs.model_name() &&
            (lhs.external_module_path() < rhs.external_module_path() ||
                (lhs.external_module_path() == rhs.external_module_path() &&
                    (lhs.simple_name() < rhs.simple_name()))));
}

abstract_object& inheritance_indexer::find_object(const qname& qn, model& m) {
    auto i(m.objects().find(qn));
    if (i == m.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << qn;
        BOOST_THROW_EXCEPTION(indexing_error(object_not_found +
                boost::lexical_cast<std::string>(qn)));
    }
    return *(i->second);
}

std::list<qname>& inheritance_indexer::
find_relationships(const relationship_types rt, abstract_object& o) {
    auto i(o.relationships().find(rt));
    if (i == o.relationships().end() || i->second.empty()) {
        BOOST_LOG_SEV(lg, error) << relationship_not_found << o.name()
                                 << " relationship: " << rt;

        BOOST_THROW_EXCEPTION(indexing_error(relationship_not_found +
                boost::lexical_cast<std::string>(o.name())));
    }
    return i->second;
}

concept& inheritance_indexer::find_concept(const qname& qn, model& m) {
    auto i(m.concepts().find(qn));
    if (i == m.concepts().end()) {
        const auto& sn(qn.simple_name());
        BOOST_LOG_SEV(lg, error) << concept_not_found << sn;
        BOOST_THROW_EXCEPTION(indexing_error(concept_not_found + sn));
    }
    return i->second;
}

void inheritance_indexer::
populate_all_properties(abstract_object& o, model& m) {
    for (const auto& pair : o.inherited_properties()) {
        o.all_properties().insert(o.all_properties().end(),
            pair.second.begin(), pair.second.end());
    }

    o.all_properties().insert(o.all_properties().end(),
        o.local_properties().begin(), o.local_properties().end());

    const auto rt(relationship_types::modeled_concepts);
    const auto i(o.relationships().find(rt));
    if (i == o.relationships().end() || i->second.empty())
        return;

    for (const auto& qn : i->second) {
        const auto& c(find_concept(qn, m));
        o.local_properties().insert(o.local_properties().end(),
            c.local_properties().begin(), c.local_properties().end());
    }
}

void inheritance_indexer::
index_object(abstract_object& parent, abstract_object& leaf, model& m) {
    const auto mc(relationship_types::modeled_concepts);
    const auto i(parent.relationships().find(mc));
    const bool has_concepts(i != parent.relationships().end() &&
        !i->second.empty());

    std::set<qname> our_concepts;
    if (has_concepts) {
        // perform concept expansion
        for (const auto& qn : i->second) {
            const auto& c(find_concept(qn, m));

            // add concepts we model directly
            our_concepts.insert(c.name());

            // add concepts refined by our concept
            our_concepts.insert(c.refines().begin(), c.refines().end());
        }
    }

    const bool is_root(!parent.is_child());
    std::set<qname> their_concepts;
    if (is_root) {
        auto& op(leaf.relationships()[relationship_types::original_parents]);
        op.push_back(parent.name());

        auto& l(parent.relationships()[relationship_types::leaves]);
        l.push_back(leaf.name());
    } else {
        const auto rt(relationship_types::parents);
        std::set<qname> gp_modeled_concepts;
        for (const auto& qn : find_relationships(rt, parent)) {
            auto& grand_parent(find_object(qn, m));
            index_object(grand_parent, leaf, m);

            parent.inherited_properties().insert(
                std::make_pair(grand_parent.name(),
                    grand_parent.all_properties()));

            const auto i(grand_parent.relationships().find(mc));
            if (i == grand_parent.relationships().end() || i->second.empty())
                continue;

            if (has_concepts) {
                // add all concepts modeled by our grand parent
                their_concepts.insert(i->second.begin(), i->second.end());
            }
        }
    }

    populate_all_properties(parent, m);

    /* we want to only model concepts which have not yet been modeled
     * by any of our grand parents.
     */
    std::set<qname> result;
    std::set_difference(our_concepts.begin(), our_concepts.end(),
        their_concepts.begin(), their_concepts.end(),
        std::inserter(result, result.end()));

    // preserve qname order.
    auto tmp(i->second);
    i->second.clear();
    for (const auto& qn : tmp) {
        if (result.find(qn) != result.end())
            i->second.push_back(qn);
    }
}

void inheritance_indexer::index_objects(model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing inheritance. Objects: "
                             << m.objects().size();

    for (auto& pair : m.objects()) {
        auto& o(*pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        const bool in_inheritance_relationship(o.is_parent() || o.is_child());
        if (!in_inheritance_relationship) {
            const auto mc(relationship_types::modeled_concepts);
            const auto i(o.relationships().find(mc));

            std::list<qname> expanded_modeled_concepts;
            if (i != o.relationships().end() && !i->second.empty()) {
                for (const auto& qn : i->second) {
                    const auto& c(find_concept(qn, m));

                    // add concepts we model directly
                    expanded_modeled_concepts.push_back(c.name());

                    // add concepts our parent models
                    expanded_modeled_concepts.insert(
                        expanded_modeled_concepts.end(),
                        c.refines().begin(), c.refines().end());
                }

                i->second = expanded_modeled_concepts;
            }
            populate_all_properties(o, m);
            continue;
        }

        const bool is_leaf(o.is_parent() && !o.is_child());
        if (!is_leaf)
            continue;

        const auto rt(relationship_types::parents);
        for (const auto& qn : find_relationships(rt, o)) {
            auto& parent(find_object(qn, m));
            index_object(parent, o, m);
        }
    }
}

void inheritance_indexer::index_concept(concept& c, model& m,
    std::unordered_set<sml::qname>& processed_qnames) {
    if (processed_qnames.find(c.name()) != processed_qnames.end())
        return;

    c.all_properties().insert(c.all_properties().end(),
        c.local_properties().begin(), c.local_properties().end());

    if (c.refines().empty()) {
        processed_qnames.insert(c.name());
        return;
    }

    std::list<qname> expanded_refines;
    for (auto& qn : c.refines()) {
        auto& parent(find_concept(qn, m));
        index_concept(parent, m, processed_qnames);

        // add concepts we refine directly
        expanded_refines.push_back(qn);

        // add concepts our parents refine
        expanded_refines.insert(expanded_refines.end(),
            parent.refines().begin(), parent.refines().end());

        // collect our parent's properties
        c.inherited_properties().insert(std::make_pair(parent.name(),
                parent.all_properties()));
        c.all_properties().insert(c.all_properties().end(),
            parent.all_properties().begin(), parent.all_properties().end());
    }

    c.refines(expanded_refines);
    processed_qnames.insert(c.name());
}

void inheritance_indexer::index_concepts(model& m) {
    std::unordered_set<sml::qname> processed_qnames;

    for (auto& pair : m.concepts()) {
        auto& c(pair.second);

        if (c.generation_type() == generation_types::no_generation)
            continue;

        index_concept(c, m, processed_qnames);
    }
}

void inheritance_indexer::index(model& m) {
    index_concepts(m);
    index_objects(m);
}

} }