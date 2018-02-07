// imgxpm.cxx
//
// "$Id: Fl_XPM_Image.cxx 12027 2016-10-14 14:33:18Z AlbrechtS $"
//
// Fl_XPM_Image routines.
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
//

//
// Include necessary header files...
//

#include <fl/fl.h>
#include <fl/imgxpm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fl/fl_utf8.h>
#include "flstring.h"


//
// 'hexdigit()' - Convert a hex digit to an integer.
//

static int hexdigit(int x) {	// I - Hex digit...
  if (isdigit(x)) return x-'0';
  if (isupper(x)) return x-'A'+10;
  if (islower(x)) return x-'a'+10;
  return 20;
}

#define MAXSIZE 2048
#define INITIALLINES 256
/**
  The constructor loads the XPM image from the name filename.

  The destructor frees all memory and server resources that are used by
  the image.
*/
Fl_XPM_Image::Fl_XPM_Image(const char *name) : Fl_Pixmap((char *const*)0) {
  FILE *f;

  if ((f = fl_fopen(name, "rb")) == NULL) return;

  // read all the c-strings out of the file:
  char** new_data = new char *[INITIALLINES];
  char** temp_data;
  int malloc_size = INITIALLINES;
  char buffer[MAXSIZE+20];
  int i = 0;
  int W,H,ncolors,chars_per_pixel;
  while (fgets(buffer,MAXSIZE+20,f)) {
    if (buffer[0] != '\"') continue;
    char *myp = buffer;
    char *q = buffer+1;
    while (*q != '\"' && myp < buffer+MAXSIZE) {
      if (*q == '\\') switch (*++q) {
      case '\r':
      case '\n':
	if (!fgets(q,(int) (buffer+MAXSIZE+20-q),f)) { /* no problem if we hit EOF */ } break;
      case 0:
	break;
      case 'x': {
	q++;
	int n = 0;
	for (int x = 0; x < 2; x++) {
	  int xd = hexdigit(*q);
	  if (xd > 15) break;
	  n = (n<<4)+xd;
	  q++;
	}
	*myp++ = n;
      } break;
      default: {
	int c = *q++;
	if (c>='0' && c<='7') {
	  c -= '0';
	  for (int x=0; x<2; x++) {
	    int xd = hexdigit(*q);
	    if (xd>7) break;
	    c = (c<<3)+xd;
	    q++;
	  }
	}
	*myp++ = c;
      } break;
      } else {
	*myp++ = *q++;
      }
    }
    *myp++ = 0;
    if (i >= malloc_size) {
      temp_data = new char *[malloc_size + INITIALLINES];
      memcpy(temp_data, new_data, sizeof(char *) * malloc_size);
      delete[] new_data;
      new_data = temp_data;
      malloc_size += INITIALLINES;
    }
    // first line has 4 ints: width, height, ncolors, chars_per_pixel
    // followed by color segment: 
    //   if ncolors < 0 this is FLTK (non standard) compressed colormap - all colors coded in single line of 4*ncolors bytes
    //   otherwise - ncolor lines of at least chars_per_pixel bytes
    // followed by pic segment: H lines of at least chars_per_pixel*W bytes
    // next line: would have loved to use measure_pixmap, but it doesn't return all the data!
    if ((!i) && (sscanf(buffer,"%d%d%d%d", &W, &H, &ncolors, &chars_per_pixel) < 4)) goto bad_data; // first line
    else if ((i > (ncolors<0?1:ncolors)) && (myp-buffer-1<W*chars_per_pixel)) goto bad_data; // pic segment
    else if (myp-buffer-1<(ncolors<0?-ncolors*4:chars_per_pixel)) goto bad_data; // color segment
    new_data[i] = new char[myp-buffer+1];
    memcpy(new_data[i], buffer,myp-buffer);
    new_data[i][myp-buffer] = 0;
    i++;
  }

  fclose(f);
  f = NULL;
  if ((!i) || (i<1+(ncolors<0?1:ncolors)+H)) goto bad_data;
  data((const char **)new_data, i);
  alloc_data = 1;

  measure();
  return;
  // dealloc and close as needed when bad data was found
bad_data:
  while (i > 0) delete[] new_data[--i];
  delete[] new_data;
  if (f) fclose(f);
}


//
// End of "$Id: Fl_XPM_Image.cxx 12027 2016-10-14 14:33:18Z AlbrechtS $".
//
