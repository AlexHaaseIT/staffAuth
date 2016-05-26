# This file is part of mauth.
#
# mauth is free software: you can redistribute it and/or modify it under the
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

# Set some paths for mauth. We will use the paths defined by GNUInstallDirs. If
# the path is not absolute, we will preprend the install prefix. This ensures
# most compatibility with dpkg and non-dpkg installations.
include(GNUInstallDirs)

set (MAUTH_CONFIG_DIR "${CMAKE_INSTALL_SYSCONFDIR}/mauth")
if (NOT IS_ABSOLUTE ${MAUTH_CONFIG_DIR})
	set (MAUTH_CONFIG_DIR "${CMAKE_INSTALL_PREFIX}/${MAUTH_CONFIG_DIR}")
endif ()

message(STATUS "Predefined paths:")
message(STATUS "  config: ${MAUTH_CONFIG_DIR}")


# recurse into subdirectories
add_subdirectory(keys)
