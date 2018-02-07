// slider.h
//
// "$Id: Fl_Slider.H 9553 2012-05-28 15:39:12Z greg.ercolano $"
//
// Slider header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Slider widget . */

#ifndef Fl_Slider_H
#define Fl_Slider_H

#ifndef Fl_Valuator_H
#include "valuator.h"
#endif

// values for type(), lowest bit indicate horizontal:
#define FL_VERT_SLIDER		0
#define FL_HOR_SLIDER		1
#define FL_VERT_FILL_SLIDER	2
#define FL_HOR_FILL_SLIDER	3
#define FL_VERT_NICE_SLIDER	4
#define FL_HOR_NICE_SLIDER	5

/**
  The Fl_Slider widget contains a sliding knob inside a box. It is
  often used as a scrollbar.  Moving the box all the way to the
  top/left sets it to the minimum(), and to the bottom/right to the
  maximum().  The minimum() may be greater than the maximum() to
  reverse the slider direction.

  Use void Fl_Widget::type(int) to set how the slider is drawn, 
  which can be one of the following:
  
  \li FL_VERTICAL - Draws a vertical slider (this is the default).
  \li FL_HORIZONTAL - Draws a horizontal slider.
  \li FL_VERT_FILL_SLIDER - Draws a filled vertical slider,
      useful as a progress or value meter.
  \li FL_HOR_FILL_SLIDER - Draws a filled horizontal  slider,
      useful as a progress or value meter.
  \li FL_VERT_NICE_SLIDER - Draws a vertical slider with  a nice
      looking control knob.
  \li FL_HOR_NICE_SLIDER - Draws a horizontal slider with  a
      nice looking control knob.

  \image html  slider.png 
  \image latex slider.png "Fl_Slider" width=4cm
*/
class FL_EXPORT Fl_Slider : public Fl_Valuator {

  float slider_size_;
  uchar slider_;
  void _Fl_Slider();
  void draw_bg(int, int, int, int);

protected:

  // these allow subclasses to put the slider in a smaller area:
  void draw(int, int, int, int);
  int handle(int, int, int, int, int);
  void draw();

public:

  int handle(int);
  Fl_Slider(int X,int Y,int W,int H, const char *L = 0);
  Fl_Slider(uchar t,int X,int Y,int W,int H, const char *L);

  int scrollvalue(int pos,int size,int first,int total);
  void bounds(double a, double b);

  /**
    Get the dimensions of the moving piece of slider.
  */
  float slider_size() const {return slider_size_;}

  /**
    Set the dimensions of the moving piece of slider. This is
    the fraction of the size of the entire widget. If you set this
    to 1 then the slider cannot move.  The default value is .08.

    For the "fill" sliders this is the size of the area around the
    end that causes a drag effect rather than causing the slider to
    jump to the mouse.
  */
  void slider_size(double v);

  /** Gets the slider box type. */
  Fl_Boxtype slider() const {return (Fl_Boxtype)slider_;}

  /** Sets the slider box type. */
  void slider(Fl_Boxtype c) {slider_ = c;}
};

#endif

//
// End of "$Id: Fl_Slider.H 9553 2012-05-28 15:39:12Z greg.ercolano $".
//
