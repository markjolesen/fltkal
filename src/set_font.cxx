// set_font.cxx
//
// "$Id: fl_set_font.cxx 12975 2018-06-26 14:04:09Z manolo $"
//
// Font utilities for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2010 by Bill Spitzak and others.
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

// Add a font to the internal table.
// Also see fl_set_fonts.cxx which adds all possible fonts.

#include <fl/fl.h>
#include <fl/platform.h>
#include <fl/fl_draw.h>
#include "drvscr.h"
#include "flstring.h"
#include <stdlib.h>

struct Fl_Fontdesc;
extern FL_EXPORT Fl_Fontdesc *fl_fonts; // the table

static int table_size;
/**
  Changes a face.  The string pointer is simply stored,
  the string is not copied, so the string must be in static memory.
*/    
void Fl::set_font(Fl_Font fnum, const char* name) {
  Fl_Graphics_Driver &d = Fl_Graphics_Driver::default_driver();
  unsigned width = d.font_desc_size();
  if (!fl_fonts) fl_fonts = d.calc_fl_fonts();
  while (fnum >= table_size) {
    int i = table_size;
    if (!i) {	// don't realloc the built-in table
      table_size = 2*FL_FREE_FONT;
      i = FL_FREE_FONT;
      Fl_Fontdesc* t = (Fl_Fontdesc*)malloc(table_size*width);
      memcpy(t, fl_fonts, FL_FREE_FONT*width);
      fl_fonts = t;
    } else {
      table_size = 2*table_size;
      fl_fonts=(Fl_Fontdesc*)realloc(fl_fonts, table_size*width);
    }
    for (; i < table_size; i++) {
      memset((char*)fl_fonts + i * width, 0, width);
    }
  }
  d.font_name(fnum, name);
  d.font(-1, 0);
}

/** Copies one face to another. */
void Fl::set_font(Fl_Font fnum, Fl_Font from) {
  Fl::set_font(fnum, get_font(from));
}

/**
    Gets the string for this face.  This string is different for each
    face. Under X this value is passed to XListFonts to get all the sizes
    of this face.
*/
const char* Fl::get_font(Fl_Font fnum) {
  return Fl_Graphics_Driver::default_driver().font_name(fnum);
}

//
// End of "$Id: fl_set_font.cxx 12975 2018-06-26 14:04:09Z manolo $".
//
