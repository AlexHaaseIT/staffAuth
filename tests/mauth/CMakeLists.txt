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

# This macro adds a test executable, links it against mauth and sets the
# variable test_command for use in add_test wrappers.
macro (add_test_executable testname source)
	# Add executable for testcase and link against nss_mauth.
	include_directories(../../src/libmauth/header)
	add_executable(${testname} ${source})
	target_link_libraries(${testname} mauth)

	# Set test_command for usage in mauth_valid_test
	set(test_command ${testname})
endmacro ()


# valid_pwnam
add_test_executable(mauth_valid_pwnam valid_pwnam.c)

add_test_exit("mauth_valid_pwnam_NoError" "${MAUTH_USER_PREFIX}test" false)
add_test_exit("mauth_valid_pwnam_PrefixOnly" "${MAUTH_USER_PREFIX}" true)
add_test_exit("mauth_valid_pwnam_RandomUser" "somerandomuser" true)


# valid_pwuid
add_test_executable(mauth_valid_pwuid valid_pwuid.c)

add_test_exit("mauth_valid_pwuid_NoError1" "${MAUTH_UIDMAP_MIN}" false)
add_test_exit("mauth_valid_pwuid_NoError2" "${MAUTH_UIDMAP_MAX}" false)

math(EXPR tmp "(${MAUTH_UIDMAP_MAX} + ${MAUTH_UIDMAP_MIN}) / 2")
add_test_exit("mauth_valid_pwuid_NoError3" "${tmp}" false)

math(EXPR tmp "${MAUTH_UIDMAP_MIN} - 1")
add_test_exit("mauth_valid_pwuid_tolow" "${tmp}" true)

math(EXPR tmp "${MAUTH_UIDMAP_MAX} + 1")
add_test_exit("mauth_valid_pwuid_tohigh" "${tmp}" true)


# valid_grnam
add_test_executable(mauth_valid_grnam valid_grnam.c)

add_test_exit("mauth_valid_grnam_NoError" "${MAUTH_GROUP_PREFIX}test" false)
add_test_exit("mauth_valid_grnam_PrefixOnly" "${MAUTH_GROUP_PREFIX}" true)
add_test_exit("mauth_valid_grnam_RandomGroup" "somerandomgroup" true)


# valid_grgid
add_test_executable(mauth_valid_grgid valid_grgid.c)

add_test_exit("mauth_valid_grgid_NoError1" "${MAUTH_GIDMAP_MIN}" false)
add_test_exit("mauth_valid_grgid_NoError2" "${MAUTH_GIDMAP_MAX}" false)

math(EXPR tmp "(${MAUTH_GIDMAP_MAX} + ${MAUTH_GIDMAP_MIN}) / 2")
add_test_exit("mauth_valid_grgid_NoError3" "${tmp}" false)

math(EXPR tmp "${MAUTH_GIDMAP_MIN} - 1")
add_test_exit("mauth_valid_grgid_tolow" "${tmp}" true)

math(EXPR tmp "${MAUTH_UIDMAP_MAX} + 1")
add_test_exit("mauth_valid_grgid_tohigh" "${tmp}" true)
