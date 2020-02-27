// menu_.h
//
// "$Id$"
//
// Menu base class header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018, 2020 The fltkal authors
// Copyright 1998-2019 by Bill Spitzak and others.
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
   Fl_Menu_ widget . */

#ifndef Fl_Menu__H
#define Fl_Menu__H

#ifndef Fl_Widget_H
#include "widget.h"
#endif
#include "menuitem.h"

/**
  Base class of all widgets that have a menu in FLTK.

  Currently FLTK provides you with Fl_Menu_Button, Fl_Menu_Bar, and Fl_Choice.

  The class contains a pointer to an array of structures of type Fl_Menu_Item.
  The array may either be supplied directly by the user program, or it may
  be "private": a dynamically allocated array managed by the Fl_Menu_.

  When the user clicks a menu item, value() is set to that item
  and then:

    - If the Fl_Menu_Item has a callback set, that callback
      is invoked with any userdata configured for it.
      (The Fl_Menu_ widget's callback is NOT invoked.)

    - For any Fl_Menu_Items that \b don't have a callback set,
      the Fl_Menu_ widget's callback is invoked with any userdata
      configured for it. The callback can determine which item
      was picked using value(), mvalue(), item_pathname(), etc.

  The line spacing between menu items can be controlled with the global setting
  Fl::menu_linespacing().
 \see Fl_Widget::shortcut_label(int)
*/
class FL_EXPORT Fl_Menu_ : public Fl_Widget {

  Fl_Menu_Item *menu_;
  const Fl_Menu_Item *value_;

protected:

  uchar alloc;			// flag indicates if menu_ is a dynamic copy (=1) or not (=0)
  uchar down_box_;
  Fl_Font textfont_;
  Fl_Fontsize textsize_;
  Fl_Color textcolor_;

  int item_pathname_(char *name, int namelen, const Fl_Menu_Item *finditem,
                     const Fl_Menu_Item *menu=0) const;
public:
  Fl_Menu_(int,int,int,int,const char * =0);
  ~Fl_Menu_();

  int item_pathname(char *name, int namelen, const Fl_Menu_Item *finditem=0) const;
  const Fl_Menu_Item* picked(const Fl_Menu_Item*);
  const Fl_Menu_Item* find_item(const char *name);
  const Fl_Menu_Item* find_item(Fl_Callback*);
  int find_index(const char *name) const;
  int find_index(const Fl_Menu_Item *item) const;
  int find_index(Fl_Callback *cb) const;

  /**
    Returns the menu item with the entered shortcut (key value).

    This searches the complete menu() for a shortcut that matches the
    entered key value.  It must be called for a FL_KEYBOARD or FL_SHORTCUT
    event.

    If a match is found, the menu's callback will be called.

    \return matched Fl_Menu_Item or NULL.
  */
  const Fl_Menu_Item* test_shortcut() {return picked(menu()->test_shortcut());}
  void global();

  /**
    Returns a pointer to the array of Fl_Menu_Items.  This will either be
    the value passed to menu(value) or the private copy or an internal
    (temporary) location (see note below).

    \note <b>Implementation details - may be changed in the future.</b>
      All modifications of the menu array are done by copying the entire
      menu array to an internal storage for optimization of memory
      allocations, for instance when using add() or insert(). While this
      is done, menu() returns the pointer to this internal location. The
      entire menu will be copied back to private storage when needed,
      i.e. when \b another Fl_Menu_ is modified. You can force this
      reallocation after you're done with all menu modifications by calling
      Fl_Menu_::menu_end() to make sure menu() returns a permanent pointer
      to private storage (until the menu is modified again).
      Note also that some menu methods (e.g. Fl_Menu_Button::popup()) call
      menu_end() internally to ensure a consistent menu array while the
      menu is open.

    \see size() -- returns the size of the Fl_Menu_Item array.
    \see menu_end() -- finish %menu modifications (optional)

    \b Example: How to walk the array:
    \code
    for ( int t=0; t<menubar->size(); t++ ) {                // walk array of items
        const Fl_Menu_Item &item = menubar->menu()[t];       // get each item
        fprintf(stderr, "item #%d -- label=%s, value=%s type=%s\n",
            t,
            item.label() ? item.label() : "(Null)",          // menu terminators have NULL labels
            (item.flags & FL_MENU_VALUE) ? "set" : "clear",  // value of toggle or radio items
            (item.flags & FL_SUBMENU) ? "Submenu" : "Item"); // see if item is a submenu or actual item
    }
    \endcode

  */
  const Fl_Menu_Item *menu() const {return menu_;}
  const Fl_Menu_Item *menu_end(); // in src/Fl_Menu_add.cxx
  void menu(const Fl_Menu_Item *m);
  void copy(const Fl_Menu_Item *m, void* user_data = 0);
  int insert(int index, const char*, int shortcut, Fl_Callback*, void* = 0, int = 0);
  int  add(const char*, int shortcut, Fl_Callback*, void* = 0, int = 0); // see src/Fl_Menu_add.cxx
  /** See int Fl_Menu_::add(const char* label, int shortcut, Fl_Callback*, void *user_data=0, int flags=0) */
  int  add(const char* a, const char* b, Fl_Callback* c, void* d = 0, int e = 0) {
      return add(a,fl_old_shortcut(b),c,d,e);
  }
  /** See int Fl_Menu_::insert(const char* label, int shortcut, Fl_Callback*, void *user_data=0, int flags=0) */
  int insert(int index, const char* a, const char* b, Fl_Callback* c, void* d = 0, int e = 0) {
      return insert(index,a,fl_old_shortcut(b),c,d,e);
  }
  int  add(const char *);
  int  size() const ;
  void size(int W, int H) { Fl_Widget::size(W, H); }
  void clear();
  int clear_submenu(int index);
  void replace(int,const char *);
  void remove(int);
  /** Changes the shortcut of item \p i to \p s. */
  void shortcut(int i, int s) {menu_[i].shortcut(s);}
  /** Sets the flags of item i.  For a list of the flags, see Fl_Menu_Item.  */
  void mode(int i,int fl) {menu_[i].flags = fl;}
  /** Gets the flags of item i.  For a list of the flags, see Fl_Menu_Item.  */
  int  mode(int i) const {return menu_[i].flags;}

  /** Returns a pointer to the last menu item that was picked.  */
  const Fl_Menu_Item *mvalue() const {return value_;}
  /** Returns the index into menu() of the last item chosen by the user.  It is zero initially. */
  int value() const {return value_ ? (int)(value_-menu_) : -1;}
  int value(const Fl_Menu_Item*);
  /**
    The value is the index into menu() of the last item chosen by
    the user.  It is zero initially.  You can set it as an integer, or set
    it with a pointer to a menu item.  The set routines return non-zero if
    the new value is different than the old one.
  */
  int value(int i) {return value(menu_+i);}
  /** Returns the title of the last item chosen.  */
  const char *text() const {return value_ ? value_->text : 0;}
  /** Returns the title of item i.  */
  const char *text(int i) const {return menu_[i].text;}

  /** Gets the current font of menu item labels.  */
  Fl_Font textfont() const {return textfont_;}
  /**  Sets the current font of menu item labels.  */
  void textfont(Fl_Font c) {textfont_=c;}
  /**  Gets the font size of menu item labels.  */
  Fl_Fontsize textsize() const {return textsize_;}
  /**  Sets the font size of menu item labels.  */
  void textsize(Fl_Fontsize c) {textsize_=c;}
  /** Get the current color of menu item labels.  */
  Fl_Color textcolor() const {return textcolor_;}
  /** Sets the current color of menu item labels. */
  void textcolor(Fl_Color c) {textcolor_=c;}

  /**
    This box type is used to surround the currently-selected items in the
    menus.  If this is FL_NO_BOX then it acts like
    FL_THIN_UP_BOX and selection_color() acts like
    FL_WHITE, for back compatibility.
  */
  Fl_Boxtype down_box() const {return (Fl_Boxtype)down_box_;}
  /**    See Fl_Boxtype Fl_Menu_::down_box() const   */
  void down_box(Fl_Boxtype b) {down_box_ = b;}

  /** For back compatibility, same as selection_color() */
  Fl_Color down_color() const {return selection_color();}
  /** For back compatibility, same as selection_color() */
  void down_color(unsigned c) {selection_color(c);}
  void setonly(Fl_Menu_Item* item);
};

#endif

//
// End of "$Id$".
//
