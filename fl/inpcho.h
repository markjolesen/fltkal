// inpcho.h
//
// "$Id: Fl_Input_Choice.H 12192 2017-03-11 23:26:32Z AlbrechtS $"
//
// An input/chooser widget.
//            ______________  ____
//           |              || __ |
//           | input area   || \/ |
//           |______________||____|
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
// Copyright 2004 by Greg Ercolano.
//

/* \file
   Fl_Input_Choice widget . */

#ifndef Fl_Input_Choice_H
#define Fl_Input_Choice_H

#include <fl/fl.h>
#include <fl/group.h>
#include <fl/input.h>
#include <fl/btnmenu.h>

// Leaving these two headers so builds don't break if user includes this
// header and uses items from fl_draw or string (but doesn't include in src).
// Note: this would ensure compatibility with FLTK 1.3.x.
// Shall we? Currently not!
// #include <FL/fl_draw.H>
// #include <string.h>

/*
  A combination of the input widget and a menu button.

  The user can either type into the input area, or use the
  menu button chooser on the right to choose an item which loads
  the input area with the selected text.

  Note: doxygen docs in src/Fl_Input_Choice.cxx
*/

class FL_EXPORT Fl_Input_Choice : public Fl_Group {

  // Private class to handle slightly 'special' behavior of menu button
  class InputMenuButton : public Fl_Menu_Button {
    void draw();
  public:
    InputMenuButton(int X, int Y, int W, int H, const char *L=0);
  };

  Fl_Input *inp_;
  InputMenuButton *menu_;

  // note: this is used by the Fl_Input_Choice ctor.
  static void menu_cb(Fl_Widget*, void *data);

  // note: this is used by the Fl_Input_Choice ctor.
  static void inp_cb(Fl_Widget*, void *data);

  // Custom resize behavior -- input stretches, menu button doesn't
  inline int inp_x() { return(x() + Fl::box_dx(box())); }
  inline int inp_y() { return(y() + Fl::box_dy(box())); }
  inline int inp_w() { return(w() - Fl::box_dw(box()) - 20); }
  inline int inp_h() { return(h() - Fl::box_dh(box())); }

  inline int menu_x() { return(x() + w() - 20 - Fl::box_dx(box())); }
  inline int menu_y() { return(y() + Fl::box_dy(box())); }
  inline int menu_w() { return(20); }
  inline int menu_h() { return(h() - Fl::box_dh(box())); }

public:

  Fl_Input_Choice(int X, int Y, int W, int H, const char *L=0);

  void resize(int X, int Y, int W, int H);

  /** Adds an item to the menu.
    You can access the more complex Fl_Menu_Button::add() methods
    (setting callbacks, userdata, etc), via menubutton(). Example:
    \code
    Fl_Input_Choice *choice = new Fl_Input_Choice(100,10,120,25,"Fonts");
    Fl_Menu_Button *mb = choice->menubutton();             // use Fl_Input_Choice's Fl_Menu_Button
    mb->add("Helvetica", 0, MyFont_CB,     (void*)mydata); // use Fl_Menu_Button's add() methods
    mb->add("Courier",   0, MyFont_CB,     (void*)mydata);
    mb->add("More..",    0, FontDialog_CB, (void*)mydata);
    \endcode
  */
  void add(const char *s) { menu_->add(s); }

  /** Returns the combined changed() state of the input and menu button widget. */
  int changed() const { return inp_->changed() | Fl_Widget::changed(); }

  // Clears the changed() state of both input and menu button widgets.
  void clear_changed();

  // Sets the changed() state of both input and menu button widgets.
  void set_changed();

  /** Removes all items from the menu. */
  void clear() { menu_->clear(); }

  /** Gets the box type of the menu button */
  Fl_Boxtype down_box() const { return (menu_->down_box()); }

  /** Sets the box type of the menu button */
  void down_box(Fl_Boxtype b) { menu_->down_box(b); }

  /** Gets the Fl_Menu_Item array used for the menu. */
  const Fl_Menu_Item *menu() { return (menu_->menu()); }

  /** Sets the Fl_Menu_Item array used for the menu. */
  void menu(const Fl_Menu_Item *m) { menu_->menu(m); }

  /// Gets the Fl_Input text field's text color.
  Fl_Color textcolor() const { return (inp_->textcolor());}

  /// Sets the Fl_Input text field's text color to \p c.
  void textcolor(Fl_Color c) { inp_->textcolor(c);}

  /// Gets the Fl_Input text field's font style.
  Fl_Font textfont() const { return (inp_->textfont());}

  /// Sets the Fl_Input text field's font style to \p f.
  void textfont(Fl_Font f) { inp_->textfont(f);}

  /// Gets the Fl_Input text field's font size
  Fl_Fontsize textsize() const { return (inp_->textsize()); }

  /// Sets the Fl_Input text field's font size to \p s.
  void textsize(Fl_Fontsize s) { inp_->textsize(s); }

  /// Returns the Fl_Input text field's current contents.
  const char* value() const { return (inp_->value()); }

  /** Sets the Fl_Input text field's contents to \p val.
    Does not affect the menu selection.
    \see void value(int val)
  */
  void value(const char *val) { inp_->value(val); }

  /* Chooses item# \p val in the menu, and sets the Fl_Input text field
    to that value. Any previous text is cleared. */
  void value(int val);

  /** Returns a pointer to the internal Fl_Menu_Button widget.
    This can be used to access any of the methods of the menu button, e.g.
    \code
    Fl_Input_Choice *choice = new Fl_Input_Choice(100,10,120,25,"Choice:");
    [..]
    // Print all the items in the choice menu
    for ( int t=0; t<choice->menubutton()->size(); t++ ) {
       const Fl_Menu_Item &item = choice->menubutton()->menu()[t];
       printf("item %d -- label=%s\n", t, item.label() ? item.label() : "(Null)");
    }
    \endcode
  */
  Fl_Menu_Button *menubutton() { return menu_; }

  /** Returns a pointer to the internal Fl_Input widget.
    This can be used to directly access all of the Fl_Input widget's methods.
  */
  Fl_Input *input() { return inp_; }
};

#endif // !Fl_Input_Choice_H

//
// End of "$Id: Fl_Input_Choice.H 12192 2017-03-11 23:26:32Z AlbrechtS $".
//
