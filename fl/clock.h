// clock.h
//
// "$Id: Fl_Clock.H 12238 2017-05-15 15:35:30Z AlbrechtS $"
//
// Clock header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2017 by Bill Spitzak and others.
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
   Fl_Clock, Fl_Clock_Output widgets . */

#ifndef Fl_Clock_H
#define Fl_Clock_H

#ifndef Fl_Widget_H
#include "widget.h"
#endif

// Values for type():
// Please change doxygen documentation below (class Fl_Clock_Output)
// accordingly as well when changing the following type values:

#define FL_SQUARE_CLOCK		0	/**< type() of Square Clock variant */
#define FL_ROUND_CLOCK		1	/**< type() of Round Clock variant */
#define FL_ANALOG_CLOCK FL_SQUARE_CLOCK	/**< An analog clock is square */
#define FL_DIGITAL_CLOCK FL_SQUARE_CLOCK /**< Not yet implemented */

// fabien: Please keep the horizontal formatting of both images in class desc, 
// don't lose vertical space for nothing!

/**
  \class Fl_Clock_Output
  \brief This widget can be used to display a program-supplied time.

  The time shown on the clock is not updated. To display the current time,
  use Fl_Clock instead.

  \htmlonly <BR>  <table align=CENTER border=1 cellpadding=5 >  
  <caption align=bottom>type() FL_SQUARE_CLOCK and FL_ROUND_CLOCK </caption> <TR><TD> \endhtmlonly
  \image html clock.png  
  \htmlonly </TD> <TD> \endhtmlonly
  \image html round_clock.png 
  \htmlonly </TD> </TR> </table> \endhtmlonly
  \image latex clock.png "FL_SQUARE_CLOCK type" width=4cm
  \image latex round_clock.png "FL_ROUND_CLOCK type" width=4cm

  Values for clock type() (\#include \<FL/Clock.H\>):

  \code
    #define FL_SQUARE_CLOCK		0	// Square Clock variant
    #define FL_ROUND_CLOCK		1	// Round Clock variant
    #define FL_ANALOG_CLOCK FL_SQUARE_CLOCK	// An analog clock is square
    #define FL_DIGITAL_CLOCK FL_SQUARE_CLOCK	// Not yet implemented
  \endcode

 */
class FL_EXPORT Fl_Clock_Output : public Fl_Widget {
  int hour_, minute_, second_;
  ulong value_;
  int shadow_; // draw shadows of hands
  void drawhands(Fl_Color,Fl_Color); // part of draw
protected:
  void draw();
  void draw(int X, int Y, int W, int H);
public:

  Fl_Clock_Output(int X, int Y, int W, int H, const char *L = 0);

  void value(ulong v);	// set to this Unix time
  
  void value(int H, int m, int s);

  /**
    Returns the displayed time.
    Returns the time in seconds since the UNIX epoch (January 1, 1970).
    \see value(ulong)
   */
  ulong value() const {return value_;}

  /**
    Returns the displayed hour (0 to 23).
    \see value(), minute(), second()
   */
  int hour() const {return hour_;}

  /**
    Returns the displayed minute (0 to 59).
    \see value(), hour(), second()
   */
  int minute() const {return minute_;}

  /**
    Returns the displayed second (0 to 60, 60=leap second).
    \see value(), hour(), minute()
   */
  int second() const {return second_;}

  /**
    Returns the shadow drawing mode of the hands.

    \returns	shadow drawing mode of the hands
    \retval 0	no shadows
    \retval 1	draw shadows of hands (default)
  */
  int shadow() const {return shadow_;}

  /**
    Sets the shadow drawing mode of the hands.

    Enables (1) or disables (0) drawing the hands with shadows.

    Values except 0 and 1 are reserved for future extensions and
    yield undefined behavior.

    The default is to draw the shadows (1).

    \param[in]	mode	1 = shadows (default), 0 = no shadows
  */
  void shadow(int mode) { shadow_ = mode ? 1 : 0; }
};

// a Fl_Clock displays the current time always by using a timeout:

/**
  \class Fl_Clock
  \brief This widget provides a round analog clock display.

  Fl_Clock is provided for Forms compatibility. 
  It installs a 1-second timeout callback using Fl::add_timeout().
  You can choose the rounded or square type of the clock with type().
  Please see Fl_Clock_Output widget for applicable values.

  \htmlonly <BR>  <table align=CENTER border=1 cellpadding=5 >  
  <caption align=bottom>type() FL_SQUARE_CLOCK and FL_ROUND_CLOCK </caption> <TR><TD> \endhtmlonly
  \image html clock.png  
  \htmlonly </TD> <TD> \endhtmlonly
  \image html round_clock.png 
  \htmlonly </TD> </TR> </table> \endhtmlonly
  \image latex clock.png "FL_SQUARE_CLOCK type" width=4cm  
  \image latex round_clock.png "FL_ROUND_CLOCK type" width=4cm

  \see class Fl_Clock_Output
 */
class FL_EXPORT Fl_Clock : public Fl_Clock_Output {
public:
  int handle(int);

  Fl_Clock(int X, int Y, int W, int H,  const char *L = 0);
  
  Fl_Clock(uchar t, int X, int Y, int W, int H, const char *L);
  
  ~Fl_Clock();
};

#endif

//
// End of "$Id: Fl_Clock.H 12238 2017-05-15 15:35:30Z AlbrechtS $".
//
