// outvalue.h
//
// "$Id$"
//
// Value output header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018,2020 The fltkal authors
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
   Fl_Value_Output widget . */

#ifndef Fl_Value_Output_H
#define Fl_Value_Output_H

#ifndef Fl_Valuator_H
#include "valuator.h"
#endif

/**
  The Fl_Value_Output widget displays a floating point value.
  If step() is not zero, the user can adjust the value by
  dragging the mouse left and right.  The left button moves one step()
  per pixel, the middle by 10 * step(), and the right button by 
  100 * step().
  <P>This is much lighter-weight than 
  Fl_Value_Input because it contains no text editing code or
  character buffer. </P>
  <P ALIGN=CENTER>\image html Fl_Value_Output.png 
  \image latex  Fl_Value_Output.png "Fl_Value_Output" width=4cm
*/
class FL_EXPORT Fl_Value_Output : public Fl_Valuator {
  Fl_Font textfont_;
  Fl_Fontsize textsize_;
  uchar soft_;
  Fl_Color textcolor_;

protected:
  void draw();

public:
  int handle(int);
  Fl_Value_Output(int x,int y,int w,int h,const char *l=0);

  /**
    If "soft" is turned on, the user is allowed to drag the value outside
    the range.  If they drag the value to one of the ends, let go, then
    grab again and continue to drag, they can get to any value.  Default is
    one.
  */
  void soft(uchar s) {soft_ = s;}
  /**
    If "soft" is turned on, the user is allowed to drag the value outside
    the range.  If they drag the value to one of the ends, let go, then
    grab again and continue to drag, they can get to any value.  Default is
    one.
  */
  uchar soft() const {return soft_;}

  /**    Gets the typeface of the text in the value box.  */
  Fl_Font textfont() const {return textfont_;}
  /**    Sets the typeface of the text in the value box.  */
  void textfont(Fl_Font s) {textfont_ = s;}
  /**    Gets the size of the text in the value box.  */
  Fl_Fontsize textsize() const {return textsize_;}
  void textsize(Fl_Fontsize s) {textsize_ = s;}
  /**    Sets the color of the text in the value box.  */
  Fl_Color textcolor() const {return textcolor_;}
  /**    Gets the color of the text in the value box.  */
  void textcolor(Fl_Color s) {textcolor_ = s;}
};

#endif

//
// End of "$Id$".
//
