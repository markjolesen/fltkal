// btnlt.cxx
//
// "$Id: Fl_Light_Button.cxx 10775 2015-06-27 15:20:23Z AlbrechtS $"
//
// Lighted button widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2015 by Bill Spitzak and others.
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

// Subclass of Fl_Button where the "box" indicates whether it is
// pushed or not, and the "down box" is drawn small and square on
// the left to indicate the current state.

// The default down_box of zero draws a rectangle designed to look
// just like Flame's buttons.

#include <fl/fl.h>
#include <fl/btnlt.h>
#include <fl/btnradlt.h>
#include <fl/fl_draw.h>
#include "flstring.h"

void Fl_Light_Button::draw() {
  if (box()) draw_box(this==Fl::pushed() ? fl_down(box()) : box(), color());
  Fl_Color col = value() ? (active_r() ? selection_color() :
                            fl_inactive(selection_color())) : color();

  int W  = labelsize();
  int bx = Fl::box_dx(box());	// box frame width
  int dx = bx + 2;		// relative position of check mark etc.
  int dy = (h() - W) / 2;	// neg. offset o.k. for vertical centering
  int lx = 0;			// relative label position (STR #3237)

  if (down_box()) {
    // draw other down_box() styles:
    switch (down_box()) {
      case FL_DOWN_BOX :
      case FL_UP_BOX :
      case _FL_PLASTIC_DOWN_BOX :
      case _FL_PLASTIC_UP_BOX :
        // Check box...
        draw_box(down_box(), x()+dx, y()+dy, W, W, FL_BACKGROUND2_COLOR);
	if (value()) {
	  if (Fl::is_scheme("gtk+")) {
	    fl_color(FL_SELECTION_COLOR);
	  } else {
	    fl_color(col);
	  }
	  int tx = x() + dx + 3;
	  int tw = W - 6;
	  int d1 = tw/3;
	  int d2 = tw-d1;
	  int ty = y() + dy + (W+d2)/2-d1-2;
	  for (int n = 0; n < 3; n++, ty++) {
	    fl_line(tx, ty, tx+d1, ty+d1);
	    fl_line(tx+d1, ty+d1, tx+tw-1, ty+d1-d2+1);
	  }
	}
        break;
      case _FL_ROUND_DOWN_BOX :
      case _FL_ROUND_UP_BOX :
        // Radio button...
        draw_box(down_box(), x()+dx, y()+dy, W, W, FL_BACKGROUND2_COLOR);
	if (value()) {
	  int tW = (W - Fl::box_dw(down_box())) / 2 + 1;
	  if ((W - tW) & 1) tW++; // Make sure difference is even to center
	  int tdx = dx + (W - tW) / 2;
	  int tdy = dy + (W - tW) / 2;

	  if (Fl::is_scheme("gtk+")) {
	    fl_color(FL_SELECTION_COLOR);
	    tW --;
	    fl_pie(x() + tdx - 1, y() + tdy - 1, tW + 3, tW + 3, 0.0, 360.0);
	    fl_color(fl_color_average(FL_WHITE, FL_SELECTION_COLOR, 0.2f));
	  } else fl_color(col);

	  switch (tW) {
	    // Larger circles draw fine...
	    default :
              fl_pie(x() + tdx, y() + tdy, tW, tW, 0.0, 360.0);
	      break;

            // Small circles don't draw well on many systems...
	    case 6 :
	      fl_rectf(x() + tdx + 2, y() + tdy, tW - 4, tW);
	      fl_rectf(x() + tdx + 1, y() + tdy + 1, tW - 2, tW - 2);
	      fl_rectf(x() + tdx, y() + tdy + 2, tW, tW - 4);
	      break;

	    case 5 :
	    case 4 :
	    case 3 :
	      fl_rectf(x() + tdx + 1, y() + tdy, tW - 2, tW);
	      fl_rectf(x() + tdx, y() + tdy + 1, tW, tW - 2);
	      break;

	    case 2 :
	    case 1 :
	      fl_rectf(x() + tdx, y() + tdy, tW, tW);
	      break;
	  }

	  if (Fl::is_scheme("gtk+")) {
	    fl_color(fl_color_average(FL_WHITE, FL_SELECTION_COLOR, 0.5));
	    fl_arc(x() + tdx, y() + tdy, tW + 1, tW + 1, 60.0, 180.0);
	  }
	}
        break;
      default :
        draw_box(down_box(), x()+dx, y()+dy, W, W, col);
        break;
    }
    lx = dx + W + 2;
  } else {
    // if down_box() is zero, draw light button style:
    int hh = h()-2*dy - 2;
    int ww = W/2+1;
    int xx = dx;
    if (w()<ww+2*xx) xx = (w()-ww)/2;
    if (Fl::is_scheme("plastic")) {
      col = active_r() ? selection_color() : fl_inactive(selection_color());
      fl_color(value() ? col : fl_color_average(col, FL_BLACK, 0.5f));
      fl_pie(x()+xx, y()+dy+1, ww, hh, 0, 360);
    } else {
      draw_box(FL_THIN_DOWN_BOX, x()+xx, y()+dy+1, ww, hh, col);
    }
    lx = dx + ww + 2;
  }
  draw_label(x()+lx, y(), w()-lx-bx, h());
  if (Fl::focus() == this) draw_focus();
}

int Fl_Light_Button::handle(int event) {
  switch (event) {
  case FL_RELEASE:
    if (box()) redraw();
  default:
    return Fl_Button::handle(event);
  }
}

/**
  Creates a new Fl_Light_Button widget using the given
  position, size, and label string.
  <P>The destructor deletes the check button.
*/
Fl_Light_Button::Fl_Light_Button(int X, int Y, int W, int H, const char* l)
: Fl_Button(X, Y, W, H, l) {
  type(FL_TOGGLE_BUTTON);
  selection_color(FL_YELLOW);
  align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
}


Fl_Radio_Light_Button::Fl_Radio_Light_Button(int X,int Y,int W,int H,const char *l)
: Fl_Light_Button(X,Y,W,H,l) 
{
  type(FL_RADIO_BUTTON);
}


//
// End of "$Id: Fl_Light_Button.cxx 10775 2015-06-27 15:20:23Z AlbrechtS $".
//
