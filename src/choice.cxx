// choice.cxx
//
// "$Id: Fl_Choice.cxx 11908 2016-08-30 19:16:50Z greg.ercolano $"
//
// Choice widget for the Fast Light Tool Kit (FLTK).
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

#include <fl/fl.h>
#include <fl/choice.h>
#include <fl/fl_draw.h>
#include "flstring.h"

// Emulates the Forms choice widget.  This is almost exactly the same
// as an Fl_Menu_Button.  The only difference is the appearance of the
// button: it draws the text of the current pick and a down-arrow.

void Fl_Choice::draw() {
  Fl_Boxtype btype = Fl::scheme() ? FL_UP_BOX		// non-default uses up box
                                  : FL_DOWN_BOX;	// default scheme uses down box
  int dx = Fl::box_dx(btype);
  int dy = Fl::box_dy(btype);

  // Arrow area
  int H = h() - 2 * dy;
  int W = Fl::is_scheme("gtk+")    ? 20 :			// gtk+  -- fixed size
          Fl::is_scheme("gleam")   ? 20 :			// gleam -- fixed size
          Fl::is_scheme("plastic") ? ((H > 20) ? 20 : H)	// plastic: shrink if H<20
                                   : ((H > 20) ? 20 : H);	// default: shrink if H<20
  int X = x() + w() - W - dx;
  int Y = y() + dy;

  // Arrow object
  int w1 = (W - 4) / 3; if (w1 < 1) w1 = 1;
  int x1 = X + (W - 2 * w1 - 1) / 2;
  int y1 = Y + (H - w1 - 1) / 2;

  if (Fl::scheme()) {
    // NON-DEFAULT SCHEME

    // Draw widget box
    draw_box(btype, color());

    // Draw arrow area
    fl_color(active_r() ? labelcolor() : fl_inactive(labelcolor()));
    if (Fl::is_scheme("plastic")) {
      // Show larger up/down arrows...
      fl_polygon(x1, y1 + 3, x1 + w1, y1 + w1 + 3, x1 + 2 * w1, y1 + 3);
      fl_polygon(x1, y1 + 1, x1 + w1, y1 - w1 + 1, x1 + 2 * w1, y1 + 1);
    } else {
      // Show smaller up/down arrows with a divider...
      x1 = x() + w() - 13 - dx;
      y1 = y() + h() / 2;
      fl_polygon(x1, y1 - 2, x1 + 3, y1 - 5, x1 + 6, y1 - 2);
      fl_polygon(x1, y1 + 2, x1 + 3, y1 + 5, x1 + 6, y1 + 2);

      fl_color(fl_darker(color()));
      fl_yxline(x1 - 7, y1 - 8, y1 + 8);

      fl_color(fl_lighter(color()));
      fl_yxline(x1 - 6, y1 - 8, y1 + 8);
    }
  } else {
    // DEFAULT SCHEME

    // Draw widget box
    if (fl_contrast(textcolor(), FL_BACKGROUND2_COLOR) == textcolor()) {
      draw_box(btype, FL_BACKGROUND2_COLOR);
    } else {
      draw_box(btype, fl_lighter(color()));
    }

    // Draw arrow area
    draw_box(FL_UP_BOX,X,Y,W,H,color());
    fl_color(active_r() ? labelcolor() : fl_inactive(labelcolor()));
    fl_polygon(x1, y1, x1 + w1, y1 + w1, x1 + 2 * w1, y1);
  }

  W += 2 * dx;

  // Draw menu item's label
  if (mvalue()) {
    Fl_Menu_Item m = *mvalue();
    if (active_r()) m.activate(); else m.deactivate();

    // Clip
    int xx = x() + dx, yy = y() + dy + 1, ww = w() - W, hh = H - 2;
    fl_push_clip(xx, yy, ww, hh);

    if ( Fl::scheme()) {
      Fl_Label l;
      l.value = m.text;
      l.image = 0;
      l.deimage = 0;
      l.type = m.labeltype_;
      l.font = m.labelsize_ || m.labelfont_ ? m.labelfont_ : textfont();
      l.size = m.labelsize_ ? m.labelsize_ : textsize();
      l.color= m.labelcolor_ ? m.labelcolor_ : textcolor();
      if (!m.active()) l.color = fl_inactive((Fl_Color)l.color);
      fl_draw_shortcut = 2; // hack value to make '&' disappear
      l.draw(xx+3, yy, ww>6 ? ww-6 : 0, hh, FL_ALIGN_LEFT);
      fl_draw_shortcut = 0;
      if ( Fl::focus() == this ) draw_focus(box(), xx, yy, ww, hh);
    }
    else {
      fl_draw_shortcut = 2; // hack value to make '&' disappear
      m.draw(xx, yy, ww, hh, this, Fl::focus() == this);
      fl_draw_shortcut = 0;
    }

    fl_pop_clip();
  }

  // Widget's label
  draw_label();
}

/**
  Create a new Fl_Choice widget using the given position, size and label string.
  The default boxtype is \c FL_UP_BOX.

  The constructor sets menu() to NULL.
  See Fl_Menu_ for the methods to set or change the menu.

  \param[in] X, Y, W, H position and size of the widget
  \param[in] L widget label, default is no label
 */
Fl_Choice::Fl_Choice(int X, int Y, int W, int H, const char *L)
: Fl_Menu_(X,Y,W,H,L) {
  align(FL_ALIGN_LEFT);
  when(FL_WHEN_RELEASE);
  textfont(FL_HELVETICA);
  box(FL_FLAT_BOX);
  down_box(FL_BORDER_BOX);
}

/**
  Sets the currently selected value using a pointer to menu item.
  Changing the selected value causes a redraw().
  \param[in] v pointer to menu item in the menu item array.
  \returns non-zero if the new value is different to the old one.
 */
int Fl_Choice::value(const Fl_Menu_Item *v) {
  if (!Fl_Menu_::value(v)) return 0;
  redraw();
  return 1;
}

/**
  Sets the currently selected value using the index into the menu item array.
  Changing the selected value causes a redraw().
  \param[in] v index of value in the menu item array.
  \returns non-zero if the new value is different to the old one.
 */
int Fl_Choice::value(int v) {
  if (v == -1) return value((const Fl_Menu_Item *)0);
  if (v < 0 || v >= (size() - 1)) return 0;
  if (!Fl_Menu_::value(v)) return 0;
  redraw();
  return 1;
}

int Fl_Choice::handle(int e) {
  if (!menu() || !menu()->text) return 0;
  const Fl_Menu_Item* v;
  switch (e) {
  case FL_ENTER:
  case FL_LEAVE:
    return 1;

  case FL_KEYBOARD:
    if (Fl::event_key() != ' ' ||
        (Fl::event_state() & (FL_SHIFT | FL_CTRL | FL_ALT | FL_META))) return 0;
  case FL_PUSH:
    if (Fl::visible_focus()) Fl::focus(this);
  J1:
    if (Fl::scheme()
	|| fl_contrast(textcolor(), FL_BACKGROUND2_COLOR) != textcolor()) {
      v = menu()->pulldown(x(), y(), w(), h(), mvalue(), this);
    } else {
      // In order to preserve the old look-n-feel of "white" menus,
      // temporarily override the color() of this widget...
      Fl_Color c = color();
      color(FL_BACKGROUND2_COLOR);
      v = menu()->pulldown(x(), y(), w(), h(), mvalue(), this);
      color(c);
    }
    if (!v || v->submenu()) return 1;
    if (v != mvalue()) redraw();
    picked(v);
    return 1;
  case FL_SHORTCUT:
    if (Fl_Widget::test_shortcut()) goto J1;
    v = menu()->test_shortcut();
    if (!v) return 0;
    if (v != mvalue()) redraw();
    picked(v);
    return 1;
  case FL_FOCUS:
  case FL_UNFOCUS:
    if (Fl::visible_focus()) {
      redraw();
      return 1;
    } else return 0;
  default:
    return 0;
  }
}

//
// End of "$Id: Fl_Choice.cxx 11908 2016-08-30 19:16:50Z greg.ercolano $".
//