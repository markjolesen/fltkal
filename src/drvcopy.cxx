// drvcopy.cxx
//
// "$Id: Fl_Copy_Surface.cxx 12968 2018-06-23 16:47:40Z matt $"
//
// Copy-to-clipboard code for the Fast Light Tool Kit (FLTK).
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

#include <fl/drvcopy.h>

/** the constructor
\param w, h Width and height of the drawing surface in FLTK units */
Fl_Copy_Surface::Fl_Copy_Surface(int w, int h) : Fl_Widget_Surface(NULL) {
  platform_surface = Fl_Copy_Surface_Driver::newCopySurfaceDriver(w, h);
  if (platform_surface) driver(platform_surface->driver());
}

/** the destructor */
Fl_Copy_Surface::~Fl_Copy_Surface() { delete platform_surface; }

void Fl_Copy_Surface::origin(int x, int y) {platform_surface->origin(x, y);}

void Fl_Copy_Surface::origin(int *x, int *y) {
  if (platform_surface) platform_surface->origin(x, y);
}

void Fl_Copy_Surface::set_current() {
  if (platform_surface) platform_surface->set_current();
}

void Fl_Copy_Surface::translate(int x, int y) {
  if (platform_surface) platform_surface->translate(x, y);
}

void Fl_Copy_Surface::untranslate() {
  if (platform_surface) platform_surface->untranslate();
}

int Fl_Copy_Surface::w() {return platform_surface ? platform_surface->width : 0;}

int Fl_Copy_Surface::h() {return platform_surface ? platform_surface->height : 0;}

int Fl_Copy_Surface::printable_rect(int *w, int *h)  {
  if (platform_surface)
    return platform_surface->printable_rect(w, h);
  else {
    *w  = *h = 0;
  }
  return 1;
}

//
// End of "$Id: Fl_Copy_Surface.cxx 12968 2018-06-23 16:47:40Z matt $".
//
