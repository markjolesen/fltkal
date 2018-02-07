// btnk.cxx
//
// "$Id: Fl_Check_Button.cxx 10386 2014-10-19 20:17:17Z AlbrechtS $"
//
// Check button widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2014 by Bill Spitzak and others.
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
#include <fl/btnk.h>

/**
  \class Fl_Check_Button
  \brief A button with a "checkmark" to show its status.

  \image html Fl_Check_Button.png
  \image latex Fl_Check_Button.png  "Fl_Check_Button" width=4cm

  Buttons generate callbacks when they are clicked by the user. You control
  exactly when and how by changing the values for type() and when().

  The Fl_Check_Button subclass displays its "ON" state by showing a "checkmark"
  rather than drawing itself pushed in.
 */

/**
  Creates a new Fl_Check_Button widget using the given position, size, and label string.

  The default box type is FL_NO_BOX, which draws the label w/o a box
  right of the checkmark.

  The selection_color() sets the color of the checkmark.
  Default is FL_FOREGROUND_COLOR (usually black).

  You can use down_box() to change the box type of the checkmark.
  Default is FL_DOWN_BOX.

  \param[in] X, Y, W, H position and size of the widget
  \param[in] L widget label, default is no label
 */
Fl_Check_Button::Fl_Check_Button(int X, int Y, int W, int H, const char *L)
: Fl_Light_Button(X, Y, W, H, L) {
  box(FL_NO_BOX);
  down_box(FL_DOWN_BOX);
  selection_color(FL_FOREGROUND_COLOR);
}
