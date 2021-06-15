// rgb32.cxx
//
// Convert RGBA image to Allegro BITMAP for the Fast Light Tool Kit (FLTK)
//
// Copyright 2017-2018 The fltkal authors
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

BITMAP *
  rgb32_to_bitmap(unsigned int const img_width,
                  unsigned int const img_height,
                  unsigned int const img_stride,
                  unsigned char const *img_bits)
{
  BITMAP *bmp = 0;
  unsigned int delta = 0;

  if (img_stride)
    {
      delta = (img_stride - img_width);
    }

  do
    {
#if defined(USE_ALLEGRO)
      bmp = create_bitmap_ex(32, img_width, img_height);
#else
      bmp = bitmap_new(img_width, img_height);
#endif

      unsigned char const *src = &img_bits[0];

      for (unsigned int row = 0; row < img_height; row++)
        {
#if defined(USE_ALLEGRO)
          uint32_t *dest = reinterpret_cast<uint32_t *>(bmp->line[row]);
#else
          uint32_t *dest = reinterpret_cast<uint32_t *>(
            &reinterpret_cast<uint8_t *>(bmp->bits.buf)[bmp->stride * row]);
#endif
          for (unsigned int index = 0; index < img_width; index++)
            {
#if defined(USE_ALLEGRO)
              uint32_t color = makecol24(*src++, *src++, *src++);
#else
              uint32_t color = ((*src++ << 16) | (*src++ << 8) | *src++);
#endif
              *dest++ = color;
              src++;
            }
          src += delta;
        }
    }
  while (0);

  return bmp;
}
