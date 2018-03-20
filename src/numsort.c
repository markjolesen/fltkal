/*
 * numsort.c
 *
 * "$Id: numericsort.c 12738 2018-03-11 16:24:36Z AlbrechtS $"
 *
 * Numeric sorting routine for the Fast Light Tool Kit (FLTK).
 *
 * Copyright 2017-2018 The fltkal authors
 * Copyright 1998-2018 by Bill Spitzak and others.
 *
 *                              FLTK License
 *                            December 11, 2001
 * 
 * The FLTK library and included programs are provided under the terms
 * of the GNU Library General Public License (LGPL) with the following
 * exceptions:
 * 
 *     1. Modifications to the FLTK configure script, config
 *        header file, and makefiles by themselves to support
 *        a specific platform do not constitute a modified or
 *        derivative work.
 * 
 *       The authors do request that such modifications be
 *       contributed to the FLTK project - send all contributions
 *       through the "Software Trouble Report" on the following page:
 *  
 *            http://www.fltk.org/str.php
 * 
 *     2. Widgets that are subclassed from FLTK widgets do not
 *        constitute a derivative work.
 * 
 *     3. Static linking of applications and widgets to the
 *        FLTK library does not constitute a derivative work
 *        and does not require the author to provide source
 *        code for the application or widget, use the shared
 *        FLTK libraries, or link their applications or
 *        widgets against a user-supplied version of FLTK.
 * 
 *        If you link the application or widget to a modified
 *        version of FLTK, then the changes to FLTK must be
 *        provided under the terms of the LGPL in sections
 *        1, 2, and 4.
 * 
 *     4. You do not have to provide a copy of the FLTK license
 *        with programs that are linked to the FLTK library, nor
 *        do you have to identify the FLTK license in your
 *        program or documentation as required by section 6
 *        of the LGPL.
 * 
 *        However, programs must still identify their use of FLTK.
 *        The following example statement can be included in user
 *        documentation to satisfy this requirement:
 * 
 *            [program/widget] is based in part on the work of
 *            the FLTK project (http://www.fltk.org).
 * 
 *     This library is free software; you can redistribute it and/or
 *     modify it under the terms of the GNU Library General Public
 *     License as published by the Free Software Foundation; either
 *     version 2 of the License, or (at your option) any later version.
 * 
 *     This library is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *     Library General Public License for more details.
 * 
 *     You should have received a copy of the GNU Library General Public
 *     License along with FLTK.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <ctype.h>
#include <stdlib.h>
#include <fl/typesplt.h>
#include <fl/filename.h>

/**
  \file numericsort.c
*/

/*
  numericsort() - Compare two directory entries, possibly with a
                  case-insensitive comparison...

  *FIXME* This is not UTF-8 aware -- particularly case-insensitive comparison.
  *FIXME* If you fix it, don't forget to update the documentation below.
*/

static int numericsort(struct dirent **A, struct dirent **B, int cs) {
  const char* a = (*A)->d_name;
  const char* b = (*B)->d_name;
  int ret = 0;
  for (;;) {
    if (isdigit(*a & 255) && isdigit(*b & 255)) {
      int diff,magdiff;
      while (*a == '0') a++;
      while (*b == '0') b++;
      while (isdigit(*a & 255) && *a == *b) {a++; b++;}
      diff = (isdigit(*a & 255) && isdigit(*b & 255)) ? *a - *b : 0;
      magdiff = 0;
      while (isdigit(*a & 255)) {magdiff++; a++;}
      while (isdigit(*b & 255)) {magdiff--; b++;}
      if (magdiff) {ret = magdiff; break;} /* compare # of significant digits */
      if (diff) {ret = diff; break;}       /* compare first non-zero digit */
    } else {
      if (cs) {
      	/* compare case-sensitive */
	if ((ret = *a-*b)) break;
      } else {
	/* compare case-insensitive */
	if ((ret = tolower(*a & 255)-tolower(*b & 255))) break;
      }

      if (!*a) break;
      a++; b++;
    }
  }
  if (!ret) return 0;
  else return (ret < 0) ? -1 : 1;
}

/**
  Compares directory entries alphanumerically (case-insensitive).

  \note	This comparison is not (yet) UTF-8 aware.

  \todo Make comparison UTF-8 aware.

  \see fl_numericsort()
*/

int fl_casenumericsort(struct dirent **A, struct dirent **B) {
  return numericsort(A, B, 0);
}

/**
  Compares directory entries alphanumerically (case-sensitive).

  Numbers are compared without sign, i.e. "-" is not taken as a sign of
  following numerical values. The following list of files would be in
  ascending order (examples are ASCII and numbers only for simplicity):

   -# 1zzz.txt
   -# 2xxx.txt
   -# 19uuu.txt
   -# 100aaa.txt
   -# file1z.txt
   -# file5a.txt
   -# file5z.txt
   -# file30z.txt
   -# file200a.txt
   -# temp+5.txt   ('+' is lexically lower than '-')
   -# temp-5.txt   ('-' is not a sign)
   -# temp-100.txt (100 is bigger than 5, no sign)

  \param[in] A first directory entry
  \param[in] B second directory entry

  \returns comparison result (-1, 0, or +1)
  \retval  -1 A \< B
  \retval   0 A == B
  \retval  +1 A \> B

  \note	This comparison is not (yet) UTF-8 aware:
    - UTF-8 characters are compared according to their binary values.
    - Locale settings may influence the result in unexpected ways.
    - The latter is particularly true for fl_casenumericsort().
  This may be changed in a future release.

  \todo Make comparison UTF-8 aware.

  \see fl_casenumericsort()
*/

int fl_numericsort(struct dirent **A, struct dirent **B) {
  return numericsort(A, B, 1);
}

/*
 * End of "$Id: numericsort.c 12738 2018-03-11 16:24:36Z AlbrechtS $".
 */
