// winovlay.h
//
// "$Id: Fl_Overlay_Window.H 11440 2016-03-27 06:58:54Z manolo $"
//
// Overlay window header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Overlay_Window class . */

#ifndef Fl_Overlay_Window_H
#define Fl_Overlay_Window_H

#include "windbl.h"

/**
  This window provides double buffering and also the ability to draw the
  "overlay" which is another picture placed on top of the main image. The
  overlay is designed to be a rapidly-changing but simple graphic such as
  a mouse selection box. Fl_Overlay_Window uses the overlay
  planes provided by your graphics hardware if they are available.
  <P>If no hardware support is found the overlay is simulated by drawing
  directly into the on-screen copy of the double-buffered window, and
  "erased" by copying the backbuffer over it again.  This means the
  overlay will blink if you change the image in the window.
*/
class FL_EXPORT Fl_Overlay_Window : public Fl_Double_Window {
#ifndef FL_DOXYGEN
  friend class _Fl_Overlay;
  friend class Fl_Window_Driver;
#endif
public:
  /**
   You must subclass Fl_Overlay_Window and provide this method.
   It is just like a draw() method, except it draws the overlay.
   The overlay will have already been "cleared" when this is called.  You
   can use any of the routines described in &lt;FL/fl_draw.H&gt;.
   */
  virtual void draw_overlay() = 0;
private:
  Fl_Window *overlay_;
public:
  void show();
  void hide();
  void flush();
  void resize(int,int,int,int);
  ~Fl_Overlay_Window();
  /** Returns non-zero if there's hardware overlay support */
  int can_do_overlay();
  void redraw_overlay();
protected:
  /**
   See Fl_Overlay_Window::Fl_Overlay_Window(int X, int Y, int W, int H, const char *l=0)
   */
  Fl_Overlay_Window(int W, int H, const char *l=0);
  /**
   Creates a new Fl_Overlay_Window widget using the given
   position, size, and label (title) string. If the 
   positions (x,y) are not given, then the window manager
   will choose them.
   */
  Fl_Overlay_Window(int X, int Y, int W, int H, const char *l=0);
public:
  void show(int a, char **b) {Fl_Double_Window::show(a,b);}
  virtual Fl_Overlay_Window *as_overlay_window() {return this; }
};

#endif

//
// End of "$Id: Fl_Overlay_Window.H 11440 2016-03-27 06:58:54Z manolo $".
//
