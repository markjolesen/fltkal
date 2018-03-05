// imgconv.cxx
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
#include "imgconv.h"
#include <stdlib.h>
#include <string.h>

BITMAP *rgb_staged_to_image(
    Fl_Draw_Image_Cb cb,
    void *data,
    unsigned int const width,
    unsigned int const height,
    unsigned int const depth)
{
    BITMAP *bmp = 0;

    do
    {

        if (0 >= static_cast<int>(width))
        {
            break;
        }

        if (0 >= static_cast<int>(height))
        {
            break;
        }

        switch (depth)
        {
        case 4:
            // TODO:
            break;
        case 3:
            bmp = rgb24cb_to_bitmap(cb, data, width, height);
            break;
        case 2:
            // TODO:
            break;
        case 1:
            // TODO:
            break;
        default:
            break;
        };

    }
    while (0);

    return bmp;
}

BITMAP *rgb_data_to_bitmap(
    unsigned int const width,
    unsigned int const height,
    unsigned int const depth,
    unsigned int const stride,
    unsigned char const *bits)
{
    BITMAP *bmp = 0;

    do
    {

        if (0 >= static_cast<int>(width))
        {
            break;
        }

        if (0 >= static_cast<int>(height))
        {
            break;
        }

        switch (depth)
        {
        case 4:
            bmp = rgb32_to_bitmap(width, height, stride, bits);
            break;
        case 3:
            bmp = rgb24_to_bitmap(width, height, stride, bits);
            break;
        case 2:
            bmp = rgb16_to_bitmap(width, height, stride, bits);
            break;
        case 1:
            bmp = rgb8_to_bitmap(width, height, stride, bits);
            break;
        default:
            break;
        };

    }
    while (0);

    return bmp;
}

BITMAP *rgb_image_to_bitmap(Fl_RGB_Image const &rgb)
{

    unsigned int width = static_cast<unsigned int>(rgb.w());
    unsigned int height = static_cast<unsigned int>(rgb.h());
    unsigned int depth = static_cast<unsigned int>(rgb.d());
    unsigned int stride = static_cast<unsigned int>(rgb.ld());
    unsigned char const *raw = rgb.array;

    BITMAP *bmp = rgb_data_to_bitmap(width, height, depth, stride, raw);

    return bmp;
}

BITMAP *pxm_to_bitmap(Fl_Pixmap const &pxm)
{
    BITMAP *bmp = 0;
    unsigned char *bits = 0;

    do
    {

        unsigned int width = static_cast<unsigned int>(pxm.w());

        if (0 >= static_cast<int>(width))
        {
            break;
        }

        unsigned int height = static_cast<unsigned int>(pxm.h());

        if (0 >= static_cast<int>(height))
        {
            break;
        }

        static unsigned int const depth = 4;
        unsigned int bytes = (width * height * depth);

        bits = reinterpret_cast<unsigned char *>(malloc(bytes));
        char const *const *raw = pxm.data();
        int rc = fl_convert_pixmap(raw, bits, 0xFF00FF00);

        if (0 == rc)
        {
            break;
        }

        static unsigned int const stride = 0;
        bmp = rgb32_to_bitmap(width, height, stride, bits);

    }
    while (0);

    free(bits);

    return bmp;
}

BITMAP *bitmap_to_bitmap(Fl_Bitmap const &bit)
{
    BITMAP *bmp = 0;

    do
    {

        unsigned int width = static_cast<unsigned int>(bit.w());

        if (0 >= static_cast<int>(width))
        {
            break;
        }

        unsigned int height = static_cast<unsigned int>(bit.h());

        if (0 >= static_cast<int>(height))
        {
            break;
        }

        unsigned int depth = static_cast<unsigned int>(bit.d());

        if (0 != depth)
        {
            break;
        }

        unsigned char const *raw = bit.array;
        bmp = xbm_to_bitmap(width, height, raw);

    }
    while (0);

    return bmp;
}

BITMAP *xpm_to_bitmap(char const *const *xpm)
{
    Fl_Pixmap pxm(xpm);
    BITMAP *bmp = pxm_to_bitmap(pxm);
    return bmp;
}
