// names.h
//
// "$Id: names.h 12121 2016-11-19 01:20:53Z AlbrechtS $"
//
// Event names header file for the Fast Light Tool Kit (FLTK).
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

// Thanks to Greg Ercolano for this addition.

#ifndef FL_NAMES_H
#define FL_NAMES_H

/** \defgroup fl_events Events handling functions
    @{
 */

/**
  This is an array of event names you can use to convert event numbers into names.

  The array gets defined inline wherever your '\#include <FL/names.h>' appears.

  \b Example:
  \code
  #include <FL/names.h>		// array will be defined here
  int MyClass::handle(int e) {
      printf("Event was %s (%d)\n", fl_eventnames[e], e);
      // ..resulting output might be e.g. "Event was FL_PUSH (1)"..
      [..]
  }
  \endcode
 */
const char * const fl_eventnames[] =
{
  "FL_NO_EVENT",
  "FL_PUSH",
  "FL_RELEASE",
  "FL_ENTER",
  "FL_LEAVE",
  "FL_DRAG",
  "FL_FOCUS",
  "FL_UNFOCUS",
  "FL_KEYDOWN",
  "FL_KEYUP",
  "FL_CLOSE",
  "FL_MOVE",
  "FL_SHORTCUT",
  "FL_DEACTIVATE",
  "FL_ACTIVATE",
  "FL_HIDE",
  "FL_SHOW",
  "FL_PASTE",
  "FL_SELECTIONCLEAR",
  "FL_MOUSEWHEEL",
  "FL_DND_ENTER",
  "FL_DND_DRAG",
  "FL_DND_LEAVE",
  "FL_DND_RELEASE",
  "FL_SCREEN_CONFIGURATION_CHANGED",
  "FL_FULLSCREEN",
  "FL_ZOOM_GESTURE",
  "FL_EVENT_27", // not yet defined, just in case it /will/ be defined ...
  "FL_EVENT_28", // not yet defined, just in case it /will/ be defined ...
  "FL_EVENT_29", // not yet defined, just in case it /will/ be defined ...
  "FL_EVENT_30"  // not yet defined, just in case it /will/ be defined ...
};

/**
  This is an array of font names you can use to convert font numbers into names.

  The array gets defined inline wherever your '\#include <FL/names.h>' appears.

  \b Example:
  \code
  #include <FL/names.h>		// array will be defined here
  int MyClass::my_callback(Fl_Widget *w, void*) {
      int fnum = w->labelfont();
      // Resulting output might be e.g. "Label's font is FL_HELVETICA (0)"
      printf("Label's font is %s (%d)\n", fl_fontnames[fnum], fnum);
      // ..resulting output might be e.g. "Label's font is FL_HELVETICA (0)"..
      [..]
  }
  \endcode
 */
const char * const fl_fontnames[] =
{
  "FL_HELVETICA",
  "FL_HELVETICA_BOLD",
  "FL_HELVETICA_ITALIC",
  "FL_HELVETICA_BOLD_ITALIC",
  "FL_COURIER",
  "FL_COURIER_BOLD",
  "FL_COURIER_ITALIC",
  "FL_COURIER_BOLD_ITALIC",
  "FL_TIMES",
  "FL_TIMES_BOLD",
  "FL_TIMES_ITALIC",
  "FL_TIMES_BOLD_ITALIC",
  "FL_SYMBOL",
  "FL_SCREEN",
  "FL_SCREEN_BOLD",
  "FL_ZAPF_DINGBATS",
};

/** @} */

#endif /* FL_NAMES_H */

//
// End of "$Id: names.h 12121 2016-11-19 01:20:53Z AlbrechtS $".
//
