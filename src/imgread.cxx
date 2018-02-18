// imgread.cxx
//
// "$Id: fl_read_image.cxx 11547 2016-04-06 22:20:32Z AlbrechtS $"
//
// X11 image reading routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2016 by Bill Spitzak and others.
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

#include <fl/fl.h>
#include <fl/platform.h>
#include <fl/drvscr.h>

/**
 Reads an RGB(A) image from the current window or off-screen buffer.
 \param[in] p     pixel buffer, or NULL to allocate one
 \param[in] X,Y   position of top-left of image to read
 \param[in] w,h   width and height of image to read
 \param[in] alpha alpha value for image (0 for none)
 \returns pointer to pixel buffer, or NULL if allocation failed.

 The \p p argument points to a buffer that can hold the image and must
 be at least \p w*h*3 bytes when reading RGB images, or \p w*h*4 bytes
 when reading RGBA images. If NULL, fl_read_image() will create an
 array of the proper size which can be freed using <tt>delete[]</tt>.

 The \p alpha parameter controls whether an alpha channel is created
 and the value that is placed in the alpha channel. If 0, no alpha
 channel is generated.
 */
uchar *fl_read_image(uchar *p, int X, int Y, int w, int h, int alpha) {
  uchar *image_data = NULL;
  Fl_RGB_Image *img;
  if (fl_find(fl_window) == 0) { // read from off_screen buffer
    img = Fl::screen_driver()->read_win_rectangle(X, Y, w, h);
    if (!img) {
      return NULL;
    }
    img->alloc_array = 1;
  } else {
    img = Fl::screen_driver()->traverse_to_gl_subwindows(Fl_Window::current(), X, Y, w, h, NULL);
  }
  int depth = alpha ? 4 : 3;
  if (img->d() != depth) {
    uchar *data = new uchar[img->w() * img->h() * depth];
    if (depth == 4) memset(data, alpha, img->w() * img->h() * depth);
    uchar *d = data;
    const uchar *q;
    int ld = img->ld() ? img->ld() : img->w() * img->d();
    for (int r = 0; r < img->h(); r++) {
      q = img->array + r * ld;
      for (int c = 0; c < img->w(); c++) {
        d[0] = q[0];
        d[1] = q[1];
        d[2] = q[2];
        d += depth; q += img->d();
      }
    }
    Fl_RGB_Image *img2 = new Fl_RGB_Image(data, img->w(), img->h(), depth);
    img2->alloc_array = 1;
    delete img;
    img = img2;
  }
  if (img) {
    if (img->w() != w || img->h() != h) {
      Fl_RGB_Image *img2 = (Fl_RGB_Image*)img->copy(w, h);
      delete img;
      img = img2;
    }
    img->alloc_array = 0;
    image_data = (uchar*)img->array;
    delete img;
  }
  if (p && image_data) {
    memcpy(p, image_data, w * h * depth);
    delete[] image_data;
    image_data = p;
  }
  return image_data;
}

//
// End of "$Id: fl_read_image.cxx 11547 2016-04-06 22:20:32Z AlbrechtS $".
//
