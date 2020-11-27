// fontft.h
//
// FreeType font for the Fast Light Tool Kit (FlTK)
//
// Copyright 2018-2019 The Fltkal authors
//
//                              FlTK License
//                            December 11, 2001
//
// The FlTK library and included programs are provided under the terms
// of the GNU Library General Public License (LGPL) with the following
// exceptions:
//
//     1. Modifications to the FlTK configure script, config
//        header file, and makefiles by themselves to support
//        a specific platform do not constitute a modified or
//        derivative work.
//
//       The authors do request that such modifications be
//       contributed to the FlTK project - send all contributions
//       through the "Software Trouble Report" on the following page:
//
//            http://www.Fltk.org/str.php
//
//     2. Widgets that are subclassed from FlTK widgets do not
//        constitute a derivative work.
//
//     3. Static linking of applications and widgets to the
//        FlTK library does not constitute a derivative work
//        and does not require the author to provide source
//        code for the application or widget, use the shared
//        FlTK libraries, or link their applications or
//        widgets against a user-supplied version of FlTK.
//
//        If you link the application or widget to a modified
//        version of FlTK, then the changes to FlTK must be
//        provided under the terms of the LGPL in sections
//        1, 2, and 4.
//
//     4. You do not have to provide a copy of the FlTK license
//        with programs that are linked to the FlTK library, nor
//        do you have to identify the FlTK license in your
//        program or documentation as required by section 6
//        of the LGPL.
//
//        However, programs must still identify their use of FlTK.
//        The following example statement can be included in user
//        documentation to satisfy this requirement:
//
//            [program/widget] is based in part on the work of
//            the FlTK project (http://www.Fltk.org).
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
//     License along with FlTK.  If not, see <http://www.gnu.org/licenses/>.
//
#if !defined(__FONTFT_H__)

#  include <stdlib.h>

#  include "fontdir.h"

#  if defined(USE_ALLEGRO)
#    include <allegro.h>
#  elif defined(USE_OWD32)
#    include "bitmap.h"
#  else
#    error "unknown build target"
#  endif

class fontft
{
public:
  fontft();

  virtual ~fontft();

  char const *
    get_face(Fl_Font const index) const;

  char const *
    get_path(Fl_Font const index) const;

  unsigned int
    get_font_count() const;

  unsigned int
    get_font_sizes(Fl_Font const index, int *&sizep) const;

  FT_Library
    get_library() const;

  FTC_Manager
    get_manager() const;

  FT_Size
    get_size(Fl_Font const index, Fl_Fontsize const size) const;

  int
    ascent(Fl_Font const index, Fl_Fontsize const size) const;

  int
    descent(Fl_Font const index, Fl_Fontsize const size) const;

  int
    height(Fl_Font const index, Fl_Fontsize const size) const;

  int
    width(char const *text,
          unsigned int const len,
          Fl_Font const index,
          Fl_Fontsize const size) const;

  void
    draw(
#  if defined(USE_ALLEGRO)
      BITMAP *surface,
#  else
      struct image *surface,
#  endif
      char const *text,
      unsigned int const len,
      int const x,
      int const y,
      Fl_Font const index,
      Fl_Fontsize const size,
      int const alcolor) const;

private:
  FT_Library lib_;
  FTC_Manager manager_;
  fontdir dir_;

  fontft(fontft const &);

  fontft &
    operator=(fontft const &);

  void
    draw(
#  if defined(USE_ALLEGRO)
      BITMAP *surface,
#  else
      struct image *surface,
#  endif
      FT_Bitmap *bitmap,
      int const x,
      int const y,
      int const alcolor) const;
};

inline char const *
  fontft::get_face(Fl_Font const index) const
{
  char const *face = 0;
  ;
  struct fontdir::id const *id = dir_.get_id(index);

  if (id)
    {
      face = id->face_;
    }

  return face;
}

inline char const *
  fontft::get_path(Fl_Font const index) const
{
  char const *path = 0;
  ;
  struct fontdir::id const *id = dir_.get_id(index);

  if (id)
    {
      path = id->path_;
    }

  return path;
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

inline FTC_Manager
  fontft::get_manager() const
{
  return manager_;
}

inline int
  fontft::ascent(Fl_Font const index, Fl_Fontsize const size) const
{
  int value = 8;
  FT_Size ftsize = get_size(index, size);

  if (ftsize)
    {
      value = ((abs(ftsize->metrics.ascender) + 63) >> 6);
    }

  return value;
}

inline int
  fontft::descent(Fl_Font const index, Fl_Fontsize const size) const
{
  int value = 0;
  FT_Size ftsize = get_size(index, size);

  if (ftsize)
    {
      value = ((abs(ftsize->metrics.descender) + 63) >> 6);
    }

  return value;
}

inline int
  fontft::height(Fl_Font const index, Fl_Fontsize const size) const
{
  int lascent = ascent(index, size);
  int ldescent = descent(index, size);
  return (lascent + ldescent);
}

#  define __FONTFT_H__
#endif
