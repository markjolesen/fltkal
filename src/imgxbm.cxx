// imgxbm.cxx
//
// "$Id: Fl_XBM_Image.cxx 12027 2016-10-14 14:33:18Z AlbrechtS $"
//
// Fl_XBM_Image routines.
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1997-2016 by Bill Spitzak and others.
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
// Contents:
//
//   Fl_XBM_Image::Fl_XBM_Image() - Load an XBM file.
//

//
// Include necessary header files...
//

#include <fl/fl.h>
#include <fl/imgxbm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fl/fl_utf8.h>
#include "flstring.h"

//
// 'Fl_XBM_Image::Fl_XBM_Image()' - Load an XBM file.
//

/**  
  The constructor loads the named XBM file from the given name filename.

  The destructor frees all memory and server resources that are used by
  the image.
*/
Fl_XBM_Image::Fl_XBM_Image(const char *name) : Fl_Bitmap((const char *)0,0,0) {
  FILE	*f;
  uchar	*ptr;

  if ((f = fl_fopen(name, "rb")) == NULL) return;

  char buffer[1024];
  char junk[1024];
  int wh[2]; // width and height
  int i;
  for (i = 0; i<2; i++) {
    for (;;) {
      if (!fgets(buffer,1024,f)) {
        fclose(f);
	return;
      }
      int r = sscanf(buffer,"#define %s %d",junk,&wh[i]);
      if (r >= 2) break;
    }
  }

  // skip to data array:
  for (;;) {
    if (!fgets(buffer,1024,f)) {
      fclose(f);
      return;
    }
    if (!strncmp(buffer,"static ",7)) break;
  }

  // Allocate memory...
  w(wh[0]);
  h(wh[1]);

  int n = ((wh[0]+7)/8)*wh[1];
  array = new uchar[n];

  // read the data:
  for (i = 0, ptr = (uchar *)array; i < n;) {
    if (!fgets(buffer,1024,f)) {
      fclose(f);
      return;
    }
    const char *a = buffer;
    while (*a && i<n) {
      unsigned int t;
      if (sscanf(a," 0x%x",&t)>0) {
        *ptr++ = (uchar)t;
	i ++;
      }
      while (*a && *a++ != ',') {/*empty*/}
    }
  }

  fclose(f);
}


//
// End of "$Id: Fl_XBM_Image.cxx 12027 2016-10-14 14:33:18Z AlbrechtS $".
//
