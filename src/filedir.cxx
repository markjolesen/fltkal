// filedir.cxx
//
// "$Id: fl_file_dir.cxx 10550 2015-02-02 17:55:22Z AlbrechtS $"
//
// File chooser widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2015 by Bill Spitzak and others.
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

#include "flstring.h"
#include <fl/filename.h>
#include <fl/filech.h>
#include <fl/fl_ask.h>


static Fl_File_Chooser	*fc = (Fl_File_Chooser *)0;
static void		(*current_callback)(const char*) = 0;
static const char	*current_label = fl_ok;


// Do a file chooser callback...
static void callback(Fl_File_Chooser *, void*) {
  if (current_callback && fc->value())
    (*current_callback)(fc->value());
}

// Pop up a file chooser dialog window and wait until it is closed...
static void popup(Fl_File_Chooser *fc) {
  fc->show();

  // deactivate Fl::grab(), because it is incompatible with modal windows
  Fl_Window* g = Fl::grab();
  if (g) Fl::grab(0);

  while (fc->shown())
    Fl::wait();

  if (g) // regrab the previous popup menu, if there was one
    Fl::grab(g);
}


/** \addtogroup  group_comdlg 
    @{ */

/** 
    Set the file chooser callback
    \note \#include <FL/Fl_File_Chooser.H>
    \relates Fl_File_Chooser
*/
void fl_file_chooser_callback(void (*cb)(const char*)) {
  current_callback = cb;
}


/** 
    Set the "OK" button label
    \note \#include <FL/Fl_File_Chooser.H>
    \relates Fl_File_Chooser
*/
void fl_file_chooser_ok_label(const char *l) {
  if (l) current_label = l;
  else current_label = fl_ok;
}

/** 
    Shows a file chooser dialog and gets a filename. 
    \note \#include <FL/Fl_File_Chooser.H>
    \image html Fl_File_Chooser.jpg 
    \image latex  Fl_File_Chooser.jpg "Fl_File_Chooser" width=12cm
    \param[in] message text in title bar
    \param[in] pat filename pattern filter
    \param[in] fname initial/default filename selection
    \param[in] relative 0 for absolute path name, relative path name otherwise
    \return the user selected filename, in absolute or relative format 
            or NULL if user cancels
    \relates Fl_File_Chooser
*/
char *					// O - Filename or NULL
fl_file_chooser(const char *message,	// I - Message in titlebar
                const char *pat,	// I - Filename pattern
		const char *fname,	// I - Initial filename selection
		int        relative) {	// I - 0 for absolute path
  static char	retname[FL_PATH_MAX];		// Returned filename

  if (!fc) {
    if (!fname || !*fname) fname = ".";

    fc = new Fl_File_Chooser(fname, pat, Fl_File_Chooser::CREATE, message);
    fc->callback(callback, 0);
  } else {
    fc->type(Fl_File_Chooser::CREATE);
    // see, if we use the same pattern between calls
    char same_pattern = 0;
    const char *fcf = fc->filter();
    if ( fcf && pat && strcmp(fcf, pat)==0)
      same_pattern = 1;
    else if ( (fcf==0L || *fcf==0) && (pat==0L || *pat==0) )
      same_pattern = 1;
    // now set the pattern to the new pattern (even if they are the same)
    fc->filter(pat);
    fc->label(message);

    if (!fname) { // null pointer reuses same filename if pattern didn't change
      if (!same_pattern && fc->value()) {
	// if pattern is different, remove name but leave old directory:
	strlcpy(retname, fc->value(), sizeof(retname));

	char *p = strrchr(retname, '/');

        if (p) {
	  // If the filename is "/foo", then the directory will be "/", not
	  // ""...
	  if (p == retname)
	    retname[1] = '\0';
	  else
	    *p = '\0';
	}
	// Set the directory...
	fc->value(retname);
      } else {
        // re-use the previously selected name
      }
    } else if (!*fname) { // empty filename reuses directory with empty name
      const char *fcv = fc->value();
      if (fcv) 
        strlcpy(retname, fc->value(), sizeof(retname));
      else 
        *retname = 0;
      const char *n = fl_filename_name(retname);
      if (n) *((char*)n) = 0;
      fc->value("");
      fc->directory(retname);
    } else {
       fc->value(fname);
    }
  }

  fc->ok_label(current_label);
  popup(fc);
  if (fc->value() && relative) {
    fl_filename_relative(retname, sizeof(retname), fc->value());

    return retname;
  } else if (fc->value()) return (char *)fc->value();
  else return 0;
}

/** Shows a file chooser dialog and gets a directory.
    \note \#include <FL/Fl_File_Chooser.H>
    \param[in] message title bar text
    \param[in] fname initial/default directory name
    \param[in] relative 0 for absolute path return, relative otherwise
    \return the directory path string chosen by the user or NULL if user cancels
    \relates Fl_File_Chooser
*/
char *					// O - Directory or NULL
fl_dir_chooser(const char *message,	// I - Message for titlebar
               const char *fname,	// I - Initial directory name
	       int        relative)	// I - 0 for absolute
{
  static char	retname[FL_PATH_MAX];		// Returned directory name

  if (!fc) {
    if (!fname || !*fname) fname = ".";

    fc = new Fl_File_Chooser(fname, "*", Fl_File_Chooser::CREATE |
                                         Fl_File_Chooser::DIRECTORY, message);
    fc->callback(callback, 0);
  } else {
    fc->type(Fl_File_Chooser::CREATE | Fl_File_Chooser::DIRECTORY);
    fc->filter("*");
    if (fname && *fname) fc->value(fname);
    fc->label(message);
  }

  popup(fc);

  if (fc->value() && relative) {
    fl_filename_relative(retname, sizeof(retname), fc->value());

    return retname;
  } else if (fc->value()) return (char *)fc->value();
  else return 0;
}
/** @} */


//
// End of "$Id: fl_file_dir.cxx 10550 2015-02-02 17:55:22Z AlbrechtS $".
//
