// add_idle.cxx
//
// "$Id: Fl_add_idle.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Idle routine support for the Fast Light Tool Kit (FLTK).
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

// Allows you to manage an arbitrary set of idle() callbacks.
// Replaces the older set_idle() call (which is used to implement this)

#include <fl/fl.h>

struct idle_cb {
  void (*cb)(void*);
  void* data;
  idle_cb *next;
};

// the callbacks are stored linked in a ring.  last points at the one
// just called, first at the next to call.  last->next == first.

static idle_cb* first;
static idle_cb* last;
static idle_cb* freelist;

static void call_idle() {
  idle_cb* p = first;
  last = p; first = p->next;
  p->cb(p->data); // this may call add_idle() or remove_idle()!
}

/**
  Adds a callback function that is called every time by Fl::wait() and also
  makes it act as though the timeout is zero (this makes Fl::wait() return
  immediately, so if it is in a loop it is called repeatedly, and thus the
  idle fucntion is called repeatedly).  The idle function can be used to get
  background processing done.
    
  You can have multiple idle callbacks. To remove an idle callback use
  Fl::remove_idle().
    
  Fl::wait() and Fl::check() call idle callbacks, but Fl::ready() does not.
    
  The idle callback can call any FLTK functions, including Fl::wait(),
  Fl::check(), and Fl::ready().

  FLTK will not recursively call the idle callback.
*/
void Fl::add_idle(Fl_Idle_Handler cb, void* data) {
  idle_cb* p = freelist;
  if (p) freelist = p->next;
  else p = new idle_cb;
  p->cb = cb;
  p->data = data;
  if (first) {
    last->next = p;
    last = p;
    p->next = first;
  } else {
    first = last = p;
    p->next = p;
    set_idle(call_idle);
  }
}

/**
  Returns true if the specified idle callback is currently installed.
*/
int Fl::has_idle(Fl_Idle_Handler cb, void* data) {
  idle_cb* p = first;
  if (!p) return 0;
  for (;; p = p->next) {
    if (p->cb == cb && p->data == data) return 1;
    if (p==last) return 0;
  }
}

/**
  Removes the specified idle callback, if it is installed.
*/
void Fl::remove_idle(Fl_Idle_Handler cb, void* data) {
  idle_cb* p = first;
  if (!p) return;
  idle_cb* l = last;
  for (;; p = p->next) {
    if (p->cb == cb && p->data == data) break;
    if (p==last) return; // not found
    l = p;
  }
  if (l == p) { // only one
    first = last = 0;
    set_idle(0);
  } else {
    last = l;
    first = l->next = p->next;
  }
  p->next = freelist;
  freelist = p;
}

//
// End of "$Id: Fl_add_idle.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
