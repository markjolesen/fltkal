// output.h
//
// "$Id: Fl_Output.H 9637 2012-07-24 04:37:22Z matt $"
//
// Output header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2011 by Bill Spitzak and others.
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
   Fl_Output widget . */

#ifndef Fl_Output_H
#define Fl_Output_H

#include "input.h"
/**
  This widget displays a piece of text.
  
  When you set the value() , Fl_Output does a strcpy() to its own storage,
  which is useful for program-generated values.  The user may select
  portions of the text using the mouse and paste the contents into other
  fields or programs.

  <P align=CENTER>\image html text.png</P>
  \image latex text.png "Fl_Output" width=8cm

  There is a single subclass, Fl_Multiline_Output, which allows you to
  display multiple lines of text. Fl_Multiline_Output does not provide
  scroll bars. If a more complete text editing widget is needed, use
  Fl_Text_Display instead.

  The text may contain any characters except \\0, and will correctly
  display anything, using ^X notation for unprintable control characters
  and \\nnn notation for unprintable characters with the high bit set. It
  assumes the font can draw any characters in the ISO-Latin1 character set.
*/
class FL_EXPORT Fl_Output : public Fl_Input {
public:
  /**
    Creates a new Fl_Output widget using the given position,
    size, and label string. The default boxtype is FL_DOWN_BOX.

    Inherited destructor destroys the widget and any value associated with it.
  */

    Fl_Output(int X,int Y,int W,int H, const char *l = 0);
};

#endif 

//
// End of "$Id: Fl_Output.H 9637 2012-07-24 04:37:22Z matt $".
//