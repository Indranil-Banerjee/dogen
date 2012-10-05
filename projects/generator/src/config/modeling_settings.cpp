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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/io/ios_state.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/generator/config/modeling_settings.hpp"

namespace dogen {
namespace generator {
namespace config {

std::ostream&
operator<<(std::ostream& stream, modeling_settings value) {
    boost::io::ios_flags_saver ifs(stream);
    stream << std::boolalpha;

    using utility::streaming::jsonify;
    stream << "\"modeling_settings\": { "
           << "\"verbose\":" << value.verbose() << ", "
           << "\"target\": " << value.target() << ", "
           << "\"external_package_path\": \"" << value.external_package_path()
           << "\", "
           << "\"references\": " << value.references() << ", "
           << "\"disable_model_package\": " << value.disable_model_package()
           << " }";

    return stream;
}

} } }
