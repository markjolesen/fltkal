// adjuster.h
//
// "$Id$"
//
// Adjuster widget header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Adjuster widget . */

// 3-button "slider", made for Nuke

#ifndef Fl_Adjuster_H
#define Fl_Adjuster_H

#ifndef Fl_Valuator_H
#include "valuator.h"
#endif

/**
  The Fl_Adjuster widget was stolen from Prisms, and has proven
  to be very useful for values that need a large dynamic range.
  \image html adjuster1.png 
  \image latex adjuster1.png "Fl_Adjuster" width=4cm
  <P>When you  press a button and drag to the right the value increases.
  When you drag  to the left it decreases.  The largest button adjusts by
  100 *  step(), the next by 10 * step() and that
  smallest button  by step().  Clicking on the buttons
  increments by 10 times the  amount dragging by a pixel does. Shift +
  click decrements by 10 times  the amount.
*/
class FL_EXPORT Fl_Adjuster : public Fl_Valuator {
  int drag;
  int ix;
  int soft_;
protected:
  void draw();
  int handle(int);
  void value_damage();
public:
  Fl_Adjuster(int X,int Y,int W,int H,const char *l=0);
  /**
    If "soft" is turned on, the user is allowed to drag the value outside
    the range.  If they drag the value to one of the ends, let go, then
    grab again and continue to drag, they can get to any value.  Default is
    one.
  */
  void soft(int s) {soft_ = s;}
  /**
    If "soft" is turned on, the user is allowed to drag the value outside
    the range.  If they drag the value to one of the ends, let go, then
    grab again and continue to drag, they can get to any value.  Default is
    one.
  */
  int soft() const {return soft_;}
};

#endif

//
// End of "$Id$".
//
