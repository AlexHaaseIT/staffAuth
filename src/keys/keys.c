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

#include <stdio.h>  // fprintf
#include <stdlib.h> // EXIT_ macros, free

#include <mauth.h> // mauth interface

#include "config.h"


int
main(int argc, char **argv)
{
	int ret = EXIT_SUCCESS;
	mauth mh;


	/* Read configuration from command line and find required configuration
	 * files. */
	mauth_keys_config config = {0};
	mauth_keys_parse_args(argc, argv, &config);


	/* Initialize mauth handle and set login. */
	mauth_init(&mh);
	mauth_status stat;
	if ((stat = mauth_set_login(&mh, config.login)) != MAUTH_SUCCESS) {
		if (stat == MAUTH_USER_UNKNOWN)
			return EXIT_SUCCESS;
		else {
			fprintf(stderr,
			        "Error while reading configuration for login '%s'.\n",
			        config.login);
			mauth_destroy(&mh);
			return EXIT_FAILURE;
		}
	}


	/* Get all SSH keys via API. */
	mauth_keylist *list = NULL;
	if (mauth_get_keys(&mh, &list) != MAUTH_SUCCESS) {
	}

	for (mauth_keylist *iter = list; iter; iter = iter->next)
		printf("environment=\"SSH_AUTH_KEY=%s\" %s\n", iter->hash, iter->key);

	mauth_keylist_free(list);
	mauth_destroy(&mh);

	return ret;
}
