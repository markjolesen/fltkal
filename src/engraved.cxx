// engraved.cxx
//
// "$Id: fl_engraved_label.cxx 10252 2014-08-23 09:22:17Z cand $"
//
// Engraved label drawing routines for the Fast Light Tool Kit (FLTK).
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

// Drawing code for XForms style engraved & embossed labels

#include <fl/fl.h>
#include <fl/widget.h>
#include <fl/fl_draw.h>

// data[] is dx, dy, color triples

static void innards(
    const Fl_Label* o, int X, int Y, int W, int H, Fl_Align align,
    const int data[][3], int n)
{
  Fl_Align a1 = align;
  if (a1 & FL_ALIGN_CLIP) {
    fl_push_clip(X, Y, W, H); a1 = (Fl_Align)(a1&~FL_ALIGN_CLIP);}
  fl_font((Fl_Font)o->font, o->size);
  for (int i = 0; i < n; i++) {
    fl_color((Fl_Color)(i < n-1 ? data[i][2] : o->color));
    fl_draw(o->value, X+data[i][0], Y+data[i][1], W, H, a1);
  }
  if (align & FL_ALIGN_CLIP) fl_pop_clip();
}

static void fl_shadow_label(
    const Fl_Label* o, int X, int Y, int W, int H, Fl_Align align)
{
  static const int data[2][3] = {{2,2,FL_DARK3},{0,0,0}};
  innards(o, X, Y, W, H, align, data, 2);
}

static void fl_engraved_label(
    const Fl_Label* o, int X, int Y, int W, int H, Fl_Align align)
{
  static const int data[7][3] = {
    {1,0,FL_LIGHT3},{1,1,FL_LIGHT3},{0,1,FL_LIGHT3},
    {-1,0,FL_DARK3},{-1,-1,FL_DARK3},{0,-1,FL_DARK3},
    {0,0,0}};
  innards(o, X, Y, W, H, align, data, 7);
}

static void fl_embossed_label(
    const Fl_Label* o, int X, int Y, int W, int H, Fl_Align align)
{
  static const int data[7][3] = {
    {-1,0,FL_LIGHT3},{-1,-1,FL_LIGHT3},{0,-1,FL_LIGHT3},
    {1,0,FL_DARK3},{1,1,FL_DARK3},{0,1,FL_DARK3},
    {0,0,0}};
  innards(o, X, Y, W, H, align, data, 7);
}

Fl_Labeltype fl_define_FL_SHADOW_LABEL() {
  Fl::set_labeltype(_FL_SHADOW_LABEL, fl_shadow_label, 0);
  return _FL_SHADOW_LABEL;
}
Fl_Labeltype fl_define_FL_ENGRAVED_LABEL() {
  Fl::set_labeltype(_FL_ENGRAVED_LABEL, fl_engraved_label, 0);
  return _FL_ENGRAVED_LABEL;
}
Fl_Labeltype fl_define_FL_EMBOSSED_LABEL() {
  Fl::set_labeltype(_FL_EMBOSSED_LABEL, fl_embossed_label, 0);
  return _FL_EMBOSSED_LABEL;
}

//
// End of "$Id: fl_engraved_label.cxx 10252 2014-08-23 09:22:17Z cand $".
//
