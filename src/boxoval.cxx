// boxoval.cxx
//
// "$Id: fl_oval_box.cxx 10781 2015-07-09 00:10:44Z AlbrechtS $"
//
// Oval box drawing code for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2011 by Bill Spitzak and others.
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


// Less-used box types are in separate files so they are not linked
// in if not used.

#include <fl/fl.h>
#include <fl/fl_draw.h>

static void fl_oval_flat_box(int x, int y, int w, int h, Fl_Color c) {
  Fl::set_box_color(c);
  fl_pie(x, y, w, h, 0, 360);
}

static void fl_oval_frame(int x, int y, int w, int h, Fl_Color c) {
  Fl::set_box_color(c);
  fl_arc(x, y, w, h, 0, 360);
}

static void fl_oval_box(int x, int y, int w, int h, Fl_Color c) {
  fl_oval_flat_box(x,y,w,h,c);
  fl_oval_frame(x,y,w,h,FL_BLACK);
}

static void fl_oval_shadow_box(int x, int y, int w, int h, Fl_Color c) {
  fl_oval_flat_box(x+3,y+3,w,h,FL_DARK3);
  fl_oval_box(x,y,w,h,c);
}

extern void fl_internal_boxtype(Fl_Boxtype, Fl_Box_Draw_F*);
Fl_Boxtype fl_define_FL_OVAL_BOX() {
  fl_internal_boxtype(_FL_OSHADOW_BOX,fl_oval_shadow_box);
  fl_internal_boxtype(_FL_OVAL_FRAME,fl_oval_frame);
  fl_internal_boxtype(_FL_OFLAT_BOX,fl_oval_flat_box);
  fl_internal_boxtype(_FL_OVAL_BOX,fl_oval_box);
  return _FL_OVAL_BOX;
}

//
// End of "$Id: fl_oval_box.cxx 10781 2015-07-09 00:10:44Z AlbrechtS $".
//
