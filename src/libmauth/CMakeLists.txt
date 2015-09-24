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

# include header directory
include_directories(header)


# search for cURL
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

# build library
add_library(mauth SHARED
	init.c
	cleanup.c
	is_staff.c
)

# link against cURL
target_link_libraries(mauth ${CURL_LIBRARIES})
