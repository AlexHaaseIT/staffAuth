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

macro(mauth_valid_test testname command argument expected_stdout)
	add_test(NAME ${testname} COMMAND ${command} ${argument})
	set_tests_properties(${testname}
		PROPERTIES PASS_REGULAR_EXPRESSION ${expected_stdout}
	)
endmacro()


#
# valid_pwnam
#

# add executable
include_directories(../../src/libmauth/header)
add_executable(mauth_valid_pwnam valid_pwnam.c)
target_link_libraries(mauth_valid_pwnam mauth)

mauth_valid_test("mauth_valid_pwnam_NoError" mauth_valid_pwnam
	"${MAUTH_USER_PREFIX}testuser" "valid")

mauth_valid_test("mauth_valid_pwnam_PrefixOnly" mauth_valid_pwnam
	"${MAUTH_USER_PREFIX}" "invalid")

mauth_valid_test("mauth_valid_pwnam_RandomUser" mauth_valid_pwnam
	"somerandomuser" "invalid")


#
# valid_pwuid
#

# add executable
include_directories(../../src/libmauth/header)
add_executable(mauth_valid_pwuid valid_pwuid.c)
target_link_libraries(mauth_valid_pwuid mauth)

mauth_valid_test("mauth_valid_pwuid_NoError1" mauth_valid_pwuid
	"${MAUTH_UIDMAP_MIN}" "valid")

mauth_valid_test("mauth_valid_pwuid_NoError2" mauth_valid_pwuid
	"${MAUTH_UIDMAP_MAX}" "valid")

math(EXPR tmp "(${MAUTH_UIDMAP_MAX} - ${MAUTH_UIDMAP_MIN}) / 2")
mauth_valid_test("mauth_valid_pwuid_NoError3" mauth_valid_pwuid "${tmp}" "valid")

math(EXPR tmp "${MAUTH_UIDMAP_MIN} - 1")
mauth_valid_test("mauth_valid_pwuid_tolow" mauth_valid_pwuid "${tmp}" "invalid")

math(EXPR tmp "${MAUTH_UIDMAP_MAX} + 1")
mauth_valid_test("mauth_valid_pwuid_tohigh" mauth_valid_pwuid "${tmp}" "invalid")
