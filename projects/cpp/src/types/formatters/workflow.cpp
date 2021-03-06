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
#include <iterator>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formattables/formattable_visitor.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formatters.workflow"));

}

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Responsible for dispatching the formattable to the
 * appropriate formatters.
 */
class dispatcher final : public formattables::formattable_visitor {
public:
    explicit dispatcher(const container& c);
    ~dispatcher() noexcept { }

public:
    using formattable_visitor::visit;
    void visit(const formattables::class_info& c) override;
    void visit(const formattables::enum_info& e) override;
    void visit(const formattables::exception_info& e) override;
    void visit(const formattables::registrar_info& r) override;
    void visit(const formattables::namespace_info& n) override;
    void visit(const formattables::visitor_info& v) override;
    void visit(const formattables::new_class_info& c) override;
    void visit(const formattables::concept_info& c) override;
    void visit(const formattables::primitive_info& p) override;

public:
    /**
     * @brief Converts the supplied entity into all supported
     * representations.
     */
    std::forward_list<dogen::formatters::file>
    format(const formattables::formattable& f);

private:
    const container& container_;
    std::forward_list<dogen::formatters::file> files_;
};

dispatcher::dispatcher(const container& c) : container_(c) { }

void dispatcher::visit(const formattables::class_info& c) {
    for (const auto f : container_.class_formatters())
        files_.push_front(f->format(c));
}

void dispatcher::visit(const formattables::enum_info& /*e*/) {
}

void dispatcher::visit(const formattables::exception_info& /*e*/) {
}

void dispatcher::visit(const formattables::registrar_info& /*r*/) {
}

void dispatcher::visit(const formattables::namespace_info& /*n*/) {
}

void dispatcher::visit(const formattables::visitor_info& /*v*/) {
}

void dispatcher::visit(const formattables::new_class_info& /*c*/) {
}

void dispatcher::visit(const formattables::concept_info& /*c*/) {
}

void dispatcher::visit(const formattables::primitive_info& /*p*/) {
}

std::forward_list<dogen::formatters::file>
dispatcher::format(const formattables::formattable& f) {
    f.accept(*this);
    return files_;
}

std::shared_ptr<cpp::formatters::registrar> workflow::registrar_;

cpp::formatters::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::formatters::registrar>();

    return *registrar_;
}

void workflow::validate() const {
    BOOST_LOG_SEV(lg, debug) << "Validating workflow.";

    registrar().validate();
    const auto& c(registrar().formatter_container());
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(
                                 c.class_formatters().begin(),
                                 c.class_formatters().end())
                             << " registered class formatter(s): ";

    BOOST_LOG_SEV(lg, debug) << "Listing all class formatters.";
    for (const auto& f : c.class_formatters())
        BOOST_LOG_SEV(lg, debug) << "Name: '" << f->formatter_name() << "'";

    BOOST_LOG_SEV(lg, debug) << "Finished validating workflow.";
}

std::forward_list<dogen::formatters::file>
workflow::execute(const std::forward_list<
        std::shared_ptr<formattables::formattable>
        >& f)
    const {
    dispatcher d(registrar().formatter_container());
    std::forward_list<dogen::formatters::file> r;
    for (const auto sp : f)
        r.splice_after(r.before_begin(), d.format(*sp));
    return r;
}

} } }
