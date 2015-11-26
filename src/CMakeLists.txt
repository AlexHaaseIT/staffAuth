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

include(easylib)   # setup easylib
include(CChelper)  # enable compiler warnings
find_package(ASan) # search for address sanitizer

# enable C99
find_package(C99 REQUIRED)
set(CMAKE_C_FLAGS "${C99_FLAGS} ${CMAKE_C_FLAGS}")

# recurse into subdirectories
add_subdirectory(libmauth)
add_subdirectory(libnss_mauth)
