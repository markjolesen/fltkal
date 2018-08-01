// hotspot.cxx
//
// "$Id: Fl_Window_hotspot.cxx 12974 2018-06-26 13:43:18Z manolo $"
//
// Common hotspot routines for the Fast Light Tool Kit (FLTK).
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

#include <fl/fl.h>
#include <fl/win.h>
#include "drvwin.h"

void Fl_Window::hotspot(int X, int Y, int offscreen) {
  int mx,my;

  // Update the screen position based on the mouse position.
  Fl::get_mouse(mx,my);
  X = mx-X; Y = my-Y;

  // If offscreen is 0 (the default), make sure that the window
  // stays on the screen, if possible.
  if (!offscreen) {
    int scr_x, scr_y, scr_w, scr_h;
    Fl::screen_work_area(scr_x, scr_y, scr_w, scr_h);

    int top = 0;
    int left = 0;
    int right = 0;
    int bottom = 0;

    if (border()) {
      pWindowDriver->decoration_sizes(&top, &left, &right, &bottom);
    }
    // now ensure contents are on-screen (more important than border):
    if (X+w()+right > scr_w+scr_x) X = scr_w+scr_x-right-w();
    if (X-left < scr_x) X = left + scr_x;
    if (Y+h()+bottom > scr_h+scr_y) Y = scr_h+scr_y-bottom-h();
    if (Y-top < scr_y) Y = top + scr_y;
    // make sure that we will force this position
    if (X==x()) x(X-1);
  }

  position(X,Y);
}

void Fl_Window::hotspot(const Fl_Widget *o, int offscreen) {
  int X = o->w()/2;
  int Y = o->h()/2;
  while (o != this && o) {
    X += o->x(); Y += o->y();
    o = o->window();
  }
  hotspot(X,Y,offscreen);
}

//
// End of "$Id: Fl_Window_hotspot.cxx 12974 2018-06-26 13:43:18Z manolo $".
//
