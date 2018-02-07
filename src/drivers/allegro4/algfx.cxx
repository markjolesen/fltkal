// algfx.cxx
//
// Additional Allegro graphics code for the Fast Light Tool Kit (FLTK)
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
#include "algfx.h"

void line_horiz_xor(BITMAP *bmp, int const x, int const y, unsigned int const len)
{

    do
    {

        if (0 > x + len)
        {
            break;
        }

        if (bmp->w <= x)
        {
            break;
        }

        if (0 > y)
        {
            break;
        }

        if (bmp->h <= y)
        {
            break;
        }

        unsigned int left = len;
        unsigned int col = 0;

        if (0 <= x)
        {
            col = x;
        }
        else
        {
            left = len + x;
        }

        do
        {

            if (0 == left)
            {
                break;
            }

            if (bmp->w <= col)
            {
                break;
            }

            int pixel = getpixel(bmp, col, y);
            pixel ^= -1;
            putpixel(bmp, col, y, pixel);

            col++;
            left--;

        }
        while (1);

    }
    while (0);

    return;
}

void line_vert_xor(BITMAP *bmp, int const x, int const y, unsigned int const len)
{

    do
    {

        if (0 > x)
        {
            break;
        }

        if (bmp->w <= x)
        {
            break;
        }

        if (0 > y + len)
        {
            break;
        }

        if (bmp->h <= y)
        {
            break;
        }

        unsigned int left = len;
        unsigned int row = 0;

        if (0 <= y)
        {
            row = y;
        }
        else
        {
            left = len + y;
        }

        do
        {

            if (0 == left)
            {
                break;
            }

            if (bmp->h <= row)
            {
                break;
            }

            int pixel = getpixel(bmp, x, row);
            pixel ^= -1;
            putpixel(bmp, x, row, pixel);

            row++;
            left--;

        }
        while (1);

    }
    while (0);

    return;
}

void rect_xor(BITMAP *bmp, int x, int y, unsigned int width, unsigned int height)
{

    line_horiz_xor(bmp, x, y, width);
    line_horiz_xor(bmp, x, y + height - 1, width);
    line_vert_xor(bmp, x, y + 1, height - 1);
    line_vert_xor(bmp, x + width - 1, y + 1, height - 1);

    return;
}
