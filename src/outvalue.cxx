// outvalue.cxx
//
// "$Id: Fl_Value_Output.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Value output widget for the Fast Light Tool Kit (FLTK).
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

// Fltk widget for drag-adjusting a floating point value.
// This is much lighter than Fl_Value_Input because it has no text editor
// If step() is zero then it can be used to display a floating-point value

#include <fl/fl.h>
#include <fl/outvalue.h>
#include <fl/fl_draw.h>

void Fl_Value_Output::draw() {
  Fl_Boxtype b = box() ? box() : FL_DOWN_BOX;
  int X = x()+Fl::box_dx(b);
  int Y = y()+Fl::box_dy(b);
  int W = w()-Fl::box_dw(b);
  int H = h()-Fl::box_dh(b);
  if (damage()&~FL_DAMAGE_CHILD)
    draw_box(b, color());
  else {
    fl_color(color());
    fl_rectf(X, Y, W, H);
  }
  char buf[128];
  format(buf);
  fl_color(active_r() ? textcolor() : fl_inactive(textcolor()));
  fl_font(textfont(), textsize());
  fl_draw(buf,X,Y,W,H,FL_ALIGN_LEFT);
}

int Fl_Value_Output::handle(int event) {
  if (!step()) return 0;
  double v;
  int delta;
  int mx = Fl::event_x();
  static int ix, drag;
  switch (event) {
  case FL_PUSH:
    ix = mx;
    drag = Fl::event_button();
    handle_push();
    return 1;
  case FL_DRAG:
    delta = Fl::event_x()-ix;
    if (delta > 5) delta -= 5;
    else if (delta < -5) delta += 5;
    else delta = 0;
    switch (drag) {
    case 3: v = increment(previous_value(),delta*100); break;
    case 2: v = increment(previous_value(),delta*10); break;
    default:v = increment(previous_value(),delta); break;
    }
    v = round(v);
    handle_drag(soft()?softclamp(v):clamp(v));;
    return 1;
  case FL_RELEASE:
    handle_release();
    return 1;
  case FL_ENTER :
  case FL_LEAVE :
    return 1;
  default:
    return 0;
  }
}

/**
  Creates a new Fl_Value_Output widget using the given
  position, size, and label string. The default boxtype is FL_NO_BOX.
  <P> Inherited destructor destroys the Valuator.
*/
Fl_Value_Output::Fl_Value_Output(int X, int Y, int W, int H,const char *l)
: Fl_Valuator(X,Y,W,H,l) {
  box(FL_NO_BOX);
  align(FL_ALIGN_LEFT);
  textfont_ = FL_HELVETICA;
  textsize_ = FL_NORMAL_SIZE;
  textcolor_ = FL_FOREGROUND_COLOR;
  soft_ = 0;
}

//
// End of "$Id: Fl_Value_Output.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
