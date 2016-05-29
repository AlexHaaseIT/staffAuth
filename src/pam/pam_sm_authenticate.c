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

#include <assert.h> // assert
#include <stddef.h> // NULL
#include <stdlib.h> // getenv

#include <mauth.h> // mauth interface

/* To be correctly initialized, PAM_SM_AUTH must be #define'd prior to including
 * <security/pam_modules.h>. This will ensure that the prototypes for static
 * modules are properly declared. */
#define PAM_SM_AUTH

/* The PAM implementations in Linux and OSX provide the same interfaces, but the
 * header files are different. */
#ifdef __APPLE__
#include <security/pam_modules.h>
#include <security/pam_appl.h> // pam_get_user, pam_get_authtok
#else
#include <security/pam_ext.h>     // pam_get_authtok
#include <security/pam_modules.h> // pam_get_user
#endif


/** \brief Authenticate mauth users with one time passwords.
 *
 * \details This PAM function authenticates the user. If the user login is
 *  handled by mauth, we'll ask the mauth API server, if the supplied one time
 *  password is valid or not. If the user is not handled by mauth, this module
 *  will simply ignore him.
 *
 *
 * \param pamh PAM handle.
 * \param flags PAM flags
 * \param argc Number of additional PAM parameters from the config file. Will be
 *  ignored by this module.
 * \param argv. Additional PAM parameters from the config file. Will be ignored
 *  by this module.
 *
 * \return If the user is handled by mauth and the one time password is valid,
 *  PAM_SUCCESS will be returned. PAM_IGNORE will be returned, if the user is
 *  not handled by mauth. See PAM documentation for other error return values.
 */
PAM_EXTERN int
pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	/* Assert required arguments. */
	assert(pamh);


	int pam_ret;


	/* Initialize mauth handle. */
	mauth mh;
	mauth_init(&mh);


	/* Try to get the login used to authenticate and set it as mauth login. If
	 * either pam_get_user or mauth_set_login fails, we'll set appropiate error
	 * return values, to indicate the specific error. */
	const char *login;
	if ((pam_ret = pam_get_user(pamh, &login, NULL)) != PAM_SUCCESS)
		goto ret_pam_sm_authenticate;

	switch (mauth_set_login(&mh, login)) {
		case MAUTH_SUCCESS: break;

		case MAUTH_USER_UNKNOWN:
			pam_ret = PAM_USER_UNKNOWN;
			goto ret_pam_sm_authenticate;

		default:
		case MAUTH_ERR_IO:
			pam_ret = PAM_AUTHINFO_UNAVAIL;
			goto ret_pam_sm_authenticate;
	}


	/* Try to get the keyid used for verification. It should be stored as
	 * SSH_AUTH_KEY variable in the users' environment. If the variable is not
	 * set, we can abort here. */
	const char *keyid;
	if ((keyid = getenv("SSH_AUTH_KEY")) == NULL) {
		pam_ret = PAM_AUTH_ERR;
		goto ret_pam_sm_authenticate;
	}


	/* Ask the user for the one time password. */
	const char *otp_token;
	if ((pam_ret = pam_get_authtok(pamh, PAM_AUTHTOK, &otp_token,
	                               "Verification code: ")) != PAM_SUCCESS)
		goto ret_pam_sm_authenticate;

	/* Validate the one time password via the mauth API. */
	switch (mauth_verify_otp(&mh, otp_token, keyid)) {
		case MAUTH_SUCCESS: pam_ret = PAM_SUCCESS; break;

		case MAUTH_ERR_IO: pam_ret = PAM_AUTHINFO_UNAVAIL; break;
		default: pam_ret = PAM_AUTH_ERR; break;
	}


ret_pam_sm_authenticate:
	/* Destroy the mauth handle. */
	mauth_destroy(&mh);

	return pam_ret;
}
