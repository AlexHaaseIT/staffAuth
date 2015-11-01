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

#include "config.h"


/** \brief Check if \p uid is a valid uid to be authenticated by mauth.
 *
 *
 * \param uid User-ID to be validated.
 *
 * \return Returns true if \p uid is a uid to be authenticated by mauth or false
 *  if not.
 */
bool
mauth_valid_pwuid(const uid_t uid)
{
	return ((uid >= MAUTH_UIDMAP_MIN) && (uid <= MAUTH_UIDMAP_MAX));
}
