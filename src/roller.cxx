// roller.cxx
//
// "$Id: Fl_Roller.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Roller widget for the Fast Light Tool Kit (FLTK).
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

// Rapid-App style knob

#include <fl/fl.h>
#include <fl/roller.h>
#include <fl/fl_draw.h>
#include <fl/fl_math.h>

int Fl_Roller::handle(int event) {
  static int ipos;
  int newpos = horizontal() ? Fl::event_x() : Fl::event_y();
  switch (event) {
  case FL_PUSH:
    if (Fl::visible_focus()) {
      Fl::focus(this);
      redraw();
    }
    handle_push();
    ipos = newpos;
    return 1;
  case FL_DRAG:
    handle_drag(clamp(round(increment(previous_value(),newpos-ipos))));
    return 1;
  case FL_RELEASE:
    handle_release();
    return 1;
  case FL_KEYBOARD :
    switch (Fl::event_key()) {
      case FL_Up:
        if (horizontal()) return 0;
	handle_drag(clamp(increment(value(),-1)));
	return 1;
      case FL_Down:
        if (horizontal()) return 0;
	handle_drag(clamp(increment(value(),1)));
	return 1;
      case FL_Left:
        if (!horizontal()) return 0;
	handle_drag(clamp(increment(value(),-1)));
	return 1;
      case FL_Right:
        if (!horizontal()) return 0;
	handle_drag(clamp(increment(value(),1)));
	return 1;
      default:
        return 0;
    }
    // break not required because of switch...
  case FL_FOCUS :
  case FL_UNFOCUS :
    if (Fl::visible_focus()) {
      redraw();
      return 1;
    } else return 0;
  case FL_ENTER :
  case FL_LEAVE :
    return 1;
  default:
    return 0;
  }
}

void Fl_Roller::draw() {
  if (damage()&FL_DAMAGE_ALL) draw_box();
  int X = x()+Fl::box_dx(box());
  int Y = y()+Fl::box_dy(box());
  int W = w()-Fl::box_dw(box())-1;
  int H = h()-Fl::box_dh(box())-1;
  if (W<=0 || H <=0) return;
  int offset = step() ? int(value()/step()) : 0;
  const double ARC = 1.5; // 1/2 the number of radians visible
  const double delta = .2; // radians per knurl
  if (horizontal()) { // horizontal one
    // draw shaded ends of wheel:
    int h1 = W/4+1; // distance from end that shading starts
    fl_color(color()); fl_rectf(X+h1,Y,W-2*h1,H);
    for (int i=0; h1; i++) {
      fl_color((Fl_Color)(FL_GRAY-i-1));
      int h2 = FL_GRAY-i-1 > FL_DARK3 ? 2*h1/3+1 : 0;
      fl_rectf(X+h2,Y,h1-h2,H);
      fl_rectf(X+W-h1,Y,h1-h2,H);
      h1 = h2;
    }
    if (active_r()) {
      // draw ridges:
      double junk;
      for (double yy = -ARC+modf(offset*sin(ARC)/(W/2)/delta,&junk)*delta;;
	   yy += delta) {
	int yy1 = int((sin(yy)/sin(ARC)+1)*W/2);
	if (yy1 <= 0) continue; else if (yy1 >= W-1) break;
	fl_color(FL_DARK3); fl_yxline(X+yy1,Y+1,Y+H-1);
	if (yy < 0) yy1--; else yy1++;
	fl_color(FL_LIGHT1);fl_yxline(X+yy1,Y+1,Y+H-1);
      }
      // draw edges:
      h1 = W/8+1; // distance from end the color inverts
      fl_color(FL_DARK2);
      fl_xyline(X+h1,Y+H-1,X+W-h1);
      fl_color(FL_DARK3);
      fl_yxline(X,Y+H,Y,X+h1);
      fl_xyline(X+W-h1,Y,X+W);
      fl_color(FL_LIGHT2);
      fl_xyline(X+h1,Y-1,X+W-h1);
      fl_yxline(X+W,Y,Y+H,X+W-h1);
      fl_xyline(X+h1,Y+H,X);
    }
  } else { // vertical one
    // draw shaded ends of wheel:
    int h1 = H/4+1; // distance from end that shading starts
    fl_color(color()); fl_rectf(X,Y+h1,W,H-2*h1);
    for (int i=0; h1; i++) {
      fl_color((Fl_Color)(FL_GRAY-i-1));
      int h2 = FL_GRAY-i-1 > FL_DARK3 ? 2*h1/3+1 : 0;
      fl_rectf(X,Y+h2,W,h1-h2);
      fl_rectf(X,Y+H-h1,W,h1-h2);
      h1 = h2;
    }
    if (active_r()) {
      // draw ridges:
      double junk;
      for (double yy = -ARC+modf(offset*sin(ARC)/(H/2)/delta,&junk)*delta;
	   ; yy += delta) {
	int yy1 = int((sin(yy)/sin(ARC)+1)*H/2);
	if (yy1 <= 0) continue; else if (yy1 >= H-1) break;
	fl_color(FL_DARK3); fl_xyline(X+1,Y+yy1,X+W-1);
	if (yy < 0) yy1--; else yy1++;
	fl_color(FL_LIGHT1);fl_xyline(X+1,Y+yy1,X+W-1);
      }
      // draw edges:
      h1 = H/8+1; // distance from end the color inverts
      fl_color(FL_DARK2);
      fl_yxline(X+W-1,Y+h1,Y+H-h1);
      fl_color(FL_DARK3);
      fl_xyline(X+W,Y,X,Y+h1);
      fl_yxline(X,Y+H-h1,Y+H);
      fl_color(FL_LIGHT2);
      fl_yxline(X,Y+h1,Y+H-h1);
      fl_xyline(X,Y+H,X+W,Y+H-h1);
      fl_yxline(X+W,Y+h1,Y);
    }
  }

  if (Fl::focus() == this) draw_focus(FL_THIN_UP_FRAME, x(), y(), w(), h());
}

/**
  Creates a new Fl_Roller widget using the given position,
  size, and label string. The default boxtype is FL_NO_BOX.
  <P>Inherited destructor destroys the valuator.
*/
Fl_Roller::Fl_Roller(int X,int Y,int W,int H,const char* L)
  : Fl_Valuator(X,Y,W,H,L) {
  box(FL_UP_BOX);
  step(1,1000);
}

//
// End of "$Id: Fl_Roller.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
