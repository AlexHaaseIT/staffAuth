# This file is part of mauth.
#
# mauth is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see
#
#   http://www.gnu.org/licenses/
#
#
# Copyright (C)
#   2015 Alexander Haase IT Services <support@alexhaase.de>
#


# minimum required cmake version
cmake_minimum_required(VERSION 2.8.11)


#
# project information
#
if (${CMAKE_MAJOR_VERSION} EQUAL 3)
	project("mauth" LANGUAGES C)
else ()
	project("mauth" C)
endif ()


# choose new behaviour for CMP0042
# see http://www.cmake.org/cmake/help/v3.0/policy/CMP0042.html for more details
if (POLICY CMP0042)
	cmake_policy(SET CMP0042 NEW)
endif (POLICY CMP0042)


#
# cmake configuration
#
set(CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/cmake"
	"${CMAKE_SOURCE_DIR}/externals/useLATEX"
	"${CMAKE_SOURCE_DIR}/externals/CMake-sanitizers/cmake"
	"${CMAKE_SOURCE_DIR}/externals/CMake-codecov/cmake"
	"${CMAKE_SOURCE_DIR}/externals/CMake-CChelper/cmake"
	${CMAKE_MODULE_PATH})

# enable code coverage
find_package(codecov)

# set mauth version
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION
	${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})


#
# recurse into subdirectories
#
add_subdirectory(doc)
add_subdirectory(conf)
add_subdirectory(src)


# evaluate coverage data
coverage_evaluate()
