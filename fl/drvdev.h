// drvdev.h
//
// "$Id: Fl_Device.H 12226 2017-04-25 12:42:22Z manolo $"
//
// Definition of classes Fl_Surface_Device, Fl_Display_Device
// for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 2010-2017 by Bill Spitzak and others.
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

/** \file Fl_Device.H 
 \brief declaration of classes Fl_Surface_Device, Fl_Display_Device, Fl_Device_Plugin.
*/

#ifndef Fl_Device_H
#define Fl_Device_H

#include <fl/plugin.h>
#include <stdlib.h>

#include <fl/export.h>

class Fl_Graphics_Driver;
class Fl_RGB_Image;
class Fl_Widget;

/**
 A drawing surface that's susceptible to receive graphical output.
 Any FLTK application has at any time a current drawing surface to which all drawing requests are directed.
 The current surface is given by Fl_Surface_Device::surface().
 When main() begins running, the current drawing surface has been set to the computer's display, 
 an instance of the Fl_Display_Device class.

 A drawing surface other than the computer's display, is typically used as follows:
 <ol><li> Create \c surface, an object from a particular Fl_Surface_Device derived class (e.g., Fl_Copy_Surface, Fl_Printer).
 <li> Call \c Fl_Surface_Device::push_current(surface); to redirect all graphics requests to \c surface which becomes the new
 current drawing surface (not necessary with class Fl_Printer because it is done by Fl_Printer::start_job()).
 <li> At this point all of the \ref fl_drawings (e.g., fl_rect()) or the \ref fl_attributes or \ref drawing_images functions
 (e.g., fl_draw_image(), Fl_Image::draw()) operate on the new current drawing surface.
 Certain drawing surfaces allow additional ways to draw to them (e.g., Fl_Printer::print_widget(), Fl_Image_Surface::draw()).
 <li> After all drawing requests have been performed, redirect graphics requests back to their previous destination
 with \c Fl_Surface_Device::pop_current();.
 <li> Delete \c surface.
 </ol>
 For back-compatibility, it is also possible to use the Fl_Surface_Device::set_current() member function
 to change the current drawing surface, once to the new surface, once to the previous one.
 */
class FL_EXPORT Fl_Surface_Device {
  /** The graphics driver in use by this surface. */
  Fl_Graphics_Driver *pGraphicsDriver;
  static Fl_Surface_Device *surface_; // the surface that currently receives graphics requests
  static Fl_Surface_Device *default_surface(); // create surface if none exists yet
  /* Some drawing surfaces (e.g., Fl_XXX_Image_Surface_Driver) re-implement this.
   Gets called each time a surface ceases to be the current drawing surface.
   The next_current argument gives the drawing surface that will become current next */
  virtual void end_current_(Fl_Surface_Device *next_current) {}
protected:
  /** Constructor that sets the graphics driver to use for the created surface. */
  Fl_Surface_Device(Fl_Graphics_Driver *graphics_driver) {pGraphicsDriver = graphics_driver; }
public:
  virtual void set_current(void);
  /** \brief Sets the graphics driver of this drawing surface. */
  inline void driver(Fl_Graphics_Driver *graphics_driver) {pGraphicsDriver = graphics_driver;};
  /** \brief Returns the graphics driver of this drawing surface. */
  inline Fl_Graphics_Driver *driver() {return pGraphicsDriver; };
  /** The current drawing surface.
   In other words, the Fl_Surface_Device object that currently receives all graphics requests */
  static inline Fl_Surface_Device *surface() {
    return surface_ ? surface_ : default_surface();
  };
  /** \brief The destructor. */
  virtual ~Fl_Surface_Device();
  static void push_current(Fl_Surface_Device *new_current);
  static Fl_Surface_Device *pop_current();
};

/**
 A display to which the computer can draw.
 When the program begins running, an object of class Fl_Display_Device has been created and made the current drawing surface.
 */
class FL_EXPORT Fl_Display_Device : public Fl_Surface_Device {
  Fl_Display_Device(Fl_Graphics_Driver *graphics_driver);
public:
  static Fl_Display_Device *display_device();
};

/**
 This plugin socket allows the integration of new device drivers for special
 window or screen types. 
 This class is not intended for use outside the FLTK library.
 It is currently used to provide an automated printing
 service and screen capture for OpenGL windows, if linked with fltk_gl.
 */
class FL_EXPORT Fl_Device_Plugin : public Fl_Plugin {
public:
  /** \brief The constructor */
  Fl_Device_Plugin(const char *pluginName)
  : Fl_Plugin(klass(), pluginName) { }
  /** \brief Returns the class name */
  virtual const char *klass() { return "fltk:device"; }
  /** \brief Returns the plugin name */
  virtual const char *name() = 0;
  /** \brief Prints a widget 
   \param w the widget
   \param x,y offsets where to print relatively to coordinates origin
   \param height height of the current drawing area
   */
  virtual int print(Fl_Widget* w, int x, int y, int height) = 0;
  /** captures a rectangle of a widget as an image
   \return The captured pixels as an RGB image
   */
  virtual Fl_RGB_Image* rectangle_capture(Fl_Widget *widget, int x, int y, int w, int h) = 0;
};

#endif // Fl_Device_H

//
// End of "$Id: Fl_Device.H 12226 2017-04-25 12:42:22Z manolo $".
//
