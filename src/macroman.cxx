// macroman.cxx
//
// "$Id: fl_encoding_mac_roman.cxx 11600 2016-04-13 14:19:13Z manolo $"
//
// Convert Mac Roman encoded text to the local encoding.
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2016 by Bill Spitzak and others.
//
//                              FLTK License
//                            December 11, 2001
// 
// The FLTK library and included programs are provided under the terms
// of the GNU Library General Public License (LGPL) with the following
// exceptions:
// 
//     1. Modifications to the FLTK configure script, config
//        header file, and makefiles by themselves to support
//        a specific platform do not constitute a modified or
//        derivative work.
// 
//       The authors do request that such modifications be
//       contributed to the FLTK project - send all contributions
//       through the "Software Trouble Report" on the following page:
//  
//            http://www.fltk.org/str.php
// 
//     2. Widgets that are subclassed from FLTK widgets do not
//        constitute a derivative work.
// 
//     3. Static linking of applications and widgets to the
//        FLTK library does not constitute a derivative work
//        and does not require the author to provide source
//        code for the application or widget, use the shared
//        FLTK libraries, or link their applications or
//        widgets against a user-supplied version of FLTK.
// 
//        If you link the application or widget to a modified
//        version of FLTK, then the changes to FLTK must be
//        provided under the terms of the LGPL in sections
//        1, 2, and 4.
// 
//     4. You do not have to provide a copy of the FLTK license
//        with programs that are linked to the FLTK library, nor
//        do you have to identify the FLTK license in your
//        program or documentation as required by section 6
//        of the LGPL.
// 
//        However, programs must still identify their use of FLTK.
//        The following example statement can be included in user
//        documentation to satisfy this requirement:
// 
//            [program/widget] is based in part on the work of
//            the FLTK project (http://www.fltk.org).
// 
//     This library is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Library General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.
// 
//     This library is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Library General Public License for more details.
// 
//     You should have received a copy of the GNU Library General Public
//     License along with FLTK.  If not, see <http://www.gnu.org/licenses/>.
//
//

#include "cfg_lib.h"
#include <fl/fl_draw.h>
#include <fl/drvsys.h>
#include <fl/fl.h>
#include <fl/fl_enums.h>
#include <stdlib.h>
#include "flstring.h"

// These function assume a western code page.
//
// On Mac OS X, nothing need to be converted. We simply return the
// original pointer.
//
// Windows and X11 render text in ISO or Latin-1 for western settings. The
// lookup tables below will convert all common character codes and replace
// unknown characters with an upsidedown question mark.

#ifdef FL_CFG_WIN_COCOA

#  include "drivers/Darwin/Fl_Darwin_System_Driver.H"

const char *Fl_Darwin_System_Driver::mac_roman_to_local(const char *t, int)
{
  return t;
}

const char *Fl_Darwin_System_Driver::local_to_mac_roman(const char *t, int)
{
  return t;
}

#endif

// This table converts Windows-1252/Latin 1 into MacRoman encoding
static uchar latin2roman[128] = {
0xdb, 0xc0, 0xe2, 0xc4, 0xe3, 0xc9, 0xa0, 0xe0, 0xf6, 0xe4, 0xc0, 0xdc, 0xce, 0xc0, 0xc0, 0xc0, 
0xc0, 0xd4, 0xd5, 0xd2, 0xd3, 0xa5, 0xd0, 0xd1, 0xf7, 0xaa, 0xc0, 0xdd, 0xcf, 0xc0, 0xc0, 0xd9, 
0xca, 0xc1, 0xa2, 0xa3, 0xc0, 0xb4, 0xc0, 0xa4, 0xac, 0xa9, 0xbb, 0xc7, 0xc2, 0xc0, 0xa8, 0xf8, 
0xa1, 0xb1, 0xc0, 0xc0, 0xab, 0xb5, 0xa6, 0xe1, 0xfc, 0xc0, 0xbc, 0xc8, 0xc0, 0xc0, 0xc0, 0xc0, 
0xcb, 0xe7, 0xe5, 0xcc, 0x80, 0x81, 0xae, 0x82, 0xe9, 0x83, 0xe6, 0xe8, 0xed, 0xea, 0xeb, 0xec, 
0xc0, 0x84, 0xf1, 0xee, 0xef, 0xcd, 0x85, 0xc0, 0xaf, 0xf4, 0xf2, 0xf3, 0x86, 0xc0, 0xc0, 0xa7, 
0x88, 0x87, 0x89, 0x8b, 0x8a, 0x8c, 0xbe, 0x8d, 0x8f, 0x8e, 0x90, 0x91, 0x93, 0x92, 0x94, 0x95, 
0xc0, 0x96, 0x98, 0x97, 0x99, 0x9b, 0x9a, 0xd6, 0xbf, 0x9d, 0x9c, 0x9e, 0x9f, 0xc0, 0xc0, 0xd8
};

// This table converts MacRoman into Windows-1252/Latin 1
static uchar roman2latin[128] = {
0xc4, 0xc5, 0xc7, 0xc9, 0xd1, 0xd6, 0xdc, 0xe1, 0xe0, 0xe2, 0xe4, 0xe3, 0xe5, 0xe7, 0xe9, 0xe8, 
0xea, 0xeb, 0xed, 0xec, 0xee, 0xef, 0xf1, 0xf3, 0xf2, 0xf4, 0xf6, 0xf5, 0xfa, 0xf9, 0xfb, 0xfc, 
0x86, 0xb0, 0xa2, 0xa3, 0xa7, 0x95, 0xb6, 0xdf, 0xae, 0xa9, 0x99, 0xb4, 0xa8, 0xbf, 0xc6, 0xd8, 
0xbf, 0xb1, 0xbf, 0xbf, 0xa5, 0xb5, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xaa, 0xba, 0xbf, 0xe6, 0xf8, 
0xbf, 0xa1, 0xac, 0xbf, 0x83, 0xbf, 0xbf, 0xab, 0xbb, 0x85, 0xa0, 0xc0, 0xc3, 0xd5, 0x8c, 0x9c, 
0x96, 0x97, 0x93, 0x94, 0x91, 0x92, 0xf7, 0xbf, 0xff, 0x9f, 0xbf, 0x80, 0x8b, 0x9b, 0xbf, 0xbf, 
0x87, 0xb7, 0x82, 0x84, 0x89, 0xc2, 0xca, 0xc1, 0xcb, 0xc8, 0xcd, 0xce, 0xcf, 0xcc, 0xd3, 0xd4, 
0xbf, 0xd2, 0xda, 0xdb, 0xd9, 0xbf, 0x88, 0x98, 0xaf, 0xbf, 0xbf, 0xbf, 0xb8, 0xbf, 0xbf, 0xbf
};

static char *buf = 0;
static int n_buf = 0;

const char *Fl_System_Driver::local_to_mac_roman(const char *t, int n)
{
  if (n==-1) n = (int) strlen(t);
  if (n<=n_buf) {
    n_buf = (n + 257) & 0x7fffff00;
    if (buf) free(buf);
    buf = (char*)malloc(n_buf);
  }
  const uchar *src = (const uchar*)t;
  uchar *dst = (uchar*)buf;
  for ( ; n>0; n--) {
    uchar c = *src;
    if (c>127) 
      *dst = latin2roman[c-128];
    else
      *dst = c;
  }
  //*dst = 0; // this would be wrong!
  return buf;
}

const char *Fl_System_Driver::mac_roman_to_local(const char *t, int n)
{
  if (n==-1) n = (int) strlen(t);
  if (n<=n_buf) {
    n_buf = (n + 257) & 0x7fffff00;
    if (buf) free(buf);
    buf = (char*)malloc(n_buf);
  }
  const uchar *src = (const uchar*)t;
  uchar *dst = (uchar*)buf;
  for ( ; n>0; n--) {
    uchar c = *src++;
    if (c>127)
      *dst++ = roman2latin[c-128];
    else
      *dst++ = c;
  }
  //*dst = 0; // this would be wrong
  return buf;
}

const char *fl_local_to_mac_roman(const char *t, int n) {
  return Fl::system_driver()->local_to_mac_roman(t, n);
}

const char *fl_mac_roman_to_local(const char *t, int n) {
  return Fl::system_driver()->mac_roman_to_local(t, n);
}

//
// End of "$Id: fl_encoding_mac_roman.cxx 11600 2016-04-13 14:19:13Z manolo $".
//
