// fnexpand.cxx
//
// "$Id: filename_expand.cxx 12976 2018-06-26 14:12:43Z manolo $"
//
// Filename expansion routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2010 by Bill Spitzak and others.
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
//

#include "drvsys.h"
#include <fl/fl.h>

/** Expands a filename containing shell variables and tilde (~).
    Currently handles these variants:
    \code
    "~username"               // if 'username' does not exist, result will be unchanged
    "~/file"
    "$VARNAME"                // does NOT handle ${VARNAME}
    \endcode

    \b Examples:
    \code
    #include <FL/filename.H>
    [..]
    putenv("TMPDIR=/var/tmp");
    fl_filename_expand(out, sizeof(out), "~fred/.cshrc");     // out="/usr/fred/.cshrc"
    fl_filename_expand(out, sizeof(out), "~/.cshrc");         // out="/usr/<yourname>/.cshrc"
    fl_filename_expand(out, sizeof(out), "$TMPDIR/foo.txt");  // out="/var/tmp/foo.txt"
    \endcode
    \param[out] to resulting expanded filename
    \param[in]  tolen size of the expanded filename buffer 
    \param[in]  from filename containing shell variables
    \return 0 if no change, non zero otherwise
 */
int fl_filename_expand(char *to,int tolen, const char *from) {
  return Fl::system_driver()->filename_expand(to, tolen, from);
}

//
// End of "$Id: filename_expand.cxx 12976 2018-06-26 14:12:43Z manolo $".
//
