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

#include <stdlib.h>


/** \brief Destroy \ref mauth handle \p mh.
 *
 * \details This function will destroy the \ref mauth handle \mh. Memory
 *  allocated by mauth functions will be freed. The \ref mauth struct \p mh will
 *  NOT be freed, because in most times it was not dynamic allocated.
 *
 *
 * \param mh \ref mauth handle.
 *
 * \info \ref mauth_init must be called for each \ref mauth handle before
 *  calling \ref mauth_destroy.
 */
void
mauth_destroy(mauth *mh)
{
	free(mh->server);
}
