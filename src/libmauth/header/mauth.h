/* This file is part of staffAuth.
 *
 * staffAuth is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see
 *
 *  http://www.gnu.org/licenses/
 *
 * Copyright (C)
 *  2015 Alexander Haase IT Services <support@alexhaase.de>
 */

#ifndef LIBMAUTH_H
#define LIBMAUTH_H


#include <stdarg.h>    // variadic arguments
#include <stdbool.h>   // bool
#include <stddef.h>    // size_t
#include <sys/types.h> // gid_t, uid_t


bool mauth_valid_grnam(const char *name);
bool mauth_valid_grgid(gid_t gid);
bool mauth_valid_pwnam(const char *login);
bool mauth_valid_pwuid(uid_t uid);

size_t mauth_find_server(char *buffer, size_t size);
char *mauth_gen_string(const char *format, ...);
char *mauth_lookup_key(const char *key);

int mauth_init();
void mauth_cleanup();


#endif
