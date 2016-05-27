# This file is part of staffAuth.
#
# staffAuth is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see
#
#   http://www.gnu.org/licenses/
#
#
# Copyright (C)
#   2015-2016 Alexander Haase IT Services <support@alexhaase.de>
#

# This CMake module is based on the CMake tutorial on "How to find libraries"
# for libxml2 and FindJSON-C.cmake by the cshark project.

find_package(PkgConfig)
pkg_check_modules(PC_JSON-C QUIET libjson-c)

find_path(JSON-C_INCLUDE_DIR json.h
	HINTS ${PC_JSON-C_INCLUDEDIR} ${PC_JSON-C_INCLUDE_DIRS}
	PATH_SUFFIXES json-c)

find_library(JSON-C_LIBRARY NAMES json-c libjson-c
	HINTS ${PC_JSON-C_LIBDIR} ${PC_JSON-C_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JSON-C DEFAULT_MSG JSON-C_LIBRARY
	JSON-C_INCLUDE_DIR)

mark_as_advanced(JSON-C_INCLUDE_DIR JSON-C_LIBRARY)
