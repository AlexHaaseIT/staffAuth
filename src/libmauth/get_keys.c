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
#include <stdlib.h> // free

#include <json-c/json.h> // JSON-C interface

#include "mauth-internal.h"


/** \brief Get ssh-keys via the mauth API.
 *
 *
 * \param mh \ref mauth handle.
 * \param list Pointer to \ref mauth_keylist pointer.
 *
 * \return \ref MAUTH_SUCCESS \p list contains all found keys.
 * \return \ref MAUTH_ERR An internal error happened.
 * \return \ref MAUTH_ERR_IO Error retrieving keys from mauth API server.
 */
mauth_status
mauth_get_keys(mauth *mh, mauth_keylist **list)
{
	/* Assert required arguments. */
	assert(mh);
	assert(list);


	/* Get the endpoint URL. */
	char *url = mauth_api_url(mh, "keys");
	if (url == NULL)
		return MAUTH_ERR;

	/* Get all SSH keys by the mauth API. */
	char *data;
	mauth_status ret;
	if ((ret = mauth_api_request(&data, url, NULL)) != MAUTH_SUCCESS)
		return ret;

	free(url);

	/* If the response is not empty, parse the response data and feed the
	 * keylist. */
	if (data != NULL) {
		json_object *jobj = json_tokener_parse(data);
		if (jobj == NULL)
			goto ret_mauth_get_keys;

		enum json_type type = json_object_get_type(jobj);
		if (type != json_type_array)
			goto ret_mauth_get_keys;

		size_t n = json_object_array_length(jobj);
		size_t i;
		json_object *iter, *buff;
		for (i = 0; i < n; i++) {
			iter = json_object_array_get_idx(jobj, i);

			const char *key, *hash;
			if (json_object_object_get_ex(iter, "key", &buff)) {
				key = json_object_get_string(buff);
				if (json_object_object_get_ex(iter, "hash", &buff)) {
					hash = json_object_get_string(buff);

					*list = mauth_keylist_add(*list, key, hash);
				}
			}
		}

		json_object_put(jobj);
	}

	free(data);
	return MAUTH_SUCCESS;


ret_mauth_get_keys:
	free(data);
	return MAUTH_ERR;
}
