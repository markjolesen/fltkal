// progress.h
//
// "$Id: Fl_Progress.H 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Progress bar widget definitions.
//
// Copyright 2017-2018 The fltkal authors
// Copyright 2000-2010 by Michael Sweet.
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
   Fl_Progress widget . */

#ifndef _Fl_Progress_H_
#  define _Fl_Progress_H_

//
// Include necessary headers.
//

#include "widget.h"


//
// Progress class...
//
/**
    Displays a progress bar for the user.
*/
class FL_EXPORT Fl_Progress : public Fl_Widget {
  
  float	value_,
	minimum_,
	maximum_;

  protected:

  virtual void draw();

  public:

  Fl_Progress(int x, int y, int w, int h, const char *l = 0);

  /** Sets the maximum value in the progress widget.  */
  void	maximum(float v) { maximum_ = v; redraw(); }
  /** Gets the maximum value in the progress widget.  */
  float	maximum() const { return (maximum_); }

  /** Sets the minimum value in the progress widget.  */
  void	minimum(float v) { minimum_ = v; redraw(); }
  /** Gets the minimum value in the progress widget.  */
  float	minimum() const { return (minimum_); }

  /** Sets the current value in the progress widget.  */
  void	value(float v) { value_ = v; redraw(); }
  /** Gets the current value in the progress widget.  */
  float	value() const { return (value_); }
};

#endif // !_Fl_Progress_H_

//
// End of "$Id: Fl_Progress.H 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
