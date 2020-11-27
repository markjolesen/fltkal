//
// "$Id: boxtype.cxx 10780 2015-07-08 23:41:19Z AlbrechtS $"
//
// Boxtype test program for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
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

#include <stdlib.h>
#include <stdio.h>
#if 0
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#else
#include <fl/fl.h>
#include <fl/windbl.h>
#include <fl/box.h>
#include <fl/fl_draw.h>
// resolve window clash with conio
#undef window
#define window _window
#endif

int N = 0;
#define W 200
#define H 50
#define ROWS 14

// Note: Run the program with command line '-s abc' to view boxtypes
// with scheme 'abc'.

// class BoxGroup - minimal class to enable visible box size debugging
//
// Set the following static variables to 0 (default) to disable
// or 1 to enable the given feature.
//
// If you enable the 'outline' variable, then a red frame should be drawn
// around each box, and it should ideally be fully visible.
//
// The white background is optional (otherwise you see the window background).
//
// Set BOTH variables = 0 to show the default image for the FLTK manual.
//
// Note: As of FLTK 1.3.3 (probably since FLTK 1.0/1.1) there are some
// shadows 'leaking' outside their widget bounding boxes (x,y,w,h).
// Is this intentional?

static const int outline = 0; // draw 1-px red frame around all boxes
static const int box_bg  = 0; // draw white background inside all boxes
static const int inactive  = 0; // deactivate boxes and use green background

class BoxGroup : public Fl_Group {
  public:
    BoxGroup(int x, int y, int w, int h) : Fl_Group(x,y,w,h) {};
    void draw() {
      draw_box();
      if (outline + box_bg) { // outline or box_bg or both
	Fl_Widget*const* a = array();
	for (int i=children(); i--;) {
	  Fl_Widget& o = **a++;
	  if (outline) {
	    fl_color(FL_RED);
	    fl_rect(o.x()-1,o.y()-1,o.w()+2,o.h()+2);
	  }
	  if (box_bg) {
	    fl_color(FL_WHITE);
	    fl_rectf(o.x(),o.y(),o.w(),o.h());
	  }
	  fl_color(FL_BLACK);
	}
      } // outline or box_bg or both
      Fl_Group::draw_children();
    } // draw()
}; // class BoxGroup

Fl_Double_Window *window;

void bt(const char *name, Fl_Boxtype type, int square=0) {
  int x = N%4;
  int y = N/4;
  N++;
  x = x*W+10;
  y = y*H+10;
  Fl_Box *b = new Fl_Box(type,x,y,square ? H-20 : W-20,H-20,name);
  b->labelsize(11);
  if (inactive) {
    b->color(FL_GREEN);
    b->deactivate();
  }
  if (square) b->align(FL_ALIGN_RIGHT);
}

int main(int argc, char ** argv) {
  window = new Fl_Double_Window(4*W,ROWS*H);
  window->box(FL_FLAT_BOX);
#if 0 // this code uses the command line arguments to set arbitrary color schemes
  Fl::args(argc, argv);
  Fl::get_system_colors();
#elif 0 // this code uses a single color to define a scheme
  Fl::args(argc, argv);
  Fl::get_system_colors();
  Fl::background(113,113,198);
#else // this code uses the nice bright blue background to show box vs. frame types
  Fl::args(argc, argv);
  Fl::get_system_colors();
  window->color(12);// light blue
#endif

  // set window title to show active scheme
  Fl::scheme(Fl::scheme()); // init scheme
  char title[100];
  sprintf(title,"FLTK boxtypes: scheme = '%s'",Fl::scheme()?Fl::scheme():"none");
  window->label(title);

  // create special container group for box size debugging
  BoxGroup *bg = new BoxGroup(0,0,window->w(),window->h());
  bg->box(FL_NO_BOX);

  // create demo boxes
  bt("FL_NO_BOX",FL_NO_BOX);
  bt("FL_FLAT_BOX",FL_FLAT_BOX);
  N += 2; // go to start of next row to line up boxes & frames
  bt("FL_UP_BOX",FL_UP_BOX);
  bt("FL_DOWN_BOX",FL_DOWN_BOX);
  bt("FL_UP_FRAME",FL_UP_FRAME);
  bt("FL_DOWN_FRAME",FL_DOWN_FRAME);
  bt("FL_THIN_UP_BOX",FL_THIN_UP_BOX);
  bt("FL_THIN_DOWN_BOX",FL_THIN_DOWN_BOX);
  bt("FL_THIN_UP_FRAME",FL_THIN_UP_FRAME);
  bt("FL_THIN_DOWN_FRAME",FL_THIN_DOWN_FRAME);
  bt("FL_ENGRAVED_BOX",FL_ENGRAVED_BOX);
  bt("FL_EMBOSSED_BOX",FL_EMBOSSED_BOX);
  bt("FL_ENGRAVED_FRAME",FL_ENGRAVED_FRAME);
  bt("FL_EMBOSSED_FRAME",FL_EMBOSSED_FRAME);
  bt("FL_BORDER_BOX",FL_BORDER_BOX);
  bt("FL_SHADOW_BOX",FL_SHADOW_BOX);
  bt("FL_BORDER_FRAME",FL_BORDER_FRAME);
  bt("FL_SHADOW_FRAME",FL_SHADOW_FRAME);
  bt("FL_ROUNDED_BOX",FL_ROUNDED_BOX);
  bt("FL_RSHADOW_BOX",FL_RSHADOW_BOX);
  bt("FL_ROUNDED_FRAME",FL_ROUNDED_FRAME);
  bt("FL_RFLAT_BOX",FL_RFLAT_BOX);
  bt("FL_OVAL_BOX",FL_OVAL_BOX);
  bt("FL_OSHADOW_BOX",FL_OSHADOW_BOX);
  bt("FL_OVAL_FRAME",FL_OVAL_FRAME);
  bt("FL_OFLAT_BOX",FL_OFLAT_BOX);
  bt("FL_ROUND_UP_BOX",FL_ROUND_UP_BOX);
  bt("FL_ROUND_DOWN_BOX",FL_ROUND_DOWN_BOX);
  bt("FL_DIAMOND_UP_BOX",FL_DIAMOND_UP_BOX);
  bt("FL_DIAMOND_DOWN_BOX",FL_DIAMOND_DOWN_BOX);

  bt("FL_PLASTIC_UP_BOX",FL_PLASTIC_UP_BOX);
  bt("FL_PLASTIC_DOWN_BOX",FL_PLASTIC_DOWN_BOX);
  bt("FL_PLASTIC_UP_FRAME",FL_PLASTIC_UP_FRAME);
  bt("FL_PLASTIC_DOWN_FRAME",FL_PLASTIC_DOWN_FRAME);
  bt("FL_PLASTIC_THIN_UP_BOX",FL_PLASTIC_THIN_UP_BOX);
  bt("FL_PLASTIC_THIN_DOWN_BOX",FL_PLASTIC_THIN_DOWN_BOX);
  N += 2;
  bt("FL_PLASTIC_ROUND_UP_BOX",FL_PLASTIC_ROUND_UP_BOX);
  bt("FL_PLASTIC_ROUND_DOWN_BOX",FL_PLASTIC_ROUND_DOWN_BOX);
  N += 2;

  bt("FL_GTK_UP_BOX",FL_GTK_UP_BOX);
  bt("FL_GTK_DOWN_BOX",FL_GTK_DOWN_BOX);
  bt("FL_GTK_UP_FRAME",FL_GTK_UP_FRAME);
  bt("FL_GTK_DOWN_FRAME",FL_GTK_DOWN_FRAME);
  bt("FL_GTK_THIN_UP_BOX",FL_GTK_THIN_UP_BOX);
  bt("FL_GTK_THIN_DOWN_BOX",FL_GTK_THIN_DOWN_BOX);
  bt("FL_GTK_THIN_UP_FRAME",FL_GTK_THIN_UP_FRAME);
  bt("FL_GTK_THIN_DOWN_FRAME",FL_GTK_THIN_DOWN_FRAME);
  bt("FL_GTK_ROUND_UP_BOX",FL_GTK_ROUND_UP_BOX);
  bt("FL_GTK_ROUND_DOWN_BOX",FL_GTK_ROUND_DOWN_BOX);
  bg->end();
  window->resizable(window);
  window->end();
  window->show();
  return Fl::run();
}

//
// End of "$Id: boxtype.cxx 10780 2015-07-08 23:41:19Z AlbrechtS $".
//
