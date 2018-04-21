// imgtiled.h
//
// "$Id: Fl_Tiled_Image.H 12786 2018-03-23 17:03:24Z manolo $"
//
// Tiled image header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2015, 2018 by Bill Spitzak and others.
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

/* \file
   Fl_Tiled_Image widget . */

#ifndef Fl_Tiled_Image_H
#  define Fl_Tiled_Image_H

#  include "img.h"


/**
  This class supports tiling of images over a specified area.

  The source (tile) image is \b not copied unless you call the
  color_average(), desaturate(), or inactive() methods.
*/
class FL_EXPORT Fl_Tiled_Image : public Fl_Image {
  protected:

  Fl_Image	*image_;		// The image that is tiled
  int		alloc_image_;		// Did we allocate this image?

  public:

  Fl_Tiled_Image(Fl_Image *i, int W = 0, int H = 0);
  virtual ~Fl_Tiled_Image();

  virtual Fl_Image *copy(int W, int H);
  Fl_Image *copy() { return Fl_Image::copy(); }
  virtual void color_average(Fl_Color c, float i);
  virtual void desaturate();
  virtual void draw(int X, int Y, int W, int H, int cx = 0, int cy = 0);
  void draw(int X, int Y) { draw(X, Y, w(), h(), 0, 0); }
  /** Gets The image that is tiled */
  Fl_Image *image() { return image_; }
};

#endif // !Fl_Tiled_Image_H

//
// End of "$Id: Fl_Tiled_Image.H 12786 2018-03-23 17:03:24Z manolo $"
//
