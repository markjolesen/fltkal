// inpfile.h
//
// "$Id: Fl_File_Input.H 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// File_Input header file for the Fast Light Tool Kit (FLTK).
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
// Original version Copyright 1998 by Curtis Edwards.
//

/* \file
   Fl_File_Input widget . */

#ifndef Fl_File_Input_H
#  define Fl_File_Input_H

#  include <fl/input.h>

/**
  \class Fl_File_Input
  \brief This widget displays a pathname in a text input field.

  A navigation bar located above the input field allows the user to
  navigate upward in the directory tree.
  You may want to handle FL_WHEN_CHANGED events for tracking text changes
  and also FL_WHEN_RELEASE for button release when changing to parent dir.
  FL_WHEN_RELEASE callback won't be called if the directory clicked
  is the same as the current one.

  <P align=CENTER> \image html Fl_File_Input.png </P> 
  \image latex Fl_File_Input.png "Fl_File_Input"  width=6cm

  \note As all Fl_Input derived objects, Fl_File_Input may call its callback
  when losing focus (see FL_UNFOCUS) to update its state like its cursor shape.
  One resulting side effect is that you should call clear_changed() early in your callback
  to avoid reentrant calls if you plan to show another window or dialog box in the callback.
*/
class FL_EXPORT Fl_File_Input : public Fl_Input {
  
  Fl_Color	errorcolor_;
  char		ok_entry_;
  uchar		down_box_;
  short		buttons_[200];
  short		pressed_;

  void		draw_buttons();
  int		handle_button(int event);
  void		update_buttons();

public:

  Fl_File_Input(int X, int Y, int W, int H, const char *L=0);

  virtual int handle(int event);

protected:
  virtual void draw();

public:
  /** Gets the box type used for the navigation bar. */
  Fl_Boxtype	down_box() const { return (Fl_Boxtype)down_box_; }
  /** Sets the box type to use for the navigation bar.  */
  void		down_box(Fl_Boxtype b) { down_box_ = b; }

  /**
    Gets the current error color.
    \todo Better docs for Fl_File_Input::errorcolor() - is it even used?
  */
  Fl_Color	errorcolor() const { return errorcolor_; }
  /** Sets the current error color to \p c */
  void		errorcolor(Fl_Color c) { errorcolor_ = c; }

  int	value(const char *str);
  int	value(const char *str, int len);

  /**
    Returns the current value, which is a pointer to an internal buffer
    and is valid only until the next event is handled.
  */
  const char	*value() { return Fl_Input_::value(); }
};

#endif // !Fl_File_Input_H


//
// End of "$Id: Fl_File_Input.H 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
