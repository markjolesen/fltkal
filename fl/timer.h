// timer.h
//
// "$Id: Fl_Timer.H 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Timer header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Timer widget . */

#ifndef Fl_Timer_H
#define Fl_Timer_H

#ifndef Fl_Widget_H
#include "widget.h"
#endif

// values for type():
#define FL_NORMAL_TIMER		0
#define FL_VALUE_TIMER		1
#define FL_HIDDEN_TIMER		2

/**
  This is provided only to emulate the Forms Timer widget.  It works by
  making a timeout callback every 1/5 second.  This is wasteful and
  inaccurate if you just want something to happen a fixed time in the
  future.  You should directly call 
  Fl::add_timeout() instead.
*/
class FL_EXPORT Fl_Timer : public Fl_Widget {
  static void stepcb(void *);
  void step();
  char on, direction_;
  double delay, total;
  long lastsec,lastusec;
protected:
  void draw();
public:
  int handle(int);
  Fl_Timer(uchar t,int x,int y,int w,int h, const char *l);
  ~Fl_Timer();
  void value(double);
  /** See void Fl_Timer::value(double)  */
  double value() const {return delay>0.0?delay:0.0;}
  /**
    Gets or sets the direction of the timer.  If the direction is zero
    then the timer will count up, otherwise it will count down from the
    initial value().
  */
  char direction() const {return direction_;}
  /**
    Gets or sets the direction of the timer.  If the direction is zero
    then the timer will count up, otherwise it will count down from the
    initial value().
  */
  void direction(char d) {direction_ = d;}
  /**    Gets or sets whether the timer is suspended.  */
  char suspended() const {return !on;}
  void suspended(char d);
};

#endif

//
// End of "$Id: Fl_Timer.H 8864 2011-07-19 04:49:30Z greg.ercolano $".
//

