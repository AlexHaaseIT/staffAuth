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

#include "keys.h"

#include <stdio.h>  // fprintf, open_memstream
#include <stdlib.h> // EXIT_ macros, free

#include <json-c/json.h> // JSON-C interface

#include "config.h"


int
main(int argc, char **argv)
{
	int ret = EXIT_SUCCESS;

	/* Read configuration from command line and find required configuration
	 * files. */
	keys_config config = {0};
	staffauth_keys_parse_args(argc, argv, &config);
	staffauth_keys_parse_conffile(&config);


	char *data = staffauth_keys_request(&config);
	if (data != NULL) {
		json_object *jobj = json_tokener_parse(data);

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
	} else {
		fprintf(stderr, "Unable to request data!\n");
		ret = EXIT_FAILURE;
	}

	free(data);
	free(config.server);

	return ret;
}
