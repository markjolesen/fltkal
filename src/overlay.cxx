// overlay.cxx
//
// "$Id: fl_overlay.cxx 12239 2017-05-17 11:54:18Z manolo $"
//
// Overlay support for the Fast Light Tool Kit (FLTK).
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

// Extremely limited "overlay" support.  You can use this to drag out
// a rectangle in response to mouse events.  It is your responsibility
// to erase the overlay before drawing anything that might intersect
// it.

#include <fl/platform.h>
#include <fl/fl_draw.h>

//#define USE_XOR
// unless USE_XOR is defined, this source file is cross-platform

#ifdef USE_XOR
#include "config.h"
#endif

static int px,py,pw,ph;

#ifndef USE_XOR
#include <stdlib.h>
static uchar *bgN = 0L, *bgS = 0L, *bgE = 0L, *bgW = 0L;

#include <fl/drvscr.h>
#include <fl/imgrgb.h>
#include <fl/imgshare.h>
static Fl_Shared_Image *s_bgN = 0, *s_bgS = 0, *s_bgE = 0, *s_bgW = 0;

static int bgx, bgy, bgw, bgh;
#endif

static void draw_current_rect() {
#ifdef USE_XOR
# if defined(USE_X11)
  GC gc = (GC)fl_graphics_driver->gc();
  XSetFunction(fl_display, gc, GXxor);
  XSetForeground(fl_display, gc, 0xffffffff);
  XDrawRectangle(fl_display, fl_window, gc, px, py, pw, ph);
  XSetFunction(fl_display, gc, GXcopy);
# elif defined(_WIN32)
  int old = SetROP2(fl_graphics_driver->gc(), R2_NOT);
  fl_rect(px, py, pw, ph);
  SetROP2(fl_graphics_driver->gc(), old);
# elif defined(__APPLE__)
  // warning: Quartz does not support xor drawing
  // Use the Fl_Overlay_Window instead.
  fl_color(FL_WHITE);
  fl_rect(px, py, pw, ph);
# else
#  error unsupported platform
# endif
#else
  bool unscaled = fl_graphics_driver->overlay_rect_unscaled();
  if (unscaled) {
    if (bgN) { free(bgN); bgN = 0L; }
    if (bgS) { free(bgS); bgS = 0L; }
    if (bgE) { free(bgE); bgE = 0L; }
    if (bgW) { free(bgW); bgW = 0L; }
  } else {
    if (s_bgN) { s_bgN->release(); s_bgN = 0; }
    if (s_bgS) { s_bgS->release(); s_bgS = 0; }
    if (s_bgE) { s_bgE->release(); s_bgE = 0; }
    if (s_bgW) { s_bgW->release(); s_bgW = 0; }
  }
  if (pw>0 && ph>0) {
    if (unscaled) {
      bgE = fl_read_image(0L, px+pw-1, py, 1, ph);
      bgW = fl_read_image(0L, px, py, 1, ph);
      bgS = fl_read_image(0L, px, py+ph-1, pw, 1);
      bgN = fl_read_image(0L, px, py, pw, 1);
    } else {
      Fl_RGB_Image *tmp;
      tmp = Fl::screen_driver()->read_win_rectangle( px+pw-1, py, 1, ph);
      if(tmp && tmp->w() && tmp->h()) {
        s_bgE = Fl_Shared_Image::get(tmp);
        s_bgE->scale(1, ph,0,1);
      }
      tmp = Fl::screen_driver()->read_win_rectangle( px, py, 1, ph);
      if(tmp && tmp->w() && tmp->h()) {
        s_bgW = Fl_Shared_Image::get(tmp);
        s_bgW->scale(1, ph,0,1);
      }
      tmp = Fl::screen_driver()->read_win_rectangle( px, py+ph-1, pw, 1);
      if(tmp && tmp->w() && tmp->h()) {
        s_bgS = Fl_Shared_Image::get(tmp);
        s_bgS->scale(pw, 1,0,1);
      }
      tmp = Fl::screen_driver()->read_win_rectangle( px, py, pw, 1);
      if(tmp && tmp->w() && tmp->h()) {
        s_bgN = Fl_Shared_Image::get(tmp);
        s_bgN->scale(pw, 1,0,1);
      }
    }
    bgx = px; bgy = py;
    bgw = pw; bgh = ph;
  }
  fl_color(FL_WHITE);
  fl_line_style(FL_SOLID);
  if (unscaled) fl_rect(px, py, pw, ph);
  else fl_graphics_driver->overlay_rect(px, py, pw, ph);

  fl_color(FL_BLACK);
  fl_line_style(FL_DOT);
  if (unscaled) fl_rect(px, py, pw, ph);
  else fl_graphics_driver->overlay_rect(px, py, pw, ph);
  fl_line_style(FL_SOLID);
#endif // USE_XOR
}

static void erase_current_rect() {
#ifdef USE_XOR
# ifdef __APPLE_QUARTZ__ // PORTME: Fl_Window_Driver - platform overlay
  fl_rect(px, py, pw, ph);
# else
  draw_current_rect();
# endif
#else
  bool unscaled = fl_graphics_driver->overlay_rect_unscaled();
  if (unscaled) {
    if (bgN) fl_draw_image(bgN, bgx, bgy, bgw, 1);
    if (bgS) fl_draw_image(bgS, bgx, bgy+bgh-1, bgw, 1);
    if (bgW) fl_draw_image(bgW, bgx, bgy, 1, bgh);
    if (bgE) fl_draw_image(bgE, bgx+bgw-1, bgy, 1, bgh);
  } else {
    if (s_bgN) s_bgN->draw(bgx, bgy);
    if (s_bgS) s_bgS->draw(bgx, (bgy+bgh-1));
    if (s_bgW) s_bgW->draw(bgx, bgy);
    if (s_bgE) s_bgE->draw((bgx+bgw-1), bgy);
  }
#endif
}

/**
  Erase a selection rectangle without drawing a new one
  */
void fl_overlay_clear() {
  if (pw > 0) {erase_current_rect(); pw = 0;}
}

/**
  Draws a selection rectangle, erasing a previous one by XOR'ing it first.
  */
void fl_overlay_rect(int x, int y, int w, int h) {
  if (w < 0) {x += w; w = -w;} else if (!w) w = 1;
  if (h < 0) {y += h; h = -h;} else if (!h) h = 1;
  if (pw > 0) {
    if (x==px && y==py && w==pw && h==ph) return;
    erase_current_rect();
  }
  px = x; py = y; pw = w; ph = h;
  draw_current_rect();
}

//
// End of "$Id: fl_overlay.cxx 12239 2017-05-17 11:54:18Z manolo $".
//
