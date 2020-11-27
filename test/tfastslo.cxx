// generated by Fast Light User Interface Designer (fluid) version 1.0400
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

#include "tfastslo.h"

Fl_Slider *control=(Fl_Slider *)0;

static void cb_control(Fl_Slider* o, void*) {
  fast->value(o->value());
if (!Fl::pushed()) slow->value(o->value());
}

Fl_Slider *fast=(Fl_Slider *)0;

Fl_Slider *slow=(Fl_Slider *)0;

int main(int argc, char **argv) {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(318, 443);
    w = o; if (w) {/* empty */}
    { Fl_Slider* o = control = new Fl_Slider(90, 200, 30, 200, "move\nthis");
      control->callback((Fl_Callback*)cb_control);
      o->when(FL_WHEN_CHANGED|FL_WHEN_RELEASE|FL_WHEN_NOT_CHANGED);
    } // Fl_Slider* control
    { Fl_Slider* o = fast = new Fl_Slider(140, 200, 30, 200, "fast\nredraw");
      o->set_output();
    } // Fl_Slider* fast
    { Fl_Slider* o = slow = new Fl_Slider(190, 200, 30, 200, "slow\nredraw");
      o->set_output();
    } // Fl_Slider* slow
    { Fl_Box* o = new Fl_Box(10, 10, 300, 180, "The left slider has changed( FL_WHEN_CHANGED | FL_WHEN_RELEASE | FL_WHEN_NOT_\
CHANGED) so it produces a callback on both drag and release mouse events.\nThe\
 middle slider (representing a widget with low overhead) is changed on every m\
ouse movement.\nThe right slider (representing a widget with high overhead) is\
 only updated when the mouse is released, by checking if Fl::pushed() is zero.");
      o->box(FL_DOWN_BOX);
      o->color((Fl_Color)53);
      o->selection_color(FL_DARK1);
      o->labelfont(4);
      o->labelsize(12);
      o->align(Fl_Align(132|FL_ALIGN_INSIDE));
    } // Fl_Box* o
    o->end();
    o->resizable(o);
  } // Fl_Double_Window* o
  w->show(argc, argv);
  return Fl::run();
}
