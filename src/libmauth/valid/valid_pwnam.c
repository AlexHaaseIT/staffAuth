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
#include <string.h> // strlen, strncmp

#include "config.h" // MAUTH_USER_PREFIX


/** \brief Check if \p name is a valid username to be authenticated by mauth.
 *
 *
 * \param login User login to be validated.
 *
 * \return Returns true if \p login is a user to be authenticated by mauth or
 *  false if not.
 */
bool
mauth_valid_pwnam(const char *login)
{
	/* login must not be NULL. */
	assert(login);

	/* Compare login with prefix for users that will be authenticated by mauth.
	 * If the prefix matches and login is longer than MAUTH_USER_PREFIX, login
	 * is valid. */
	size_t len = strlen(MAUTH_USER_PREFIX);
	if (strncmp(login, MAUTH_USER_PREFIX, len) == 0)
		if (*(login + len) != '\0')
			return true;

	return false;
}
