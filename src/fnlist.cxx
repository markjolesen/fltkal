// fnlist.cxx
//
// "$Id: filename_list.cxx 12976 2018-06-26 14:12:43Z manolo $"
//
// Filename list routines for the Fast Light Tool Kit (FLTK).
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

// Wrapper for scandir with const-correct function prototypes.

#include <fl/filename.h>
#include <fl/fl.h>
#include "drvsys.h"
#include <fl/fl_utf8.h>
#include "flstring.h"
#include <stdlib.h>


int fl_alphasort(struct dirent **a, struct dirent **b) {
  return strcmp((*a)->d_name, (*b)->d_name);
}

int fl_casealphasort(struct dirent **a, struct dirent **b) {
  return strcasecmp((*a)->d_name, (*b)->d_name);
}


/**
  Portable and const-correct wrapper for the scandir() function.

  For each file in that directory a "dirent" structure is created.
  The only portable thing about a dirent is that dirent.d_name is the
  nul-terminated file name. A pointers array to these dirent's is created
  and a pointer to the array is returned in *list.
  The number of entries is given as a return value.
  If there is an error reading the directory a number less than zero is
  returned, and errno has the reason; errno does not work under Windows.

  \b Include:
  \code
  #include <FL/filename.H>
  \endcode

  \param[in] d the name of the directory to list.  It does not matter if it has a trailing slash.
  \param[out] list table containing the resulting directory listing
  \param[in] sort sorting functor:
  - fl_alphasort: The files are sorted in ascending alphabetical order;
      upper and lowercase letters are compared according to their ASCII ordering  uppercase before lowercase.
  - fl_casealphasort: The files are sorted in ascending alphabetical order;
      upper and lowercase letters are compared equally case is not significant.
  - fl_casenumericsort: The files are sorted in ascending "alphanumeric" order, where an attempt is made
      to put unpadded numbers in consecutive order; upper and lowercase letters
      are compared equally case is not significant.
  - fl_numericsort: The files are sorted in ascending "alphanumeric" order, where an attempt is made
      to put unpadded numbers in consecutive order; upper and lowercase letters are compared
      according to their ASCII ordering - uppercase before lowercase.
  \return the number of entries if no error, a negative value otherwise.
*/
int fl_filename_list(const char *d, dirent ***list, Fl_File_Sort_F *sort) {
  return Fl::system_driver()->filename_list(d, list, sort);
}

/**
 \brief Free the list of filenames that is generated by fl_filename_list().
 
 Free everything that was allocated by a previous call to fl_filename_list().
 Use the return values as parameters for this function.
 
 \param[in,out] list table containing the resulting directory listing
 \param[in] n number of entries in the list
 */
void fl_filename_free_list(struct dirent ***list, int n)
{
  if (n<0) return;
  
  int i;
  for (i = 0; i < n; i ++) {
    if ((*list)[i])
      free((*list)[i]);
  }  
  free(*list);
  *list = 0;
}

//
// End of "$Id: filename_list.cxx 12976 2018-06-26 14:12:43Z manolo $".
//
