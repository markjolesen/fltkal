// drvimg.h
//
// "$Id: Fl_Image_Surface.H 12125 2016-11-30 07:09:48Z manolo $"
//
// Draw-to-image code for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Image_Surface_H
#define Fl_Image_Surface_H

#include <fl/widgsurf.h>
#include <fl/img.h>
#include <fl/imgshare.h>
#include <fl/drvgr.h> // for Fl_Offscreen


/** 
 \brief Directs all graphics requests to an Fl_Image.
 
 After creation of an Fl_Image_Surface object, call set_current() on it, and all
 subsequent graphics requests will be recorded in the image. It's possible to 
 draw widgets (using Fl_Image_Surface::draw()) or to use any of the 
 \ref fl_drawings or the \ref fl_attributes. Finally, call image() on the object
 to obtain a newly allocated Fl_RGB_Image object.
 Fl_GL_Window objects can be drawn in the image as well.
 
 Usage example:
 \code
 // this is the widget that you want to draw into an image
 Fl_Widget *g = ...;

 // create an Fl_Image_Surface object
 Fl_Image_Surface *image_surface = new Fl_Image_Surface(g->w(), g->h());
 
 // direct all further graphics requests to the image
 image_surface->set_current();

 // draw a white background
 fl_color(FL_WHITE); 
 fl_rectf(0, 0, g->w(), g->h());

 // draw the g widget in the image
 image_surface->draw(g);

 // get the resulting image
 Fl_RGB_Image* image = image_surface->image();
 
 // delete the image_surface object, but not the image itself
 delete image_surface;

 // direct graphics requests back to the screen
 Fl_Display_Device::display_device()->set_current();
 \endcode
*/
class FL_EXPORT Fl_Image_Surface : public Fl_Widget_Surface {
  friend FL_EXPORT Fl_Offscreen fl_create_offscreen(int w, int h);
  friend FL_EXPORT void fl_begin_offscreen(Fl_Offscreen ctx);
  friend FL_EXPORT void fl_end_offscreen(void);
  friend FL_EXPORT void fl_delete_offscreen(Fl_Offscreen ctx);
private:
  class Fl_Image_Surface_Driver *platform_surface;
protected:
  void translate(int x, int y);
  void untranslate();
public:
  Fl_Image_Surface(int w, int h, int high_res = 0, Fl_Offscreen off = 0);
  ~Fl_Image_Surface();
  void set_current();
  Fl_RGB_Image *image();
  Fl_Shared_Image *highres_image();
  void origin(int *x, int *y);
  void origin(int x, int y);
  int printable_rect(int *w, int *h);
  Fl_Offscreen get_offscreen_before_delete();
  Fl_Offscreen offscreen();
};


/** A base class describing the interface between FLTK and draw-to-image operations.
 This class is only for internal use by the FLTK library.
 A supported platform should implement the virtual methods of this class
 in order to support drawing to an Fl_RGB_Image through class Fl_Image_Surface.
 */
class Fl_Image_Surface_Driver : public Fl_Widget_Surface {
  friend class Fl_Image_Surface;
protected:
  int width;
  int height;
  Fl_Offscreen offscreen;
  Fl_Image_Surface_Driver(int w, int h, int high_res, Fl_Offscreen off) : Fl_Widget_Surface(NULL), width(w), height(h), offscreen(off) {}
  virtual ~Fl_Image_Surface_Driver() {}
  virtual void set_current() {}
  virtual void translate(int x, int y) {}
  virtual void untranslate() {}
  int printable_rect(int *w, int *h) {*w = width; *h = height; return 0;}
  virtual Fl_RGB_Image *image() {return NULL;}
  /** Each platform implements this function its own way.
   It returns an object implementing all virtual functions
   of class Fl_Image_Surface_Driver for the plaform.
   */
  static Fl_Image_Surface_Driver *newImageSurfaceDriver(int w, int h, int high_res, Fl_Offscreen off);
};

#endif // Fl_Image_Surface_H

//
// End of "$Id: Fl_Image_Surface.H 12125 2016-11-30 07:09:48Z manolo $".
//
