//
// "$Id: tiled_image.cxx 12655 2018-02-09 14:39:42Z AlbrechtS $"
//
// Fl_Tiled_Image test program for the Fast Light Tool Kit (FLTK).
//
// Copyright 2018 The fltkal authors
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

#if 0
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Tiled_Image.H>
#else
#include <fl/fl.h>
#include <fl/windbl.h>
#include <fl/btn.h>
#include <fl/imgpix.h>
#include <fl/imgtiled.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "pixmaps/tile.xpm"

Fl_Button *b;
Fl_Double_Window *w;

void button_cb(Fl_Widget *,void *) {
  w->hide();
}

#if 0
#include <FL/platform.H>
#if !defined(_WIN32) && !defined(__APPLE__)
#include "list_visuals.cxx"
#endif
#else
#include <fl/platform.h>
#endif

int visid = -1;
int arg(int argc, char **argv, int &i) {
  if (argv[i][1] == 'v') {
    if (i+1 >= argc) return 0;
    visid = atoi(argv[i+1]);
    i += 2;
    return 2;
  }
  return 0;
}

int main(int argc, char **argv) {
#if 0
#if !defined(_WIN32) && !defined(__APPLE__)
  int i = 1;

  Fl::args(argc,argv,i,arg);

  if (visid >= 0) {
    fl_open_display();
    XVisualInfo templt; int num;
    templt.visualid = visid;
    fl_visual = XGetVisualInfo(fl_display, VisualIDMask, &templt, &num);
    if (!fl_visual) {
      fprintf(stderr, "No visual with id %d, use one of:\n",visid);
      list_visuals();
      exit(1);
    }
    fl_colormap = XCreateColormap(fl_display, RootWindow(fl_display,fl_screen),
				fl_visual->visual, AllocNone);
    fl_xpixel(FL_BLACK); // make sure black is allocated in overlay visuals
  } else {
    Fl::visual(FL_RGB);
  }
#endif
#endif

  Fl_Double_Window window(400,400); ::w = &window;
  Fl_Group group(0,0,400,400);
  group.image(new Fl_Tiled_Image(new Fl_Pixmap((const char * const *)tile_xpm)));
  group.align(FL_ALIGN_INSIDE);

  Fl_Button b(340,365,50,25,"Close"); ::b = &b;
  b.callback(button_cb);

  group.end();

  window.resizable(group);
  window.end();
  window.show(argc, argv);

  return Fl::run();
}

//
// End of "$Id: tiled_image.cxx 12655 2018-02-09 14:39:42Z AlbrechtS $".
//
