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

#include "nss_mauth.h"

#include <stdio.h>  // printf
#include <stdlib.h> // free

#include <mauth.h> // mauth functions


/** \brief Get user by \p name.
 */
enum nss_status
_nss_mauth_getpwnam_r(const char *name, struct passwd *pwd, char *buffer,
                      size_t bufsize, int *errnop)
{
	/* Check if name is a valid user authenticated by mauth. */
	if (!mauth_valid_pwnam(name))
		return NSS_STATUS_NOTFOUND;

	/* Generate key for mauth server request. */
	char *key = mauth_gen_string("user/%s/passwd", name);
	printf("key: %s\n", key);


	mauth_lookup(key);
	free(key);

	return NSS_STATUS_NOTFOUND;
}


/** \brief Get user by \p uid.
 */
enum nss_status
_nss_mauth_getpwuid_r(uid_t uid, struct passwd *pwd, char *buffer,
                      size_t bufsize, int *errnop)
{
	if (!mauth_valid_pwuid(uid))
		return NSS_STATUS_NOTFOUND;

	return NSS_STATUS_NOTFOUND;
}
