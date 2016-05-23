/* This is an alternative and stripped memstream implementation taken from
 *  http://piumarta.com/software/memstream/
 *
 * It is needed for usage on OSX and BSD platforms to make open_memstream avail-
 * able at these platforms, which seems to be available at recent GNU/Linux
 * platforms only. On a recent GNU/Linux platform the object file will be empty.
 * On anything derived from 4.4 BSD (Darwin, the Three BSDs, etc.) it will
 * contain an implementation of open_memstream() as described in the POSIX and
 * Linux manual pages. On anything else it will probably cause a compilation
 * error.
 *
 * Memstream is distributed under the MIT license.
 */

#if defined(__linux__)
#include <features.h>
#endif

#include <stdio.h>

#if _POSIX_C_SOURCE < 200809L

FILE *open_memstream(char **ptr, size_t *sizeloc);

#endif /* _POSIX_C_SOURCE < 200809L */
