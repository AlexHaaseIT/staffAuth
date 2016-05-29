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

#ifndef MAUTH_H
#define MAUTH_H


#include <stdbool.h>


/** \brief Internal status and storage of mauth library.
 *
 * \details This struct stores internal data and status of the mauth instance.
 *  This struct must be initialized by mauth_init and destroyed by mauth_destroy
 *  to free allocated memory.
 */
typedef struct mauth
{
	char *server;
} mauth;


/** \brief Return statuses of mauth.
 */
typedef enum mauth_status {
	MAUTH_SUCCESS,      //< Everything went fine.
	MAUTH_FAILURE,      //< An error happened.
	MAUTH_USER_UNKNOWN, //< The user is not handled by mauth.
	MAUTH_ERR,          //< An error happend inside the function.
	MAUTH_ERR_IO        //< File or network IO error.
} mauth_status;


void mauth_init(mauth *mh);
void mauth_destroy(mauth *mauth);

mauth_status mauth_set_login(mauth *mh, const char *login);

mauth_status mauth_verify_otp(mauth *mh, const char *token, const char *keyid);


#endif
