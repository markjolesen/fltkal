// fontft.h
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
#if !defined(__FONTFT_H__)

#include <stdlib.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_CACHE_H

#include "fontdir.h"

#if defined(USE_ALLEGRO)
#   include <allegro.h>
#elif defined(USE_OWD32)
#   include "bitmap.h"
#else
#   error "unknown build target"
#endif

class fontft
{

  public:

    fontft();

    virtual ~fontft();

    char const* get_face(Fl_Font const font) const;

    char const* get_path(Fl_Font const font) const;

    unsigned int get_font_count() const;

    unsigned int get_font_sizes(Fl_Font const font, int*& sizep) const;

    FT_Library get_library() const;

    FT_Size get_size(Fl_Font const font, int const height) const;

    int ascent(Fl_Font const font, int const height) const;

    int descent(Fl_Font const font, int const height) const;

    int height(Fl_Font const font, int const height) const;

    int width(
      char const* text,
      unsigned int const len,
      Fl_Font const font,
      int const height) const;

    void draw(
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
      int const alcolor) const;

  private:

    FT_Library lib_;
    FTC_Manager manager_;
    FTC_CMapCache cmap_cache_;
    FTC_ImageCache image_cache_;
    fontdir dir_;

    fontft(fontft const&);

    fontft& operator=(fontft const&);

    void draw(
#if defined(USE_ALLEGRO)
      BITMAP* surface,
#else
      struct image* surface,
#endif
      FT_Bitmap* bitmap,
      int const x,
      int const y,
      int const alcolor) const;

};

inline char const*
fontft::get_face(Fl_Font const font) const
{
  return dir_.get_face(font);
}

inline char const*
fontft::get_path(Fl_Font const font) const
{
  return dir_.get_path(font);
}

inline unsigned int
fontft::get_font_count() const
{
  return dir_.get_count();
}

inline FT_Library
fontft::get_library() const
{
  return lib_;
}

inline int
fontft::ascent(Fl_Font const font, int const height) const
{
  int ascent = 8;
  FT_Size size = get_size(font, height);

  if (size)
  {
    ascent = ((abs(size->metrics.ascender) + 63) >> 6);
  }

  return ascent;
}

inline int
fontft::descent(Fl_Font const font, int const height) const
{
  int descent = 0;
  FT_Size size = get_size(font, height);

  if (size)
  {
    descent = ((abs(size->metrics.descender) + 63) >> 6);
  }

  return descent;
}

inline int
fontft::height(Fl_Font const font, int const height) const
{
  int ascent2 = ascent(font, height);
  int descent2 = descent(font, height);
  return (ascent2 + descent2);
}

#define __FONTFT_H__
#endif
