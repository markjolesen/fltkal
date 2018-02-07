// fl_font.cxx
//
// "$Id: fl_font.cxx 11643 2016-04-17 15:36:23Z matt $"
//
// Font selection code for the Fast Light Tool Kit (FLTK).
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


// Select fonts from the FLTK font table.
#include "flstring.h"
#include <fl/fl_draw.h>

// -----------------------------------------------------------------------------
// all driver code is now in drivers/XXX/Fl_XXX_Graphics_Driver_xyz.cxx
// -----------------------------------------------------------------------------

double fl_width(const char* c) {
  if (c) return fl_width(c, (int) strlen(c));
  else return 0.0f;
}

void fl_draw(const char* str, int x, int y) {
  fl_draw(str, (int) strlen(str), x, y);
}

void fl_draw(int angle, const char* str, int x, int y) {
  fl_draw(angle, str, (int) strlen(str), x, y);//must be fixed!
}

void fl_text_extents(const char *c, int &dx, int &dy, int &w, int &h) {
  if (c)  fl_text_extents(c, (int) strlen(c), dx, dy, w, h);
  else {
    w = 0; h = 0;
    dx = 0; dy = 0;
  }
} // fl_text_extents


void fl_draw(const char* str, int l, float x, float y) {
  fl_graphics_driver->draw(str, l, x, y);
}

void fl_set_spot(int font, int size, int X, int Y, int W, int H, Fl_Window *win)
{
  Fl_Graphics_Driver::default_driver().set_spot(font, size, X, Y, W, H, win);
}

void fl_reset_spot()
{
  Fl_Graphics_Driver::default_driver().reset_spot();
}

//
// End of "$Id: fl_font.cxx 11643 2016-04-17 15:36:23Z matt $".
//
