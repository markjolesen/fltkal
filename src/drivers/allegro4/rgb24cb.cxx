// rgb24cb.cxx
//
// Convert RGB image to Allegro BITMAP for the Fast Light Tool Kit (FLTK)
//
// Copyright 2017-2019 The fltkal authors
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
#include <fl/drvgr.h>
#if defined(USE_ALLEGRO)
#  include <allegro.h>

BITMAP *
  rgb24cb_to_bitmap(Fl_Draw_Image_Cb cb,
                    void *data,
                    unsigned int const img_width,
                    unsigned int const img_height)
{
  BITMAP *bmp = 0;

  do
    {
      bmp = create_bitmap_ex(32, img_width, img_height);

      if (0 == bmp)
        {
          break;
        }

      unsigned char *line
        = reinterpret_cast<unsigned char *>(malloc(3 * img_width));

      for (unsigned int row = 0; row < img_height; row++)
        {
          (*cb)(data, 0, row, img_width, line);
          uint32_t *dest = reinterpret_cast<uint32_t *>(bmp->line[row]);
          unsigned char *src = &line[0];
          for (unsigned int index = 0; index < img_width; index++)
            {
              uint32_t color = makecol24(*src++, *src++, *src++);
              *dest++ = color;
            }
        }

      free(line);
    }
  while (0);

  return bmp;
}
#else

#  include "bitmap.h"

struct bitmap *
  rgb24cb_to_bitmap(Fl_Draw_Image_Cb cb,
                    void *data,
                    unsigned int const img_width,
                    unsigned int const img_height)
{
  struct bitmap *bmp = bitmap_new(img_width, img_height);

  unsigned char *line
    = reinterpret_cast<unsigned char *>(malloc(3 * img_width));

  for (unsigned int row = 0; row < img_height; row++)
    {
      (*cb)(data, 0, row, img_width, line);
      unsigned char *buf = reinterpret_cast<unsigned char *>(bmp->bits.buf);
      unsigned char *dest = &buf[4 * row * img_width];
      unsigned char *src = &line[0];
      for (unsigned int index = 0; index < img_width; index++)
        {
          *dest++ = 0;
          *dest++ = *src++;
          *dest++ = *src++;
          *dest++ = *src++;
        }
    }

  free(line);

  return bmp;
}

#endif
