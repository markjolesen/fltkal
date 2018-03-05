// adjuster.cxx
//
// "$Id: Fl_Adjuster.cxx 9418 2012-04-30 23:18:28Z matt $"
//
// Adjuster widget for the Fast Light Tool Kit (FLTK).
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

#include <fl/fl.h>
#include <fl/adjuster.h>
#include <fl/imgbit.h>
#include <fl/fl_draw.h>

#include "arrowfas.h"
static Fl_Bitmap fastarrow(fastarrow_bits, fastarrow_width, fastarrow_height);
#include "arrowmed.h"
static Fl_Bitmap mediumarrow(mediumarrow_bits, mediumarrow_width, mediumarrow_height);
#include "arrowslo.h"
static Fl_Bitmap slowarrow(slowarrow_bits, slowarrow_width, slowarrow_height);

// changing the value does not change the appearance:
void Fl_Adjuster::value_damage() {}

void Fl_Adjuster::draw() {
  int dx, dy, W, H;
  if (w()>=h()) {
    dx = W = w()/3;
    dy = 0; H = h();
  } else {
    dx = 0; W = w();
    dy = H = h()/3;
  }
  draw_box(drag==1?FL_DOWN_BOX:box(), x(),  y()+2*dy, W, H, color());
  draw_box(drag==2?FL_DOWN_BOX:box(), x()+dx, y()+dy, W, H, color());
  draw_box(drag==3?FL_DOWN_BOX:box(), x()+2*dx,  y(), W, H, color());
  if (active_r())
    fl_color(selection_color());
  else
    fl_color(fl_inactive(selection_color()));
  fastarrow.draw(x()+(W-fastarrow_width)/2,
		 y()+2*dy+(H-fastarrow_height)/2, W, H);
  mediumarrow.draw(x()+dx+(W-mediumarrow_width)/2,
		   y()+dy+(H-mediumarrow_height)/2, W, H);
  slowarrow.draw(x()+2*dx+(W-slowarrow_width)/2,
		 y()+(H-slowarrow_width)/2, W, H);
  if (Fl::focus() == this) draw_focus();
}

int Fl_Adjuster::handle(int event) {
  double v;
  int delta;
  int mx = Fl::event_x();
  // Fl_Widget_Tracker wp(this);
  switch (event) {
    case FL_PUSH:
      if (Fl::visible_focus()) Fl::focus(this);
      ix = mx;
      if (w()>=h())
	drag = 3*(mx-x())/w() + 1;
      else
	drag = 3-3*(Fl::event_y()-y()-1)/h();
      { Fl_Widget_Tracker wp(this);
	handle_push();
	if (wp.deleted()) return 1;
      }
      redraw();
      return 1;
    case FL_DRAG:
      if (w() >= h()) {
	delta = x()+(drag-1)*w()/3;	// left edge of button
	if (mx < delta)
	  delta = mx-delta;
	else if (mx > (delta+w()/3)) // right edge of button
	  delta = mx-delta-w()/3;
	else
	  delta = 0;
      } else {
	if (mx < x())
	  delta = mx-x();
	else if (mx > (x()+w()))
	  delta = mx-x()-w();
	else
	  delta = 0;
      }
      switch (drag) {
	case 3: v = increment(previous_value(), delta); break;
	case 2: v = increment(previous_value(), delta*10); break;
	default:v = increment(previous_value(), delta*100); break;
      }
      handle_drag(soft() ? softclamp(v) : clamp(v));
      return 1;
    case FL_RELEASE:
      if (Fl::event_is_click()) { // detect click but no drag
	if (Fl::event_state()&0xF0000) delta = -10;
	else delta = 10;
	switch (drag) {
	  case 3: v = increment(previous_value(), delta); break;
	  case 2: v = increment(previous_value(), delta*10); break;
	  default:v = increment(previous_value(), delta*100); break;
	}
	Fl_Widget_Tracker wp(this);
	handle_drag(soft() ? softclamp(v) : clamp(v));
	if (wp.deleted()) return 1;
      }
      drag = 0;
      redraw();
      handle_release();
      return 1;
    case FL_KEYBOARD :
      switch (Fl::event_key()) {
	case FL_Up:
          if (w() > h()) return 0;
	  handle_drag(clamp(increment(value(),-1)));
	  return 1;
	case FL_Down:
          if (w() > h()) return 0;
	  handle_drag(clamp(increment(value(),1)));
	  return 1;
	case FL_Left:
          if (w() < h()) return 0;
	  handle_drag(clamp(increment(value(),-1)));
	  return 1;
	case FL_Right:
          if (w() < h()) return 0;
	  handle_drag(clamp(increment(value(),1)));
	  return 1;
	default:
          return 0;
      }
      // break not required because of switch...

    case FL_FOCUS:
    case FL_UNFOCUS:
      if (Fl::visible_focus()) {
        redraw();
        return 1;
      } else return 0;

    case FL_ENTER :
    case FL_LEAVE :
      return 1;
  }
  return 0;
}

/**
  Creates a new Fl_Adjuster widget using the given position,
  size, and label string. It looks best if one of the dimensions is 3
  times the other.
  <P> Inherited destructor destroys the Valuator.
*/
Fl_Adjuster::Fl_Adjuster(int X, int Y, int W, int H, const char* l)
  : Fl_Valuator(X, Y, W, H, l) {
  box(FL_UP_BOX);
  step(1, 10000);
  selection_color(FL_SELECTION_COLOR);
  drag = 0;
  soft_ = 1;
}

//
// End of "$Id: Fl_Adjuster.cxx 9418 2012-04-30 23:18:28Z matt $".
//
