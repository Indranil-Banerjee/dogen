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
#ifndef DOGEN_DYNAMIC_SCHEMA_TYPES_REPOSITORY_WORKFLOW_HPP
#define DOGEN_DYNAMIC_SCHEMA_TYPES_REPOSITORY_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/dynamic/schema/types/field_definition.hpp"

namespace dogen {
namespace dynamic {
namespace schema {

/**
 * @brief Produces a repository.
 */
class repository_workflow {
private:
    /**
     * @brief Hydrate all files in all of the supplied directories.
     */
    std::list<field_definition> hydrate_directories_activity(
        const std::forward_list<boost::filesystem::path>& dirs) const;

    /**
     * @brief Index fields into the repository.
     */
    repository create_repository_activity(
        const std::list<field_definition>& fds) const;

public:
    /**
     * @brief Generate the repository with the data available in the
     * supplied directories.
     */
    repository execute(
        const std::forward_list<boost::filesystem::path>& dirs) const;
};

} } }

#endif
