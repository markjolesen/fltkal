// dial.cxx
//
// "$Id: Fl_Dial.cxx 12279 2017-06-29 01:13:05Z AlbrechtS $"
//
// Circular dial widget for the Fast Light Tool Kit (FLTK).
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
#include <fl/dial.h>
#include <fl/dialfill.h>
#include <fl/dialline.h>
#include <fl/fl_draw.h>
#include <stdlib.h>
#include <fl/fl_math.h>


// All angles are measured with 0 to the right and counter-clockwise
/**
  Draws dial at given position and size.
  \param[in] X, Y, W, H position and size
*/
void Fl_Dial::draw(int X, int Y, int W, int H) {
  if (damage()&FL_DAMAGE_ALL) draw_box(box(), X, Y, W, H, color());
  X += Fl::box_dx(box());
  Y += Fl::box_dy(box());
  W -= Fl::box_dw(box());
  H -= Fl::box_dh(box());
  double angle = (a2-a1)*(value()-minimum())/(maximum()-minimum()) + a1;
  if (type() == FL_FILL_DIAL) {
    // foo: draw this nicely in certain round box types
    int foo = (box() > _FL_ROUND_UP_BOX && Fl::box_dx(box()));
    if (foo) {X--; Y--; W+=2; H+=2;}
    if (active_r()) fl_color(color());
    else fl_color(fl_inactive(color()));
    fl_pie(X, Y, W, H, 270-a1, angle > a1 ? 360+270-angle : 270-360-angle);
    if (active_r()) fl_color(selection_color());
    else fl_color(fl_inactive(selection_color()));
    fl_pie(X, Y, W, H, 270-angle, 270-a1);
    if (foo) {
      if (active_r()) fl_color(FL_FOREGROUND_COLOR);
      else fl_color(fl_inactive(FL_FOREGROUND_COLOR));
      fl_arc(X, Y, W, H, 0, 360);
    }
    return;
  }
  if (!(damage()&FL_DAMAGE_ALL)) {
    if (active_r()) fl_color(color());
    else fl_color(fl_inactive(color()));
    fl_pie(X+1, Y+1, W-2, H-2, 0, 360);
  }
  fl_push_matrix();
  fl_translate(X+W/2-.5, Y+H/2-.5);
  fl_scale(W-1, H-1);
  fl_rotate(45-angle);
  if (active_r()) fl_color(selection_color());
  else fl_color(fl_inactive(selection_color()));
  if (type()) { // FL_LINE_DIAL
    fl_begin_polygon();
    fl_vertex(0.0,   0.0);
    fl_vertex(-0.04, 0.0);
    fl_vertex(-0.25, 0.25);
    fl_vertex(0.0,   0.04);
    fl_end_polygon();
    if (active_r()) fl_color(FL_FOREGROUND_COLOR);
    else fl_color(fl_inactive(FL_FOREGROUND_COLOR));
    fl_begin_loop();
    fl_vertex(0.0,   0.0);
    fl_vertex(-0.04, 0.0);
    fl_vertex(-0.25, 0.25);
    fl_vertex(0.0,   0.04);
    fl_end_loop();
  } else {
    fl_begin_polygon(); fl_circle(-0.20, 0.20, 0.07); fl_end_polygon();
    if (active_r()) fl_color(FL_FOREGROUND_COLOR);
    else fl_color(fl_inactive(FL_FOREGROUND_COLOR));
    fl_begin_loop(); fl_circle(-0.20, 0.20, 0.07); fl_end_loop();
  }
  fl_pop_matrix();
}

/**
  Draws dial at current position and size.
*/
void Fl_Dial::draw() {
  draw(x(), y(), w(), h());
  draw_label();
}

/**
  Allows subclasses to handle event based on given position and size.
  \param[in] event, X, Y, W, H event to handle, related position and size.
*/
int Fl_Dial::handle(int event, int X, int Y, int W, int H) {
  switch (event) {
  case FL_PUSH:
    handle_push();
    /* FALLTHROUGH */
  case FL_DRAG: {
    int mx = (Fl::event_x()-X-W/2)*H;
    int my = (Fl::event_y()-Y-H/2)*W;
    if (!mx && !my) return 1;
    double angle = 270-atan2((float)-my, (float)mx)*180/M_PI;
    double oldangle = (a2-a1)*(value()-minimum())/(maximum()-minimum()) + a1;
    while (angle < oldangle-180) angle += 360;
    while (angle > oldangle+180) angle -= 360;
    double val;
    if ((a1<a2) ? (angle <= a1) : (angle >= a1)) {
      val = minimum();
    } else if ((a1<a2) ? (angle >= a2) : (angle <= a2)) {
      val = maximum();
    } else {
      val = minimum() + (maximum()-minimum())*(angle-a1)/(a2-a1);
    }
    handle_drag(clamp(round(val)));
    return 1;
  } /* NOTREACHED */
  case FL_RELEASE:
    handle_release();
    return 1;
  case FL_ENTER: /* FALLTHROUGH */
  case FL_LEAVE:
    return 1;
  default:
    return 0;
  }
}

/**
  Allow subclasses to handle event based on current position and size.
*/
int Fl_Dial::handle(int e) {
  return handle(e, x(), y(), w(), h());
}

Fl_Dial::Fl_Dial(int X, int Y, int W, int H, const char* l)
/**
  Creates a new Fl_Dial widget using the given position, size,
  and label string. The default type is FL_NORMAL_DIAL.
*/
: Fl_Valuator(X, Y, W, H, l) {
  box(FL_OVAL_BOX);
  selection_color(FL_INACTIVE_COLOR); // was 37
  a1 = 45;
  a2 = 315;
}


Fl_Fill_Dial::Fl_Fill_Dial(int X,int Y,int W,int H, const char *L)
: Fl_Dial(X,Y,W,H,L) {
  type(FL_FILL_DIAL);
}


Fl_Line_Dial::Fl_Line_Dial(int X,int Y,int W,int H, const char *L)
: Fl_Dial(X,Y,W,H,L) {
  type(FL_LINE_DIAL);
}


//
// End of "$Id: Fl_Dial.cxx 12279 2017-06-29 01:13:05Z AlbrechtS $".
//
