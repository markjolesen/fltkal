// dial.h
//
// "$Id: Fl_Dial.H 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Dial header file for the Fast Light Tool Kit (FLTK).
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

/* \file
   Fl_Dial widget . */

#ifndef Fl_Dial_H
#define Fl_Dial_H

#ifndef Fl_Valuator_H
#include "valuator.h"
#endif

// values for type():
#define FL_NORMAL_DIAL	0	/**< type() for dial variant with dot */
#define FL_LINE_DIAL	1	/**< type() for dial variant with line */
#define FL_FILL_DIAL	2	/**< type() for dial variant with filled arc */

/**
  The Fl_Dial widget provides a circular dial to control a
  single floating point value.
  <P ALIGN=CENTER>\image html dial.png 
  \image latex dial.png "Fl_Dial" width=4cm
  Use type() to set the type of the dial to:
  <UL>
  <LI>FL_NORMAL_DIAL - Draws a normal dial with a knob. </LI>
  <LI>FL_LINE_DIAL - Draws a dial with a line. </LI>
  <LI>FL_FILL_DIAL - Draws a dial with a filled arc. </LI>
  </UL>

*/
class FL_EXPORT Fl_Dial : public Fl_Valuator {

  short a1,a2;

protected:

  // these allow subclasses to put the dial in a smaller area:
  void draw(int X, int Y, int W, int H);
  int handle(int event, int X, int Y, int W, int H);
  void draw();

public:

  int handle(int);
  /**
    Creates a new Fl_Dial widget using the given position, size,
    and label string. The default type is FL_NORMAL_DIAL.
  */
  Fl_Dial(int x,int y,int w,int h, const char *l = 0);
  /** 
     Sets Or gets the angles used for the minimum and maximum values.  The default
     values are 45 and 315 (0 degrees is straight down and the angles
     progress clockwise).  Normally angle1 is less than angle2, but if you
     reverse them the dial moves counter-clockwise.
  */
  short angle1() const {return a1;}
  /** See short angle1() const */
  void angle1(short a) {a1 = a;}
  /** See short angle1() const */
  short angle2() const {return a2;}
  /** See short angle1() const */
  void angle2(short a) {a2 = a;}
  /** See short angle1() const */
  void angles(short a, short b) {a1 = a; a2 = b;}

};

#endif

//
// End of "$Id: Fl_Dial.H 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
