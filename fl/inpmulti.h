// inpmulti.h
//
// "$Id: Fl_Multiline_Input.H 10365 2014-10-09 11:45:02Z AlbrechtS $"
//
// Multiline input header file for the Fast Light Tool Kit (FLTK).
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

/* \file
   Fl_Multiline_Input widget . */ 

#ifndef Fl_Multiline_Input_H
#define Fl_Multiline_Input_H

#include "input.h"

/**
  This input field displays '\\n' characters as new lines rather than ^J,
  and accepts the Return, Tab, and up and down arrow keys.  This is for
  editing multiline text.

  This is far from the nirvana of text editors, and is probably only
  good for small bits of text, 10 lines at most. Note that this widget
  does not support scrollbars or per-character color control.

  If you are presenting large amounts of text and need scrollbars
  or full color control of characters, you probably want Fl_Text_Editor
  instead.

  In FLTK 1.3.x, the default behavior of the 'Tab' key was changed
  to support consistent focus navigation. To get the older FLTK 1.1.x
  behavior, set Fl_Input_::tab_nav() to 0. Newer programs should consider using
  Fl_Text_Editor.
*/
class FL_EXPORT Fl_Multiline_Input : public Fl_Input {
public:
  /**
    Creates a new Fl_Multiline_Input widget using the given
    position, size, and label string. The default boxtype is FL_DOWN_BOX.

    Inherited destructor destroys the widget and any value associated with it.
  */
  Fl_Multiline_Input(int X,int Y,int W,int H,const char *l = 0);
};

#endif

//
// End of "$Id: Fl_Multiline_Input.H 10365 2014-10-09 11:45:02Z AlbrechtS $".
//
