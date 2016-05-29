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

/* This header file is for internal functions, which should not be used public.
 * Functions defined in this header are non-stable and may change in future
 * releases! */

#ifndef MAUTH_INTERNAL_H
#define MAUTH_INTERNAL_H


#include "mauth.h"


/** \brief Mark function as internal.
 *
 * \details This macro will be used to mark functions as internal functions,
 *  which will be hidden for global exports.
 */
#define MAUTH_INTERNAL __attribute__((visibility("hidden")))


char *mauth_api_url(mauth *mh, const char *target);
mauth_status mauth_api_request(char **dest, const char *url,
                               const char *payload);

mauth_keylist *mauth_keylist_add(mauth_keylist *list, const char *key,
                                 const char *hash);


#endif
