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
#include <boost/shared_ptr.hpp>
#include "dogen/dynamic/expansion/types/default_value_expander.hpp"
#include "dogen/dynamic/expansion/types/root_object_copier.hpp"
#include "dogen/dynamic/expansion/types/options_copier.hpp"
#include "dogen/dynamic/expansion/types/workflow.hpp"
#include "dogen/dynamic/expansion/types/initializer.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

void register_expander(expander_interface * const p) {
    workflow::registrar()
        .register_expander(boost::shared_ptr<expander_interface>(p));
}

void initializer::initialize() {
    register_expander(new default_value_expander());
    register_expander(new root_object_copier());
    register_expander(new options_copier());
}

} } }
