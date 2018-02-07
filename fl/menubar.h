// menubar.h
//
// "$Id: Fl_Menu_Bar.H 12575 2017-12-02 16:20:30Z manolo $"
//
// Menu bar header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2017 by Bill Spitzak and others.
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
   Fl_Menu_Bar widget . */

#ifndef Fl_Menu_Bar_H
#define Fl_Menu_Bar_H

#include "menu_.h"

/**
  This widget provides a standard menubar interface.  Usually you will
  put this widget along the top edge of your window.  The height of the
  widget should be 30 for the menu titles to draw correctly with the
  default font.

  The items on the bar and the menus they bring up are defined by a
  single Fl_Menu_Item array.
  Because a Fl_Menu_Item array defines a hierarchy, the
  top level menu defines the items in the menubar, while the submenus
  define the pull-down menus. Sub-sub menus and lower pop up to the right
  of the submenus.

  \image html  menubar.png
  \image latex  menubar.png " menubar" width=12cm

  If there is an item in the top menu that is not a title of a
  submenu, then it acts like a "button" in the menubar.  Clicking on it
  will pick it.

  When the user clicks a menu item, value() is set to that item
  and then:

    - The item's callback is done if one has been set; the
      Fl_Menu_Bar is passed as the Fl_Widget* argument,
      along with any userdata configured for the callback.

    - If the item does not have a callback, the Fl_Menu_Bar's callback
      is done instead, along with any userdata configured for the callback.
      The callback can determine which item was picked using
      value(), mvalue(), item_pathname(), etc.

  Submenus will also pop up in response to shortcuts indicated by
  putting a '&' character in the name field of the menu item. If you put a
  '&' character in a top-level "button" then the shortcut picks it.  The
  '&' character in submenus is ignored until the menu is popped up.

  Typing the shortcut() of any of the menu items will cause
  callbacks exactly the same as when you pick the item with the mouse.
*/
class FL_EXPORT Fl_Menu_Bar : public Fl_Menu_ {
  friend class Fl_Sys_Menu_Bar_Driver;
protected:
    void draw();
public:
    int handle(int);
  /**
    Creates a new Fl_Menu_Bar widget using the given position,
    size, and label string. The default boxtype is FL_UP_BOX.

    The constructor sets menu() to NULL.  See
    Fl_Menu_ for the methods to set or change the menu.

    labelsize(), labelfont(), and labelcolor()
    are used to control how the menubar items are drawn.  They are
    initialized from the Fl_Menu static variables, but you can
    change them if desired.

    label() is ignored unless you change align() to
    put it outside the menubar.

    The destructor removes the Fl_Menu_Bar widget and all of its
    menu items.
  */
  Fl_Menu_Bar(int X, int Y, int W, int H, const char *l=0);
  /** Updates the menu bar after any change to its items.
   This is useful when the menu bar can be an Fl_Sys_Menu_Bar object.
   */
  virtual void update() {}
};

#endif

//
// End of "$Id: Fl_Menu_Bar.H 12575 2017-12-02 16:20:30Z manolo $".
//
