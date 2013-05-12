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
#include <boost/throw_exception.hpp>
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/licence.hpp"
#include "dogen/cpp/types/formatters/header_guards.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/includes.hpp"
#include "dogen/cpp/types/formatters/namespace_helper.hpp"
#include "dogen/cpp/types/formatters/qname.hpp"
#include "dogen/cpp/types/formatters/indenter.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatters/generator_header.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.generator_header"));

const std::string missing_class_info(
    "Meta type is pod but class view model is empty");
const std::string missing_enumeration_info(
    "Meta type is enumeration but enumeration view model is empty");

}

namespace dogen {
namespace cpp {
namespace formatters {

generator_header::
generator_header(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr generator_header::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new generator_header(stream));
}

void generator_header::generator_class(const enumeration_info& vm) {
    const std::string class_name(vm.name() + "_generator");

    stream_ << indenter_ << "class " << class_name << " ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);

        utility_.public_access_specifier();
        stream_ << indenter_ << class_name << "();" << std::endl;
        utility_.blank_line();

        utility_.public_access_specifier();

        stream_ << indenter_ << "typedef ";
        qname qname(stream_);
        qname.format(vm);
        stream_ << " result_type;" << std::endl;
        utility_.blank_line();

        utility_.public_access_specifier();
        stream_ << indenter_
                << "static void populate(const unsigned int position,"
                <<" result_type& v);"
                << std::endl;

        stream_ << indenter_
                << "static result_type create(const unsigned int position);"
                << std::endl;

        stream_ << indenter_ << "result_type operator()();" << std::endl;
        utility_.blank_line();

        utility_.private_access_specifier();
        stream_ << indenter_ << "unsigned int "
                << utility_.as_member_variable("position") << ";"
                << std::endl;
    }
    stream_ << "};";
}

void generator_header::generator_class(const class_info& vm) {
    const std::string class_name(vm.name() + "_generator");

    stream_ << indenter_ << "class " << class_name << " ";
    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);

        utility_.public_access_specifier();
        stream_ << indenter_ << class_name << "();" << std::endl;
        utility_.blank_line();

        utility_.public_access_specifier();

        stream_ << indenter_ << "typedef ";
        qname qname(stream_);
        qname.format(vm);
        stream_ << " result_type;" << std::endl;
        utility_.blank_line();

        utility_.public_access_specifier();
        if (!vm.is_immutable()) {
            stream_ << indenter_
                    << "static void populate(const unsigned int position,"
                    <<" result_type& v);"
                    << std::endl;
        }

        if (!vm.is_parent()) {
            stream_ << indenter_
                    << "static result_type create(const unsigned int position);"
                    << std::endl;

            stream_ << indenter_ << "result_type operator()();" << std::endl;
            utility_.blank_line();

            utility_.private_access_specifier();
            stream_ << indenter_ << "unsigned int "
                    << utility_.as_member_variable("position") << ";"
                    << std::endl;
        }

        utility_.public_access_specifier();
        stream_ << indenter_
                << "static result_type* create_ptr("
                << "const unsigned int position);"
                << std::endl;
    }
    stream_ << "};";
}

void generator_header::format_enumeration(const file_info& vm) {
    const auto o(vm.enumeration_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enumeration_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_enumeration_info));
    }

    const auto evm(*o);
    {
        std::list<std::string> namespaces(evm.namespaces());
        namespace_helper ns_helper(stream_, namespaces);
        utility_.blank_line();

        generator_class(evm);
        utility_.blank_line(2);
    }
    utility_.blank_line(2);
}

void generator_header::format_class(const file_info& vm) {
    boost::optional<class_info> o(vm.class_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    {
        const class_info& cvm(*o);
        std::list<std::string> namespaces(cvm.namespaces());
        namespace_helper ns_helper(stream_, namespaces);
        utility_.blank_line();

        generator_class(cvm);
        utility_.blank_line(2);
    }
    utility_.blank_line(2);
}

void generator_header::format(const file_info& vm) {
    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    utility_.blank_line();

    includes includes(stream_);
    includes.format(vm);

    if (vm.meta_type() == sml::meta_types::enumeration)
        format_enumeration(vm);
    else if (vm.meta_type() == sml::meta_types::pod)
        format_class(vm);

    guards.format_end();
}

} } }
