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
#include <memory>
#include "dogen/frontend/types/workflow.hpp"
#include "dogen/frontend/types/dia_frontend.hpp"
#include "dogen/frontend/types/json_sml_frontend.hpp"
#include "dogen/frontend/types/initializer.hpp"

namespace dogen {
namespace frontend {

template<typename Frontend>
inline void register_frontend() {
    auto s(std::make_shared<Frontend>());
    for (const auto& se : s->supported_extensions())
        workflow::registrar().register_frontend_for_extension(se, s);
}

void initializer::initialize() {
    register_frontend<dia_frontend>();
    register_frontend<json_sml_frontend>();
}

} }
