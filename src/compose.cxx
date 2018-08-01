// compose.cxx
//
// "$Id: Fl_compose.cxx 12975 2018-06-26 14:04:09Z manolo $"
//
// Character compose processing for the Fast Light Tool Kit (FLTK).
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

/**
\file Fl_compose.cxx
Utility functions to support text input.
*/

#include <fl/fl.h>
#include "drvscr.h"

#ifndef FL_DOXYGEN
int Fl::compose_state = 0;
#endif


/** Any text editing widget should call this for each FL_KEYBOARD event.
 Use of this function is very simple.
 
 <p>If <i>true</i> is returned, then it has modified the
 Fl::event_text() and Fl::event_length() to a set of <i>bytes</i> to
 insert (it may be of zero length!).  It will also set the "del"
 parameter to the number of <i>bytes</i> to the left of the cursor to
 delete, this is used to delete the results of the previous call to
 Fl::compose().
 
 <p>If <i>false</i> is returned, the keys should be treated as function
 keys, and del is set to zero. You could insert the text anyways, if
 you don't know what else to do.
 
 <p>On the Mac OS platform, text input can involve marked text, that is, 
 temporary text replaced by other text during the input process. This occurs,
 e.g., when using dead keys or when entering CJK characters.
 Text editing widgets should preferentially signal
 marked text, usually underlining it. Widgets can use
 <tt>int Fl::compose_state</tt> <i>after</i> having called Fl::compose(int&)
 to obtain the length in bytes of marked text that always finishes at the
 current insertion point. Widgets should also call
 <tt>void Fl::reset_marked_text()</tt> when processing FL_UNFOCUS
 events. Optionally, widgets can also call
 <tt>void Fl::insertion_point_location(int x, int y, int height)</tt> to indicate the window 
 coordinates of the bottom of the current insertion point and the line height. 
 This way, auxiliary windows that help choosing among alternative characters 
 appear just below the insertion point. If widgets don't do that, 
 auxiliary windows appear at the widget's bottom. The
 Fl_Input and Fl_Text_Editor widgets underline marked text.
 If none of this is done by a user-defined text editing widget,
 text input will work, but will not signal to the user what text is marked.
 Finally, text editing widgets should call <tt>set_flag(MAC_USE_ACCENTS_MENU);</tt>
 in their constructor if they want to use the feature introduced with Mac OS 10.7 "Lion"
 where pressing and holding certain keys on the keyboard opens an accented-character menu window.
 
 <p>Though the current implementation returns immediately, future
 versions may take quite awhile, as they may pop up a window or do
 other user-interface things to allow characters to be selected.
 */
int Fl::compose(int& del) {
  return Fl::screen_driver()->compose(del);
}

/**
 If the user moves the cursor, be sure to call Fl::compose_reset().
 The next call to Fl::compose() will start out in an initial state. In
 particular it will not set "del" to non-zero. This call is very fast
 so it is ok to call it many times and in many places.
 */
void Fl::compose_reset()
{
  Fl::screen_driver()->compose_reset();
}

//
// End of "$Id: Fl_compose.cxx 12975 2018-06-26 14:04:09Z manolo $"
//

