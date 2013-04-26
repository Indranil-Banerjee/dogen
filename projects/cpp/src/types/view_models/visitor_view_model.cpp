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
#include "dogen/cpp/types/view_models/visitor_view_model.hpp"

namespace dogen {
namespace cpp {
namespace view_models {

visitor_view_model::visitor_view_model(
    const std::string& name,
    const std::list<std::string>& types)
    : name_(name),
      types_(types) { }

void visitor_view_model::swap(visitor_view_model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(types_, other.types_);
}

bool visitor_view_model::operator==(const visitor_view_model& rhs) const {
    return name_ == rhs.name_ &&
        types_ == rhs.types_;
}

visitor_view_model& visitor_view_model::operator=(visitor_view_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& visitor_view_model::name() const {
    return name_;
}

std::string& visitor_view_model::name() {
    return name_;
}

void visitor_view_model::name(const std::string& v) {
    name_ = v;
}

void visitor_view_model::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<std::string>& visitor_view_model::types() const {
    return types_;
}

std::list<std::string>& visitor_view_model::types() {
    return types_;
}

void visitor_view_model::types(const std::list<std::string>& v) {
    types_ = v;
}

void visitor_view_model::types(const std::list<std::string>&& v) {
    types_ = std::move(v);
}

} } }