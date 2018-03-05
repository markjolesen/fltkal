// imgconv.h
//
// Convert FLTK images to Allegro BITMAP for the Fast Light Tool Kit (FLTK)
//
// Copyright 2018 The fltkal authors
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
#if !defined(__IMGCONV_H__)

#include <allegro.h>
#include <fl/drvgr.h>
#include <fl/fl.h>
#include <fl/img.h>
#include <fl/imgbit.h>

extern int fl_convert_pixmap(
    const char *const *cdata,
    uchar *out,
    Fl_Color bg);

extern BITMAP *rgb_image_to_bitmap(Fl_RGB_Image const &rgb);

extern BITMAP *rgb_data_to_bitmap(
    unsigned int const img_width,
    unsigned int const img_height,
    unsigned int const img_depth,
    unsigned int const img_stride,
    unsigned char const *img_bits);

extern BITMAP *rgb_staged_to_image(
    Fl_Draw_Image_Cb cb,
    void *data,
    unsigned int const img_width,
    unsigned int const img_height,
    unsigned int const img_depth);

extern BITMAP *rgb32_to_bitmap(
    unsigned int const img_width,
    unsigned int const img_height,
    unsigned int const img_stride,
    unsigned char const *img_bits);

extern BITMAP *rgb24_to_bitmap(
    unsigned int const img_width,
    unsigned int const img_height,
    unsigned int const img_stride,
    unsigned char const *img_bits);

extern BITMAP *rgb24cb_to_bitmap(
    Fl_Draw_Image_Cb cb,
    void *data,
    unsigned int const img_width,
    unsigned int const img_height);

extern BITMAP *rgb16_to_bitmap(
    unsigned int const img_width,
    unsigned int const img_height,
    unsigned int const img_stride,
    unsigned char const *img_bits);

extern BITMAP *rgb8_to_bitmap(
    unsigned int const img_width,
    unsigned int const img_height,
    unsigned int const img_stride,
    unsigned char const *img_bits);

extern BITMAP *xbm_to_bitmap(
    unsigned int const img_width,
    unsigned int const img_height,
    unsigned char const *img_bits);

extern BITMAP *xpm_to_bitmap(char const *const *xpm);

extern BITMAP *pxm_to_bitmap(Fl_Pixmap const &pxm);

extern BITMAP *bitmap_to_bitmap(Fl_Bitmap const &bit);

#define __IMGCONV_H__
#endif
