// widgsurf.h
//
// "$Id: Fl_Widget_Surface.H 12196 2017-03-13 23:31:38Z AlbrechtS $"
//
// Drivers code for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Widget_Surface_h
#define Fl_Widget_Surface_h

#include <fl/drvdev.h>
#include <fl/win.h>

/** A surface on which any FLTK widget can be drawn.
 */
class FL_EXPORT Fl_Widget_Surface : public Fl_Surface_Device {
private:
  void traverse(Fl_Widget *widget); // finds subwindows of widget and prints them
protected:
  /** \brief horizontal offset to the origin of graphics coordinates */
  int x_offset;
  /** \brief vertical offset to the origin of graphics coordinates */
  int y_offset;
  Fl_Widget_Surface(Fl_Graphics_Driver *d);
public:
  /**
   Translates the current graphics origin accounting for the current rotation.
   
   Each translate() call must be matched by an untranslate() call.
   Successive translate() calls add up their effects.
   */
  virtual void translate(int x, int y);
  /**
   Undoes the effect of a previous translate() call.
   */
  virtual void untranslate(void) {}
  void draw(Fl_Widget* widget, int delta_x = 0, int delta_y = 0);
  virtual void draw_decorated_window(Fl_Window *win, int x_offset = 0, int y_offset = 0);
  virtual void print_window_part(Fl_Window *win, int x, int y, int w, int h, int delta_x = 0, int delta_y = 0);
  virtual int printable_rect(int *w, int *h);
  virtual void origin(int x, int y);
  virtual void origin(int *x, int *y);
};

#endif /* Fl_Widget_Surface_h */

//
// End of "$Id: Fl_Widget_Surface.H 12196 2017-03-13 23:31:38Z AlbrechtS $".
//
