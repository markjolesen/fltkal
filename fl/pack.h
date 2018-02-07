// pack.h
//
// "$Id: Fl_Pack.H 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Pack header file for the Fast Light Tool Kit (FLTK).
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

/* \file
   Fl_Pack widget . */

#ifndef Fl_Pack_H
#define Fl_Pack_H

#include <fl/group.h>

/**
  This widget was designed to add the functionality of compressing and
  aligning widgets.
  <P>If type() is Fl_Pack::HORIZONTAL all the children are
  resized to the height of the Fl_Pack, and are moved next to
  each other horizontally. If type() is not Fl_Pack::HORIZONTAL
  then the children are resized to the width and are stacked below each
  other.  Then the Fl_Pack resizes itself to surround the child
  widgets.
  <P>This widget is needed for the Fl_Tabs.
  In addition you may want to put the Fl_Pack inside an 
  Fl_Scroll.

  <P>The resizable for Fl_Pack is set to NULL by default.</p>
  <P>See also: Fl_Group::resizable()
*/
class FL_EXPORT Fl_Pack : public Fl_Group {
  int spacing_;

public:
  enum { // values for type(int)
    VERTICAL = 0,
    HORIZONTAL = 1
  };

protected:
  void draw();

public:
  Fl_Pack(int x,int y,int w ,int h,const char *l = 0);
  /**
    Gets the number of extra pixels of blank space that are added
    between the children.
  */
  int spacing() const {return spacing_;}
  /**
    Sets the number of extra pixels of blank space that are added
    between the children.
  */
  void spacing(int i) {spacing_ = i;}
  /** Same as Fl_Group::type() */
  uchar horizontal() const {return type();}
};

#endif

//
// End of "$Id: Fl_Pack.H 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
