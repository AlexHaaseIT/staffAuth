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
#include <ctype.h>  // isdigit
#include <stddef.h> // NULL

#include <json-c/json.h> // JSON-C interface

#include "mauth-internal.h"


/** \brief Verify one time password \p token via the mauth API.
 *
 * \details This function is used to authenticate the user additionally to his
 *  SSH key with a verification code (a one time password). The code will not be
 *  verified at the local machine, but by the mauth API.
 *
 *
 * \param mh \ref mauth handle.
 * \param token One time password to verify.
 * \param keyid Key ID used for SSH authentication.
 *
 * \return \ref MAUTH_SUCCESS \p token is valid.
 * \return \ref MAUTH_FAILURE \p token is invalid.
 * \return \ref MAUTH_ERR An error happend inside the function.
 * \return \ref MAUTH_ERR_IO Network is unavailable.
 */
mauth_status
mauth_verify_otp(mauth *mh, const char *token, const char *keyid)
{
	/* Assert parameters. mh and token MUST NOT be NULL. */
	assert(mh);
	assert(token);
	assert(keyid);


	/* If the entered token does not match the requirements for one time pass-
	 * words as defined in RFC 6238, or if token is an empty string, abort
	 * immediately before asking the mauth API server, if the token is valid. */
	if (*token == '\0')
		return MAUTH_FAILURE;

	for (const char *p = token; *p; p++)
		if (!isdigit(*p))
			return MAUTH_FAILURE;


	/* Create a new JSON object to send it to the mauth API server. The request
	 * must contain the keyid and token properties. If the request payload could
	 * not be generated, abort the function and mark it as internal error. */
	json_object *pjobj = json_object_new_object();
	json_object_object_add(pjobj, "keyid", json_object_new_string(keyid));
	json_object_object_add(pjobj, "token", json_object_new_string(token));

	const char *payload =
	    json_object_to_json_string_ext(pjobj, JSON_C_TO_STRING_NOZERO);
	if (payload == NULL)
		goto err_mauth_verify_otp;


	/* Make an API request to endpoint /verify/otp to verify the one time
	 * password token. */
	char *url = mauth_api_url(mh, "verify/otp");
	if (url == NULL)
		goto err_mauth_verify_otp;

	char *data;
	switch (mauth_api_request(&data, url, payload)) {
		/* Destroy the payload JSON object. It is not needed anymore, so the
		 * memory will be released here to make the error handling below more
		 * simple. */
		json_object_put(pjobj);

		case MAUTH_SUCCESS: {
			json_object *rjobj = json_tokener_parse(data);
			if (json_object_get_type(rjobj) == json_type_object) {
				json_object *iter;
				if (json_object_object_get_ex(rjobj, "verified", &iter))
					if (json_object_get_boolean(iter)) {
						json_object_put(rjobj);
						return MAUTH_SUCCESS;
					}
			}
			json_object_put(rjobj);

			/* If the response JSON object was invalid, we will not break here
			 * to set ret to MAUTH_ERR_IO. */
		}

		case MAUTH_FAILURE: return MAUTH_ERR_IO;
		default: break;
	}


err_mauth_verify_otp:
	return MAUTH_ERR;
}
