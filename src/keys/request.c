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

#include "keys.h"

#include <assert.h> // assert
#include <stdio.h>  // open_memstream, fprintf
#include <stdlib.h> // free

#include <curl/curl.h> // cURL interface

/* open_memstream is available at recent GNU/Linux platforms only. To be
 * compatible with older Linux platforms, BSD and OSX (Darwin), an alternative
 * memstream implementation might be used on these platforms. The memstream
 * header file will decide, if open_memstream is available at the current
 * platform and support an alternative if needed. */
#include "memstream.h"


/** \brief Generate URL for API request.
 *
 *
 * \param config Pointer to \ref keys_config struct.
 *
 * \return On success this function will return a pointer to a new allocated
 *  array of char containing the URL. On any failure NULL will be returned.
 *
 * \note The allocated data will not be freed by this function. The user is
 *  responsible to free the memory.
 */
static char *
staffauth_keys_genurl(keys_config *config)
{
	/* Check all variables, if they are valid. In addition to the function
	 * parameters check if a server was set in config. */
	assert(config->server);


	/* Instead of maintianing our own implementation of dynamic buffer
	 * allocation, use memstream of libc. Memstream may not be available at any
	 * platform, but the platforms supported by staffAuth support memstream. */
	char *buffer;
	size_t len;
	FILE *fd = open_memstream(&buffer, &len);
	if (fd == NULL)
		return NULL;

	/* Append API target ssh-keys to server domain defined in config. https://
	 * will not be prefixed, thus communication at localhost may use http for
	 * testing purposes. */
	int ret = fprintf(fd, "%s/ssh-keys", config->server);
	fclose(fd);

	/* If fprintf failed, free allocated memory buffer and return a NULL pointer
	 * to indicate an error. */
	if (ret < 0) {
		free(buffer);
		return NULL;
	}

	return buffer;
}


/** \brief Make an API request for \p config.
 *
 *
 * \param config Pointer to \ref keys_config struct.
 *
 * \return On success this function will return a pointer to a new allocated
 *  array of char containing the response. On any failure NULL will be returned.
 *
 * \note The allocated data will not be freed by this function. The user is
 *  responsible to free the memory.
 */
char *
staffauth_keys_request(keys_config *config)
{
	// Check all function parameters, if they are valid.
	assert(config);


	/* Define some variables at the beginning of the function, thus they should
	 * be set on a default value, if some code in this function fails and a jump
	 * to the end of the function will be performed. */
	CURLcode ret = CURLE_OK;
	CURL *curl = NULL;
	char *buffer;
	size_t len;

	// initialisize cURL.
	if ((curl = curl_easy_init()) == NULL)
		return NULL;

	/* Generate a valid URL for the following cURL request. The URL will be
	 * stored in a new allocated buffer and will be freed just after transfering
	 * to cURL. */
	char *url = staffauth_keys_genurl(config);
	if (url == NULL)
		goto cleanup_curl;

	ret = curl_easy_setopt(curl, CURLOPT_URL, url);
	free(url);
	if (ret != CURLE_OK)
		goto cleanup_curl;


	FILE *fd = open_memstream(&buffer, &len);
	if (fd == NULL)
		goto cleanup_curl;
	if ((ret = curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd)) != CURLE_OK)
		goto close_fd;

	/* Perform the request, res will get the return code. If the request fails,
	 * no jump has to be performed, because the next commands are the
	 * destination for these jump labels. */
	ret = curl_easy_perform(curl);


close_fd:
	fclose(fd);

cleanup_curl:
	curl_easy_cleanup(curl);

	/* If cURL returned an error code, free the (maybe) allocated memory and
	 * return NULL to indicate an error. Otherwise return the buffer pointer, so
	 * the callee is able to use the response data. If an error happend, buffer
	 * may be set to NULL, which will indicate an error, too. */
	if (ret != CURLE_OK) {
		free(buffer);
		return NULL;
	}
	return buffer;
}
