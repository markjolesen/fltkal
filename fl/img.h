// img.h
//
// "$Id: Fl_Image.H 12443 2017-09-11 18:54:10Z AlbrechtS $"
//
// Image header file for the Fast Light Tool Kit (FLTK).
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

/** \file
   Fl_Image, Fl_RGB_Image classes. */

#ifndef Fl_Image_H
#define Fl_Image_H

#include "fl_enums.h"
#include <stdlib.h>
#include "widget.h" // for fl_uintptr_t

class Fl_Widget;
class Fl_Pixmap;
struct Fl_Menu_Item;
struct Fl_Label;
class Fl_RGB_Image;


/** \enum Fl_RGB_Scaling
 The scaling algorithm to use for RGB images.
*/
enum Fl_RGB_Scaling {
  FL_RGB_SCALING_NEAREST = 0, ///< default RGB image scaling algorithm
  FL_RGB_SCALING_BILINEAR     ///< more accurate, but slower RGB image scaling algorithm
};


/**
 \brief Base class for image caching and drawing.
 
 Fl_Image is the base class used for caching and drawing all kinds of images 
 in FLTK. This class keeps track of common image data such as the pixels, 
 colormap, width, height, and depth. Virtual methods are used to provide 
 type-specific image handling.
  
 Since the Fl_Image class does not support image
 drawing by itself, calling the draw() method results in
 a box with an X in it being drawn instead.
*/
class FL_EXPORT Fl_Image {
  friend class Fl_Graphics_Driver;
public:
  static const int ERR_NO_IMAGE    = -1;
  static const int ERR_FILE_ACCESS = -2;
  static const int ERR_FORMAT      = -3;
    
private:
  int w_, h_, d_, ld_, count_;
  const char * const *data_;
  static Fl_RGB_Scaling RGB_scaling_;

  // Forbid use of copy constructor and assign operator
  Fl_Image & operator=(const Fl_Image &);
  Fl_Image(const Fl_Image &);

protected:

  /**
   Sets the current image width in pixels.
   */
  void w(int W) {w_ = W;}
  /**
   Sets the current image height in pixels.
   */
  void h(int H) {h_ = H;}
  /**
   Sets the current image depth.
   */
  void d(int D) {d_ = D;}
  /**
   Sets the current line data size in bytes.

   Color images may contain extra data that is included after every
   line of color image data and is normally not present.

   If \p LD is zero, then line data size is assumed to be w() * d() bytes.

   If \p LD is non-zero, then it must be positive and larger than w() * d()
   to account for the extra data per line.
   */
  void ld(int LD) {ld_ = LD;}
  /** 
   Sets the current array pointer and count of pointers in the array.
   */
  void data(const char * const *p, int c) {data_ = p; count_ = c;}
  void draw_empty(int X, int Y);

  static void labeltype(const Fl_Label *lo, int lx, int ly, int lw, int lh, Fl_Align la);
  static void measure(const Fl_Label *lo, int &lw, int &lh);
  virtual int draw_scaled(int X, int Y, int W, int H);

public:

  /** 
   Returns the current image width in pixels.
   */
  int w() const {return w_;}
  /**
   Returns the current image height in pixels.
   */
  int h() const {return h_;}
  /**
   Returns the current image depth.
   The return value will be 0 for bitmaps, 1 for
   pixmaps, and 1 to 4 for color images.</P>
   */
  int d() const {return d_;}
  /**
   Returns the current line data size in bytes.
   \see ld(int)
   */
  int ld() const {return ld_;}
  /**
   The count() method returns the number of data values
   associated with the image. The value will be 0 for images with
   no associated data, 1 for bitmap and color images, and greater
   than 2 for pixmap images.
   */
  int count() const {return count_;}
  /**
   Returns a pointer to the current image data array.
   Use the count() method to find the size of the data array.
   */
  const char * const *data() const {return data_;}
  int fail();
  Fl_Image(int W, int H, int D);
  virtual ~Fl_Image();
  virtual Fl_Image *copy(int W, int H);
  /**
   The copy() method creates a copy of the specified
   image. If the width and height are provided, the image is
   resized to the specified size. The image should be deleted (or in
   the case of Fl_Shared_Image, released) when you are done
   with it.
   */
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void color_average(Fl_Color c, float i);
  /**
   The inactive() method calls
   color_average(FL_BACKGROUND_COLOR, 0.33f) to produce
   an image that appears grayed out.

   An internal copy is made of the original image before
   changes are applied, to avoid modifying the original image.
   */
  void inactive() { color_average(FL_GRAY, .33f); }
  virtual void desaturate();
  virtual void label(Fl_Widget*w);
  virtual void label(Fl_Menu_Item*m);
  /**
   Draws the image to the current drawing surface with a bounding box.
   Arguments <tt>X,Y,W,H</tt> specify
   a bounding box for the image, with the origin        
   (upper-left corner) of the image offset by the \c cx
   and \c cy arguments.
   
   In other words:  <tt>fl_push_clip(X,Y,W,H)</tt> is applied,
   the image is drawn with its upper-left corner at <tt>X-cx,Y-cy</tt> and its own width and height,
   <tt>fl_pop_clip</tt><tt>()</tt> is applied.
   */
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0); // platform dependent
  /**
   Draws the image to the current drawing surface.
   \param X, Y specify the upper-lefthand corner of the image.
   */
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);} // platform dependent
  virtual void uncache();

  // used by fl_define_FL_IMAGE_LABEL() to avoid 'friend' declaration
  static Fl_Labeltype define_FL_IMAGE_LABEL();

  // set RGB image scaling method
  static void RGB_scaling(Fl_RGB_Scaling);

  // get RGB image scaling method
  static Fl_RGB_Scaling RGB_scaling();
  /** Use this method if you have an Fl_Image object and want to know whether it is derived 
   from class Fl_RGB_Image. 
   If the method returns non-NULL, then the image in question is
   derived from Fl_RGB_Image, and the returned value is a pointer to this image.
   */
  virtual Fl_RGB_Image *as_rgb_image() {return NULL;}
};


/**
  The Fl_RGB_Image class supports caching and drawing
  of full-color images with 1 to 4 channels of color information.
  Images with an even number of channels are assumed to contain
  alpha information, which is used to blend the image with the
  contents of the screen.

  Fl_RGB_Image is defined in
  &lt;FL/Fl_Image.H&gt;, however for compatibility reasons
  &lt;FL/Fl_RGB_Image.H&gt; should be included.
*/
class FL_EXPORT Fl_RGB_Image : public Fl_Image {
  friend class Fl_Graphics_Driver;
  static size_t max_size_;
public:

  /** Points to the start of the object's data array
   */
  const uchar *array;
  /** If non-zero, the object's data array is delete[]'d when deleting the object.
   */
  int alloc_array;

private:
  // These two variables are used to cache the image and mask for the main display graphics driver
  fl_uintptr_t id_;
  fl_uintptr_t mask_;
  float cache_scale_; // graphics scaling value when id_ was computed
  
protected:
  virtual int draw_scaled(int X, int Y, int W, int H);

public:

  Fl_RGB_Image(const uchar *bits, int W, int H, int D=3, int LD=0);
  Fl_RGB_Image(const Fl_Pixmap *pxm, Fl_Color bg=FL_GRAY);
  virtual ~Fl_RGB_Image();
  virtual Fl_Image *copy(int W, int H);
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void color_average(Fl_Color c, float i);
  virtual void desaturate();
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0);
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);}
  virtual void label(Fl_Widget*w);
  virtual void label(Fl_Menu_Item*m);
  virtual void uncache();
  /** Sets the maximum allowed image size in bytes when creating an Fl_RGB_Image object.
   
   The image size in bytes of an Fl_RGB_Image object is the value of the product w() * h() * d().
   If this product exceeds size, the created object of a derived class of Fl_RGB_Image 
   won't be loaded with the image data.
   This does not apply to direct RGB image creation with 
   Fl_RGB_Image::Fl_RGB_Image(const uchar *bits, int W, int H, int D, int LD).
   The default max_size() value is essentially infinite. 
   */
  static void max_size(size_t size) { max_size_ = size;}
  /** Returns the maximum allowed image size in bytes when creating an Fl_RGB_Image object.
   
   \sa  void Fl_RGB_Image::max_size(size_t)
   */
  static size_t max_size() {return max_size_;}
  virtual Fl_RGB_Image *as_rgb_image() {return this;}
};

#endif // !Fl_Image_H

//
// End of "$Id: Fl_Image.H 12443 2017-09-11 18:54:10Z AlbrechtS $".
//
