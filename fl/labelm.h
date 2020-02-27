// labelm.h
//
// "$Id$"
//
// Multi-label header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018, 2020 The fltkal authors
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

#ifndef Fl_Multi_Label_H
#define Fl_Multi_Label_H

class Fl_Widget;
struct Fl_Menu_Item;

/** Allows a mixed text and/or graphics label to be applied to an Fl_Menu_Item or Fl_Widget.

    Most regular FLTK widgets now support the ability to associate both images and text
    with a label but some special cases, notably the non-widget Fl_Menu_Item objects, do not.
    Fl_Multi_Label may be used to create menu items that have an icon and text, which would
    not normally be possible for an Fl_Menu_Item.
    For example, Fl_Multi_Label is used in the New->Code submenu in fluid, and others.

    \image html Fl_Multi_Label-menu-item.png "Menu items with icons using Fl_Multi_Label"
    \image latex Fl_Multi_Label-menu-item.png "Menu items with icons using Fl_Multi_Label" width=4cm

    Each Fl_Multi_Label holds two elements, labela and labelb; each may hold either a
    text label (const char*) or an image (Fl_Image*). When displayed, labela is drawn first
    and labelb is drawn immediately to its right.

    More complex labels might be constructed by setting labelb as another Fl_Multi_Label and
    thus chaining up a series of label elements.

    When assigning a label element to one of labela or labelb, they should be explicitly cast
    to (const char*) if they are not of that type already.

    Example Use: Fl_Menu_Bar
    \code
      Fl_Pixmap *image = new Fl_Pixmap(..);	// image for menu item; any Fl_Image based widget
      Fl_Menu_Bar *menu = new Fl_Menu_Bar(..);	// can be any Fl_Menu_ oriented widget (Fl_Choice, Fl_Menu_Button..)

      // Create a menu item
      int i = menu->add("File/New", ..);
      Fl_Menu_Item *item = (Fl_Menu_Item*)&(menu->menu()[i]);

      // Create a multi label, assign it an image + text
      Fl_Multi_Label *ml = new Fl_Multi_Label;

      // Left side of label is an image
      ml->typea  = FL_IMAGE_LABEL;
      ml->labela = (const char*)image;           // any Fl_Image widget: Fl_Pixmap, Fl_PNG_Image, etc..

      // Right side of label is label text
      ml->typeb  = FL_NORMAL_LABEL;
      ml->labelb = item->label();

      // Assign the multilabel to the menu item
      ml->label(item);
    \endcode

    \see Fl_Label and Fl_Labeltype and examples/howto-menu-with-images.cxx
 */
struct FL_EXPORT Fl_Multi_Label {
  /** Holds the "leftmost" of the two elements in the composite label.
      Typically this would be assigned either a text string (const char*),
      a (Fl_Image*) or a (Fl_Multi_Label*). */
  const char* labela;
  /** Holds the "rightmost" of the two elements in the composite label.
      Typically this would be assigned either a text string (const char*),
      a (Fl_Image*) or a (Fl_Multi_Label*). */
  const char* labelb;
  /** Holds the "type" of labela.
    Typically this is set to FL_NORMAL_LABEL for a text label,
    FL_IMAGE_LABEL for an image (based on Fl_image) or FL_MULTI_LABEL
    if "chaining" multiple Fl_Multi_Label elements together. */
  uchar typea;
  /** Holds the "type" of labelb.
    Typically this is set to FL_NORMAL_LABEL for a text label,
    FL_IMAGE_LABEL for an image (based on Fl_image) or FL_MULTI_LABEL
    if "chaining" multiple Fl_Multi_Label elements together. */
  uchar typeb;

  /** This method is used to associate a Fl_Multi_Label with a Fl_Widget. */
  void label(Fl_Widget*);
  /** This method is used to associate a Fl_Multi_Label with a Fl_Menu_Item. */
  void label(Fl_Menu_Item*);
};

#endif

//
// End of "$Id$".
//
