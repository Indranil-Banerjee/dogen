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
#include <boost/pointer_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/cpp/types/formattables/class_info.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/facet_includer.hpp"

namespace {

const std::string unexpected_class_info(
    "File view model should not contain a class view model");

}

namespace dogen {
namespace cpp_formatters {

facet_includer::facet_includer(std::ostream& stream) :
    stream_(stream), utility_(stream_, indenter_) { }

file_formatter::shared_ptr facet_includer::
create(std::ostream& stream) {
    return file_formatter::shared_ptr(new facet_includer(stream));
}

void facet_includer::format(const cpp::formattables::file_info& f) {
    auto o(boost::dynamic_pointer_cast<
            cpp::formattables::class_info>(f.formattable()));
    if (o)
        BOOST_THROW_EXCEPTION(formatting_error(unexpected_class_info));

    licence licence(stream_);
    licence.format();

    const bool blank_line(false);
    includes includes(stream_, blank_line);
    includes.format(f);
}

} }
