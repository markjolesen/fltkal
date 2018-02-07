/* 
 * spacing.c
 *
 * "$Id: is_spacing.c 12193 2017-03-12 15:12:35Z AlbrechtS $"
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

/* include UCS tables */
#include "headers/spacing.h"

unsigned short
XUtf8IsNonSpacing(unsigned int ucs) {

  if (ucs <= 0x0361) {
    if (ucs >= 0x0300) return ucs_table_0300[ucs - 0x0300];
    return 0;
  }

  if (ucs <= 0x0486) {
    if (ucs >= 0x0483) return ucs_table_0483[ucs - 0x0483];
    return 0;
  }

  if (ucs <= 0x05C4) {
    if (ucs >= 0x0591) return ucs_table_0591[ucs - 0x0591];
    return 0;
  }

  if (ucs <= 0x06ED) {
    if (ucs >= 0x064B) return ucs_table_064B[ucs - 0x064B];
    return 0;
  }

  if (ucs <= 0x0D4D) {
    if (ucs >= 0x0901) return ucs_table_0901[ucs - 0x0901];
    return 0;
  }

  if (ucs <= 0x0FB9) {
    if (ucs >= 0x0E31) return ucs_table_0E31[ucs - 0x0E31];
    return 0;
  }

  if (ucs <= 0x20E1) {
    if (ucs >= 0x20D0) return ucs_table_20D0[ucs - 0x20D0];
    return 0;
  }

  if (ucs <= 0x309A) {
    if (ucs >= 0x302A) return ucs_table_302A[ucs - 0x302A];
    return 0;
  }

  if (ucs <= 0xFB1E) {
    if (ucs >= 0xFB1E) return ucs_table_FB1E[ucs - 0xFB1E];
    return 0;
  }

  if (ucs <= 0xFE23) {
    if (ucs >= 0xFE20) return ucs_table_FE20[ucs - 0xFE20];
    return 0;
  }

  return 0;
}

/*
 * End of "$Id: is_spacing.c 12193 2017-03-12 15:12:35Z AlbrechtS $".
 */
