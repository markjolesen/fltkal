// fnisdir.cxx
//
// "$Id: filename_isdir.cxx 11609 2016-04-15 07:33:26Z manolo $"
//
// Directory detection routines for the Fast Light Tool Kit (FLTK).
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

// Used by fl_file_chooser

#include "flstring.h"
#include <fl/drvsys.h>
#include <fl/filename.h>
#include <fl/fl.h>

/*
 * filename_isdir_quick() is a private function that checks for a
 * trailing slash and assumes that the passed name is a directory if
 * it finds one.  This function is used by Fl_File_Browser and
 * Fl_File_Chooser to avoid extra stat() calls, but is not supported
 * outside of FLTK...
 */
int Fl_System_Driver::filename_isdir_quick(const char* n) {
  // Do a quick optimization for filenames with a trailing slash...
  if (*n && n[strlen(n) - 1] == '/') return 1;
  return filename_isdir(n);
}

/**
   Determines if a file exists and is a directory from its filename.
   \code
   #include <FL/filename.H>
   [..]
   fl_filename_isdir("/etc");		// returns non-zero
   fl_filename_isdir("/etc/hosts");	// returns 0
   \endcode
   \param[in] n the filename to parse
   \return non zero if file exists and is a directory, zero otherwise
*/
int fl_filename_isdir(const char* n) {
  return Fl::system_driver()->filename_isdir(n);
}

int Fl_System_Driver::filename_isdir(const char* n) {
  struct stat	s;
  char		fn[FL_PATH_MAX];
  int		length;
  length = (int) strlen(n);
  // Matt: Just in case, we strip the slash for other operating
  // systems as well, avoid bugs by sloppy implementations
  // of "stat".
  if (length > 1 && n[length - 1] == '/') {
    length --;
    memcpy(fn, n, length);
    fn[length] = '\0';
    n = fn;
  }
  return !stat(n, &s) && (s.st_mode & S_IFDIR);
}

//
// End of "$Id: filename_isdir.cxx 11609 2016-04-15 07:33:26Z manolo $".
//
