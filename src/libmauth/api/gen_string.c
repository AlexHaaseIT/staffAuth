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

#include <mauth.h>

#include <stdlib.h> // free
#include <stdio.h>  // vfprintf


/** \brief Generate a string as defined in \p format.
 *
 * \details This function generates a string according to \p format. The memory
 *  for the generated string will be allocated dynamically and a pointer to the
 *  memory will be returned.
 *
 * \param format Format for generated string. For allowed placeholders see
 *  vfprintf documentation.
 * \param ... Variadic parameters for \p format.
 *
 * \return Returns a pointer to a new generated string. This pointer must be
 *  freed after usage! If an error occured NULL will be returned.
 */
char *
mauth_gen_string(const char *format, ...)
{
	/* String stream to store generated key in. */
	size_t size;
	char *buffer;
	FILE *stream = open_memstream(&buffer, &size);
	if (stream == NULL)
		return NULL;

	/* Parse variadic arguments and pass them to vfprintf. */
	va_list ap;
	va_start(ap, format);
	int len = vfprintf(stream, format, ap);
	va_end(ap);

	/* Close string stream and return pointer if no error occured. Otherwise
	 * return NULL. */
	if (fclose(stream) == 0)
		if (len >= 0)
			return buffer;

	/* If an error occured and pointer will not be used anymore, free allocated
	 * memory. */
	if (buffer != NULL)
		free(buffer);

	return NULL;
}
