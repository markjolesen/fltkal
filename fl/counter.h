// counter.h
//
// "$Id: Fl_Counter.H 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Counter header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Counter widget . */

// A numerical value with up/down step buttons.  From Forms.

#ifndef Fl_Counter_H
#define Fl_Counter_H

#ifndef Fl_Valuator_H
#include "valuator.h"
#endif

// values for type():
#define FL_NORMAL_COUNTER	0	/**< type() for counter with fast buttons */
#define FL_SIMPLE_COUNTER	1	/**< type() for counter without fast buttons */

/**
  Controls a single floating point value with button (or keyboard) arrows.
  Double arrows buttons achieve larger steps than simple arrows.
  \see Fl_Spinner for value input with vertical step arrows.
  <P align=center>\image html counter.png</P>
  \image latex counter.png "Fl_Counter" width=4cm

  \todo Refactor the doxygen comments for Fl_Counter type() documentation.

  The type of an Fl_Counter object can be set using type(uchar t) to:
  \li \c FL_NORMAL_COUNTER: Displays a counter with 4 arrow buttons.
  \li \c FL_SIMPLE_COUNTER: Displays a counter with only 2 arrow buttons.
*/
class FL_EXPORT Fl_Counter : public Fl_Valuator {

  Fl_Font textfont_;
  Fl_Fontsize textsize_;
  Fl_Color textcolor_;
  double lstep_;
  uchar mouseobj;
  static void repeat_callback(void *);
  int calc_mouseobj();
  void increment_cb();

protected:

  void draw();

public:

  int handle(int);

  Fl_Counter(int X, int Y, int W, int H, const char* L = 0);
  ~Fl_Counter();

  /**
    Sets the increment for the large step buttons.
    The default value is 1.0.
    \param[in] a large step increment.
  */
  void lstep(double a) {lstep_ = a;}

  /**
    Sets the increments for the normal and large step buttons.
    \param[in] a, b normal and large step increments.
  */
  void step(double a,double b) {Fl_Valuator::step(a); lstep_ = b;}

  /**
    Sets the increment for the normal step buttons.
    \param[in] a normal step increment.
  */
  void step(double a) {Fl_Valuator::step(a);}

  /**
    Returns the increment for normal step buttons.
   */
  double step() const {return Fl_Valuator::step();}

  /** Gets the text font */
  Fl_Font textfont() const {return textfont_;}
  /** Sets the text font to \p s */
  void textfont(Fl_Font s) {textfont_ = s;}

  /** Gets the font size */
  Fl_Fontsize textsize() const {return textsize_;}
  /** Sets the font size to \p s */
  void textsize(Fl_Fontsize s) {textsize_ = s;}

  /** Gets the font color */
  Fl_Color textcolor() const {return textcolor_;}
  /** Sets the font color to \p s */
  void textcolor(Fl_Color s) {textcolor_ = s;}

};

#endif

//
// End of "$Id: Fl_Counter.H 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
