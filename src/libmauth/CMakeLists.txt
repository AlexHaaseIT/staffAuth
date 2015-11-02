# This file is part of staffAuth.
#
# staffAuth is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
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

# default values for config.h
set(MAUTH_UIDMAP_MIN "65537" CACHE STRING "Minimum UID for mauth users.")
set(MAUTH_UIDMAP_MAX "99999" CACHE STRING "Maximum UID for mauth users.")
set(MAUTH_USER_PREFIX "adm_" CACHE STRING "Prefix for mauth users.")

set(MAUTH_GIDMAP_MIN "65537" CACHE STRING "Minimum GID for mauth groups.")
set(MAUTH_GIDMAP_MAX "99999" CACHE STRING "Maximum GID for mauth groups.")
set(MAUTH_GROUP_PREFIX "adm_" CACHE STRING "Prefix for mauth groups.")

# configure config.h
configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})


# include header directory
include_directories(header)


# recurse into subdirectories
add_subdirectory(valid)


# search for cURL
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

# build library
add_library(mauth SHARED
	$<TARGET_OBJECTS:mauth_valid>

	init.c
	cleanup.c
)
add_coverage(mauth)

# link against cURL
target_link_libraries(mauth ${CURL_LIBRARIES})
