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

/* To be correctly initialized, PAM_SM_AUTH must be #define'd prior to including
 * <security/pam_modules.h>. This will ensure that the prototypes for static
 * modules are properly declared. */
#define PAM_SM_AUTH

/* The PAM implementations in Linux and OSX provide the same interfaces, but the
 * header files are different. */
#ifdef __APPLE__
#include <security/pam_modules.h>
#include <security/pam_appl.h>
#else
#include <security/pam_modules.h> // pam_get_user
#endif


/** \brief Stub function.
 *
 * \details This function is only a stub to satisfy PAM and to avoid error
 *  messages in syslog about the non-existence of this function.
 *
 *
 * \param pamh PAM handle.
 * \param flags PAM flags
 * \param argc Number of additional PAM parameters from the config file. Will be
 *  ignored by this module.
 * \param argv. Additional PAM parameters from the config file. Will be ignored
 *  by this module.
 *
 * \return PAM_IGNORE Will be returned for every request.
 */
PAM_EXTERN int
pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	return PAM_IGNORE;
}
