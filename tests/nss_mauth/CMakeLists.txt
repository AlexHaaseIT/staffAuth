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

# This macro adds a test executable, links it against nss_mauth and sets the
# variable test_command for use in add_test wrappers.
macro (add_test_executable testname source)
	# Add executable for testcase and link against nss_mauth.
	include_directories(../../src/libnss_mauth)
	add_executable(${testname} ${source})
	target_link_libraries(${testname} nss_mauth)

	# Set test_command for usage in mauth_valid_test
	set(test_command ${testname})
endmacro ()


# getpwnam
add_test_executable(nss_mauth_pwnam getpwnam.c)

add_test_exit("nss_valid_pwnam_RandomUser" "somerandomuser" true)


# getpwuid
add_test_executable(nss_mauth_getpwuid getpwuid.c)

math(EXPR tmp "${MAUTH_UIDMAP_MIN} - 1")
add_test_exit("nss_valid_pwuid_tolow" "${tmp}" true)
