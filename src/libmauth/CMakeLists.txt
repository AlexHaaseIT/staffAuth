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

find_package(CURL REQUIRED)
find_package(JSON-C REQUIRED)
find_package(Libconfig REQUIRED)


# Set some paths for mauth. We will use the paths defined by GNUInstallDirs. If
# the path is not absolute, we will preprend the install prefix. This ensures
# most compatibility with dpkg and non-dpkg installations.
set (MAUTH_CONFIG_DIR "${CMAKE_INSTALL_SYSCONFDIR}/mauth")
if (NOT IS_ABSOLUTE ${MAUTH_CONFIG_DIR})
	set (MAUTH_CONFIG_DIR "${CMAKE_INSTALL_PREFIX}/${MAUTH_CONFIG_DIR}")
endif ()


# Configure files.
configure_file(cmake-config.h.in cmake-config.h)


# Add libmauth.
add_library(mauth SHARED
	init.c
	destroy.c

	keylist_free.c
	set_login.c

	get_keys.c
	verify_otp.c

	api_url.c
	api_request.c
	memstream.c
	keylist_add.c
)

add_coverage(mauth)
add_sanitizers(mauth)

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CURL_INCLUDE_DIRS}
	${JSON-C_INCLUDE_DIR}
	${LIBCONFIG_INCLUDE_DIR}
)

target_link_libraries(mauth PRIVATE
	${CURL_LIBRARIES}
	${JSON-C_LIBRARY}
	${LIBCONFIG_LIBRARY}
)

set_target_properties(mauth PROPERTIES
	VERSION   ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}
)

install(TARGETS mauth LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(FILES mauth.h DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
