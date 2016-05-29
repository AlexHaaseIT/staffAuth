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

#define _GNU_SOURCE // required for asprintf in stdio.h
#include <assert.h> // assert
#include <stdio.h>  // asprintf
#include <stdlib.h> // free
#include <string.h> // strdup
#include <unistd.h> // access

#include <libconfig.h> // libconfig interface

#include "cmake-config.h" // Macros defined at configuration time


#define MAUTH_USER_CONF_DIR "users.d"


/** \brief Get configuration filename for \p login.
 *
 * \details This function will check for the login's configuration file. If it
 *  is found and can be read by the current process, this function will allocate
 *  a new buffer to store the filename in. If the file is not present or can't
 *  be accessed, the application will be exited immediately.
 *
 *
 * \param config Current configuration.
 *
 * \return If the configuration file for login is present and can be accessed,
 *  a pointer to the new allocated buffer will be returned. In any other case
 *  this function will exit the application.
 *
 * \info The new allocated buffer MUST be freed by the caller.
 */
static mauth_status
login_config_file(char **dest, const char *login)
{
	/* Assert required arguments. If no login was set, a previous function has
	 * failed. If no login was set in an API function, previous called commands
	 * should have failed already. If they didn't, this is an errornous
	 * behavíour and we should fail here. */
	assert(dest);
	assert(login);


	/* Get the filename for the required config file, that stores the configura-
	 * tion for the users mauth API server. */
	char *config_file;
	asprintf(&config_file, "%s/%s/%s.conf", MAUTH_CONFIG_DIR,
	         MAUTH_USER_CONF_DIR, login);


	/* Check, if the file is present and readable. */
	if (access(config_file, F_OK) != 0) {
		/* If it is not present, the login will not be managed via mauth. Free
		 * the memory allocated for config_file and return an error code. */
		free(config_file);
		return MAUTH_USER_UNKNOWN;

	} else if (access(config_file, R_OK) != 0) {
		/* If the file is present, but can't be read, there is a permission
		 * error. Free the memory allocated for config file and return an error
		 * code. */
		free(config_file);
		return MAUTH_ERR_IO;
	}

	/* Set dest to config_file and return success. */
	*dest = config_file;
	return MAUTH_SUCCESS;
}


/** \brief Set \p login to use for mauth.
 *
 * \details This function will set the login to use for mauth. The login will be
 *  used to search configuration files.
 *
 *
 * \param mh \ref mauth handle.
 * \param login Login to be used for mauth.
 *
 * \return This function returns
 */
mauth_status
mauth_set_login(mauth *mh, const char *login)
{
	/* Assert required arguments. */
	assert(mh);
	assert(login);


	mauth_status ret;

	/* Get config file for login. If the user is not handled by mauth or there
	 * is an IO error, pass through the rror. The allocated memory was freed by
	 * login_config_file in an errornous situation, so we don't have to take
	 * care about this. */
	char *config_file;
	if ((ret = login_config_file(&config_file, login)) != MAUTH_SUCCESS)
		return ret;


	/* Try to read the configuration file. If there is an error (e.g. syntax
	 * error) MAUTH_ERR_IO will be returned. */
	config_t cfg;
	config_init(&cfg);

	if (!config_read_file(&cfg, config_file)) {
		ret = MAUTH_ERR_IO;
		goto ret_set_login;
	}


	const char *buffer;
	if (!config_lookup_string(&cfg, "server", &buffer)) {
		ret = MAUTH_ERR_IO;
		goto ret_set_login;
	}
	mh->server = strdup(buffer);


ret_set_login:
	config_destroy(&cfg);
	free(config_file);

	return ret;
}
