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

#include "config.h" // MAUTH_GROUP_PREFIX


/** \brief Check if \p name is a valid group to be authenticated by mauth.
 *
 *
 * \param name Group to be validated.
 *
 * \return Returns true if \p name is a group to be authenticated by mauth or
 *  false if not.
 */
bool
mauth_valid_grnam(const char *name)
{
	/* name must not be NULL. */
	assert(name);

	/* Compare name with prefix for groups that will be authenticated by mauth.
	 * If the prefix matches and name is longer than MAUTH_USER_PREFIX, name is
	 * valid. */
	size_t len = strlen(MAUTH_GROUP_PREFIX);
	if (strncmp(name, MAUTH_GROUP_PREFIX, len) == 0)
		if (*(name + len) != '\0')
			return true;

	return false;
}
