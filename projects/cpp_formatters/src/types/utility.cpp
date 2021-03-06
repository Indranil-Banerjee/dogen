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
#include <sstream>
#include <ostream>
#include "dogen/cpp_formatters/types/utility.hpp"

namespace  {

const std::string member_variable_postfix("_");
const std::string open_bracket("{");
const std::string close_bracket("}");
const std::string function_brackets("()");
const std::string quote_escaped("\\\"");
const std::string quote("\"");
const std::string inserter("<< ");
const std::string space(" ");

const std::string public_access_specifier("public:");
const std::string protected_access_specifier("protected:");
const std::string private_access_specifier("private:");

}

namespace dogen {
namespace cpp_formatters {

void utility::public_access_specifier() {
    negative_indenter_scope s(indenter_);
    stream_ << ::public_access_specifier << std::endl;
}

void utility::protected_access_specifier() {
    negative_indenter_scope s(indenter_);
    stream_ << ::protected_access_specifier << std::endl;
}

void utility::private_access_specifier() {
    negative_indenter_scope s(indenter_);
    stream_ << ::private_access_specifier << std::endl;
}

void utility::open_scope() {
    stream_ << open_bracket << std::endl;
}

void utility::close_scope() {
    stream_ << indenter_ << close_bracket << std::endl;
}

void utility::blank_line(unsigned int how_many) {
    for (unsigned int i(0); i < how_many; ++i)
        stream_ << std::endl;
}

std::string
utility::as_member_variable(const std::string& property_name) const {
    return property_name + member_variable_postfix;
}

std::string
utility::as_getter(const std::string& property_name) const {
    return property_name + function_brackets;
}

std::string utility::quote(const std::string& original) const {
    return ::quote + original + ::quote;
}

std::string utility::quote_escaped(const std::string& original) const {
    return ::quote_escaped + original + ::quote_escaped;
}

std::string
utility::quote_escaped_streamed(const std::string& original) const {
    std::ostringstream s;
    s << ::quote << ::quote_escaped << ::quote << space
      << inserter << original << space
      << inserter << ::quote << ::quote_escaped << ::quote;
    return s.str();
}

} }
