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

# Header directory for mauth doesn't need to be included, thus it is included in
# mauth root directory.

# build object library
add_library(mauth_api OBJECT
	find_server.c
	gen_string.c
	lookup_key.c
)

# Add coverage for mauth_api. Thus we link our test-cases against the shared
# library of mauth, we have to capture the data of mauth_api_pic which is
# creaded by CMake-easylib.
add_coverage(mauth_api_pic)
