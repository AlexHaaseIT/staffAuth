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

#include <mauth.h>

#include <assert.h> // assert
#include <stdio.h>


/* The maximum length of a domain is limited to 255 bytes as defined in RFC 1034
 * section 3.1. */
#define SERVER_BUFFER_LENGTH 255


/** \brief
 */
char *
mauth_lookup_key(const char *key)
{
	/* key must not be NULL. */
	assert(key);

	/* Search for local mauth server in hosts FQDN domains. If no server was
	 * found return NULL. */
	char server[SERVER_BUFFER_LENGTH];
	if (mauth_find_server(server, SERVER_BUFFER_LENGTH) == 0)
		return NULL;

	printf("server: %s\n", server);

	return false;
}
