//
// "$Id: native-filechooser.cxx 12506 2017-10-17 00:28:56Z greg.ercolano $"
//
// Simple test of the Fl_Native_File_Chooser.
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2016 by Bill Spitzak and others.
// Copyright 2004 Greg Ercolano.
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
#include <stdio.h>
#include <string.h>		/* strstr() */
#if 0
#include <FL/Fl.H>
#include <FL/fl_ask.H>		/* fl_beep() */
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Help_View.H>
#include <FL/Fl_Simple_Terminal.H>
#else
#include <fl/fl.h>
#include <fl/fl_ask.h>		/* fl_beep() */
#include <fl/win.h>
#include <fl/btn.h>
#include <fl/input.h>
#include <fl/inpmulti.h>
#include <fl/box.h>
#include <fl/filechn.h>
#include <fl/helpview.h>
#include <fl/terminal.h>
#endif

#define TERMINAL_HEIGHT 120

// GLOBALS
Fl_Input *G_filename = NULL;
Fl_Multiline_Input *G_filter = NULL;
Fl_Simple_Terminal *G_tty = NULL;

void PickFile_CB(Fl_Widget*, void*) {
  // Create native chooser
  Fl_Native_File_Chooser native;
  native.title("Pick a file");
  native.type(Fl_Native_File_Chooser::BROWSE_FILE);
  native.filter(G_filter->value());
  native.preset_file(G_filename->value());
  // Show native chooser
  switch ( native.show() ) {
    case -1: G_tty->printf("ERROR: %s\n", native.errmsg()); break;	// ERROR
    case  1: G_tty->printf("*** CANCEL\n"); fl_beep(); break;		// CANCEL
    default: 								// PICKED FILE
      if ( native.filename() ) {
        G_filename->value(native.filename());
	G_tty->printf("filename='%s'\n", native.filename());
      } else {
	G_filename->value("NULL");
	G_tty->printf("filename='(null)'\n");
      }
      break;
  }
}

void PickDir_CB(Fl_Widget*, void*) {
  // Create native chooser
  Fl_Native_File_Chooser native;
  native.title("Pick a Directory");
  native.directory(G_filename->value());
  native.type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
  // Show native chooser
  switch ( native.show() ) {
    case -1: G_tty->printf("ERROR: %s\n", native.errmsg()); break;	// ERROR
    case  1: G_tty->printf("*** CANCEL\n"); fl_beep(); break;		// CANCEL
    default: 								// PICKED DIR
      if ( native.filename() ) {
        G_filename->value(native.filename());
	G_tty->printf("dirname='%s'\n", native.filename());
      } else {
	G_filename->value("NULL");
	G_tty->printf("dirname='(null)'\n");
      }
      break;
  }
}

int main(int argc, char **argv) {
  //// For a nicer looking browser under linux, call Fl_File_Icon::load_system_icons();
  //// (If you do this, you'll need to link with fltk_images)
  //// NOTE: If you do not load the system icons, the file chooser will still work, but
  ////       no icons will be shown. However, this means you do not need to link in the
  ////       fltk_images library, potentially reducing the size of your executable.
  //// Loading the system icons is not required by the OSX or Windows native file choosers.
#if !defined(WIN32) && !defined(__APPLE__)
  Fl_File_Icon::load_system_icons();
#endif

  int argn = 1;
#ifdef __APPLE__
  // OS X may add the process number as the first argument - ignore
  if (argc>argn && strncmp(argv[1], "-psn_", 5)==0)
    argn++;
#endif
  
  Fl_Window *win = new Fl_Window(640, 400+TERMINAL_HEIGHT, "Native File Chooser Test");
  win->size_range(win->w(), win->h(), 0, 0);
  win->begin();
  {
    G_tty = new Fl_Simple_Terminal(0,400,win->w(),TERMINAL_HEIGHT);

    int x = 80, y = 10;
    G_filename = new Fl_Input(x, y, win->w()-80-10, 25, "Filename");
    G_filename->value(argc <= argn ? "." : argv[argn]);
    G_filename->tooltip("Default filename");

    y += G_filename->h() + 10;
    G_filter = new Fl_Multiline_Input(x, y, G_filename->w(), 100, "Filter");
    G_filter->value("Text\t*.txt\n"
                    "C Files\t*.{cxx,h,c,cpp}\n"
                    "Tars\t*.{tar,tar.gz}\n"
		    "Apps\t*.app");
    G_filter->tooltip("Filter to be used for browser.\n"
                      "An empty string may be used.\n");

    y += G_filter->h() + 10;
    Fl_Help_View *view = new Fl_Help_View(x, y, G_filename->w(), 200);
    view->box(FL_FLAT_BOX);
    view->color(win->color());
#define TAB "&lt;Tab&gt;"
    view->textfont(FL_HELVETICA);
    view->textsize(10);
    view->value("The Filter can be one or more filter patterns, one per line.\n"
		"Patterns can be:<ul>\n"
		"  <li>A single wildcard (e.g. <tt>\"*.txt\"</tt>)</li>\n"
		"  <li>Multiple wildcards (e.g. <tt>\"*.{cxx,h,H}\"</tt>)</li>\n"
		"  <li>A descriptive name followed by a " TAB " and a wildcard (e.g. <tt>\"Text Files" TAB "*.txt\"</tt>)</li>\n"
		"</ul>\n"
                "In the above \"Filter\" field, you can use <b><font color=#55f face=Courier>Ctrl-I</font></b> to enter " TAB " characters as needed.<br>\n"
		"Example:<pre>\n"
		"\n"
		"    Text<font color=#55f>&lt;Ctrl-I&gt;</font>*.txt\n"
		"    C Files<font color=#55f>&lt;Ctrl-I&gt;</font>*.{cxx,h,c,cpp}\n"
		"    Tars<font color=#55f>&lt;Ctrl-I&gt;</font>*.{tar,tar.gz}\n"
		"    Apps<font color=#55f>&lt;Ctrl-I&gt;</font>*.app\n"
		"</pre>\n");

    Fl_Button *but = new Fl_Button(win->w()-x-10, win->h()-TERMINAL_HEIGHT-25-10, 80, 25, "Pick File");
    but->callback(PickFile_CB);

    Fl_Button *butdir = new Fl_Button(but->x()-x-10, win->h()-TERMINAL_HEIGHT-25-10, 80, 25, "Pick Dir");
    butdir->callback(PickDir_CB);

    win->resizable(G_filter);
  }
  win->end();
  win->show(argc, argv);
  return(Fl::run());
}

//
// End of "$Id: native-filechooser.cxx 12506 2017-10-17 00:28:56Z greg.ercolano $".
//
