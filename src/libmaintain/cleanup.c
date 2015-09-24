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


/** \brief This function cleans up the environment of libmaintain.
 *
 * \details This function releases resources acquired by
 *  \ref maintain_init. You should call it once for each call you make to
 *  \ref maintain_init.
 *
 *
 * \note This function is not thread safe. You must not call it when any other
 *  thread in the program is running. You should call it before your threads
 *  will be initialized. This function calls functions which are not thread
 *  safe, so it could conflict with other threads.
 *
 *
 * \return This function returnes no value.
 */
void
maintain_cleanup()
{
	// cleanup cURL environment
	curl_global_cleanup();
}
