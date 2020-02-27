// browserh.h
//
//
// Hold browser header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018, 2020 The fltkal authors
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

/* \file
   Fl_Hold_Browser widget . */

#ifndef Fl_Hold_Browser_H
#define Fl_Hold_Browser_H

#include "browser.h"

/**
  The Fl_Hold_Browser is a subclass of Fl_Browser which lets the user 
  select a single item, or no items by clicking on the empty space.

  \image html  fl_hold_browser.png "Fl_Hold_Browser"
  \image latex fl_hold_browser.png "Fl_Hold_Browser" width=4cm

  As long as the mouse button is held down the item
  pointed to by it is highlighted, and this highlighting remains on when
  the mouse button is released. Normally the callback is done when the
  user releases the mouse, but you can change this with when().
  <P>See Fl_Browser for methods to add and remove lines from the browser.
*/
class FL_EXPORT Fl_Hold_Browser : public Fl_Browser {
public:
  /**
    Creates a new Fl_Hold_Browser widget using the given
    position, size, and label string. The default boxtype is FL_DOWN_BOX.
    The constructor specializes Fl_Browser() by setting the type to FL_HOLD_BROWSER.
    The destructor destroys the widget and frees all memory that has been allocated.
 */
  Fl_Hold_Browser(int X,int Y,int W,int H,const char *L=0);
};

#endif
