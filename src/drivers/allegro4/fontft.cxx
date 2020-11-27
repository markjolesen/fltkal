// fontft.cxx
//
// FreeType font for the Fast Light Tool Kit (FLTK)
//
// Copyright 2018-2019 The fltkal authors
//
//                              FLTK License
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
#include "fontft.h"

#include <sys/stat.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "../../flstring.h"
#include "utf8proc.h"
#include "util.h"
#include <fl/filename.h>
#include <fl/fl_utf8.h>

FT_Error
  face_requester(FTC_FaceID face_id,
                 FT_Library library,
                 FT_Pointer req_data,
                 FT_Face *aface)
{
  FT_Error error = ENOENT;
  fontft *fft = reinterpret_cast<fontft *>(req_data);
  struct fontdir::id *id = reinterpret_cast<struct fontdir::id *>(face_id);
  char *prgpath = 0;
  char *fontpath = 0;

  do
    {
      error = FT_New_Face(fft->get_library(), id->path_, 0, aface);

      if (0 == error)
        {
          break;
        }

      fontpath = reinterpret_cast<char *>(malloc(FL_PATH_MAX));

      char const *name = filename_extract(id->path_);

      char const *envpath = fl_getenv("FLFONT");

      if (envpath)
        {
          snprintf(fontpath, FL_PATH_MAX, "%s/%s", envpath, name);

          error = FT_New_Face(fft->get_library(), fontpath, 0, aface);

          if (0 == error)
            {
              break;
            }
        }
      *aface = 0;
    }
  while (0);

  if (*aface)
    {
      if (0 == id->cmap_cache_)
        {
          FTC_CMapCache_New(fft->get_manager(), &id->cmap_cache_);
        }

      if (0 == id->image_cache_)
        {
          FTC_ImageCache_New(fft->get_manager(), &id->image_cache_);
        }
    }

  free(prgpath);
  free(fontpath);

  return error;
}

fontft::fontft() : lib_(0), manager_(0), dir_()
{
  FT_Error error;

  do
    {
      error = FT_Init_FreeType(&lib_);

      if (error)
        {
          break;
        }

      error = FTC_Manager_New(lib_, 0, 0, 0, face_requester, this, &manager_);

      Fl_Preferences *prefs = fltkcfg();

      if (0 == prefs)
        {
          break;
        }

      dir_.load(*prefs);

      delete prefs;
    }
  while (0);

  if (error || (0 == dir_.get_count()))
    {
      abort();
    }

  return;
}

fontft::~fontft()
{
  FTC_Manager_Done(manager_);
  FT_Done_FreeType(lib_);

  return;
}

FT_Size
  fontft::get_size(Fl_Font const index, Fl_Fontsize const size) const
{
  FT_Size ftsize = 0;

  do
    {
      struct fontdir::id *id = dir_.get_id(index);

      if (0 == id)
        {
          break;
        }

      FTC_ScalerRec scaler;

      memset(&scaler, 0, sizeof(scaler));

      scaler.face_id = id;
      scaler.height = (size << 6);
      scaler.x_res = 72;
      scaler.y_res = 72;

      FT_Error error = FTC_Manager_LookupSize(manager_, &scaler, &ftsize);
    }
  while (0);

  return ftsize;
}

#if defined(USE_ALLEGRO)

void
  fontft::draw(BITMAP *surface,
               FT_Bitmap *bitmap,
               int const x,
               int const y,
               int const alcolor) const
{
  unsigned char *src_line = bitmap->buffer;

  for (unsigned int row = 0; row < bitmap->rows; row++)
    {
      unsigned char *src = src_line;

      for (unsigned int col = 0; col < bitmap->width; col++)
        {
          if (*src)
            {
              _putpixel32(surface, x + col, y + row, alcolor);
            }

          *src++;
        }

      src_line += bitmap->pitch;
    }

  return;
}

#else /* USE_OWD32 */

inline void
  fontft::draw(struct image *surface,
               FT_Bitmap *bitmap,
               int const x,
               int const y,
               int const alcolor) const
{
  struct bitmap bmp;

  bmp.stride = bitmap->pitch;
  bmp.width = bitmap->width;
  bmp.height = bitmap->rows;
  bmp.bits.ref = bitmap->buffer;

  bitmap_8bpp_blt(surface, x, y, &bmp, alcolor);

  return;
}

#endif

void
  fontft::draw(
#if defined(USE_ALLEGRO)
    BITMAP *surface,
#else
    struct image *surface,
#endif
    char const *text,
    unsigned int const len,
    int const x,
    int const y,
    Fl_Font const index,
    Fl_Fontsize const size,
    int const alcolor) const
{
  do
    {
      struct fontdir::id *id = dir_.get_id(index);

      if (0 == id)
        {
          break;
        }

      FTC_ScalerRec scaler;

      memset(&scaler, 0, sizeof(scaler));

      scaler.face_id = id;
      scaler.height = (size << 6);
      scaler.x_res = 72;
      scaler.y_res = 72;

      FT_Face face = 0;

      FT_Error error = FTC_Manager_LookupFace(manager_, id, &face);

      if (error)
        {
          break;
        }

      FT_UInt advance_def = (face->glyph->advance.x >> 16);
      FT_Int cmap_index = FT_Get_Charmap_Index(face->charmap);
      FT_UInt glyph_index = 0;
      FT_UInt glyph_index_prev = 0;
      // bool use_kerning = FT_HAS_KERNING(face);

      utf8proc_uint8_t const *ptr
        = reinterpret_cast<utf8proc_uint8_t const *>(text);
      utf8proc_ssize_t left = len;

      int pen_x = x;

      do
        {
          if (0 >= left)
            {
              break;
            }

          utf8proc_int32_t codepoint;
          utf8proc_ssize_t ate = utf8proc_iterate(ptr, left, &codepoint);

          if (0 < ate)
            {
              ptr += ate;
              left -= ate;
            }
          else
            {
              ptr++;
              left--;
              codepoint = 0xc2bf;
            }

          FT_UInt glyph_index
            = FTC_CMapCache_Lookup(id->cmap_cache_, id, cmap_index, codepoint);

          if (0 == glyph_index)
            {
              continue;
            }

#if 0
          if (glyph_index_prev)
            {
              if (use_kerning)
                {
                  FT_Vector delta;

                  FT_Get_Kerning(face,
                                 glyph_index_prev,
                                 glyph_index,
                                 FT_KERNING_DEFAULT,
                                 &delta);

                  pen_x += (delta.x >> 6);
                }
            }
#endif

          FT_Glyph glyph = 0;

          error = FTC_ImageCache_LookupScaler(id->image_cache_,
                                              &scaler,
                                              FT_LOAD_DEFAULT | FT_LOAD_RENDER
                                                | FT_LOAD_FORCE_AUTOHINT,
                                              glyph_index,
                                              &glyph,
                                              0);

          FT_BitmapGlyph slot = reinterpret_cast<FT_BitmapGlyph>(glyph);

          draw(surface,
               &slot->bitmap,
               (pen_x + slot->left),
               (y - slot->top),
               alcolor);

          //        pen_x += (glyph->advance.x >> 16);
          pen_x += size;
          glyph_index_prev = glyph_index;
        }
      while (1);
    }
  while (0);

  return;
}

int
  fontft::width(char const *text,
                unsigned int const len,
                Fl_Font const index,
                Fl_Fontsize const size) const
{
  // int pen_x= 0;
  int pen_x = (len * size);

#if 0
  do
    {
      struct fontdir::id *id = dir_.get_id(index);

      if (0 == id)
        {
          break;
        }

      FTC_ScalerRec scaler;

      memset(&scaler, 0, sizeof(scaler));

      scaler.face_id = id;
      scaler.height = (size << 6);
      scaler.x_res = 72;
      scaler.y_res = 72;

      FT_Face face = 0;

      FT_Error error = FTC_Manager_LookupFace(manager_, id, &face);

      if (error)
        {
          break;
        }

      FT_UInt advance_def = (face->glyph->advance.x >> 16);
      FT_Int cmap_index = FT_Get_Charmap_Index(face->charmap);
      FT_UInt glyph_index = 0;
      FT_UInt glyph_index_prev = 0;
      // bool use_kerning = FT_HAS_KERNING(face);
      utf8proc_uint8_t const *ptr
        = reinterpret_cast<utf8proc_uint8_t const *>(text);
      utf8proc_ssize_t left = len;

      do
        {
          if (0 >= left)
            {
              break;
            }

          utf8proc_int32_t codepoint;
          utf8proc_ssize_t ate = utf8proc_iterate(ptr, left, &codepoint);

          if (0 < ate)
            {
              ptr += ate;
              left -= ate;
            }

          else
            {
              ptr++;
              left--;
              codepoint = 0xc2bf;
            }

          glyph_index
            = FTC_CMapCache_Lookup(id->cmap_cache_, id, cmap_index, codepoint);

#  if 0
          if (glyph_index)
            {
              if (glyph_index_prev)
                {
                  if (use_kerning)
                    {
                      FT_Vector delta;

                      FT_Get_Kerning(face,
                                     glyph_index_prev,
                                     glyph_index,
                                     FT_KERNING_DEFAULT,
                                     &delta);

                      pen_x += (delta.x >> 6);
                    }
                }
#  endif

              FT_Glyph glyph = 0;

              FTC_ImageCache_LookupScaler(id->image_cache_,
                                          &scaler,
                                          FT_LOAD_DEFAULT | FT_LOAD_RENDER
                                            | FT_LOAD_FORCE_AUTOHINT,
                                          glyph_index,
                                          &glyph,
                                          0);

              pen_x += (glyph->advance.x >> 16);
              glyph_index_prev = glyph_index;
            }
        }
      while (1);
    }
  while (0);
#endif

  return pen_x;
}

unsigned int
  fontft::get_font_sizes(Fl_Font const index, int *&sizep) const
{
  static int sizes[]
    = { 6, 8, 9, 10, 11, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72 };

  sizep = sizes;

  return (sizeof(sizes) / sizeof(sizes[0]));
}
