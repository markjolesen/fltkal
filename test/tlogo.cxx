//
// Input field test program for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     https://www.fltk.org/COPYING.php
//
// Please see the following page on how to report bugs and issues:
//
//     https://www.fltk.org/bugs.php
//

#include <stdio.h>
#include <fl/fl.h>
#include <fl/win.h>
#include <fl/imgbmp.h>
#include <fl/box.h>

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(500,500);

  Fl_Box *box= new Fl_Box(0,0,450,128);
  Fl_BMP_Image *bmp= new Fl_BMP_Image("logo.bmp");
  box->image(bmp);

  window->end();
  window->show(argc,argv);

  return Fl::run();
}
