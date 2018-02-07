//
// "$Id: buttons.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Another button test program for the Fast Light Tool Kit (FLTK).
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

#include <stdlib.h>
#include <stdio.h>
#if 0
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Repeat_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Tooltip.H>
#else
#include <fl/fl.h>
#include <fl/win.h>
#include <fl/btn.h>
#include <fl/btnret.h>
#include <fl/btnrpt.h>
#include <fl/btnk.h>
#include <fl/btnlt.h>
#include <fl/btnro.h>
#include <fl/tooltip.h>
// resolve window clash with conio
#undef window
#define window _window
#endif

int main(int argc, char ** argv) {
  Fl_Window *window = new Fl_Window(320,130);
  window->begin();
  Fl_Button *b = new Fl_Button(10, 10, 130, 30, "Fl_Button");
  b->tooltip("This is a Tooltip.");
  new Fl_Return_Button(150, 10, 160, 30, "Fl_Return_Button");
  new Fl_Repeat_Button(10,50,130,30,"Fl_Repeat_Button");
  new Fl_Light_Button(10,90,130,30,"Fl_Light_Button");
  new Fl_Round_Button(150,50,160,30,"Fl_Round_Button");
  new Fl_Check_Button(150,90,160,30,"Fl_Check_Button");
  new Fl_Check_Button(100,100,160,30,"Fl_Check_Button");
  window->end();
  window->show(argc,argv);
  return Fl::run();
}

//
// End of "$Id: buttons.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
