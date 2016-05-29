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

#include "mauth.h"

#include <assert.h> // assert
#include <stddef.h> // NULL


/** \brief Initialize \ref mauth handle \p mh.
 *
 * \details This function will initialize the \ref mauth handle \mh to its
 *  default values.
 *
 *
 * \param mh \ref mauth handle.
 *
 * \info \ref mauth_destroy must be called for each initialized \ref mauth
 *  handle after usage.
 */
void
mauth_init(mauth *mh)
{
	/* Assert required arguments. */
	assert(mh);


	mh->server = NULL;
}
