/* This file is part of mauth.
 *
 * mauth is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see
 *
 *  http://www.gnu.org/licenses/
 *
 *
 * Copyright (C)
 *  2015-2016 Alexander Haase IT Services <support@alexhaase.de>
 */

#include "mauth-internal.h"

#define _GNU_SOURCE // required for asprintf in stdio.h
#include <assert.h> // assert
#include <stdio.h>  // asprintf


/** \brief Generate URL for API \p endpoint.
 *
 *
 * \param mh \ref mauth handle.
 * \param endpoint API endpoint to be used.
 *
 * \return On success this function will return a pointer to a new allocated
 *  array of char containing the URL. On any failure NULL will be returned.
 *
 * \note The allocated data will not be freed by this function. The calling
 *  function is responsible to free the memory.
 */
char *
mauth_api_url(mauth *mh, const char *endpoint)
{
	/* Check all variables, if they are valid. In addition to the function
	 * parameters check if a server was set in mauth handle. */
	assert(mh);
	assert(mh->server);
	assert(endpoint);


	/* Concatenate server and API endpoint. If everything went fine, return the
	 * pointer to new allocated memory. Otherwise return NULL. */
	char *url;
	if (asprintf(&url, "%s/%s", mh->server, endpoint) > 0)
		return url;
	else
		return NULL;
}
