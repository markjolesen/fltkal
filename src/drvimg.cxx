// drvimg.cxx
//
// "$Id: Fl_Image_Surface.cxx 12968 2018-06-23 16:47:40Z matt $"
//
// Draw-to-image code for the Fast Light Tool Kit (FLTK).
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

#include <fl/drvimg.h>
#include <fl/drvdev.h>

#if defined(FL_PORTING)
# pragma message "FL_PORTING: optionally implement class Fl_XXX_Image_Surface_Driver for your platform"
Fl_Image_Surface_Driver *Fl_Image_Surface_Driver::newImageSurfaceDriver(int w, int h, int high_res, Fl_Offscreen)
{
  return NULL;
}
#endif


/** Constructor with optional high resolution.
 \param w and \param h set the size of the resulting image. The value of the \p high_res
 parameter controls whether \p w and \p h are interpreted as pixel or FLTK units.
 
 \param high_res If zero, the created image surface is sized at \p w x \p h pixels.
 If non-zero, the pixel size of the created image surface depends on
 the value of the display scale factor (see Fl_Graphics_Driver::scale()):
 the resulting image has the same number of pixels as an area of the display of size
 \p w x \p h expressed in FLTK units.

 \param off If not null, the image surface is constructed around a pre-existing
 Fl_Offscreen. The caller is responsible for both construction and destruction of this Fl_Offscreen object.
 Is mostly intended for internal use by FLTK.
 \version 1.3.4 (1.3.3 without the \p highres parameter)
 */
Fl_Image_Surface::Fl_Image_Surface(int w, int h, int high_res, Fl_Offscreen off) : Fl_Widget_Surface(NULL) {
  platform_surface = Fl_Image_Surface_Driver::newImageSurfaceDriver(w, h, high_res, off);
  if (platform_surface) driver(platform_surface->driver());
}


/** The destructor. */
Fl_Image_Surface::~Fl_Image_Surface() { delete platform_surface; }

void Fl_Image_Surface::origin(int x, int y) {platform_surface->origin(x, y);}

void Fl_Image_Surface::origin(int *x, int *y) {
  if (platform_surface) platform_surface->origin(x, y);
}

void Fl_Image_Surface::set_current() {
  if (platform_surface) platform_surface->set_current();
}

void Fl_Image_Surface::translate(int x, int y) {
  if (platform_surface) platform_surface->translate(x, y);
}

void Fl_Image_Surface::untranslate() {
  if (platform_surface) platform_surface->untranslate();
}

/** Returns the Fl_Offscreen object associated to the image surface.
 The returned Fl_Offscreen object is deleted when the Fl_Image_Surface object is deleted,
 unless the Fl_Image_Surface was constructed with non-null Fl_Offscreen argument.
 */
Fl_Offscreen Fl_Image_Surface::offscreen() { 
  return platform_surface ? platform_surface->offscreen : (Fl_Offscreen)0;
}

int Fl_Image_Surface::printable_rect(int *w, int *h)  {return platform_surface->printable_rect(w, h);}


/** Returns an image made of all drawings sent to the Fl_Image_Surface object.
 The returned object contains its own copy of the RGB data.
 The caller is responsible for deleting the image.
 */
Fl_RGB_Image *Fl_Image_Surface::image() {
  bool need_push = (Fl_Surface_Device::surface() != platform_surface);
  if (need_push) Fl_Surface_Device::push_current(platform_surface);
  Fl_RGB_Image *img = platform_surface->image();
  if (need_push) Fl_Surface_Device::pop_current();
  img->scale(platform_surface->width, platform_surface->height, 1, 1);
  return img;
}

/** Returns a possibly high resolution image made of all drawings sent to the Fl_Image_Surface object.
 The Fl_Image_Surface object should have been constructed with Fl_Image_Surface(W, H, 1).
 The returned Fl_Shared_Image object is scaled to a size of WxH FLTK units and may have a 
 pixel size larger than these values.
 The returned object should be deallocated with Fl_Shared_Image::release() after use.
 Deprecated: use image() instead.
 \version 1.4 (1.3.4 for MacOS platform only)
 */
Fl_Shared_Image* Fl_Image_Surface::highres_image()
{
  if (!platform_surface) return NULL;
  Fl_Shared_Image *s_img = Fl_Shared_Image::get(image());
  int width, height;
  platform_surface->printable_rect(&width, &height);
  s_img->scale(width, height, 1, 1);
  return s_img;
}

// Allows to delete the Fl_Image_Surface object while keeping its underlying Fl_Offscreen
Fl_Offscreen Fl_Image_Surface::get_offscreen_before_delete_() {
  Fl_Offscreen keep = platform_surface->offscreen;
  platform_surface->offscreen = 0;
  return keep;
}

/** Adapts the Fl_Image_Surface object to the new value of the GUI scale factor.
 The Fl_Image_Surface object must not be the current drawing surface.
 This function is useful only for an object constructed with non-zero \p high_res parameter.
 \version 1.4
 */
void Fl_Image_Surface::rescale() {
  Fl_RGB_Image *rgb = image();
  int w, h;
  printable_rect(&w, &h);
  delete platform_surface;
  platform_surface = Fl_Image_Surface_Driver::newImageSurfaceDriver(w, h, 1, 0);
  Fl_Surface_Device::push_current(this);
  rgb->draw(0,0);
  Fl_Surface_Device::pop_current();
  delete rgb;
}

// implementation of the fl_XXX_offscreen() functions

static Fl_Image_Surface **offscreen_api_surface = NULL;
static int count_offscreens = 0;

static int find_slot(void) { // return an available slot to memorize an Fl_Image_Surface object
  static int max = 0;
  for (int num = 0; num < count_offscreens; num++) {
    if (!offscreen_api_surface[num]) return num;
  }
  if (count_offscreens >= max) {
    max += 20;
    offscreen_api_surface = (Fl_Image_Surface**)realloc(offscreen_api_surface, max * sizeof(void *));
  }
  return count_offscreens++;
}

/** \addtogroup fl_drawings
   @{
   */

/**
   Creation of an offscreen graphics buffer.
   \param w,h     width and height in FLTK units of the buffer.
   \return    the created graphics buffer.
 
 The pixel size of the created graphics buffer is equal to the number of pixels
 in an area of the screen containing the current window sized at \p w,h FLTK units.
 This pixel size varies with the value of the scale factor of this screen.
 \note Work with the fl_XXX_offscreen() functions is equivalent to work with
 an Fl_Image_Surface object, as follows :
 <table>
 <tr> <th>Fl_Offscreen-based approach</th><th>Fl_Image_Surface-based approach</th> </tr>
 <tr> <td>Fl_Offscreen off = fl_create_offscreen(w, h)</td><td>Fl_Image_Surface *surface = new Fl_Image_Surface(w, h, 1)</td> </tr>
 <tr> <td>fl_begin_offscreen(off)</td><td>Fl_Surface_Device::push_current(surface)</td> </tr>
 <tr> <td>fl_end_offscreen()</td><td>Fl_Surface_Device::pop_current()</td> </tr>
 <tr> <td>fl_copy_offscreen(x,y,w,h, off, sx,sy)</td><td>fl_copy_offscreen(x,y,w,h, surface->offscreen(), sx,sy)</td> </tr>
 <tr> <td>fl_rescale_offscreen(off)</td><td>surface->rescale()</td> </tr>
 <tr> <td>fl_delete_offscreen(off)</td><td>delete surface</td> </tr>
 </table>
   */
Fl_Offscreen fl_create_offscreen(int w, int h) {
  int rank = find_slot();
  offscreen_api_surface[rank] = new Fl_Image_Surface(w, h, 1/*high_res*/);
  return offscreen_api_surface[rank]->offscreen();
}

/**  Deletion of an offscreen graphics buffer.
   \param ctx     the buffer to be deleted.
   \note The \p ctx argument must have been created by fl_create_offscreen().
   */
void fl_delete_offscreen(Fl_Offscreen ctx) {
  if (!ctx) return;
  for (int i = 0; i < count_offscreens; i++) {
    if (offscreen_api_surface[i] && offscreen_api_surface[i]->offscreen() == ctx) {
      delete offscreen_api_surface[i];
      offscreen_api_surface[i] = NULL;
      return;
    }
  }
}

/**  Send all subsequent drawing commands to this offscreen buffer.
   \param ctx     the offscreen buffer.
   \note The \p ctx argument must have been created by fl_create_offscreen().
   */
void fl_begin_offscreen(Fl_Offscreen ctx) {
  for (int i = 0; i < count_offscreens; i++) {
    if (offscreen_api_surface[i] && offscreen_api_surface[i]->offscreen() == ctx) {
      Fl_Surface_Device::push_current(offscreen_api_surface[i]);
      return;
    }
  }
}

/** Quit sending drawing commands to the current offscreen buffer.
   */
void fl_end_offscreen() {
  Fl_Surface_Device::pop_current();
}

/** Adapts an offscreen buffer to a changed value of the scale factor.
 The \p ctx argument must have been created by fl_create_offscreen()
 and the calling context must not be between fl_begin_offscreen() and fl_end_offscreen().
 The graphical content of the offscreen is preserved. The current scale factor
 value is given by <tt>Fl_Graphics_Driver::default_driver().scale()</tt>.
 \version 1.4
 */
void fl_rescale_offscreen(Fl_Offscreen &ctx) {
  int i;
  for (i = 0; i < count_offscreens; i++) {
    if (offscreen_api_surface[i] && offscreen_api_surface[i]->offscreen() == ctx) {
      break;
    }
  }
  if (i >= count_offscreens) return;
  offscreen_api_surface[i]->rescale();
  ctx = offscreen_api_surface[i]->offscreen();
}

/** @} */


//
// End of "$Id: Fl_Image_Surface.cxx 12968 2018-06-23 16:47:40Z matt $".
//
