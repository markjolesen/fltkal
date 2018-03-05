//
// "$Id: pixmap.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Pixmap label test program for the Fast Light Tool Kit (FLTK).
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

#if 0
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Toggle_Button.H>
#else
#include <fl/fl.h>
#include <fl/windbl.h>
#include <fl/btn.h>
#include <fl/imgpix.h>
#include <fl/btntog.h>
#endif

#include <stdio.h>

#include "pixmaps/fltk.xpm"


Fl_Toggle_Button *leftb,*rightb,*topb,*bottomb,*insideb,*overb,*inactb;
Fl_Button *b;
Fl_Double_Window *w;

void button_cb(Fl_Widget *,void *) {
  int i = 0;
  if (leftb->value()) i |= FL_ALIGN_LEFT;
  if (rightb->value()) i |= FL_ALIGN_RIGHT;
  if (topb->value()) i |= FL_ALIGN_TOP;
  if (bottomb->value()) i |= FL_ALIGN_BOTTOM;
  if (insideb->value()) i |= FL_ALIGN_INSIDE;
  if (overb->value()) i |= FL_ALIGN_TEXT_OVER_IMAGE;
  b->align(i);
  if (inactb->value()) b->deactivate();
  else b->activate();
  w->redraw();
}

int dvisual = 0;
int arg(int, char **argv, int &i) {
  if (argv[i][1] == '8') {dvisual = 1; i++; return 1;}
  return 0;
}

#if 0
#include <FL/Fl_Multi_Label.H>
#else
#include <fl/labelm.h>
#endif

int main(int argc, char **argv) {
  int i = 1;
  if (Fl::args(argc,argv,i,arg) < argc)
    Fl::fatal(" -8 # : use default visual\n%s\n",Fl::help);

  Fl_Double_Window window(400,400); ::w = &window;
  Fl_Button b(140,160,120,120,"Pixmap"); ::b = &b;
  Fl_Pixmap *pixmap = new Fl_Pixmap(fltk_xpm);
  Fl_Pixmap *depixmap;
  depixmap = (Fl_Pixmap *)pixmap->copy();
  depixmap->inactive();

  b.image(pixmap);
  b.deimage(depixmap);

  leftb = new Fl_Toggle_Button(25,50,50,25,"left");
  leftb->callback(button_cb);
  rightb = new Fl_Toggle_Button(75,50,50,25,"right");
  rightb->callback(button_cb);
  topb = new Fl_Toggle_Button(125,50,50,25,"top");
  topb->callback(button_cb);
  bottomb = new Fl_Toggle_Button(175,50,50,25,"bottom");
  bottomb->callback(button_cb);
  insideb = new Fl_Toggle_Button(225,50,50,25,"inside");
  insideb->callback(button_cb);
  overb = new Fl_Toggle_Button(25,75,100,25,"text over");
  overb->callback(button_cb);
  inactb = new Fl_Toggle_Button(125,75,100,25,"inactive");
  inactb->callback(button_cb);
  if (!dvisual) Fl::visual(FL_RGB);
  window.resizable(window);
  window.end();
  window.show(argc,argv);
  return Fl::run();
}

//
// End of "$Id: pixmap.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
