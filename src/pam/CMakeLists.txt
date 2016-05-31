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

find_package(PAM REQUIRED)


# Add mauth PAM module.
add_library(mauth-pam SHARED
	pam_sm_authenticate.c
	pam_sm_setcred.c
)

add_coverage(mauth-pam)
add_sanitizers(mauth-pam)

include_directories(${PAM_INCLUDE_DIR} ../libmauth)

target_link_libraries(mauth-pam mauth pam)

set_target_properties(mauth-pam PROPERTIES OUTPUT_NAME "mauth" PREFIX "pam_")

# PAM modules have the fixed install path /lib/security, /lib64/security or
# /lib/<triplet>/security for multiarch installations. Instead of installing it
# to the CMAKE_INSTALL_PREFIX path, we'll always install it to the original PAM
# location.
# To not break local builds, the CMAKE_INSTALL_PREFIX_PAM must be set explictly
# to "/", otherwise the default CMAKE_INSTALL_PREFIX will be used.
if (NOT CMAKE_INSTALL_PREFIX_PAM)
	set(CMAKE_INSTALL_PREFIX_PAM "")
endif ()
install(TARGETS mauth-pam
	LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX_PAM}${CMAKE_INSTALL_LIBDIR}")
