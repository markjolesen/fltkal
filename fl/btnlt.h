//
// Lighted button header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     https://www.fltk.org/COPYING.php
//
// Please see the following page on how to report bugs and issues:
//
//     https://www.fltk.org/bugs.php
//

/* \file
   Fl_Light_Button widget . */

#ifndef Fl_Light_Button_H
#define Fl_Light_Button_H

#include "btn.h"

/**
  This subclass displays the "on" state by turning on a light,
  rather than drawing pushed in.  The shape of the  "light"
  is initially set to FL_DOWN_BOX.  The color of the light when
  on is controlled with selection_color(), which defaults to FL_YELLOW.

  Buttons generate callbacks when they are clicked by the user.  You
  control exactly when and how by changing the values for type() and when().
  <P ALIGN=CENTER>\image html Fl_Light_Button.png</P>
  \image latex Fl_Light_Button.png "Fl_Light_Button" width=4cm
*/
class FL_EXPORT Fl_Light_Button : public Fl_Button {
protected:
    virtual void draw();
public:
    virtual int handle(int);
    Fl_Light_Button(int x,int y,int w,int h,const char *l = 0);
};

#endif
