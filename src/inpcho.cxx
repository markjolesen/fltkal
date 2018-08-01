// inpcho.cxx
//
// "$Id: Fl_Input_Choice.cxx 12908 2018-05-07 21:24:06Z greg.ercolano $"
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

#include <fl/inpcho.h>

#include <fl/fl_draw.h>
#include <string.h>

/**
  \class Fl_Input_Choice

  \brief A combination of the input widget and a menu button.

  \image html input_choice.jpg
  \image latex input_choice.jpg "Fl_Input_Choice widget" width=6cm

  The user can either type into the input area, or use the
  menu button chooser on the right to choose an item which loads
  the input area with the selected text.

  The application can directly access both the internal Fl_Input
  and Fl_Menu_Button widgets respectively using the input() and menubutton()
  accessor methods.

  The default behavior is to invoke the Fl_Input_Choice::callback()
  if the user changes the input field's contents, either by typing,
  pasting, or clicking a different item in the choice menu.

  The callback can determine if an item was picked vs. typing
  into the input field by checking the value of menubutton()->changed(),
  which will be:

      - 1: the user picked a different item in the choice menu
      - 0: the user typed or pasted directly into the input field

  Example use:
  \code
  #include <stdio.h>
  #include <FL/Fl.H>
  #include <FL/Fl_Double_Window.H>
  #include <FL/Fl_Input_Choice.H>
  void choice_cb(Fl_Widget *w, void *userdata) {

    // Show info about the picked item
    Fl_Input_Choice *choice = (Fl_Input_Choice*)w;
    printf("*** Choice Callback:\n");
    printf("    widget's text value='%s'\n", choice->value());   // normally all you need

    // Access the menu via menubutton()..
    const Fl_Menu_Item *item = choice->menubutton()->mvalue();
    printf("    item label()='%s'\n", item ? item->label() : "(No item)");
    printf("    item value()=%d\n", choice->menubutton()->value());
    printf("    input value()='%s'\n", choice->input()->value());
    printf("    The user %s\n", choice->menubutton()->changed()
                                    ? "picked a menu item"
                                    : "typed text");
  }
  int main() {
    Fl_Double_Window win(200,100,"Input Choice");
    win.begin();
      Fl_Input_Choice choice(10,10,100,30);
      choice.callback(choice_cb, 0);
      choice.add("Red");
      choice.add("Orange");
      choice.add("Yellow");
      //choice.value("Red");    // uncomment to make "Red" default
    win.end();
    win.show();
    return Fl::run();
  }
  \endcode
*/

/** Constructor for private menu button. */

Fl_Input_Choice::InputMenuButton::InputMenuButton(int x,int y,int w,int h,const char*l)
                                 :Fl_Menu_Button(x,y,w,h,l)
{
  box(FL_UP_BOX);
}

/** Draws the private menu button. */

void Fl_Input_Choice::InputMenuButton::draw() {
  draw_box(FL_UP_BOX, color());
  fl_color(active_r() ? labelcolor() : fl_inactive(labelcolor()));
  int xc = x()+w()/2, yc=y()+h()/2;
  fl_polygon(xc-5,yc-3,xc+5,yc-3,xc,yc+3);
  if (Fl::focus() == this) draw_focus();
}


/** Callback for the Fl_Input_Choice menu. */

void Fl_Input_Choice::menu_cb(Fl_Widget*, void *data) {
  Fl_Input_Choice *o=(Fl_Input_Choice *)data;
  Fl_Widget_Tracker wp(o);
  const Fl_Menu_Item *item = o->menubutton()->mvalue();
  if (item && item->flags & (FL_SUBMENU|FL_SUBMENU_POINTER)) return;	// ignore submenus
  if (!strcmp(o->inp_->value(), o->menu_->text()))
  {
    o->Fl_Widget::clear_changed();
    if (o->when() & FL_WHEN_NOT_CHANGED)
      o->do_callback();
  }
  else
  {
    o->inp_->value(o->menu_->text());
    o->inp_->set_changed();
    o->Fl_Widget::set_changed();
    if (o->when() & (FL_WHEN_CHANGED|FL_WHEN_RELEASE))
      o->do_callback();
  }

  if (wp.deleted()) return;

  if (o->callback() != default_callback)
  {
    o->Fl_Widget::clear_changed();
    o->inp_->clear_changed();
  }
}

/** Callback for the Fl_Input_Choice input field. */

void Fl_Input_Choice::inp_cb(Fl_Widget*, void *data) {
  Fl_Input_Choice *o=(Fl_Input_Choice *)data;
  Fl_Widget_Tracker wp(o);
  if (o->inp_->changed()) {
    o->Fl_Widget::set_changed();
    if (o->when() & (FL_WHEN_CHANGED|FL_WHEN_RELEASE))
      o->do_callback();
  } else {
    o->Fl_Widget::clear_changed();
    if (o->when() & FL_WHEN_NOT_CHANGED)
      o->do_callback();
  }

  if (wp.deleted()) return;

  if (o->callback() != default_callback)
    o->Fl_Widget::clear_changed();
}

/**
  Creates a new Fl_Input_Choice widget using the given position, size,
  and label string.

  Inherited destructor destroys the widget and any values associated with it.
*/
Fl_Input_Choice::Fl_Input_Choice (int X, int Y, int W, int H, const char *L)
: Fl_Group(X,Y,W,H,L) {
  Fl_Group::box(FL_DOWN_BOX);
  align(FL_ALIGN_LEFT);					// default like Fl_Input
  inp_ = new Fl_Input(inp_x(), inp_y(),
                      inp_w(), inp_h());
  inp_->callback(inp_cb, (void*)this);
  inp_->box(FL_FLAT_BOX);				// cosmetic
  inp_->when(FL_WHEN_CHANGED|FL_WHEN_NOT_CHANGED);
  menu_ = new InputMenuButton(menu_x(), menu_y(),
                              menu_w(), menu_h());
  menu_->callback(menu_cb, (void*)this);
  menu_->box(FL_FLAT_BOX);				// cosmetic
  end();
}

/** Resizes the Fl_Input_Choice widget.
*/
void Fl_Input_Choice::resize(int X, int Y, int W, int H) {
  Fl_Group::resize(X,Y,W,H);
  inp_->resize(inp_x(), inp_y(), inp_w(), inp_h());
  menu_->resize(menu_x(), menu_y(), menu_w(), menu_h());
}

/** Chooses item# \p val in the menu, and sets the Fl_Input text field
    to that value. Any previous text is cleared.
    \see void value(const char *val)
*/
void Fl_Input_Choice::value(int val) {
  menu_->value(val);
  inp_->value(menu_->text(val));
}

/** Sets the changed() state of both input and menu button widgets
    to the specified value.
*/
void Fl_Input_Choice::set_changed() {
  inp_->set_changed();
  // no need to call Fl_Widget::set_changed()
}

/** Clears the changed() state of both input and menu button widgets. */
void Fl_Input_Choice::clear_changed() {
  inp_->clear_changed();
  Fl_Widget::clear_changed();
}

/** Updates the menubutton with the string value in Fl_Input.

    If the string value currently in Fl_Input matches one of the
    menu items in menubutton(), that menu item will become the
    current item selected.

    Call this method after setting value(const char*) if you need
    the menubutton() to be synchronized with the Fl_Input field.

    \code
    // Add items
    choice->add(".25");
    choice->add(".50");
    choice->add("1.0");
    choice->add("2.0");
    choice->add("4.0");

    choice->value("1.0");            // sets Fl_Input to "1.0"
    choice->update_menubutton();     // cause menubutton to reflect this value too
                                     // (returns 1 if match was found, 0 if not)
    // Verify menubutton()'s value.
    printf("menu button choice index=%d, value=%s\n", 
                                choice->menubutton()->value(),    // would be -1 if update not done
                                choice->menubutton()->text());    // would be NULL if update not done
    \endcode

    \returns 1 if a matching menuitem was found and value set, 0 if not.
    \version 1.4.0
*/
int Fl_Input_Choice::update_menubutton() {
  // Find item in menu
  for ( int i=0; i<menu_->size(); i++ ) {
    const Fl_Menu_Item &item = menu_->menu()[i];
    if (item.flags & (FL_SUBMENU|FL_SUBMENU_POINTER)) continue;   // ignore submenus
    const char *name = menu_->text(i);
    if ( name && strcmp(name, inp_->value()) == 0) {
      menu_->value(i);
      return 1;
    }
  }
  return 0;		// not found
}

//
// End of "$Id: Fl_Input_Choice.cxx 12908 2018-05-07 21:24:06Z greg.ercolano $".
//
