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
#include "dogen/formatters/types/modeline.hpp"

namespace dogen {
namespace formatters {

modeline::modeline()
    : editor_(static_cast<dogen::formatters::editors>(0)),
      location_(static_cast<dogen::formatters::modeline_locations>(0)) { }

modeline::modeline(
    const dogen::formatters::editors& editor,
    const dogen::formatters::modeline_locations& location,
    const std::list<dogen::formatters::modeline_field>& fields)
    : editor_(editor),
      location_(location),
      fields_(fields) { }

void modeline::swap(modeline& other) noexcept {
    using std::swap;
    swap(editor_, other.editor_);
    swap(location_, other.location_);
    swap(fields_, other.fields_);
}

bool modeline::operator==(const modeline& rhs) const {
    return editor_ == rhs.editor_ &&
        location_ == rhs.location_ &&
        fields_ == rhs.fields_;
}

modeline& modeline::operator=(modeline other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::formatters::editors modeline::editor() const {
    return editor_;
}

void modeline::editor(const dogen::formatters::editors& v) {
    editor_ = v;
}

dogen::formatters::modeline_locations modeline::location() const {
    return location_;
}

void modeline::location(const dogen::formatters::modeline_locations& v) {
    location_ = v;
}

const std::list<dogen::formatters::modeline_field>& modeline::fields() const {
    return fields_;
}

std::list<dogen::formatters::modeline_field>& modeline::fields() {
    return fields_;
}

void modeline::fields(const std::list<dogen::formatters::modeline_field>& v) {
    fields_ = v;
}

void modeline::fields(const std::list<dogen::formatters::modeline_field>&& v) {
    fields_ = std::move(v);
}

} }