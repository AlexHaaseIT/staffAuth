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

# This macro adds a testcase to test the exit status of test_command.
# test_command must be set before calling this macro. For usual this variable
# will be set ba another macro to build the testcase
macro(add_test_exit testname test_argument will_fail)
	add_test(NAME ${testname} COMMAND ${test_command} ${test_argument})
	if (${will_fail})
		set_tests_properties(${testname} PROPERTIES WILL_FAIL true)
	endif ()
endmacro()


# recurse into subdirectories
add_subdirectory(mauth)
add_subdirectory(nss_mauth)
