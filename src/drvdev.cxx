// drvdev.cxx
//
// "$Id: Fl_Device.cxx 12396 2017-08-24 12:40:29Z manolo $"
//
// implementation of Fl_Device class for the Fast Light Tool Kit (FLTK).
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

#include <fl/fl.h>
#include "cfg_lib.h"
#include <fl/drvdev.h>
#include <fl/drvgr.h>

/* Attempt at an inheritance diagram.
 
 
  +- Fl_Surface_Device: any kind of surface that we can draw onto -> uses an Fl_Graphics_Driver
      |
      +- Fl_Display_Device: some kind of video device
      +- Fl_Copy_Surface: create an image for dnd or copy/paste
      +- Fl_Image_Surface: create an RGB Image
      +- Fl_Paged_Device: output to a printer or similar
          |
          +- Fl_..._Surface_: platform specific driver
          +- Fl_Printer: user can instantiate this to gain access to a printer
          +- Fl_System_Printer:
          +- Fl_PostScript_File_Device
              |
              +- Fl_PostScript_Printer
 
  +- Fl_Graphics_Driver
      |
      +- Fl_..._Graphics_Driver: platform specific graphics driver

*/

/** Make this surface the current drawing surface.
 This surface will receive all future graphics requests. 
 \p Starting from FLTK 1.4.0, another convenient API to set/unset the current drawing surface
 is Fl_Surface_Device::push_current( ) / Fl_Surface_Device::pop_current().*/
void Fl_Surface_Device::set_current(void)
{
  if (surface_) surface_->end_current_(this);
  fl_graphics_driver = pGraphicsDriver;
  surface_ = this;
  pGraphicsDriver->global_gc();
  driver()->set_current_();
}

Fl_Surface_Device* Fl_Surface_Device::surface_; // the current target surface of graphics operations


Fl_Surface_Device::~Fl_Surface_Device()
{
  if (surface_ == this) surface_ = NULL;
}


/**  A constructor that sets the graphics driver used by the display */
Fl_Display_Device::Fl_Display_Device(Fl_Graphics_Driver *graphics_driver) : Fl_Surface_Device(graphics_driver) {
  this->set_current();
};


/** Returns a pointer to the unique display device */
Fl_Display_Device *Fl_Display_Device::display_device() {
  static Fl_Display_Device *display = new Fl_Display_Device(Fl_Graphics_Driver::newMainGraphicsDriver());
  return display;
};


Fl_Surface_Device *Fl_Surface_Device::default_surface()
{
  return Fl_Display_Device::display_device();
}

static unsigned int surface_stack_height = 0;
static Fl_Surface_Device *surface_stack[16];

/** Pushes \p new_current on top of the stack of current drawing surfaces, and makes it current.
 \p new_current will receive all future graphics requests.
 \version 1.4.0 */
void Fl_Surface_Device::push_current(Fl_Surface_Device *new_current)
{
  if (surface_stack_height < sizeof(surface_stack)/sizeof(void*)) {
    surface_stack[surface_stack_height++] = surface();
  } else {
    fprintf(stderr, "FLTK Fl_Surface_Device::push_current Stack overflow error\n");
  }
  new_current->set_current();
}

/** Removes the top element from the current drawing surface stack, and makes the new top element current.
 \return A pointer to the new current drawing surface. 
 \version 1.4.0 */
Fl_Surface_Device *Fl_Surface_Device::pop_current()
{
  if (surface_stack_height > 0) surface_stack[--surface_stack_height]->set_current();
  return surface_;
}

//
// End of "$Id: Fl_Device.cxx 12396 2017-08-24 12:40:29Z manolo $".
//
