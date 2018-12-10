// fontdir.h
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
#if !defined(__FONTDIR_H__)

#include <fl/fl_enums.h>
#include <fl/pref.h>

class fontdir
{

public:

    fontdir();

    virtual ~fontdir();

    void clear();

    void add(char const *face, char const *path);

    void load(Fl_Preferences &pref);

    unsigned int get_count() const;

    char const *get_face(Fl_Font const font) const;

    char const *get_path(Fl_Font const font) const;

    void set_invalid(Fl_Font const font);

protected:

    struct fontdir_element
    {
        char face[32];
        char path[128];
        bool valid;
    };

    struct fontdir_element *fonts;
    unsigned int size;

private:

    fontdir(fontdir const &);

    fontdir &operator=(fontdir const &);
};

inline unsigned int fontdir::get_count() const
{
    return size;
}

inline char const *fontdir::get_face(Fl_Font const font) const
{
    char const *face = 0;

    if (size && size > font)
    {
        if (fonts[font].valid)
        {
            face = fonts[font].face;
        }
    }

    return face;
}

inline char const *fontdir::get_path(Fl_Font const font) const
{
    char const *path = 0;

    if (size && size > font)
    {
        if (fonts[font].valid)
        {
            path = fonts[font].path;
        }
    }

    return path;
}

inline void fontdir::set_invalid(Fl_Font const font)
{

    if (size && size > font)
    {
        fonts[font].valid = false;
    }

    return;
}

#define __FONTDIR_H__
#endif
