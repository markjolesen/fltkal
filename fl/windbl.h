// windbl.h
//
// "$Id: Fl_Double_Window.H 11359 2016-03-13 22:16:37Z matt $"
//
// Double-buffered window header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Double_Window widget . */

#ifndef Fl_Double_Window_H
#define Fl_Double_Window_H

#include "win.h"

/**
  The Fl_Double_Window provides a double-buffered window.
  If possible this will use the X double buffering extension (Xdbe).  If
  not, it will draw the window data into an off-screen pixmap, and then
  copy it to the on-screen window.
  <P>It is highly recommended that you put the following code before the
  first show() of <I>any</I> window in your program: </P>
  \code
  Fl::visual(FL_DOUBLE|FL_INDEX)
  \endcode
  This makes sure you can use Xdbe on servers where double buffering
  does not exist for every visual.
*/
class FL_EXPORT Fl_Double_Window : public Fl_Window
{
public:
  /**
    Return non-null if this is an Fl_Overlay_Window object.
  */
  virtual Fl_Double_Window *as_double_window() {return this; }
  void show();
  void show(int a, char **b) {Fl_Window::show(a,b);}
  void resize(int,int,int,int);
  void hide();
  void flush();
  ~Fl_Double_Window();
  
  /**
   Creates a new Fl_Double_Window widget using the given
   position, size, and label (title) string.
  */
  Fl_Double_Window(int W, int H, const char *l = 0);
  
  /**
   See  Fl_Double_Window::Fl_Double_Window(int w, int h, const char *label = 0)
  */
  Fl_Double_Window(int X, int Y, int W, int H, const char *l = 0);

};

#endif

//
// End of "$Id: Fl_Double_Window.H 11359 2016-03-13 22:16:37Z matt $".
//
