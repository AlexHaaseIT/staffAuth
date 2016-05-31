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

# This CMake module is based on the CMake tutorial on "How to find libraries"
# for libxml2. Thus libpam does not support pkgconfig, pkgconfig will be skipped
# in this module.

find_path(PAM_INCLUDE_DIR security/pam_modules.h)

find_library(PAM_LIBRARY NAMES pam libpam)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PAM DEFAULT_MSG PAM_LIBRARY PAM_INCLUDE_DIR)

mark_as_advanced(PAM_INCLUDE_DIR PAM_LIBRARY)
