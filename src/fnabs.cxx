// fnabs.cxx
//
// "$Id: filename_absolute.cxx 12558 2017-11-12 18:00:45Z AlbrechtS $"
//
// Filename expansion routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2017 by Bill Spitzak and others.
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

/* expand a file name by prepending current directory, deleting . and
   .. (not really correct for symbolic links) between the prepended
   current directory.  Use $PWD if it exists.
   Returns true if any changes were made.
*/

#include <fl/filename.h>
#include <fl/fl.h>
#include <fl/drvsys.h>
#include <stdlib.h>
#include "flstring.h"

inline int isdirsep(char c) {return c == '/';}

/** Makes a filename absolute from a relative filename.
    \code
    #include <FL/filename.H>
    [..]
    fl_chdir("/var/tmp");
    fl_filename_absolute(out, sizeof(out), "foo.txt");         // out="/var/tmp/foo.txt"
    fl_filename_absolute(out, sizeof(out), "./foo.txt");       // out="/var/tmp/foo.txt"
    fl_filename_absolute(out, sizeof(out), "../log/messages"); // out="/var/log/messages"
    \endcode
    \param[out] to resulting absolute filename
    \param[in]  tolen size of the absolute filename buffer 
    \param[in]  from relative filename
    \return 0 if no change, non zero otherwise
 */
int fl_filename_absolute(char *to, int tolen, const char *from) {
  return Fl::system_driver()->filename_absolute(to, tolen, from);
}


int Fl_System_Driver::filename_absolute(char *to, int tolen, const char *from) {
  if (isdirsep(*from) || *from == '|') {
    strlcpy(to, from, tolen);
    return 0;
  }
  char *a;
  char *temp = new char[tolen];
  const char *start = from;
  a = fl_getcwd(temp, tolen);
  if (!a) {
    strlcpy(to, from, tolen);
    delete[] temp;
    return 0;
  }
  a = temp+strlen(temp);
  if (isdirsep(*(a-1))) a--;
  /* remove intermediate . and .. names: */
  while (*start == '.') {
    if (start[1]=='.' && isdirsep(start[2])) {
      char *b;
      for (b = a-1; b >= temp && !isdirsep(*b); b--) {/*empty*/}
      if (b < temp) break;
      a = b;
      start += 3;
    } else if (isdirsep(start[1])) {
      start += 2;
    } else if (!start[1]) {
      start ++; // Skip lone "."
      break;
    } else
      break;
  }
  *a++ = '/';
  strlcpy(a,start,tolen - (a - temp));
  strlcpy(to, temp, tolen);
  delete[] temp;
  return 1;
}

/** Makes a filename relative to the current working directory.
    \code
    #include <FL/filename.H>
    [..]
    fl_chdir("/var/tmp/somedir");       // set cwd to /var/tmp/somedir
    [..]
    char out[FL_PATH_MAX];
    fl_filename_relative(out, sizeof(out), "/var/tmp/somedir/foo.txt");  // out="foo.txt",    return=1
    fl_filename_relative(out, sizeof(out), "/var/tmp/foo.txt");          // out="../foo.txt", return=1
    fl_filename_relative(out, sizeof(out), "foo.txt");                   // out="foo.txt",    return=0 (no change)
    fl_filename_relative(out, sizeof(out), "./foo.txt");                 // out="./foo.txt",  return=0 (no change)
    fl_filename_relative(out, sizeof(out), "../foo.txt");                // out="../foo.txt", return=0 (no change)
    \endcode
    \param[out] to resulting relative filename
    \param[in]  tolen size of the relative filename buffer 
    \param[in]  from absolute filename
    \return 0 if no change, non zero otherwise
 */
int					// O - 0 if no change, 1 if changed
fl_filename_relative(char       *to,	// O - Relative filename
                     int        tolen,	// I - Size of "to" buffer
                     const char *from)  // I - Absolute filename
{
  char cwd_buf[FL_PATH_MAX];	// Current directory
  // get the current directory and return if we can't
  if (!fl_getcwd(cwd_buf, sizeof(cwd_buf))) {
    strlcpy(to, from, tolen);
    return 0;
  }
  return fl_filename_relative(to, tolen, from, cwd_buf);
}


/** Makes a filename relative to any other directory.
 \param[out] to resulting relative filename
 \param[in]  tolen size of the relative filename buffer 
 \param[in]  from absolute filename
 \param[in]  base relative to this absolute path
 \return 0 if no change, non zero otherwise
 */
int					// O - 0 if no change, 1 if changed
fl_filename_relative(char       *to,	// O - Relative filename
                     int        tolen,	// I - Size of "to" buffer
                     const char *from,  // I - Absolute filename
                     const char *base) { // I - Find path relative to this path
  return Fl::system_driver()->filename_relative(to, tolen, from, base);
}

int                                             // O - 0 if no change, 1 if changed
Fl_System_Driver::filename_relative(char *to,	// O - Relative filename
                     int        tolen,          // I - Size of "to" buffer
                     const char *from,          // I - Absolute filename
                     const char *base)          // I - Find path relative to this path
{
  char          *newslash;		// Directory separator
  const char	*slash;			// Directory separator
  char          *cwd = 0L, *cwd_buf = 0L;
  if (base) cwd = cwd_buf = strdup(base);
  
  // return if "from" is not an absolute path
  if (from[0] == '\0' || !isdirsep(*from)) {
    strlcpy(to, from, tolen);
    if (cwd_buf) free(cwd_buf);
    return 0;
  }
  
  // return if "cwd" is not an absolute path
  if (!cwd || cwd[0] == '\0' || !isdirsep(*cwd)) {
    strlcpy(to, from, tolen);
    if (cwd_buf) free(cwd_buf);
    return 0;
  }
  
  // test for the exact same string and return "." if so
  if (!strcmp(from, cwd)) {
    strlcpy(to, ".", tolen);
    free(cwd_buf);
    return (1);
  }
  
  // compare both path names until we find a difference
  for (slash = from, newslash = cwd;
       *slash != '\0' && *newslash != '\0';
       slash ++, newslash ++)
    if (isdirsep(*slash) && isdirsep(*newslash)) continue;
    else if (*slash != *newslash) break;
  
  // skip over trailing slashes
  if ( *newslash == '\0' && *slash != '\0' && !isdirsep(*slash)
      &&(newslash==cwd || !isdirsep(newslash[-1])) )
    newslash--;
  
  // now go back to the first character of the first differing paths segment
  while (!isdirsep(*slash) && slash > from) slash --;
  if (isdirsep(*slash)) slash ++;
  
  // do the same for the current dir
  if (isdirsep(*newslash)) newslash --;
  if (*newslash != '\0')
    while (!isdirsep(*newslash) && newslash > cwd) newslash --;
  
  // prepare the destination buffer
  to[0]         = '\0';
  to[tolen - 1] = '\0';
  
  // now add a "previous dir" sequence for every following slash in the cwd
  while (*newslash != '\0') {
    if (isdirsep(*newslash)) strlcat(to, "../", tolen);
    
    newslash ++;
  }
  
  // finally add the differing path from "from"
  strlcat(to, slash, tolen);
  
  free(cwd_buf);
  return 1;
}

//
// End of "$Id: filename_absolute.cxx 12558 2017-11-12 18:00:45Z AlbrechtS $".
//
