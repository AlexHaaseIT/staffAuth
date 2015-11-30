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

#include "config.h" // MAUTH_GIDMAP_MIN, MAUTH_GIDMAP_MAX


/** \brief Check if \p gid is a valid gid to be authenticated by mauth.
 *
 *
 * \param gid Group-ID to be validated.
 *
 * \return Returns true if \p gid is a gid to be authenticated by mauth or false
 *  if not.
 */
bool
mauth_valid_grgid(gid_t gid)
{
	return ((gid >= MAUTH_GIDMAP_MIN) && (gid <= MAUTH_GIDMAP_MAX));
}
