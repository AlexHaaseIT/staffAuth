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
# for libxml2.

find_package(PkgConfig)
pkg_check_modules(PC_LIBCONFIG QUIET libconfig)

find_path(LIBCONFIG_INCLUDE_DIR libconfig.h
	HINTS ${PC_LIBCONFIG_INCLUDEDIR} ${PC_LIBCONFIG_INCLUDE_DIRS})

find_library(LIBCONFIG_LIBRARY NAMES config libconfig
	HINTS ${PC_LIBCONFIG_LIBDIR} ${PC_LIBCONFIG_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libconfig DEFAULT_MSG LIBCONFIG_LIBRARY
	LIBCONFIG_INCLUDE_DIR)

mark_as_advanced(LIBCONFIG_INCLUDE_DIR LIBCONFIG_LIBRARY)
