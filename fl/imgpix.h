// pixmap.h
//
// "$Id: Fl_Pixmap.H 12776 2018-03-19 17:43:18Z manolo $"
//
// Pixmap header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2017 by Bill Spitzak and others.
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
   Fl_Pixmap widget . */

#ifndef Fl_Pixmap_H
#define Fl_Pixmap_H
#  include "img.h"

class Fl_Widget;
struct Fl_Menu_Item;

// Older C++ compilers don't support the explicit keyword... :(
#  if defined(__sgi) && !defined(_COMPILER_VERSION)
#    define explicit
#  endif // __sgi && !_COMPILER_VERSION

/**
  The Fl_Pixmap class supports caching and drawing of colormap
  (pixmap) images, including transparency.
*/
class FL_EXPORT Fl_Pixmap : public Fl_Image {
  friend class Fl_Graphics_Driver;
  void copy_data();
  void delete_data();
  void set_data(const char * const *p);
  int prepare(int XP, int YP, int WP, int HP, int &cx, int &cy,
			 int &X, int &Y, int &W, int &H);

protected:
  void measure();

public:

  int alloc_data; // Non-zero if data was allocated
  
private:
  // for internal use
  fl_uintptr_t id_;
  fl_uintptr_t mask_;
  Fl_Color pixmap_bg_color;
  float cache_scale_; // graphics scaling value when id_ was computed

public:

  /**    The constructors create a new pixmap from the specified XPM data.  */
  explicit Fl_Pixmap(char * const * D) : Fl_Image(-1,0,1), alloc_data(0), id_(0), mask_(0) {set_data((const char*const*)D); measure();}
  /**    The constructors create a new pixmap from the specified XPM data.  */
  explicit Fl_Pixmap(uchar* const * D) : Fl_Image(-1,0,1), alloc_data(0), id_(0), mask_(0) {set_data((const char*const*)D); measure();}
  /**    The constructors create a new pixmap from the specified XPM data.  */
  explicit Fl_Pixmap(const char * const * D) : Fl_Image(-1,0,1), alloc_data(0), id_(0), mask_(0) {set_data((const char*const*)D); measure();}
  /**    The constructors create a new pixmap from the specified XPM data.  */
  explicit Fl_Pixmap(const uchar* const * D) : Fl_Image(-1,0,1), alloc_data(0), id_(0), mask_(0) {set_data((const char*const*)D); measure();}
  virtual ~Fl_Pixmap();
  virtual Fl_Image *copy(int W, int H);
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void color_average(Fl_Color c, float i);
  virtual void desaturate();
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0);
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);}
  virtual void label(Fl_Widget*w);
  virtual void label(Fl_Menu_Item*m);
  virtual void uncache();
};

#endif

//
// End of "$Id: Fl_Pixmap.H 12776 2018-03-19 17:43:18Z manolo $".
//
