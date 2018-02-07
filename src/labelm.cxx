// labelm.cxx
//
// "$Id: Fl_Multi_Label.cxx 12443 2017-09-11 18:54:10Z AlbrechtS $"
//
// Multi-label widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2017 by Bill Spitzak and others.
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

// Allows two or more labels to be used on a widget (by having one of them
// be one of these it allows an infinite number!)

#include <fl/fl.h>
#include <fl/widget.h>
#include <fl/menuitem.h>
#include <fl/labelm.h>

static void multi_labeltype(
    const Fl_Label* o, int x, int y, int w, int h, Fl_Align a)
{
  Fl_Multi_Label* b = (Fl_Multi_Label*)(o->value);
  Fl_Label local = *o;
  local.value = b->labela;
  local.type = b->typea;
  int W = w; int H = h; local.measure(W, H);
  local.draw(x,y,w,h,a);
  if (a & FL_ALIGN_BOTTOM) h -= H;
  else if (a & FL_ALIGN_TOP) {y += H; h -= H;}
  else if (a & FL_ALIGN_RIGHT) w -= W;
  else if (a & FL_ALIGN_LEFT) {x += W; w -= W;}
  else {int d = (h+H)/2; y += d; h -= d;}
  local.value = b->labelb;
  local.type = b->typeb;
  local.draw(x,y,w,h,a);
}

// measurement is only correct for left-to-right appending...
static void multi_measure(const Fl_Label* o, int& w, int& h) {
  Fl_Multi_Label* b = (Fl_Multi_Label*)(o->value);
  Fl_Label local = *o;
  local.value = b->labela;
  local.type = b->typea;
  local.measure(w,h);
  local.value = b->labelb;
  local.type = b->typeb;
  int W = 0; int H = 0; local.measure(W,H);
  w += W; if (H>h) h = H;
}

// used by FL_MULTI_LABEL to set up the internal table, see FL/Enumerations.H
Fl_Labeltype fl_define_FL_MULTI_LABEL() {
  Fl::set_labeltype(_FL_MULTI_LABEL, multi_labeltype, multi_measure);
  return _FL_MULTI_LABEL;
}

void Fl_Multi_Label::label(Fl_Widget* o) {
  o->label(FL_MULTI_LABEL, (const char*)this); // calls fl_define_FL_MULTI_LABEL()
}

void Fl_Multi_Label::label(Fl_Menu_Item* o) {
  o->label(FL_MULTI_LABEL, (const char*)this); // calls fl_define_FL_MULTI_LABEL()
}

//
// End of "$Id: Fl_Multi_Label.cxx 12443 2017-09-11 18:54:10Z AlbrechtS $".
//
