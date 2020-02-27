// fl_types.h
//
// Simple "C"-style types for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018, 2020 The fltkal authors
// Copyright 1998-2020 by Bill Spitzak and others.
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

/** \file
 *  This file contains simple "C"-style type definitions.
 */

#ifndef FL_TYPES_H
#define FL_TYPES_H

/** \name	Miscellaneous */
/*@{*/	/* group: Miscellaneous */

/** unsigned char */
typedef unsigned char uchar;
/** unsigned long */
typedef unsigned long ulong;

/** Flexible length UTF-8 Unicode text.
 *
 *  \todo FIXME: temporary (?) typedef to mark UTF-8 and Unicode conversions
 */
typedef char *Fl_String;

/** Flexible length UTF-8 Unicode read-only string.
 *  \sa Fl_String
 */
typedef const char *Fl_CString;

/** 16-bit Unicode character + 8-bit indicator for keyboard flags.

  \note This \b should be 24-bit Unicode character + 8-bit indicator for
    keyboard flags. The upper 8 bits are currently unused but reserved.

  Due to compatibility issues this type and all FLTK \b shortcuts can only
  be used with 16-bit Unicode characters (<tt>U+0000 .. U+FFFF</tt>) and
  not with the full range of unicode characters (<tt>U+0000 .. U+10FFFF</tt>).

  This is caused by the bit flags \c FL_SHIFT, \c FL_CTRL, \c FL_ALT, and
  \c FL_META being all in the range <tt>0x010000 .. 0x400000</tt>.

  \todo Discuss and decide whether we can "shift" these special keyboard
    flags to the upper byte to enable full 21-bit Unicode characters
    (<tt>U+0000 .. U+10FFFF</tt>) plus the keyboard indicator bits as this
    was originally intended. This would be possible if we could rely on \b all
    programs being coded with symbolic names and not hard coded bit values.

  \internal Can we do the move for 1.4 or, if not, for any later version
    that is allowed to break the ABI?
*/
typedef unsigned int Fl_Shortcut;

/** 24-bit Unicode character - upper 8 bits are unused */
typedef unsigned int Fl_Char;

/*@}*/	/* group: Miscellaneous */

#endif

