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

#include "config.h"

#define _GNU_SOURCE // required for asprintf in stdio.h
#include <assert.h> // assert
#include <stdio.h>  // fprintf, asprintf
#include <stdlib.h> // free
#include <string.h> // strdup
#include <unistd.h> // access

#include <libconfig.h> // libconfig interface

#include "cmake-config.h" // Macros defined at configuration time


#define MAUTH_USER_CONF_DIR "users.d"


/** \brief Get configuration filename for login of \p config.
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
static char *
mauth_keys_login_config_file(mauth_keys_config *config)
{
	/* Assert required arguments. Config parameter MUST NOT be NULL. In addition
	 * to this, a login must have been set in config. If no login was set, a
	 * previous function may have failed. If no login was set as command line
	 * argument, previous called command line argument parser should have
	 * printed an error and exit the application. If he didn't, this is an
	 * errornous behavíour and we should fail here. */
	assert(config);
	assert(config->login);


	/* Get the filename for the required config file, that stores the configura-
	* tion for the users mauth API server. */
	char *config_file;
	asprintf(&config_file, "%s/%s/%s.conf", MAUTH_CONFIG_DIR,
	         MAUTH_USER_CONF_DIR, config->login);


	/* Check, if the file is present and readable. */
	if (access(config_file, F_OK) != 0) {
		/* If it is not present, the login will not be managed via mauth, so we
		 * will fail silently. The exit code will be EXIT_SUCCESS, to prevent
		 * OpenSSH server sending error log messages to syslog. */
		free(config_file);
		exit(EXIT_SUCCESS);

	} else if (access(config_file, R_OK) != 0) {
		/* If the file is present, but can't be read, there is a permission
		 * error and we should print an error message before exiting. */
		fprintf(stderr, "Can't read configuration file in '%s'.\n",
		        config_file);
		free(config_file);
		exit(EXIT_FAILURE);
	}


	/* Return the config file path, if it is accessable by the user. */
	return config_file;
}


/** \brief Parse configuration files.
 *
 * \details
 *
 *
 + \param config
 */
void
mauth_keys_parse_conffile(mauth_keys_config *config)
{
	/* Assert required arguments. Config parameter MUST NOT be NULL. */
	assert(config);


	/* Get the filename for the required config file, that stores the configura-
	 * tion for the users mauth API server. This function will either return a
	 * new allocated array of char containing the filename or will exit the
	 * application, if there are any errors. */
	char *config_file = mauth_keys_login_config_file(config);


	/* Try to read the configuration file. */
	config_t cfg;
	config_init(&cfg);

	if (!config_read_file(&cfg, config_file)) {
		fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
		        config_error_line(&cfg), config_error_text(&cfg));
		config_destroy(&cfg);
		free(config_file);
		exit(EXIT_FAILURE);
	}


	const char *buffer;
	if (!config_lookup_string(&cfg, "server", &buffer)) {
		fprintf(stderr, "Server not defined.\n");
		config_destroy(&cfg);
		free(config_file);
		exit(EXIT_FAILURE);
	}
	config->server = strdup(buffer);


	config_destroy(&cfg);
	free(config_file);
}
