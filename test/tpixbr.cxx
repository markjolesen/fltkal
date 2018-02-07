//
// "$Id: pixmap_browser.cxx 12477 2017-10-04 16:26:51Z manolo $"
//
// A shared image test program for the Fast Light Tool Kit (FLTK).
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

#if 0
#include <config.h>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Printer.H>
#include <string.h>
#include <errno.h>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_message.H>
#else
#include <fl/fl.h>
#include <fl/box.h>
#include <fl/windbl.h>
#include <fl/btn.h>
#include <fl/imgshare.h>
#include <string.h>
#include <errno.h>
#include <fl/filech.h>
#include <fl/message.h>
#define window _window
#endif

Fl_Box *b;
Fl_Double_Window *w;
Fl_Shared_Image *img;


static char name[1024];

void load_file(const char *n) {
  if (img) {
    ((Fl_Shared_Image*)b->image())->release();
    img = 0L;
  }
  if (fl_filename_isdir(n)) {
    b->label("@fileopen"); // show a generic folder
    b->labelsize(64);
    b->labelcolor(FL_LIGHT2);
    b->image(0);
    b->redraw();
    return;
  }
  Fl_Shared_Image *img2 = Fl_Shared_Image::get(n);
 
  if (!img2) {
    b->label("@filenew"); // show an empty document
    b->labelsize(64);
    b->labelcolor(FL_LIGHT2);
    b->image(0);
    b->redraw();
    return;
  }
  img = img2;
  b->labelsize(14);
  b->labelcolor(FL_FOREGROUND_COLOR);
  b->image(img);
  img->scale(b->w(), b->h());
  b->label(NULL);
  b->redraw();
}

void file_cb(const char *n) {
  if (!strcmp(name,n)) return;
  load_file(n);
  strcpy(name,n);
  w->label(name);
}

void button_cb(Fl_Widget *,void *) {
  fl_file_chooser_callback(file_cb);
  const char *fname = fl_file_chooser("Image file?","*.{bm,bmp,gif,jpg,pbm,pgm,png,ppm,xbm,xpm"
#ifdef FLTK_USE_NANOSVG
                                      ",svg"
#ifdef HAVE_LIBZ
                                      ",svgz"
#endif
#endif
                                      "}", name);
  puts(fname ? fname : "(null)"); fflush(stdout);
  fl_file_chooser_callback(0);
}
void print_cb(Fl_Widget *widget, void *) {
#if 0
  Fl_Printer printer;
  int width, height;
  if (printer.start_job(1)) return;
  printer.start_page();
  printer.printable_rect(&width, &height);
  float fw = widget->window()->decorated_w() / float(width);
  float fh = widget->window()->decorated_h() / float(height);
  if (fh > fw) fw = fh;
  printer.scale(1/fw);
  printer.print_window(widget->window());
  printer.end_page();
  printer.end_job();
#endif
}

int dvisual = 0;
int arg(int, char **argv, int &i) {
  if (argv[i][1] == '8') {dvisual = 1; i++; return 1;}
  return 0;
}

int main(int argc, char **argv) {
  int i = 1;

  fl_register_images();

  Fl::args(argc,argv,i,arg);

  Fl_Double_Window window(400,450); ::w = &window;
window.label("Main Window"); //_mjo
  Fl_Box b(10,45,380,380); ::b = &b;
  b.box(FL_THIN_DOWN_BOX);
  b.align(FL_ALIGN_INSIDE|FL_ALIGN_CENTER|FL_ALIGN_CLIP);
  Fl_Button button(150,5,100,30,"load");
  button.callback(button_cb);
  if (!dvisual) Fl::visual(FL_RGB);
  if (argv[1]) load_file(argv[1]);
  window.resizable(b);
  Fl_Button print(300,425,50,25,"Print");
  print.callback(print_cb);

  window.show(argc,argv);
  return Fl::run();
}

//
// End of "$Id: pixmap_browser.cxx 12477 2017-10-04 16:26:51Z manolo $".
//
