// fontdir.cxx
//
// Font container for the Fast Light Tool Kit (FLTK)
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

#include "fontdir.h"

#include <stdlib.h>
#include <string.h>

#include "../../flstring.h"
#include <fl/fl_str.h>

fontdir::fontdir() : id_(0), count_(0), size_(0)
{
  return;
}

fontdir::~fontdir()
{
  size_t index;

  for (index = 0; count_ > index; index++)
    {
      struct fontdir::id *id = &id_[index];
      free(id->face_);
      free(id->path_);
    }

  free(id_);

  return;
}

void
  fontdir::add(char const *face, char const *path)
{
  if (size_ < (1 + count_))
    {
      size_ += 100;
      id_ = (struct fontdir::id *)realloc(
        id_, (size_ * sizeof(struct fontdir::id)));
    }

  struct fontdir::id *id = &id_[count_];

  memset(id, 0, sizeof(*id));
  id->face_ = fl_strdup(face);
  id->path_ = fl_strdup(path);

  count_++;

  return;
}

static bool
  enum_fonts_cb(void *user_data,
                char const *path,
                char const *key,
                char const *value,
                unsigned int const index)
{
  fontdir &dir = *reinterpret_cast<fontdir *>(user_data);
  dir.add(key, value);
  return true;
}

void
  fontdir::load(Fl_Preferences &pref)
{
  Fl_Preferences sect(pref, "fonts");
  sect.enumerate(enum_fonts_cb, this);
}
