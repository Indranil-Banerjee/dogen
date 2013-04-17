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
#include "dogen/dia_to_sml/types/context.hpp"

namespace dogen {
namespace dia_to_sml {

context::context()
    : is_target_(static_cast<bool>(0)) { }

context::context(
    const bool is_target,
    const std::unordered_map<std::string, std::string>& child_to_parent,
    const std::unordered_set<std::string>& parent_ids,
    const std::unordered_map<std::string, dogen::sml::qname>& dia_id_to_qname,
    const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& original_parent,
    const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& leaves,
    const std::unordered_set<std::string>& top_level_package_names,
    const dogen::sml::model& model)
    : is_target_(is_target),
      child_to_parent_(child_to_parent),
      parent_ids_(parent_ids),
      dia_id_to_qname_(dia_id_to_qname),
      original_parent_(original_parent),
      leaves_(leaves),
      top_level_package_names_(top_level_package_names),
      model_(model) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(is_target_, other.is_target_);
    swap(child_to_parent_, other.child_to_parent_);
    swap(parent_ids_, other.parent_ids_);
    swap(dia_id_to_qname_, other.dia_id_to_qname_);
    swap(original_parent_, other.original_parent_);
    swap(leaves_, other.leaves_);
    swap(top_level_package_names_, other.top_level_package_names_);
    swap(model_, other.model_);
}

bool context::operator==(const context& rhs) const {
    return is_target_ == rhs.is_target_ &&
        child_to_parent_ == rhs.child_to_parent_ &&
        parent_ids_ == rhs.parent_ids_ &&
        dia_id_to_qname_ == rhs.dia_id_to_qname_ &&
        original_parent_ == rhs.original_parent_ &&
        leaves_ == rhs.leaves_ &&
        top_level_package_names_ == rhs.top_level_package_names_ &&
        model_ == rhs.model_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool context::is_target() const {
    return is_target_;
}

void context::is_target(const bool v) {
    is_target_ = v;
}

const std::unordered_map<std::string, std::string>& context::child_to_parent() const {
    return child_to_parent_;
}

std::unordered_map<std::string, std::string>& context::child_to_parent() {
    return child_to_parent_;
}

void context::child_to_parent(const std::unordered_map<std::string, std::string>& v) {
    child_to_parent_ = v;
}

void context::child_to_parent(const std::unordered_map<std::string, std::string>&& v) {
    child_to_parent_ = std::move(v);
}

const std::unordered_set<std::string>& context::parent_ids() const {
    return parent_ids_;
}

std::unordered_set<std::string>& context::parent_ids() {
    return parent_ids_;
}

void context::parent_ids(const std::unordered_set<std::string>& v) {
    parent_ids_ = v;
}

void context::parent_ids(const std::unordered_set<std::string>&& v) {
    parent_ids_ = std::move(v);
}

const std::unordered_map<std::string, dogen::sml::qname>& context::dia_id_to_qname() const {
    return dia_id_to_qname_;
}

std::unordered_map<std::string, dogen::sml::qname>& context::dia_id_to_qname() {
    return dia_id_to_qname_;
}

void context::dia_id_to_qname(const std::unordered_map<std::string, dogen::sml::qname>& v) {
    dia_id_to_qname_ = v;
}

void context::dia_id_to_qname(const std::unordered_map<std::string, dogen::sml::qname>&& v) {
    dia_id_to_qname_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& context::original_parent() const {
    return original_parent_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::qname>& context::original_parent() {
    return original_parent_;
}

void context::original_parent(const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& v) {
    original_parent_ = v;
}

void context::original_parent(const std::unordered_map<dogen::sml::qname, dogen::sml::qname>&& v) {
    original_parent_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& context::leaves() const {
    return leaves_;
}

std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& context::leaves() {
    return leaves_;
}

void context::leaves(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& v) {
    leaves_ = v;
}

void context::leaves(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >&& v) {
    leaves_ = std::move(v);
}

const std::unordered_set<std::string>& context::top_level_package_names() const {
    return top_level_package_names_;
}

std::unordered_set<std::string>& context::top_level_package_names() {
    return top_level_package_names_;
}

void context::top_level_package_names(const std::unordered_set<std::string>& v) {
    top_level_package_names_ = v;
}

void context::top_level_package_names(const std::unordered_set<std::string>&& v) {
    top_level_package_names_ = std::move(v);
}

const dogen::sml::model& context::model() const {
    return model_;
}

dogen::sml::model& context::model() {
    return model_;
}

void context::model(const dogen::sml::model& v) {
    model_ = v;
}

void context::model(const dogen::sml::model&& v) {
    model_ = std::move(v);
}

} }