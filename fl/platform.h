// platform.h
//
// "$Id: platform.H 12969 2018-06-23 17:04:18Z matt $"
//
// Platform header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2018 by Bill Spitzak and others.
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

// These are internal fltk symbols that are necessary or useful for
// calling Xlib.  You should include this file if (and ONLY if) you
// need to call Xlib directly.  These symbols may not exist on non-X
// systems.

#if !defined(FL_PLATFORM_H) && !defined(FL_DOXYGEN)
#  define FL_PLATFORM_H

#   include <fl/export.h>
#   include <fl/typesplt.h>
#   include <fl/fl_types.h> // for uchar
class Fl_Window;

#  ifdef _WIN32
#    include "win32.H"
#  elif defined(__APPLE__)
#    include "mac.H"
#  elif defined(__ANDROID__)
#    include "android.H"
#  elif defined(__DJGPP__) || defined(USE_ALLEGRO)
#    include "allegro4.h"
#  else // X11
#   include <FL/fl_types.h>
#   include <FL/Enumerations.H>
#    if !defined(USE_X11)
#      define USE_X11 1
#    endif
#    if defined(_ABIN32) || defined(_ABI64) // fix for broken SGI Irix X .h files
#      pragma set woff 3322
#    endif
#    include <X11/Xlib.h>
#    include <X11/Xutil.h>
#    if defined(_ABIN32) || defined(_ABI64)
#      pragma reset woff 3322
#    endif
#    include <X11/Xatom.h>

FL_EXPORT void fl_open_display(Display*);

// constant info about the X server connection:
extern FL_EXPORT Display *fl_display;
extern FL_EXPORT int fl_screen;
extern FL_EXPORT XVisualInfo *fl_visual;
extern FL_EXPORT Colormap fl_colormap;

// drawing functions:
extern FL_EXPORT GC fl_gc;
FL_EXPORT ulong fl_xpixel(Fl_Color i);
FL_EXPORT ulong fl_xpixel(uchar r, uchar g, uchar b);

// feed events into fltk:
FL_EXPORT int fl_handle(const XEvent&);

// you can use these in Fl::add_handler() to look at events:
extern FL_EXPORT const XEvent* fl_xevent;
extern FL_EXPORT ulong fl_event_time;

#if defined(FL_LIBRARY) || defined(FL_INTERNALS)
extern FL_EXPORT Window fl_message_window;
extern FL_EXPORT void *fl_xftfont;

// access to core fonts:
// This class provides a "smart pointer" that returns a pointer to an XFontStruct.
// The global variable fl_xfont can be called wherever a bitmap "core" font is
// needed, e.g. when rendering to a GL context under X11.
// With Xlib / X11 fonts, fl_xfont will return the current selected font.
// With XFT / X11 fonts, fl_xfont will attempt to return the bitmap "core" font most
// similar to (usually the same as) the current XFT font.
class FL_EXPORT Fl_XFont_On_Demand
{
public:
  Fl_XFont_On_Demand(XFontStruct* p = NULL) : ptr(p) { }
  Fl_XFont_On_Demand& operator=(const Fl_XFont_On_Demand& x)
  { ptr = x.ptr;  return *this; }
  Fl_XFont_On_Demand& operator=(XFontStruct* p)
  { ptr = p;  return *this; }
  XFontStruct* value();
  operator XFontStruct*() { return value(); }
  XFontStruct& operator*() { return *value(); }
  XFontStruct* operator->() { return value(); }
  bool operator==(const Fl_XFont_On_Demand& x) { return ptr == x.ptr; }
  bool operator!=(const Fl_XFont_On_Demand& x) { return ptr != x.ptr; }
private:
  XFontStruct *ptr;
};
extern FL_EXPORT Fl_XFont_On_Demand fl_xfont;

extern FL_EXPORT char fl_override_redirect; // hack into Fl_X::make_xid()
extern FL_EXPORT int fl_background_pixel;  // hack into Fl_X::make_xid()

#endif // FL_LIBRARY || FL_INTERNALS

#  endif // X11

//
// cross-platform declarations
//
#if defined(FL_LIBRARY) || defined(FL_INTERNALS)
#  include <fl/win.h>

class FL_EXPORT Fl_X {
public:
  Window xid;
  Fl_Window* w;
  Fl_Region region;
  Fl_X *next;
  // static variables, static functions and member functions
  static Fl_X* first;
  static Fl_X* i(const Fl_Window* w) {return (Fl_X*)w->i;}
#  if defined(USE_X11) // for backward compatibility
  static void make_xid(Fl_Window*, XVisualInfo* =fl_visual, Colormap=fl_colormap);
  static Fl_X* set_xid(Fl_Window*, Window);
#  endif
};

inline Window fl_xid(const Fl_Window* w) { Fl_X *xTemp = Fl_X::i(w); return xTemp ? xTemp->xid : 0; }
#else
extern FL_EXPORT Window fl_xid_(const Fl_Window* w);
#  define fl_xid(w) fl_xid_(w)
#endif // FL_LIBRARY || FL_INTERNALS

extern FL_EXPORT Fl_Window* fl_find(Window xid);
extern FL_EXPORT void fl_open_display();
extern FL_EXPORT void fl_close_display();
extern FL_EXPORT Window fl_window;
extern FL_EXPORT Fl_Bitmask fl_create_bitmask(int w, int h, const uchar *data);
extern FL_EXPORT Fl_Bitmask fl_create_alphamask(int w, int h, int d, int ld, const uchar *data);
extern FL_EXPORT void fl_delete_bitmask(Fl_Bitmask bm);
extern FL_EXPORT int fl_parse_color(const char* p, uchar& r, uchar& g, uchar& b);
extern FL_EXPORT void fl_open_callback(void (*)(const char *));

#endif // !FL_PLATFORM_H

//
// End of "$Id: platform.H 12969 2018-06-23 17:04:18Z matt $".
//
