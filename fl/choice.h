// choice.h
//
// "$Id: Fl_Choice.H 10513 2015-01-10 22:05:15Z greg.ercolano $"
//
// Choice header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Choice widget . */

#ifndef Fl_Choice_H
#define Fl_Choice_H

#include "menu_.h"

/**
  \class Fl_Choice
  \brief A button that is used to pop up a menu.

  This is a button that, when pushed, pops up a menu (or hierarchy of menus)
  defined by an array of Fl_Menu_Item objects.
  Motif calls this an OptionButton.

  The only difference between this and a Fl_Menu_Button is that the name of
  the most recent chosen menu item is displayed inside the box, while the
  label is displayed outside the box. However, since the use of this is most
  often to control a single variable rather than do individual callbacks,
  some of the Fl_Menu_Button methods are redescribed here in those terms.

  When the user clicks a menu item, value() is set to that item
  and then:

      - The item's callback is done if one has been set; the
        Fl_Choice is passed as the Fl_Widget* argument, 
        along with any userdata configured for the callback.

      - If the item does not have a callback, the Fl_Choice widget's
        callback is done instead, along with any userdata configured
        for it.  The callback can determine which item was picked using
        value(), mvalue(), item_pathname(), etc.

  All three mouse buttons pop up the menu. The Forms behavior of the first
  two buttons to increment/decrement the choice is not implemented.  This
  could be added with a subclass, however.

  The menu will also pop up in response to shortcuts indicated by putting
  a '\&' character in the label().  See Fl_Button::shortcut(int s) for a
  description of this.

  Typing the shortcut() of any of the items will do exactly the same as when
  you pick the item with the mouse.  The '\&' character in item names are
  only looked at when the menu is popped up, however.

  \image html choice.png
  \image latex choice.png  "Fl_Choice" width=4cm
  \todo Refactor the doxygen comments for Fl_Choice changed() documentation.

  \li <tt>int Fl_Widget::changed() const</tt>
      This value is true the user picks a different value. <em>It is turned
      off by value() and just before doing a callback (the callback can turn
      it back on if desired).</em>
  \li <tt>void Fl_Widget::set_changed()</tt>
      This method sets the changed() flag.
  \li <tt>void Fl_Widget::clear_changed()</tt>
      This method clears the changed() flag.
  \li <tt>Fl_Boxtype Fl_Choice::down_box() const</tt>
      Gets the current down box, which is used when the menu is popped up.
      The default down box type is \c FL_DOWN_BOX.
  \li <tt>void Fl_Choice::down_box(Fl_Boxtype b)</tt>
      Sets the current down box type to \p b.
 */
class FL_EXPORT Fl_Choice : public Fl_Menu_ {
protected:
  void draw();
public:
  int handle(int);

  Fl_Choice(int X, int Y, int W, int H, const char *L = 0);

  /**
    Gets the index of the last item chosen by the user.
    The index is zero initially.
   */
  int value() const {return Fl_Menu_::value();}

  int value(int v);

  int value(const Fl_Menu_Item* v);
};

#endif

//
// End of "$Id: Fl_Choice.H 10513 2015-01-10 22:05:15Z greg.ercolano $".
//
