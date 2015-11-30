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

#include <stdio.h>
#include <stdlib.h>

#include <nss_mauth.h>


int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s login\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct passwd pwd_buf;
	char buffer[512];
	int pwd_errno = 0;
	enum nss_status ret =
	    _nss_mauth_getpwnam_r(argv[1], &pwd_buf, buffer, 512, &pwd_errno);

	if (ret == NSS_STATUS_NOTFOUND) {
		printf("%s was not found\n", argv[1]);
		return EXIT_FAILURE;
	}

	printf("name:\t%s\nuid:\t%u\ngid:\t%u\ngecos:\t%s\ndir:\t%s\nshell:\t%s\n",
	       pwd_buf.pw_name, pwd_buf.pw_uid, pwd_buf.pw_gid, pwd_buf.pw_gecos,
	       pwd_buf.pw_dir, pwd_buf.pw_shell);
	return EXIT_SUCCESS;
}
