// scrlbar.h
//
// "$Id: Fl_Scrollbar.H 9116 2011-10-02 06:25:13Z matt $"
//
// Scroll bar header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Scrollbar widget . */

#ifndef Fl_Scrollbar_H
#define Fl_Scrollbar_H

#include "slider.h"

/**
  The Fl_Scrollbar widget displays a slider with arrow buttons at
  the ends of the scrollbar. Clicking on the arrows move up/left and
  down/right by linesize(). Scrollbars also accept FL_SHORTCUT events:
  the arrows move by linesize(), and vertical scrollbars take Page
  Up/Down (they move by the page size minus linesize()) and Home/End
  (they jump to the top or bottom).

  Scrollbars have step(1) preset (they always return integers). If
  desired you can set the step() to non-integer values. You will then
  have to use casts to get at the floating-point versions of value()
  from Fl_Slider.

  \image html  scrollbar.png 
  \image latex scrollbar.png "Fl_Scrollbar" width=4cm
*/
class FL_EXPORT Fl_Scrollbar : public Fl_Slider {

  int linesize_;
  int pushed_;
  static void timeout_cb(void*);
  void increment_cb();
protected:
  void draw();

public:

  Fl_Scrollbar(int X,int Y,int W,int H, const char *L = 0);
  ~Fl_Scrollbar();
  int handle(int);

  /**
    Gets the integer value (position) of the slider in the scrollbar.
    You can get the floating point value with Fl_Slider::value().

    \see Fl_Scrollbar::value(int p)
    \see Fl_Scrollbar::value(int pos, int size, int first, int total)
  */
  int value() const {return int(Fl_Slider::value());}

  /**
    Sets the value (position) of the slider in the scrollbar.

    \see Fl_Scrollbar::value()
    \see Fl_Scrollbar::value(int pos, int size, int first, int total)
  */
  int value(int p) {return int(Fl_Slider::value((double)p));}

  /**
    Sets the position, size and range of the slider in the scrollbar.
    \param[in] pos   position, first line displayed
    \param[in] windowSize  number of lines displayed
    \param[in] first number of first line
    \param[in] total total number of lines

    You should call this every time your window changes size, your data
    changes size, or your scroll position changes (even if in response
    to a callback from this scrollbar).
    All necessary calls to redraw() are done.

    Calls Fl_Slider::scrollvalue(int pos, int size, int first, int total).
  */
  int value(int pos, int windowSize, int first, int total) {
    return scrollvalue(pos, windowSize, first, total);
  }

  /**
    Get the size of step, in lines, that the arror keys move.
  */
  int linesize() const {return linesize_;}

  /**
    This number controls how big the steps are that the arrow keys do.
    In addition page up/down move by the size last sent to value()
    minus one linesize().  The default is 16.
  */
  void linesize(int i) {linesize_ = i;}

};

#endif

//
// End of "$Id: Fl_Scrollbar.H 9116 2011-10-02 06:25:13Z matt $".
//
