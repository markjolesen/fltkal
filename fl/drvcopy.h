// drvcopy.h
//
// "$Id$"
//
// Copy-to-clipboard code for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2014 by Bill Spitzak and others.
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

#ifndef Fl_Copy_Surface_H
#define Fl_Copy_Surface_H

#include <fl/widgsurf.h>

/** Supports copying of graphical data to the clipboard.
 
 <br> After creation of an Fl_Copy_Surface object, make it the current drawing surface calling Fl_Surface_Device::push_current(), and all subsequent graphics requests
 will be recorded in the clipboard. It's possible to draw widgets (using Fl_Copy_Surface::draw()
 ) or to use any of the \ref fl_drawings or the \ref fl_attributes.
 Finally, delete the Fl_Copy_Surface object to load the clipboard with the graphical data.
 <br> Fl_Gl_Window 's can be copied to the clipboard as well. 
 <br> Usage example:
 \code
 Fl_Widget *g = ...; // a widget you want to copy to the clipboard
 Fl_Copy_Surface *copy_surf = new Fl_Copy_Surface(g->w(), g->h()); // create an Fl_Copy_Surface object
 Fl_Surface_Device::push_current(copy_surf); // direct graphics requests to the clipboard
 fl_color(FL_WHITE); fl_rectf(0, 0, g->w(), g->h()); // draw a white background
 copy_surf->draw(g); // draw the g widget in the clipboard
 Fl_Surface_Device::pop_current();  // direct graphics requests back to their previous destination
 delete copy_surf; // after this, the clipboard is loaded
 \endcode
 Platform details:
 \li Windows: Transparent RGB images copy without transparency.
 The graphical data are copied to the clipboard in two formats: 1) as an 'enhanced metafile';
 2) as a color bitmap. Applications to which the clipboard content is pasted can use the format
 that suits them best.
 \li Mac OS: The graphical data are copied to the clipboard (a.k.a. pasteboard) in two 'flavors':
 1) in vectorial form as PDF data; 2) in bitmap form as a TIFF image. 
 Applications to which the clipboard content is pasted can use the flavor that suits them best.
 \li X11: the graphical data are copied to the clipboard as an image in BMP format.
*/
class FL_EXPORT Fl_Copy_Surface : public Fl_Widget_Surface {
private:
  class Fl_Copy_Surface_Driver *platform_surface;
protected:
  void translate(int x, int y);
  void untranslate();
public:
  Fl_Copy_Surface(int w, int h);
  ~Fl_Copy_Surface();
  void set_current();
  virtual bool is_current();
  /** Returns the pixel width of the copy surface */
  int w();
  /** Returns the pixel height of the copy surface */
  int h();
  void origin(int *x, int *y);
  void origin(int x, int y);
  int printable_rect(int *w, int *h);
  virtual void draw_decorated_window(Fl_Window *win, int x_offset = 0, int y_offset = 0);
};


/**
 \cond DriverDev
 \addtogroup DriverDeveloper
 \{
 */

/**
 A base class describing the interface between FLTK and draw-to-clipboard operations.
 
 This class is only for internal use by the FLTK library.

 A supported platform should implement the virtual methods of this class
 in order to support drawing to the clipboard through class Fl_Copy_Surface.
 */
class Fl_Copy_Surface_Driver : public Fl_Widget_Surface {
  friend class Fl_Copy_Surface;
protected:
  int width;
  int height;
  Fl_Copy_Surface_Driver(int w, int h) : Fl_Widget_Surface(NULL), width(w), height(h) {}
  virtual ~Fl_Copy_Surface_Driver() {}
  virtual void set_current() = 0;
  virtual void translate(int x, int y) = 0;
  virtual void untranslate() = 0;
  int printable_rect(int *w, int *h);
  /** Each platform implements this function its own way.
   It returns an object implementing all virtual functions
   of class Fl_Copy_Surface_Driver for the plaform.
   */
  static Fl_Copy_Surface_Driver *newCopySurfaceDriver(int w, int h);
};

/**
 \}
 \endcond
 */

#endif // Fl_Copy_Surface_H

//
// End of "$Id$".
//
