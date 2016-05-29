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

#include <assert.h> // assert
#include <stddef.h> // NULL
#include <stdlib.h> // malloc
#include <string.h> // strdup


/** \brief Append SSH key to \ref mauth_keylist \p list.
 *
 *
 * \param list Pointer to current list.
 * \param key SSH public key.
 * \param hash Public key hash in SHA256 format.
 *
 * \return Pointer to new list head or NULL on any failure.
 */
MAUTH_INTERNAL mauth_keylist *
mauth_keylist_add(mauth_keylist *list, const char *key, const char *hash)
{
	/* Assert required arguments. */
	assert(key);
	assert(hash);


	/* Allocate memory for new list head. */
	mauth_keylist *n = malloc(sizeof(mauth_keylist));
	if (n == NULL)
		return NULL;

	n->key = strdup(key);
	n->hash = strdup(hash);
	n->next = list;

	return n;
}
