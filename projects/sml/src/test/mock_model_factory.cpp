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
#include <boost/throw_exception.hpp>
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml.mock_model_factory"));

const std::string model_name_prefix("some_model_");
const std::string pod_name_prefix("some_type_");
const std::string property_name_prefix("some_property_");

const std::string boolean("bool");
const std::string unsigned_int("unsigned int");

std::string pod_name(unsigned int i) {
    std::ostringstream stream;
    stream << pod_name_prefix << i;
    return stream.str();
}

std::string model_name(unsigned int i) {
    std::ostringstream stream;
    stream << model_name_prefix << i;
    return stream.str();
}

std::string property_name(unsigned int i) {
    std::ostringstream stream;
    stream << property_name_prefix << i;
    return stream.str();
}

dogen::sml::nested_qname mock_qname(dogen::sml::pod p) {
    dogen::sml::qname qn;
    qn.type_name(p.name().type_name());
    qn.model_name(p.name().model_name());
    qn.meta_type(dogen::sml::meta_types::pod);

    dogen::sml::nested_qname r;
    r.type(qn);
    return r;
}

dogen::sml::nested_qname mock_qname_shared_ptr(dogen::sml::pod p) {
    dogen::sml::qname e;
    e.type_name("boost");
    e.model_name("shared_ptr");
    e.meta_type(dogen::sml::meta_types::pod);

    dogen::sml::nested_qname r;
    r.type(e);

    dogen::sml::nested_qname c;
    c.type(p.name());

    r.children(std::list<dogen::sml::nested_qname> { c });

    return r;
}

dogen::sml::nested_qname mock_qname(
    dogen::sml::test::mock_model_factory::property_types pt) {
    dogen::sml::qname qn;
    dogen::sml::nested_qname r;

    typedef dogen::sml::test::mock_model_factory::property_types property_types;
    switch(pt) {
    case property_types::unsigned_int:
        qn.type_name(unsigned_int);
        qn.meta_type(dogen::sml::meta_types::primitive);
        r.type(qn);
        break;
    case property_types::boolean:
        qn.type_name(boolean);
        qn.meta_type(dogen::sml::meta_types::primitive);
        r.type(qn);
        break;
    case property_types::boost_variant: {
        dogen::sml::qname e;
        e.type_name("variant");
        e.model_name("boost");
        r.type(e);

        dogen::sml::qname f;
        f.type_name(boolean);
        dogen::sml::nested_qname c;
        c.type(f);

        dogen::sml::qname g;
        g.type_name(unsigned_int);
        dogen::sml::nested_qname d;
        d.type(g);
        r.children(std::list<dogen::sml::nested_qname> { c, d });
        break;
    }
    case property_types::std_string:
        qn.type_name("string");
        qn.model_name("std");
        r.type(qn);
        break;
    case property_types::std_pair: {
        dogen::sml::qname e;
        e.type_name("pair");
        e.model_name("std");
        r.type(e);

        dogen::sml::qname f;
        f.type_name(boolean);
        dogen::sml::nested_qname c;
        c.type(f);

        dogen::sml::qname g;
        g.type_name(boolean);
        dogen::sml::nested_qname d;
        d.type(g);
        r.children(std::list<dogen::sml::nested_qname> { c, d });
        break;
    }
    default:
        BOOST_LOG_SEV(lg, error) << "Unknown property type.";
        BOOST_THROW_EXCEPTION(
            dogen::utility::exception::exception("Unknown property type."));
    }
    return r;
}

dogen::sml::pod mock_pod(unsigned int i, std::string model_name) {
    dogen::sml::qname qn;
    qn.model_name(model_name);
    qn.type_name(pod_name(i));
    qn.meta_type(dogen::sml::meta_types::pod);

    dogen::sml::pod r;
    r.name(qn);
    r.generation_type(dogen::sml::generation_types::full_generation);
    return r;
}

dogen::sml::pod mock_pod(unsigned int i) {
    return mock_pod(i, model_name(i));
}

}

namespace dogen {
namespace sml {
namespace test {

std::string mock_model_factory::model_name(const unsigned int n) {
    return ::model_name(n);
}

std::string mock_model_factory::pod_name(const unsigned int n) {
    return ::pod_name(n);
}

model mock_model_factory::build_single_pod_model(const unsigned int n) {
    pod p(mock_pod(n));
    model r;
    r.pods().insert(std::make_pair(p.name(), p));
    r.name(model_name(n));
    return r;
}

model mock_model_factory::build_multi_pod_model(const unsigned int n,
    const unsigned int pod_n) {

    model r;
    for (unsigned int i(0); i < pod_n; ++i) {
        const auto p(mock_pod(i, model_name(n)));
        r.pods().insert(std::make_pair(p.name(), p));
    }
    r.name(model_name(n));
    return r;
}

model mock_model_factory::pod_with_property(const property_types pt) {
    using namespace dogen::sml;
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod pod2;

    dogen::sml::qname qn;
    qn.type_name("boost");
    qn.model_name("shared_ptr");
    qn.meta_type(dogen::sml::meta_types::pod);
    pod2.name(qn);
    pod2.pod_type(dogen::sml::pod_types::smart_pointer);

    property p;
    p.name(property_name(0));

    if (pt == property_types::other_pod)
        p.type_name(mock_qname(pod1));
    else if (pt == property_types::boost_shared_ptr)
        p.type_name(mock_qname_shared_ptr(pod1));
    else
        p.type_name(mock_qname(pt));

    pod0.properties().push_back(p);

    model r;
    r.pods().insert(std::make_pair(pod0.name(), pod0));
    if (pt == property_types::other_pod ||
        pt == property_types::boost_shared_ptr)
        r.pods().insert(std::make_pair(pod1.name(), pod1));

    if (pt == property_types::boost_shared_ptr)
        r.pods().insert(std::make_pair(pod2.name(), pod2));

    r.name(mn);
    return r;
}

std::array<model, 2>
mock_model_factory::pod_with_property_type_in_different_model() {
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));

    property p;
    p.name(property_name(0));
    p.type_name(mock_qname(pod1));
    pod0.properties().push_back(p);

    model m0;
    m0.pods().insert(std::make_pair(pod0.name(), pod0));
    m0.name(model_name(0));

    model m1;
    m1.pods().insert(std::make_pair(pod1.name(), pod1));
    m1.name(model_name(1));

    return std::array<model, 2> {{ m0, m1 }};
}

model mock_model_factory::pod_with_missing_property_type() {
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));

    property p;
    p.name(property_name(0));
    p.type_name(mock_qname(pod1));
    pod0.properties().push_back(p);

    model r;
    r.pods().insert(std::make_pair(pod0.name(), pod0));
    r.name(model_name(0));
    return r;
}

model mock_model_factory::pod_with_parent_in_the_same_model() {
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod0.parent_name(pod1.name());
    pod0.original_parent_name(pod1.name());
    pod1.is_parent(true);
    pod1.leaves().push_back(pod0.name());

    model r;
    r.pods().insert(std::make_pair(pod0.name(), pod0));
    r.pods().insert(std::make_pair(pod1.name(), pod1));
    r.name(mn);
    return r;
}

model mock_model_factory::pod_with_missing_child_in_the_same_model() {
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod0.parent_name(pod1.name());
    pod0.original_parent_name(pod1.name());
    pod1.is_parent(true);
    pod1.leaves().push_back(pod0.name());

    model r;
    r.pods().insert(std::make_pair(pod1.name(), pod1));
    r.name(mn);
    return r;
}

std::array<model, 2> mock_model_factory::
pod_with_parent_in_different_models() {
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));
    pod0.original_parent_name(pod1.name());
    pod0.parent_name(pod1.name());
    pod1.is_parent(true);
    pod1.leaves().push_back(pod0.name());

    model m0;
    m0.pods().insert(std::make_pair(pod0.name(), pod0));
    m0.name(model_name(0));

    model m1;
    m1.pods().insert(std::make_pair(pod1.name(), pod1));
    m1.name(model_name(1));

    return std::array<model, 2> {{ m0, m1 }};
}

model mock_model_factory::pod_with_three_children_in_same_model() {
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod pod2(mock_pod(2, mn));
    pod pod3(mock_pod(3, mn));

    pod0.parent_name(pod3.name());
    pod0.original_parent_name(pod3.name());

    pod1.parent_name(pod3.name());
    pod1.original_parent_name(pod3.name());

    pod2.parent_name(pod3.name());
    pod2.original_parent_name(pod3.name());

    pod3.is_parent(true);
    pod3.leaves().push_back(pod0.name());
    pod3.leaves().push_back(pod1.name());
    pod3.leaves().push_back(pod2.name());

    model r;
    r.pods().insert(std::make_pair(pod0.name(), pod0));
    r.pods().insert(std::make_pair(pod1.name(), pod1));
    r.pods().insert(std::make_pair(pod2.name(), pod2));
    r.pods().insert(std::make_pair(pod3.name(), pod3));
    r.name(mn);
    return r;

}

model mock_model_factory::pod_with_third_degree_parent_in_same_model() {
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod pod2(mock_pod(2, mn));
    pod pod3(mock_pod(3, mn));

    pod0.parent_name(pod1.name());
    pod0.original_parent_name(pod3.name());

    pod1.parent_name(pod2.name());
    pod1.original_parent_name(pod3.name());
    pod1.is_parent(true);
    pod1.leaves().push_back(pod0.name());

    pod2.parent_name(pod3.name());
    pod2.original_parent_name(pod3.name());
    pod2.is_parent(true);
    pod2.leaves().push_back(pod0.name());

    pod3.leaves().push_back(pod0.name());
    pod3.is_parent(true);

    model r;
    r.pods().insert(std::make_pair(pod0.name(), pod0));
    r.pods().insert(std::make_pair(pod1.name(), pod1));
    r.pods().insert(std::make_pair(pod2.name(), pod2));
    r.pods().insert(std::make_pair(pod3.name(), pod3));
    r.name(mn);
    return r;
}

model mock_model_factory::pod_with_third_degree_parent_missing() {
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod pod2(mock_pod(2, mn));
    pod pod3(mock_pod(3, mn));

    pod0.parent_name(pod1.name());
    pod0.original_parent_name(pod3.name());

    pod1.parent_name(pod2.name());
    pod1.original_parent_name(pod3.name());
    pod1.is_parent(true);
    pod1.leaves().push_back(pod0.name());

    pod2.parent_name(pod3.name());
    pod2.original_parent_name(pod3.name());
    pod2.is_parent(true);
    pod2.leaves().push_back(pod0.name());

    pod3.is_parent(true);
    pod3.leaves().push_back(pod0.name());

    model r;
    r.pods().insert(std::make_pair(pod0.name(), pod0));
    r.pods().insert(std::make_pair(pod1.name(), pod1));
    r.pods().insert(std::make_pair(pod2.name(), pod2));
    r.name(mn);
    return r;
}

std::array<model, 4>
mock_model_factory::pod_with_third_degree_parent_in_different_models() {
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));
    pod pod2(mock_pod(2));
    pod pod3(mock_pod(3));

    pod0.parent_name(pod1.name());
    pod0.original_parent_name(pod3.name());

    pod1.parent_name(pod2.name());
    pod1.original_parent_name(pod3.name());
    pod1.is_parent(true);
    pod1.leaves().push_back(pod0.name());

    pod2.parent_name(pod3.name());
    pod2.original_parent_name(pod3.name());
    pod2.is_parent(true);
    pod2.leaves().push_back(pod0.name());

    pod3.is_parent(true);
    pod3.leaves().push_back(pod0.name());

    model m0;
    m0.pods().insert(std::make_pair(pod0.name(), pod0));
    m0.name(model_name(0));

    model m1;
    m1.pods().insert(std::make_pair(pod1.name(), pod1));
    m1.name(model_name(1));

    model m2;
    m2.pods().insert(std::make_pair(pod2.name(), pod2));
    m2.name(model_name(2));

    model m3;
    m3.pods().insert(std::make_pair(pod3.name(), pod3));
    m3.name(model_name(3));

    return std::array<model, 4>{{ m0, m1, m2, m3 }};
}

std::array<model, 4> mock_model_factory::
pod_with_missing_third_degree_parent_in_different_models() {
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));
    pod pod2(mock_pod(2));
    pod pod3(mock_pod(3));

    pod0.parent_name(pod1.name());
    pod0.original_parent_name(pod3.name());

    pod1.parent_name(pod2.name());
    pod1.original_parent_name(pod3.name());
    pod1.is_parent(true);
    pod1.leaves().push_back(pod0.name());

    pod2.parent_name(pod3.name());
    pod2.original_parent_name(pod3.name());
    pod2.is_parent(true);
    pod2.leaves().push_back(pod0.name());

    pod3.is_parent(true);
    pod3.leaves().push_back(pod0.name());

    model m0;
    m0.pods().insert(std::make_pair(pod0.name(), pod0));
    m0.name(model_name(0));

    model m1;
    m1.pods().insert(std::make_pair(pod1.name(), pod1));
    m1.name(model_name(1));

    model m2;
    m2.pods().insert(std::make_pair(pod2.name(), pod2));
    m2.name(model_name(2));

    return std::array<model, 4>{{ m0, m1, m2 }};
}

} } }