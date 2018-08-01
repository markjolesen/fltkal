// scrxywh.cxx
//
// "$Id: screen_xywh.cxx 12975 2018-06-26 14:04:09Z manolo $"
//
// Screen/monitor bounding box API for the Fast Light Tool Kit (FLTK).
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

#include <fl/fl.h>
#include <fl/platform.h>
#include "drvscr.h"
#include "config.h"


#ifndef FL_DOXYGEN
void Fl::call_screen_init()
{
  screen_driver()->init();
}
#endif

/** Returns the leftmost x coordinate of the main screen work area. */
int Fl::x()
{
  return screen_driver()->x();
}


/** Returns the topmost y coordinate of the main screen work area. */
int Fl::y()
{
  return screen_driver()->y();
}


/** Returns the width in pixels of the main screen work area. */
int Fl::w()
{
  return screen_driver()->w();
}


/** Returns the height in pixels of the main screen work area. */
int Fl::h()
{
  return screen_driver()->h();
}


/**
  Gets the number of available screens.
*/
int Fl::screen_count()
{
  return screen_driver()->screen_count();
}


/**
  Gets the bounding box of a screen
  that contains the specified screen position \p mx, \p my
  \param[out]  X,Y,W,H the corresponding screen bounding box
  \param[in] mx, my the absolute screen position
*/
void Fl::screen_xywh(int &X, int &Y, int &W, int &H, int mx, int my)
{
  screen_driver()->screen_xywh(X, Y, W, H, mx, my);
}


/**
 Gets the bounding box of the work area of a screen
 that contains the specified screen position \p mx, \p my
 \param[out]  X,Y,W,H the work area bounding box
 \param[in] mx, my the absolute screen position
 */
void Fl::screen_work_area(int &X, int &Y, int &W, int &H, int mx, int my)
{
  screen_driver()->screen_work_area(X, Y, W, H, mx, my);
}


/**
 Gets the bounding box of the work area of the given screen.
 \param[out]  X,Y,W,H the work area bounding box
 \param[in] n the screen number (0 to Fl::screen_count() - 1)
 \see void screen_xywh(int &x, int &y, int &w, int &h, int mx, int my)
*/
void Fl::screen_work_area(int &X, int &Y, int &W, int &H, int n)
{
  screen_driver()->screen_work_area(X, Y, W, H, n);
}


/**
  Gets the screen bounding rect for the given screen.
  Under Windows, Mac OS X, and the Gnome desktop, screen #0 contains the menubar/taskbar
  \param[out]  X,Y,W,H the corresponding screen bounding box
  \param[in] n the screen number (0 to Fl::screen_count() - 1)
  \see void screen_xywh(int &x, int &y, int &w, int &h, int mx, int my)
*/
void Fl::screen_xywh(int &X, int &Y, int &W, int &H, int n)
{
  screen_driver()->screen_xywh(X, Y, W, H, n);
}


/**
  Gets the screen bounding rect for the screen
  which intersects the most with the rectangle
  defined by \p mx, \p my, \p mw, \p mh.
  \param[out]  X,Y,W,H the corresponding screen bounding box
  \param[in] mx, my, mw, mh the rectangle to search for intersection with
  \see void screen_xywh(int &X, int &Y, int &W, int &H, int n)
  */
void Fl::screen_xywh(int &X, int &Y, int &W, int &H, int mx, int my, int mw, int mh)
{
  screen_driver()->screen_xywh(X, Y, W, H, mx, my, mw, mh);
}


/**
  Gets the screen number of a screen
  that contains the specified screen position \p x, \p y
  \param[in] x, y the absolute screen position
*/
int Fl::screen_num(int x, int y)
{
  return screen_driver()->screen_num(x, y);
}


/**
  Gets the screen number for the screen
  which intersects the most with the rectangle
  defined by \p x, \p y, \p w, \p h.
  \param[in] x, y, w, h the rectangle to search for intersection with
  */
int Fl::screen_num(int x, int y, int w, int h)
{
  return screen_driver()->screen_num(x, y, w, h);
}


/**
 Gets the screen resolution in dots-per-inch for the given screen.
 \param[out]  h, v  horizontal and vertical resolution
 \param[in]   n     the screen number (0 to Fl::screen_count() - 1)
 \see void screen_xywh(int &x, int &y, int &w, int &h, int mx, int my)
 */
void Fl::screen_dpi(float &h, float &v, int n)
{
  screen_driver()->screen_dpi(h, v, n);
}


/**
 Gets the bounding box of a screen that contains the mouse pointer.
 \param[out]  X,Y,W,H the corresponding screen bounding box
 \see void screen_xywh(int &x, int &y, int &w, int &h, int mx, int my)
 */
void Fl::screen_xywh(int &X, int &Y, int &W, int &H)
{
  int mx, my;
  int nscreen = Fl::screen_driver()->get_mouse(mx, my);
  Fl::screen_driver()->screen_xywh(X, Y, W, H, nscreen);
}


/**
 Gets the bounding box of the work area of the screen that contains the mouse pointer.
 \param[out]  X,Y,W,H the work area bounding box
 \see void screen_work_area(int &x, int &y, int &w, int &h, int mx, int my)
 */
void Fl::screen_work_area(int &X, int &Y, int &W, int &H)
{
  int mx, my;
  int nscreen = Fl::screen_driver()->get_mouse(mx, my);
  Fl::screen_driver()->screen_work_area(X, Y, W, H, nscreen);
}


//
// End of "$Id: screen_xywh.cxx 12975 2018-06-26 14:04:09Z manolo $".
//
