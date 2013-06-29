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
#include "dogen/sml/test_data/abstract_entity_td.hpp"
#include "dogen/sml/test_data/abstract_object_td.hpp"
#include "dogen/sml/test_data/entity_td.hpp"
#include "dogen/sml/test_data/keyed_entity_td.hpp"
#include "dogen/sml/test_data/property_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::sml::property
create_dogen_sml_property(const unsigned int position) {
    return dogen::sml::property_generator::create(position);
}

std::list<dogen::sml::property> create_std_list_dogen_sml_property(unsigned int position) {
    std::list<dogen::sml::property> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_sml_property(position + i));
    }
    return r;
}

}

namespace dogen {
namespace sml {


void abstract_entity_generator::
populate(const unsigned int position, result_type& v) {
    dogen::sml::abstract_object_generator::populate(position, v);
    v.is_aggregate_root(create_bool(position + 0));
    v.identity(create_std_list_dogen_sml_property(position + 1));
}

abstract_entity_generator::result_type*
abstract_entity_generator::create_ptr(const unsigned int position) {
    if ((position % 1) == 0)
        return dogen::sml::entity_generator::create_ptr(position);
    return dogen::sml::keyed_entity_generator::create_ptr(position);
}


} }
