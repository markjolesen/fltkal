//
// "$Id: windowfocus.cxx 10594 2015-02-27 14:10:29Z AlbrechtS $"
//
// Cross-window show/focus test program for the Fast Light Tool Kit (FLTK).
//
// Copyright 2018 The fltkal authors
// Copyright 1998-2015 by Bill Spitzak and others.
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

#if 0
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#else
#include <fl/fl.h>
#include <fl/box.h>
#include <fl/windbl.h>
#include <fl/input.h>
#endif

static Fl_Double_Window *win1, *win2;
static Fl_Input *input1;

static void popup(Fl_Widget *, void *) {

  win2->position(win1->x() + win1->w(), win1->y());

  win2->show();
  win2->wait_for_expose();
  input1->take_focus();
}

int main(int argc, char **argv) {

  win1 = new Fl_Double_Window(300, 200);
  win1->label("show() focus test");

  Fl_Box *b = new Fl_Box(10, 10, 280, 130);
  b->label("Type something to pop the subwindow up. "
	   "The focus should stay on the input, "
	   "and you should be able to continue typing.");
  b->align(FL_ALIGN_WRAP | FL_ALIGN_LEFT | FL_ALIGN_INSIDE);

  input1 = new Fl_Input(10, 150, 150, 25);
  input1->when(FL_WHEN_CHANGED);
  input1->callback(popup);

  win1->end();

  win2 = new Fl_Double_Window(300, 200);
  win2->label("window2");
  win2->end();

  win2->show(argc,argv);
  win1->show(argc,argv);

  return Fl::run();
}

//
// End of "$Id: windowfocus.cxx 10594 2015-02-27 14:10:29Z AlbrechtS $".
//
