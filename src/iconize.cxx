//
// Window minification code for the Fast Light Tool Kit (FLTK).
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

#include <fl/win.h>
#include "drvwin.h"

void Fl_Window::iconize() {
  if (!shown()) {
    show_iconic_ = 1;
    show();
  } else {
    pWindowDriver->iconize();
  }
}
