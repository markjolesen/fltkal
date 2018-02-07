// btnro.cxx
//
// "$Id: Fl_Round_Button.cxx 10386 2014-10-19 20:17:17Z AlbrechtS $"
//
// Round button for the Fast Light Tool Kit (FLTK).
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

// A subclass of Fl_Button that always draws as a round circle.  This
// circle is smaller than the widget size and can be surrounded by
// another box type, for compatibility with Forms.

#include <fl/fl.h>
#include <fl/btnro.h>
#include <fl/btnradro.h>

/**
  Creates a new Fl_Round_Button widget using the given position, size, and label string.

  \image html Fl_Round_Button.png
  \image latex Fl_Round_Button.png " Fl_Round_Button" width=4cm

  The Fl_Round_Button subclass displays the "ON" state by
  turning on a light, rather than drawing pushed in.

  The default box type is FL_NO_BOX, which draws the label w/o a box
  right of the checkmark.

  The shape of the "light" is set with down_box() and its default
  value is FL_ROUND_DOWN_BOX.

  The color of the light when on is controlled with selection_color(),
  which defaults to FL_FOREGROUND_COLOR (usually black).

  \param[in] X, Y, W, H position and size of the widget
  \param[in] L widget label, default is no label
*/
Fl_Round_Button::Fl_Round_Button(int X,int Y,int W,int H, const char *L)
: Fl_Light_Button(X,Y,W,H,L) {
  box(FL_NO_BOX);
  down_box(FL_ROUND_DOWN_BOX);
  selection_color(FL_FOREGROUND_COLOR);
}

/**
  Creates a new Fl_Radio_Button widget using the given position, size, and label string.

  The button type() is set to FL_RADIO_BUTTON.

  \param[in] X, Y, W, H position and size of the widget
  \param[in] L widget label, default is no label
*/

Fl_Radio_Round_Button::Fl_Radio_Round_Button(int X,int Y,int W,int H,const char *L)
: Fl_Round_Button(X,Y,W,H,L)
{
  type(FL_RADIO_BUTTON);
}


//
// End of "$Id: Fl_Round_Button.cxx 10386 2014-10-19 20:17:17Z AlbrechtS $".
//
