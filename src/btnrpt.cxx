// btnrpt.cxx
//
// "$Id: Fl_Repeat_Button.cxx 9637 2012-07-24 04:37:22Z matt $"
//
// Repeat button widget for the Fast Light Tool Kit (FLTK).
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
#include <fl/btnrpt.h>

#define INITIALREPEAT .5
#define REPEAT .1

void Fl_Repeat_Button::repeat_callback(void *v) {
  Fl_Button *b = (Fl_Button*)v;
  Fl::add_timeout(REPEAT,repeat_callback,b);
  b->do_callback();
}

int Fl_Repeat_Button::handle(int event) {
  int newval;
  switch (event) {
  case FL_HIDE:
  case FL_DEACTIVATE:
  case FL_RELEASE:
    newval = 0; goto J1;
  case FL_PUSH:
  case FL_DRAG:
    if (Fl::visible_focus()) Fl::focus(this);
    newval = Fl::event_inside(this);
  J1:
    if (!active()) 
      newval = 0;
    if (value(newval)) {
      if (newval) {
	Fl::add_timeout(INITIALREPEAT,repeat_callback,this);
	do_callback();
      } else {
	Fl::remove_timeout(repeat_callback,this);
      }
    }
    return 1;
  default:
    return Fl_Button::handle(event);
  }
}


Fl_Repeat_Button::Fl_Repeat_Button(int X,int Y,int W,int H,const char *l)
: Fl_Button(X,Y,W,H,l) 
{
}


//
// End of "$Id: Fl_Repeat_Button.cxx 9637 2012-07-24 04:37:22Z matt $".
//
