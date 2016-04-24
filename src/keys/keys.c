/* This file is part of staffAuth.
 *
 * staffAuth is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
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

#include <stdio.h>  // fprintf, open_memstream
#include <stdlib.h> // EXIT_ macros, free
#include <string.h> // strlen

#include <curl/curl.h>   // cURL interface
#include <json-c/json.h> // JSON-C interface

#include "config.h"


int
main(int argc, char **argv)
{
	/* Read configuration from command line and find required configuration
	 * files. */
	keys_config config = {0};
	staffauth_keys_parse_args(argc, argv, &config);
	staffauth_keys_parse_conffile(&config);


	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl == NULL) {
		fprintf(stderr, "curl_easy_init failed\n");
		return EXIT_FAILURE;
	}

	char *buffer = NULL;
	size_t buffer_len = 0;
	FILE *fd = open_memstream(&buffer, &buffer_len);

	size_t url_len = strlen(config.server) + 10;
	char url[url_len];
	snprintf(url, url_len, "%s/ssh-keys", config.server);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);

	/* Perform the request, res will get the return code */
	res = curl_easy_perform(curl);
	/* Check for errors */
	if (res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
		        curl_easy_strerror(res));
		curl_easy_cleanup(curl);
		fclose(fd);
		free(buffer);
		return EXIT_FAILURE;
	}


	/* always cleanup */
	curl_easy_cleanup(curl);
	fclose(fd);


	json_object *jobj = json_tokener_parse(buffer);

	enum json_type type = json_object_get_type(jobj);
	if (type != json_type_array) {
		fprintf(stderr, "Wrong type of root object!\n");
		exit(EXIT_FAILURE);
	}

	size_t n = json_object_array_length(jobj);
	size_t i;
	json_object *iter, *buff;
	for (i = 0; i < n; i++) {
		iter = json_object_array_get_idx(jobj, i);
		if (json_object_object_get_ex(iter, "key", &buff))
			printf("%s\n", json_object_get_string(buff));
	}

	json_object_put(jobj);


	free(buffer);

	free(config.server);

	return EXIT_SUCCESS;
}
