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

#include <stdio.h>  // fclose, open_memstream
#include <stdlib.h> // free

#include <curl/curl.h> // cURL interface

/* open_memstream is available at recent GNU/Linux platforms only. To be
 * compatible with older Linux platforms, BSD and OSX (Darwin), an alternative
 * memstream implementation might be used on these platforms. The memstream
 * header file will decide, if open_memstream is available at the current
 * platform and support an alternative if needed. */
#include "memstream.h"


/** \brief Make an API request for \p url.
 *
 *
 * \param dest Pointer to a char pointer.
 * \param url API request URL.
 * \param payload JSON encoded payload. Request will be send as POST, if \p
 *  payload is not NULL.
 *
 * \return MAUTH_SUCCESS The request successed.
 * \return MAUTH_FAILURE An error occured.
 *
 * \note The allocated data will not be freed by this function. The user is
 *  responsible to free the memory.
 */
mauth_status
mauth_api_request(char **dest, const char *url, const char *payload)
{
	/* Check all function parameters, if they are valid. */
	assert(dest);
	assert(url);


	/* Initialisize cURL and set URL. */
	CURL *curl;
	CURLcode ret;

	if ((curl = curl_easy_init()) == NULL)
		return MAUTH_FAILURE;

	if ((ret = curl_easy_setopt(curl, CURLOPT_URL, url)) != CURLE_OK)
		goto curl_cleanup;


	/* If payload is not NULL, set payload as POST data to be send. */
	if (payload != NULL) {
		/* Change the HTTP query method to POST and the content type header to
		 * application/json. payload will be set as POST data. */
		if ((ret = curl_easy_setopt(curl, CURLOPT_POST, 1)) != CURLE_OK)
			goto curl_cleanup;

		struct curl_slist *header = NULL;
		if ((header = curl_slist_append(
		         header, "Content-Type: application/json")) == NULL)
			goto curl_cleanup;
		if ((ret = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header)) !=
		    CURLE_OK)
			goto curl_cleanup;

		if ((ret = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload)) !=
		    CURLE_OK)
			goto curl_cleanup;
	}


	/* Open a new memstream to use it with cURL. The memstream will allocate new
	 * memory automatically, so we don't have to manage the memory requirements
	 * for the HTTP response by ourself. If anything goes wrong, the memory and
	 * cURL instance will be freed. */
	*dest = NULL;
	size_t len;
	FILE *fd;

	if ((fd = open_memstream(dest, &len)) == NULL)
		goto curl_cleanup;

	if ((ret = curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd)) != CURLE_OK)
		goto memstream_cleanup;


	/* Perform the request, res will get the return code. If the request fails,
	 * no jump has to be performed, because the next commands are the
	 * destination for these jump labels. */
	ret = curl_easy_perform(curl);


memstream_cleanup:
	/* Close file descriptor. If cURL request failed, free the allocated memory
	 * of the memstream. */
	fclose(fd);
	if (ret != CURLE_OK) {
		free(*dest);
		*dest = NULL;
	}


curl_cleanup:
	curl_easy_cleanup(curl);

	if (ret != CURLE_OK)
		return MAUTH_FAILURE;

	return MAUTH_SUCCESS;
}
