# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
add_custom_target(codegen)

set(dogen_dir "${CMAKE_BINARY_DIR}/stage/bin/")
set(dogen_binary "${dogen_dir}/dogen_knitter")
set(dogen_version "")
set(use_latest_knitter FALSE)
execute_process(
    COMMAND ${dogen_binary} --version
    COMMAND head -n1
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    OUTPUT_VARIABLE dogen_version
    RESULT_VARIABLE ret_var
    OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "Using: ${dogen_version}")

set(target sml)
add_custom_target(codegen_${target}
    COMMENT "Generating SML model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/schema.dia,dogen::dynamic
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-cmakelists
    --cpp-disable-eos-serialization
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target dia)
add_custom_target(codegen_${target}
    COMMENT "Generating Dia model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-eos-serialization
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target config)
add_custom_target(codegen_${target}
    COMMENT "Generating Config model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-eos-serialization
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target cpp)
add_custom_target(codegen_${target}
    COMMENT "Generating C++ model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/sml.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/formatters.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-eos-serialization
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target database)
add_custom_target(codegen_${target}
    COMMENT "Generating database model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/test_models
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-enable-facet odb
    --cpp-disable-eos-serialization
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*CMakeLists.txt
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*sql
    --ignore-files-matching-regex .*-odb.*
    --verbose
    --delete-extra-files
    --external-module-path dogen::test_models)
if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target knit)
add_custom_target(codegen_${target}
    COMMENT "Generating knit model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/sml.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/cpp.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-eos-serialization
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target dia_to_sml)
add_custom_target(codegen_${target}
    COMMENT "Generating Dia to SML model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dia.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/sml.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-cmakelists
    --cpp-disable-eos-serialization
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target cpp_formatters)
add_custom_target(codegen_${target}
    COMMENT "Generating C++ Formatters model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dia.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/sml.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/cpp.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/formatters.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-cmakelists
    --cpp-disable-eos-serialization
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)

if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target sml_to_cpp)
add_custom_target(codegen_${target}
    COMMENT "Generating SML to C++ model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dia.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/sml.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/cpp.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-eos-serialization
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)

if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target formatters)
add_custom_target(codegen_${target}
    COMMENT "Generating the Formatters Model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-eos-serialization
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/file_formatter_interface_io.hpp
    --ignore-files-matching-regex .*/repository_io.hpp
    --ignore-files-matching-regex .*/transformer_interface_io.hpp
    --ignore-files-matching-regex .*/file_formatter_interface_io.cpp
    --ignore-files-matching-regex .*/repository_io.cpp
    --ignore-files-matching-regex .*/transformer_interface_io.cpp
    --verbose
    --delete-extra-files
    --external-module-path dogen)

if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target frontend)
add_custom_target(codegen_${target}
    COMMENT "Generating Frontend model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dia.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dia_to_sml.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/sml.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-cmakelists
    --cpp-disable-eos-serialization
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target backend)
add_custom_target(codegen_${target}
    COMMENT "Generating Backend model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/sml.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/formatters.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-cmakelists
    --cpp-disable-eos-serialization
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target schema)
add_custom_target(codegen_${target}
    COMMENT "Generating Dynamic Schema model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/dynamic
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-cmakelists
    --cpp-disable-eos-serialization
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen::dynamic)
if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})

set(target expansion)
add_custom_target(codegen_${target}
    COMMENT "Generating Dynamic Expansion model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/schema.dia,dogen::dynamic
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/sml.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/dynamic
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-cmakelists
    --cpp-disable-eos-serialization
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen::dynamic)
if(use_latest_knitter)
    add_dependencies(codegen_${target} knitter)
endif()
add_dependencies(codegen codegen_${target})
