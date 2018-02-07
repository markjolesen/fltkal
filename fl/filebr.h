// filebr.h
//
// "$Id: Fl_File_Browser.H 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// FileBrowser definitions.
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1999-2010 by Michael Sweet.
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

/* \file
   Fl_File_Browser widget . */

//
// Include necessary header files...
//

#ifndef _Fl_File_Browser_H_
#  define _Fl_File_Browser_H_

#  include "browser.h"
#  include "iconfile.h"
#  include "filename.h"


//
// Fl_File_Browser class...
//

/** The Fl_File_Browser widget displays a list of filenames, optionally with file-specific icons. */
class FL_EXPORT Fl_File_Browser : public Fl_Browser {
  
  int		filetype_;
  const char	*directory_;
  uchar		iconsize_;
  const char	*pattern_;

  int		full_height() const;
  int		item_height(void *) const;
  int		item_width(void *) const;
  void		item_draw(void *, int, int, int, int) const;
  int		incr_height() const { return (item_height(0)); }

public:
  enum { FILES, DIRECTORIES };

  /**
    The constructor creates the Fl_File_Browser widget at the specified position and size.
    The destructor destroys the widget and frees all memory that has been allocated.
  */
  Fl_File_Browser(int, int, int, int, const char * = 0);

  /**    Sets or gets the size of the icons. The default size is 20 pixels.  */
  uchar		iconsize() const { return (iconsize_); };
  /**    Sets or gets the size of the icons. The default size is 20 pixels.  */
  void		iconsize(uchar s) { iconsize_ = s; redraw(); };

  /**
    Sets or gets the filename filter. The pattern matching uses
    the fl_filename_match()
    function in FLTK.
  */
  void	filter(const char *pattern);
  /**
    Sets or gets the filename filter. The pattern matching uses
    the fl_filename_match()
    function in FLTK.
  */
  const char	*filter() const { return (pattern_); };

  /**
    Loads the specified directory into the browser. If icons have been
    loaded then the correct icon is associated with each file in the list.
    
    <P>The sort argument specifies a sort function to be used with
    fl_filename_list().
  */
  int		load(const char *directory, Fl_File_Sort_F *sort = fl_numericsort);

  Fl_Fontsize  textsize() const { return Fl_Browser::textsize(); };
  void		textsize(Fl_Fontsize s) { Fl_Browser::textsize(s); iconsize_ = (uchar)(3 * s / 2); };

  /**
    Sets or gets the file browser type, FILES or
    DIRECTORIES. When set to FILES, both
    files and directories are shown. Otherwise only directories are
    shown.
  */
  int		filetype() const { return (filetype_); };
  /**
    Sets or gets the file browser type, FILES or
    DIRECTORIES. When set to FILES, both
    files and directories are shown. Otherwise only directories are
    shown.
  */
  void		filetype(int t) { filetype_ = t; };
};

#endif // !_Fl_File_Browser_H_

//
// End of "$Id: Fl_File_Browser.H 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
