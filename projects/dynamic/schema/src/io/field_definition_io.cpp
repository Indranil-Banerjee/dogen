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
#include <ostream>
#include "dogen/dynamic/schema/io/field_definition_io.hpp"
#include "dogen/dynamic/schema/io/name_io.hpp"
#include "dogen/dynamic/schema/io/ownership_hierarchy_io.hpp"
#include "dogen/dynamic/schema/io/scope_types_io.hpp"
#include "dogen/dynamic/schema/io/value_io.hpp"
#include "dogen/dynamic/schema/io/value_types_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::dynamic::schema::value>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s<< " }";
    return s;
}

}

namespace dogen {
namespace dynamic {
namespace schema {

std::ostream& operator<<(std::ostream& s, const field_definition& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::dynamic::schema::field_definition\"" << ", "
      << "\"name\": " << v.name() << ", "
      << "\"type\": " << v.type() << ", "
      << "\"scope\": " << v.scope() << ", "
      << "\"ownership_hierarchy\": " << v.ownership_hierarchy() << ", "
      << "\"default_value\": " << v.default_value()
      << " }";
    return(s);
}

} } }