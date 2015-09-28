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

#include <stdio.h>
#include <string.h>

#include <nss.h>
#include <pwd.h>


/** \brief Get user by \p name.
 */
enum nss_status
_nss_mauth_getpwnam_r(const char *name, struct passwd *pwd, char *buffer,
                      size_t bufsize, int *errnop)
{
	// check if this is a request for our debug account
	if (strcmp(name, "adm_test") != 0)
		return NSS_STATUS_NOTFOUND;

	// set pwd to zero
	struct passwd pwd_zero = {0};
	*pwd = pwd_zero;

	printf("getpwnam_r for %s\n", name);
	printf("buffer size: %lu\n", bufsize);

	strcpy(buffer, name);
	pwd->pw_name = buffer;

	return NSS_STATUS_FOUND;
}


/** \brief Get user by \p uid.
 */
enum nss_status
_nss_mauth_getpwuid_r(uid_t uid, struct passwd *pwd, char *buffer,
                      size_t bufsize, int *errnop)
{
	printf("getpwuid_r for %u\n", uid);

	return NSS_STATUS_NOTFOUND;
}
