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

include_directories(../../src/libmauth/header)
add_executable(is_staff_username is_staff_username.c)
target_link_libraries(is_staff_username mauth)


# First test with valid user.
add_test(NAME mauth_valid_user_NoError
	COMMAND is_staff_username "${MAUTH_USER_PREFIX}testuser"
)
set_tests_properties(mauth_valid_user_NoError
	PROPERTIES PASS_REGULAR_EXPRESSION "valid"
)

# Only prefix as user should fail.
add_test(NAME mauth_valid_user_PrefixOnly
	COMMAND is_staff_username "${MAUTH_USER_PREFIX}"
)
set_tests_properties(mauth_valid_user_PrefixOnly
	PROPERTIES PASS_REGULAR_EXPRESSION "invalid"
)

# Random user should fail
add_test(NAME mauth_valid_user_RandomUser
	COMMAND is_staff_username "somerandomuser"
)
set_tests_properties(mauth_valid_user_RandomUser
	PROPERTIES PASS_REGULAR_EXPRESSION "invalid"
)
