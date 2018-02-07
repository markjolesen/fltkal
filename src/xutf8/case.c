/*
 * case.c
 *
 * "$Id: case.c 12193 2017-03-12 15:12:35Z AlbrechtS $"
 *
 * Author: Jean-Marc Lienher ( http://oksid.ch )
 * Copyright 2017-2018 The fltkal authors
 * Copyright 2000-2010 by O'ksi'D.
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

/*
 * This file is required on all platforms for UTF-8 support
 */

#include "../utf8priv.h"
#include <stdlib.h>

/* include UCS tables */
#include "headers/case.h"

int
XUtf8Tolower(int ucs) {
  int ret;
  if (ucs <= 0x02B6) {
    if (ucs >= 0x0041) {
      ret = ucs_table_0041[ucs - 0x0041];
      if (ret > 0) return ret;
    }
    return ucs;
  }

  if (ucs <= 0x0556) {
    if (ucs >= 0x0386) {
      ret = ucs_table_0386[ucs - 0x0386];
      if (ret > 0) return ret;
    }
    return ucs;
  }

  if (ucs <= 0x10C5) {
    if (ucs >= 0x10A0) {
      ret = ucs_table_10A0[ucs - 0x10A0];
      if (ret > 0) return ret;
    }
    return ucs;
  }

  if (ucs <= 0x1FFC) {
    if (ucs >= 0x1E00) {
      ret = ucs_table_1E00[ucs - 0x1E00];
      if (ret > 0) return ret;
    }
    return ucs;
  }

  if (ucs <= 0x2133) {
    if (ucs >= 0x2102) {
      ret = ucs_table_2102[ucs - 0x2102];
      if (ret > 0) return ret;
    }
    return ucs;
  }

  if (ucs <= 0x24CF) {
    if (ucs >= 0x24B6) {
      ret = ucs_table_24B6[ucs - 0x24B6];
      if (ret > 0) return ret;
    }
    return ucs;
  }

  if (ucs <= 0x33CE) {
    if (ucs >= 0x33CE) {
      ret = ucs_table_33CE[ucs - 0x33CE];
      if (ret > 0) return ret;
    }
    return ucs;
  }

  if (ucs <= 0xFF3A) {
    if (ucs >= 0xFF21) {
      ret = ucs_table_FF21[ucs - 0xFF21];
      if (ret > 0) return ret;
    }
    return ucs;
  }

  return ucs;
}

int 
XUtf8Toupper(int ucs) {
  int i;
  static unsigned short *table = NULL;

  if (!table) {
    table = (unsigned short*) malloc(sizeof(unsigned short) * 0x10000);
    for (i = 0; i < 0x10000; i++) {
      table[i] = (unsigned short) i;
    }
    for (i = 0; i < 0x10000; i++) {
      int l;
      l = XUtf8Tolower(i);
      if (l != i) table[l] = (unsigned short) i;
    }
  }
  if (ucs >= 0x10000 || ucs < 0) return ucs;
  return table[ucs];
}

/*
* End of "$Id: case.c 12193 2017-03-12 15:12:35Z AlbrechtS $".
*/
