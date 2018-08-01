// visual.cxx
//
// "$Id: Fl_visual.cxx 12975 2018-06-26 14:04:09Z manolo $"
//
// Visual support for the Fast Light Tool Kit (FLTK).
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

// Set the default visual according to passed switches:

#include <fl/fl.h>
#include "drvscr.h"

/** \fn  Fl::visual(int flags)
    Selects a visual so that your graphics are drawn correctly.  This is
    only allowed before you call show() on any windows.  This does nothing
    if the default visual satisfies the capabilities, or if no visual
    satisfies the capabilities, or on systems that don't have such
    brain-dead notions.
    
    <P>Only the following combinations do anything useful:
    
    <UL>
    <LI>Fl::visual(FL_RGB)
    <BR>Full/true color (if there are several depths FLTK chooses  the
    largest).  Do this if you use fl_draw_image
    for much better (non-dithered)  output.
    <BR>&nbsp; </LI>
    <LI>Fl::visual(FL_RGB8)
    <BR>Full color with at least 24 bits of color. FL_RGB will
    always  pick this if available, but if not it will happily return a
    less-than-24 bit deep visual.  This call fails if 24 bits are not
    available.
    <BR>&nbsp; </LI>
    <LI>Fl::visual(FL_DOUBLE|FL_INDEX)
    <BR>Hardware double buffering.  Call this if you are going to use 
    Fl_Double_Window.
    <BR>&nbsp; </LI>
    <LI>Fl::visual(FL_DOUBLE|FL_RGB)</LI>
    <LI>Fl::visual(FL_DOUBLE|FL_RGB8)
    <BR>Hardware double buffering and full color.
    </UL>
    
    <P>This returns true if the system has the capabilities by default or
    FLTK suceeded in turing them on.  Your program will still work even if
    this returns false (it just won't look as good).
*/
int Fl::visual(int flags)
{
  return screen_driver()->visual(flags);
}


//
// End of "$Id: Fl_visual.cxx 12975 2018-06-26 14:04:09Z manolo $".
//
