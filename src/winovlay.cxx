// winovlay.cxx
//
// "$Id: Fl_Overlay_Window.cxx 12974 2018-06-26 13:43:18Z manolo $"
//
// Overlay window code for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2016 by Bill Spitzak and others.
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


// A window using double-buffering and able to draw an overlay
// on top of that.  Uses the hardware to draw the overlay if
// possible, otherwise it just draws in the front buffer.

#include <fl/fl.h>
#include <fl/winovlay.h>
#include "drvwin.h"


Fl_Overlay_Window::Fl_Overlay_Window(int W, int H, const char *l)
: Fl_Double_Window(W,H,l)
{
  overlay_ = 0;
  image(0);
}

Fl_Overlay_Window::Fl_Overlay_Window(int X, int Y, int W, int H, const char *l)
: Fl_Double_Window(X,Y,W,H,l)
{
  overlay_ = 0;
  image(0);
}

void Fl_Overlay_Window::show() {
  Fl_Double_Window::show();
  if (overlay_ && overlay_ != this) overlay_->show();
}

void Fl_Overlay_Window::hide() {
  Fl_Double_Window::hide();
}

void Fl_Overlay_Window::flush()
{
  Fl_Window_Driver::driver(this)->flush_overlay();
}

void Fl_Overlay_Window::resize(int X, int Y, int W, int H) {
  Fl_Double_Window::resize(X,Y,W,H);
  if (overlay_ && overlay_!=this) overlay_->resize(0,0,w(),h());
}

/**
  Destroys the window and all child widgets.
*/
Fl_Overlay_Window::~Fl_Overlay_Window() {
  hide();
//  delete overlay; this is done by ~Fl_Group
}

int Fl_Overlay_Window::can_do_overlay() {
  return Fl_Window_Driver::driver(this)->can_do_overlay();
}

/**
 Call this to indicate that the overlay data has changed and needs to
 be redrawn.  The overlay will be clear until the first time this is
 called, so if you want an initial display you must call this after
 calling show().
 */
void Fl_Overlay_Window::redraw_overlay() {
  Fl_Window_Driver::driver(this)->redraw_overlay();
}

//
// End of "$Id: Fl_Overlay_Window.cxx 12974 2018-06-26 13:43:18Z manolo $".
//
