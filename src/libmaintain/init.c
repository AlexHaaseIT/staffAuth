/* This file is part of staffAuth.
 *
 * staffAuth is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see
 *
 *  http://www.gnu.org/licenses/
 *
 * Copyright (C)
 *  2015 Alexander Haase IT Services <support@alexhaase.de>
 */

#include <maintain.h>

#include <curl/curl.h>


/** \brief This function sets up the program environment that libmaintain needs.
 *
 * \details This function must be called at least once before any other function
 *  of libmaintain will be called. It sets up the environment that is needed by
 *  all functions of libmaintain.
 *
 *
 * \note This function is not thread safe. You must not call it when any other
 *  thread in the program is running. You should call it before your threads
 *  will be initialized. This function calls functions which are not thread
 *  safe, so it could conflict with other threads.
 *
 *
 * \return If this function returns non-zero, something went wrong and you
 *  cannot use the other functions of libmaintain.
 */
int
maintain_init()
{
	// init cURL environment
	if (curl_global_init(CURL_GLOBAL_DEFAULT) != 0)
		return -1;

	// return success
	return 0;
}
