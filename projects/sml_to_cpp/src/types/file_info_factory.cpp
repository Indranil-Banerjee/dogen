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
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/io/formattables/content_types_io.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/sml_to_cpp/types/file_info_factory.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml_to_cpp.file_info_factory"));

const std::string empty;
const std::string dot(".");
const std::string separator("_");
const std::string visitor_postfix("_visitor");

}

namespace dogen {
namespace sml_to_cpp {

file_info_factory::file_info_factory(const locator& l) : locator_(l) { }

std::string file_info_factory::
to_header_guard_name(const boost::filesystem::path& rp) const {
    bool is_first(true);
    std::ostringstream stream;
    for (auto p : rp) {
        std::string s(p.string());
        boost::replace_all(s, dot, separator);
        boost::to_upper(s);
        stream << (is_first ? empty : separator) << s;
        is_first = false;
    }
    return stream.str();
}

cpp::formattables::file_info file_info_factory::
create(const cpp::formattables::content_descriptor& cd) const {
    cpp::formattables::file_info r;
    r.descriptor(cd);
    r.file_path(locator_.absolute_path(cd));

    const auto rp(locator_.relative_logical_path(cd));
    r.relative_path(rp);
    if (cd.file_type() == cpp::formattables::file_types::header)
        r.header_guard(to_header_guard_name(rp));

    return r;
}

cpp::formattables::file_info file_info_factory::
create(boost::shared_ptr<cpp::formattables::enum_info> ei,
    const cpp::formattables::content_descriptor& cd,
    const cpp::formattables::includes& inc) const {
    cpp::formattables::file_info r(create(cd));
    r.formattable(ei);
    r.includes(inc);
    return r;
}

cpp::formattables::file_info file_info_factory::
create(boost::shared_ptr<cpp::formattables::exception_info> ei,
    const cpp::formattables::content_descriptor& cd,
    const cpp::formattables::includes& inc) const {
    cpp::formattables::file_info r(create(cd));
    r.formattable(ei);
    r.includes(inc);
    return r;
}

cpp::formattables::file_info file_info_factory::
create(boost::shared_ptr<cpp::formattables::namespace_info> ni,
    const cpp::formattables::content_descriptor& cd) const {
    cpp::formattables::file_info r(create(cd));
    r.formattable(ni);
    return r;
}

cpp::formattables::file_info file_info_factory::
create(boost::shared_ptr<cpp::formattables::class_info> ci,
    const cpp::formattables::content_descriptor& cd,
    const cpp::formattables::includes& inc) const {
    cpp::formattables::file_info r(create(cd));
    r.formattable(ci);
    r.includes(inc);
    return r;
}

cpp::formattables::file_info file_info_factory::create_includer(
    const cpp::formattables::content_descriptor& cd,
    const cpp::formattables::includes& inc) const {
    cpp::formattables::file_info r(create(cd));
    r.descriptor().content_type(cpp::formattables::content_types::includer);
    r.includes(inc);
    return r;
}

cpp::formattables::file_info file_info_factory::
create_registrar(boost::shared_ptr<cpp::formattables::registrar_info> ri,
    const cpp::formattables::content_descriptor& cd,
    const cpp::formattables::includes& inc) const {
    cpp::formattables::file_info r(create(cd));
    r.formattable(ri);
    r.includes(inc);
    return r;
}

cpp::formattables::file_info file_info_factory::
create_visitor(boost::shared_ptr<cpp::formattables::visitor_info> vi,
    const cpp::formattables::content_descriptor& cd,
    const cpp::formattables::includes& inc) const {
    cpp::formattables::file_info r(create(cd));
    r.formattable(vi);
    r.includes(inc);
    return r;
}

} }
