// diamond.cxx
//
// "$Id: fl_diamond_box.cxx 10781 2015-07-09 00:10:44Z AlbrechtS $"
//
// Diamond box code for the Fast Light Tool Kit (FLTK).
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

// Box drawing code for an obscure box type.
// These box types are in separate files so they are not linked
// in if not used.

// The diamond box draws best if the area is square!

#include <fl/fl.h>
#include <fl/fl_draw.h>

extern const uchar* fl_gray_ramp();

static void fl_diamond_up_box(int x,int y,int w,int h,Fl_Color bgcolor) {
  w &= -2;
  h &= -2;
  int x1 = x+w/2;
  int y1 = y+h/2;
  Fl::set_box_color(bgcolor);
  fl_polygon(x+3, y1, x1,y+3, x+w-3,y1, x1,y+h-3);
  const uchar *g = fl_gray_ramp();
  fl_color(g[(int)'W']); fl_line(x+1, y1, x1, y+1, x+w-1, y1);
  fl_color(g[(int)'U']); fl_line(x+2, y1, x1, y+2, x+w-2, y1);
  fl_color(g[(int)'S']); fl_line(x+3, y1, x1, y+3, x+w-3, y1);
  fl_color(g[(int)'P']); fl_line(x+3, y1, x1, y+h-3, x+w-3, y1);
  fl_color(g[(int)'N']); fl_line(x+2, y1, x1, y+h-2, x+w-2, y1);
  fl_color(g[(int)'H']); fl_line(x+1, y1, x1, y+h-1, x+w-1, y1);
  fl_color(g[(int)'A']); fl_loop(x, y1, x1, y, x+w, y1, x1, y+h);
}

static void fl_diamond_down_box(int x,int y,int w,int h,Fl_Color bgcolor) {
  w &= -2;
  h &= -2;
  int x1 = x+w/2;
  int y1 = y+h/2;
  const uchar *g = fl_gray_ramp();
  fl_color(g[(int)'P']); fl_line(x+0, y1, x1, y+0, x+w-0, y1);
  fl_color(g[(int)'N']); fl_line(x+1, y1, x1, y+1, x+w-1, y1);
  fl_color(g[(int)'H']); fl_line(x+2, y1, x1, y+2, x+w-2, y1);
  fl_color(g[(int)'W']); fl_line(x+2, y1, x1, y+h-2, x+w-2, y1);
  fl_color(g[(int)'U']); fl_line(x+1, y1, x1, y+h-1, x+w-1, y1);
  fl_color(g[(int)'S']); fl_line(x+0, y1, x1, y+h-0, x+w-0, y1);
  Fl::set_box_color(bgcolor);
  fl_polygon(x+3, y1, x1,y+3, x+w-3,y1, x1,y+h-3);
  fl_color(g[(int)'A']); fl_loop(x+3, y1, x1, y+3, x+w-3, y1, x1, y+h-3);
}

extern void fl_internal_boxtype(Fl_Boxtype, Fl_Box_Draw_F*);
Fl_Boxtype fl_define_FL_DIAMOND_BOX() {
  fl_internal_boxtype(_FL_DIAMOND_DOWN_BOX, fl_diamond_down_box);
  fl_internal_boxtype(_FL_DIAMOND_UP_BOX,fl_diamond_up_box);
  return _FL_DIAMOND_UP_BOX;
}

//
// End of "$Id: fl_diamond_box.cxx 10781 2015-07-09 00:10:44Z AlbrechtS $".
//
