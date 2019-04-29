// fontft.cxx
//
// FreeType font for the Fast Light Tool Kit (FLTK)
//
// Copyright 2018-2019 The fltkal authors
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
#include "fontft.h"
#include "util.h"
#include "utf8proc.h"
#include "../../flstring.h"
#include <fl/fl_utf8.h>
#include <fl/filename.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#if (7 > FREETYPE_MINOR)
#define FT_LOAD_BITMAP_METRICS_ONLY FT_LOAD_DEFAULT
#endif


FT_Error
face_requester(
  FTC_FaceID  face_id,
  FT_Library  library,
  FT_Pointer  req_data,
  FT_Face*    aface)
{
  Fl_Font font = static_cast<Fl_Font>(reinterpret_cast<ptrdiff_t>((face_id)));
  font--;
  fontft* cache = reinterpret_cast<fontft*>(req_data);
  const char* path = cache->get_path(font);
  FT_Error error = ENOENT;
  char const* fname = 0;
  char const* envpath = 0;
  char* prgpath = 0;
  char* fontpath = 0;

  do
  {

    if (0 == path)
    {
      break;
    }

    error = FT_New_Face(cache->get_library(), path, 0, aface);

    if (0 == error)
    {
      break;
    }

    fname = filename_extract(path);
    fontpath = reinterpret_cast<char*>(malloc(FL_PATH_MAX));
    envpath = fl_getenv("FLFONT");

    if (envpath)
    {
      snprintf(fontpath, FL_PATH_MAX, "%s/%s", envpath, fname);
      error = FT_New_Face(cache->get_library(), fontpath, 0, aface);

      if (0 == error)
      {
        break;
      }
    }

    prgpath = program_path();
    snprintf(fontpath, FL_PATH_MAX, "%s/%s", prgpath, fname);
    error = FT_New_Face(cache->get_library(), fontpath, 0, aface);

  }
  while (0);

  free(prgpath);
  free(fontpath);

  return error;
}

fontft::fontft() :
  lib_(0),
  manager_(0),
  cmap_cache_(0),
  image_cache_(0),
  dir_()
{
  FT_Error error;

  do
  {

    error = FT_Init_FreeType(&lib_);

    if (error)
    {
      break;
    }

    dir_.clear();

    Fl_Preferences* prefs = fltkcfg();

    if (0 == prefs)
    {
      break;
    }

    dir_.load(*prefs);
    delete prefs;

    error = FTC_Manager_New(lib_, 3, 0, 0, face_requester, this, &manager_);

    if (error)
    {
      break;
    }

    error = FTC_CMapCache_New(manager_, &cmap_cache_);

    if (error)
    {
      break;
    }

    error = FTC_ImageCache_New(manager_, &image_cache_);

  }
  while (0);

  if (error)
  {
    FTC_Manager_Done(manager_);
    FT_Done_FreeType(lib_);
    manager_ = 0;
    lib_ = 0;
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
fontft::get_size(Fl_Font const font, int const height) const
{
  FT_Size  size = 0;

  do
  {

    if (0 == manager_)
    {
      break;
    }

    FTC_ScalerRec scaler;
    memset(&scaler, 0, sizeof(scaler));
    scaler.face_id = reinterpret_cast<FTC_FaceID>(font + 1);
    scaler.height = height;
    scaler.pixel = 1;
    FTC_Manager_LookupSize(manager_, &scaler, &size);

  }
  while (0);

  return size;
}

#if defined(USE_ALLEGRO)

void
fontft::draw(
  BITMAP* surface,
  FT_Bitmap* bitmap,
  int const x,
  int const y,
  int const alcolor) const
{

  unsigned char* src_line = bitmap->buffer;

  for (unsigned int row = 0; row < bitmap->rows; row++)
  {
    unsigned char* src = src_line;

    for (unsigned int col = 0; col < bitmap->width; col++)
    {
      if (*src)
      {
        // putpixel(surface, x + col, y + row, alcolor);
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
fontft::draw(
  struct image* surface,
  FT_Bitmap* bitmap,
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
  BITMAP* surface,
#else
  struct image* surface,
#endif
  char const* text,
  unsigned int const len,
  int const x,
  int const y,
  Fl_Font const font,
  int const height,
  int const alcolor) const
{
  bool fallback = false;
  FT_Error error;
  FT_Face face = 0;
  FTC_ScalerRec scaler;
  FT_Int pen_x = x;
  FT_Int pen_y = y;

  memset(&scaler, 0, sizeof(scaler));
  scaler.face_id = reinterpret_cast<FTC_FaceID>(font + 1);
  scaler.height = height;
  scaler.pixel = 1;

  do
  {

    if (0 == manager_)
    {
      fallback = true;
      break;
    }

    error = FTC_Manager_LookupFace(manager_, scaler.face_id, &face);

    if (error)
    {
      fallback = true;
      break;
    }

    FT_Int charmap_index = FT_Get_Charmap_Index(face->charmap);

    utf8proc_uint8_t const* ptr =
      reinterpret_cast<utf8proc_uint8_t const*>(text);
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
        continue;
      }

      FT_UInt glyph_index = FTC_CMapCache_Lookup(
                              cmap_cache_,
                              scaler.face_id,
                              charmap_index,
                              codepoint);

      if (0 == glyph_index)
      {
        continue;
      }

      FT_Glyph glyph = 0;

      error = FTC_ImageCache_LookupScaler(
                image_cache_,
                &scaler,
                FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL,
                glyph_index,
                &glyph,
                0);

      FT_BitmapGlyph slot = reinterpret_cast<FT_BitmapGlyph>(glyph);

      if (0 == error)
      {
        draw(
          surface,
          &slot->bitmap,
          pen_x + slot->left,
          pen_y - slot->top,
          alcolor);
      }

      pen_x += (glyph->advance.x >> 16);
    }
    while (1);

  }
  while (0);

#if defined(USE_ALLEGRO)

  if (fallback)
  {
    char* buf = reinterpret_cast<char*>(::malloc((len + 1)));

    if (buf)
    {
      ::memcpy(buf, text, len);
      buf[len] = 0;
      ::textout_ex(surface, ::font, buf, x, (y - 8), alcolor, -1);
      ::free(buf);
    }
  }

#endif

  return;
}

int
fontft::width(
  char const* text,
  unsigned int const len,
  Fl_Font const font,
  int const height) const
{
  FT_Error error;
  FT_Face face = 0;
  FTC_ScalerRec scaler;
  FT_Int pen_x = 0;

  memset(&scaler, 0, sizeof(scaler));
  scaler.face_id = reinterpret_cast<FTC_FaceID>(font + 1);
  scaler.height = height;
  scaler.pixel = 1;

  do
  {

    if (0 == manager_)
    {
      pen_x = (8 * len);
      break;
    }

    error = FTC_Manager_LookupFace(manager_, scaler.face_id, &face);

    if (error)
    {
      pen_x = (8 * len);
      break;
    }

    FT_Int charmap_index = FT_Get_Charmap_Index(face->charmap);

    utf8proc_uint8_t const* ptr =
      reinterpret_cast<utf8proc_uint8_t const*>(text);
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
        continue;
      }

      FT_UInt glyph_index = FTC_CMapCache_Lookup(
                              cmap_cache_,
                              scaler.face_id,
                              charmap_index,
                              codepoint);

      if (0 == glyph_index)
      {
        continue;
      }

      FT_Glyph glyph = 0;

      error = FTC_ImageCache_LookupScaler(
                image_cache_,
                &scaler,
                FT_LOAD_BITMAP_METRICS_ONLY,
                glyph_index,
                &glyph,
                0);

      pen_x += (glyph->advance.x >> 16);

    }
    while (1);

  }
  while (0);

  return pen_x;
}

unsigned int
fontft::get_font_sizes(Fl_Font const font, int*& sizep) const
{
  unsigned int count = 0;
  static int sizes[128];

  do
  {

    count = 1;
    sizes[0] = 8;

    if (0 == manager_)
    {
      break;
    }

    FT_Face face;

    FT_Error error = FTC_Manager_LookupFace(
                       manager_,
                       reinterpret_cast<FTC_FaceID>(font + 1),
                       &face);

    if (error)
    {
      break;
    }

    if (0 == face->num_fixed_sizes)
    {
      for (count = 0; count < 127; count++)
      {
        sizes[count] = (1 + count);
      };

      break;
    }

    for (count = 0; count < face->num_fixed_sizes; count++)
    {
      sizes[count] = face->available_sizes[count].height;
    }

  }
  while (0);

  sizep = sizes;
  return count;
}
