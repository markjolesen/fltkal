// fl_boxro.cxx
//
// "$Id: fl_rounded_box.cxx 11815 2016-07-15 22:12:30Z AlbrechtS $"
//
// Rounded box drawing routines for the Fast Light Tool Kit (FLTK).
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

#include <fl/fl.h>
#include <fl/fl_draw.h>

// Constants for rounded corner drawing algorithm:
//
//  RN = number of segments per corner (must match offset array size)
//  RS = max. corner radius
//  BW = box shadow width

#define RN	5
#define RS	15
#define BW	3

static double offset[RN] = { 0.0, 0.07612, 0.29289, 0.61732, 1.0};

static inline void fl_vertex_r(double x, double y) {
  fl_vertex(x + 0.5, y + 0.5);
}

static void rbox(int fill, int x, int y, int w, int h) {
  int i;
  int rs, rsy;
  rs = w*2/5; rsy = h*2/5;
  if (rs > rsy) rs = rsy; // use smaller radius
  if (rs > RS) rs = RS;
  if (rs == 5) rs = 4;	// use only even sizes for small corners (STR #2943)
  if (rs == 7) rs = 8;	// note: 8 is better than 6 (really)

  if (fill) fl_begin_polygon(); else fl_begin_loop();
  for (i=0; i<RN; i++)
    fl_vertex_r(x + offset[RN-i-1]*rs, y + offset[i] * rs);
  for (i=0; i<RN; i++)
    fl_vertex_r(x + offset[i]*rs, y + h-1 - offset[RN-i-1] * rs);
  for (i=0; i<RN; i++)
    fl_vertex_r(x + w-1 - offset[RN-i-1]*rs, y + h-1 - offset[i] * rs);
  for (i=0; i<RN; i++)
    fl_vertex_r(x + w-1 - offset[i]*rs, y + offset[RN-i-1] * rs);
  if (fill) fl_end_polygon(); else fl_end_loop();
}

static void fl_rflat_box(int x, int y, int w, int h, Fl_Color c) {
  Fl::set_box_color(c);
  rbox(1, x, y, w, h); rbox(0, x, y, w, h);
}

static void fl_rounded_frame(int x, int y, int w, int h, Fl_Color c) {
  Fl::set_box_color(c);
  rbox(0, x, y, w, h);
}

static void fl_rounded_box(int x, int y, int w, int h, Fl_Color c) {
  Fl::set_box_color(c);
  rbox(1, x, y, w, h);
  fl_color(FL_BLACK); rbox(0, x, y, w, h);
}

static void fl_rshadow_box(int x, int y, int w, int h, Fl_Color c) {
  // draw shadow:
  fl_color(FL_DARK3);
  rbox(1, x+BW, y+BW, w, h);
  rbox(0, x+BW, y+BW, w, h);
  // draw the box:
  fl_rounded_box(x, y, w, h, c);
}

extern void fl_internal_boxtype(Fl_Boxtype, Fl_Box_Draw_F*);

Fl_Boxtype fl_define_FL_ROUNDED_BOX() {
  fl_internal_boxtype(_FL_ROUNDED_FRAME, fl_rounded_frame);
  fl_internal_boxtype(_FL_ROUNDED_BOX, fl_rounded_box);
  return _FL_ROUNDED_BOX;
}

Fl_Boxtype fl_define_FL_RFLAT_BOX() {
  fl_internal_boxtype(_FL_RFLAT_BOX, fl_rflat_box);
  return _FL_RFLAT_BOX;
}

Fl_Boxtype fl_define_FL_RSHADOW_BOX() {
  fl_internal_boxtype(_FL_RSHADOW_BOX, fl_rshadow_box);
  return _FL_RSHADOW_BOX;
}

//
// End of "$Id: fl_rounded_box.cxx 11815 2016-07-15 22:12:30Z AlbrechtS $".
//
