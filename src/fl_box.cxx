// fl_box.cxx
//
// "$Id: fl_round_box.cxx 10781 2015-07-09 00:10:44Z AlbrechtS $"
//
// Round box drawing routines for the Fast Light Tool Kit (FLTK).
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

// Box drawing code for an obscure box type.
// These box types are in separate files so they are not linked
// in if not used.

#include <fl/fl.h>
#include <fl/fl_draw.h>

// A compiler from a certain very large software company will not compile
// the function pointer assignment due to the name conflict with fl_arc.
// This function is to fix that:
static void fl_arc_i(int x,int y,int w,int h,double a1,double a2) {
  fl_arc(x,y,w,h,a1,a2);
}

enum {UPPER_LEFT, LOWER_RIGHT, CLOSED, FILL};

static void draw(int which, int x,int y,int w,int h, int inset, Fl_Color color)
{
  if (inset*2 >= w) inset = (w-1)/2;
  if (inset*2 >= h) inset = (h-1)/2;
  x += inset;
  y += inset;
  w -= 2*inset;
  h -= 2*inset;
  int d = w <= h ? w : h;
  if (d <= 1) return;
  fl_color(color);
  void (*f)(int,int,int,int,double,double);
  f = (which==FILL) ? fl_pie : fl_arc_i;
  if (which >= CLOSED) {
    f(x+w-d, y, d, d, w<=h ? 0 : -90, w<=h ? 180 : 90);
    f(x, y+h-d, d, d, w<=h ? 180 : 90, w<=h ? 360 : 270);
  } else if (which == UPPER_LEFT) {
    f(x+w-d, y, d, d, 45, w<=h ? 180 : 90);
    f(x, y+h-d, d, d, w<=h ? 180 : 90, 225);
  } else { // LOWER_RIGHT
    f(x, y+h-d, d, d, 225, w<=h ? 360 : 270);
    f(x+w-d, y, d, d, w<=h ? 360 : 270, 360+45);
  }
  if (which == FILL) {
    if (w < h)
      fl_rectf(x, y+d/2, w, h-(d&-2));
    else if (w > h)
      fl_rectf(x+d/2, y, w-(d&-2), h);
  } else {
    if (w < h) {
      if (which != UPPER_LEFT) fl_yxline(x+w-1, y+d/2-1, y+h-d/2+1);
      if (which != LOWER_RIGHT) fl_yxline(x, y+d/2-1, y+h-d/2+1);
    } else if (w > h) {
      if (which != UPPER_LEFT) fl_xyline(x+d/2-1, y+h-1, x+w-d/2+1);
      if (which != LOWER_RIGHT) fl_xyline(x+d/2-1, y, x+w-d/2+1);
    }
  }
}

extern const uchar* fl_gray_ramp();

void fl_round_down_box(int x, int y, int w, int h, Fl_Color bgcolor) {
  const uchar *g = fl_gray_ramp();
  draw(FILL,	    x,   y, w,   h, 2, Fl::box_color(bgcolor));
  draw(UPPER_LEFT,  x+1, y, w-2, h, 0, (Fl_Color)g[(int)'N']);
  draw(UPPER_LEFT,  x+1, y, w-2, h, 1, (Fl_Color)g[(int)'H']);
  draw(UPPER_LEFT,  x,   y, w,   h, 0, (Fl_Color)g[(int)'N']);
  draw(UPPER_LEFT,  x,   y, w,   h, 1, (Fl_Color)g[(int)'H']);
  draw(LOWER_RIGHT, x,   y, w,   h, 0, (Fl_Color)g[(int)'S']);
  draw(LOWER_RIGHT, x+1, y, w-2, h, 0, (Fl_Color)g[(int)'U']);
  draw(LOWER_RIGHT, x,   y, w,   h, 1, (Fl_Color)g[(int)'U']);
  draw(LOWER_RIGHT, x+1, y, w-2, h, 1, (Fl_Color)g[(int)'W']);
  draw(CLOSED,	    x,   y, w,   h, 2, (Fl_Color)g[(int)'A']);
}

void fl_round_up_box(int x, int y, int w, int h, Fl_Color bgcolor) {
  const uchar *g = fl_gray_ramp();
  draw(FILL,	    x,   y, w,   h, 2, Fl::box_color(bgcolor));
  draw(LOWER_RIGHT, x+1, y, w-2, h, 0, (Fl_Color)g[(int)'H']);
  draw(LOWER_RIGHT, x+1, y, w-2, h, 1, (Fl_Color)g[(int)'N']);
  draw(LOWER_RIGHT, x,   y, w,   h, 1, (Fl_Color)g[(int)'H']);
  draw(LOWER_RIGHT, x,   y, w,   h, 2, (Fl_Color)g[(int)'N']);
  draw(UPPER_LEFT,  x,   y, w,   h, 2, (Fl_Color)g[(int)'U']);
  draw(UPPER_LEFT,  x+1, y, w-2, h, 1, (Fl_Color)g[(int)'S']);
  draw(UPPER_LEFT,  x,   y, w,   h, 1, (Fl_Color)g[(int)'W']);
  draw(UPPER_LEFT,  x+1, y, w-2, h, 0, (Fl_Color)g[(int)'U']);
  draw(CLOSED,	    x,   y, w,   h, 0, (Fl_Color)g[(int)'A']);
}

extern void fl_internal_boxtype(Fl_Boxtype, Fl_Box_Draw_F*);
Fl_Boxtype fl_define_FL_ROUND_UP_BOX() {
  fl_internal_boxtype(_FL_ROUND_DOWN_BOX, fl_round_down_box);
  fl_internal_boxtype(_FL_ROUND_UP_BOX, fl_round_up_box);
  return _FL_ROUND_UP_BOX;
}

//
// End of "$Id: fl_round_box.cxx 10781 2015-07-09 00:10:44Z AlbrechtS $".
//
