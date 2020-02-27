// tabs.h
//
// "$Id$"
//
// Tab header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018, 2020 The fltkal authors
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
   Fl_Tabs widget . */

#ifndef Fl_Tabs_H
#define Fl_Tabs_H

#include "group.h"

/**
  The Fl_Tabs widget is the "file card tabs"
  interface that allows you to put lots and lots of buttons and
  switches in a panel, as popularized by many toolkits.
  
  \image html  tabs.png
  \image latex tabs.png "Fl_Tabs" width=8cm
  
  Clicking the tab makes a child visible() by calling
  show() on it, and all other children are made invisible
  by calling hide() on them. Usually the children are Fl_Group widgets
  containing several widgets themselves.
  
  Each child makes a card, and its label() is printed
  on the card tab, including the label font and style.  The
  selection color of that child is used to color the tab, while
  the color of the child determines the background color of the pane.
  '&' in labels are used to prefix a shortcut that is drawn underlined and
  that activates the corresponding tab; repeated '&&' avoids that.
  
  The size of the tabs is controlled by the bounding box of the
  children (there should be some space between the children and
  the edge of the Fl_Tabs), and the tabs may be placed
  "inverted" on the bottom - this is determined by which
  gap is larger. It is easiest to lay this out in fluid, using the
  fluid browser to select each child group and resize them until
  the tabs look the way you want them to.
  
  The background area behind and to the right of the tabs is
  "transparent", exposing the background detail of the parent. The
  value of Fl_Tabs::box() does not affect this area. So if Fl_Tabs is
  resized by itself without the parent, force the appropriate parent
  (visible behind the tabs) to redraw() to prevent artifacts.

  See "Resizing Caveats" below on how to keep tab heights constant.
  See "Callback's Use Of when()" on how to control the details
  of how clicks invoke the callback().

  A typical use of the Fl_Tabs widget:

  \par
  \code
      // Typical use of Fl_Tabs
      Fl_Tabs *tabs = new Fl_Tabs(10,10,300,200);
      {
          Fl_Group *grp1 = new Fl_Group(20,30,280,170,"Tab1");
	  {
	      ..widgets that go in tab#1..
          }
	  grp1->end();
          Fl_Group *grp2 = new Fl_Group(20,30,280,170,"Tab2");
	  {
	      ..widgets that go in tab#2..
	  }
	  grp2->end();
      }
      tabs->end();
  \endcode

  \b Default \b Appearance

  The appearance of each "tab" is taken from the label() and color() of the
  child group corresponding to that "tab" and panel. Where the "tabs" appear
  depends on the position and size of the child groups that make up the
  panels within the Fl_Tab, i.e. whether there is more space above or
  below them. The height of the "tabs" depends on how much free space
  is available.

  \image html  tabs_default.png "Fl_Tabs Default Appearance"
  \image latex tabs_default.png "Fl_Tabs Default Appearance" width=8cm

  \b Highlighting \b The \b Selected \b Tab

  The selected "tab" can be highlighted further by setting the
  selection_color() of the Fl_Tab itself, e.g.

  \par
  \code
  ..
  tabs = new Fl_Tabs(..);
  tabs->selection_color(FL_DARK3);
  ..
  \endcode

  The result of the above looks like:
  \image html  tabs_selection.png "Highlighting the selected tab"
  \image latex tabs_selection.png "Highlighting the selected tab" width=8cm

  \b Uniform \b Tab \b and \b Panel \b Appearance

  In order to have uniform tab and panel appearance, not only must the color()
  and selection_color() for each child group be set, but also the 
  selection_color() of the Fl_Tab itself any time a new "tab" is selected.
  This can be achieved within the Fl_Tab callback, e.g.

  \par
  \code
  void MyTabCallback(Fl_Widget *w, void*) {
    Fl_Tabs *tabs = (Fl_Tabs*)w;
    // When tab changed, make sure it has same color as its group
    tabs->selection_color( (tab->value())->color() );
  }
  ..
  int main(..) {
    // Define tabs widget
    tabs = new Fl_Tabs(..);
    tabs->callback(MyTabCallback);

    // Create three tabs each colored differently
    grp1 = new Fl_Group(.. "One");
     grp1->color(9);
     grp1->selection_color(9);
    grp1->end();

    grp2 = new Fl_Group(.. "Two");
     grp2->color(10);
     grp2->selection_color(10);
    grp2->end();

    grp3 = new Fl_Group(.. "Three");
     grp3->color(14);
     grp3->selection_color(14);
    grp3->end();
    ..
    // Make sure default tab has same color as its group
    tabs->selection_color( (tab->value())->color() );
    ..
    return Fl::run();
  }
  \endcode

  The result of the above looks like:
  \image html  tabs_uniform.png "Fl_Tabs with uniform colors"
  \image latex tabs_uniform.png "Fl_Tabs with uniform colors" width=8cm

  \b Resizing \b Caveats

  When Fl_Tabs is resized vertically, the default behavior scales the
  tab's height as well as its children.  To keep the tab height constant
  during resizing, set the tab widget's resizable() to one of the tab's
  child groups, i.e.

  \par
  \code
    tabs = new Fl_Tabs(..);
    grp1 = new Fl_Group(..);
    ..
    grp2 = new Fl_Group(..);
    ..
    tabs->end();
    tabs->resizable(grp1);	// keeps tab height constant
  \endcode

  \par Callback's Use Of when()

  As of FLTK 1.3.3, Fl_Tabs() supports the following flags for when():

    - \ref FL_WHEN_NEVER       -- callback never invoked (all flags off)
    - \ref FL_WHEN_CHANGED     -- if flag set, invokes callback when a tab has been changed (on click or keyboard navigation)
    - \ref FL_WHEN_NOT_CHANGED -- if flag set, invokes callback when the tabs remain unchanged (on click or keyboard navigation)
    - \ref FL_WHEN_RELEASE     -- if flag set, invokes callback on RELEASE of mouse button or keyboard navigation

  Notes:

    -#  The above flags can be logically OR-ed (|) or added (+) to combine behaviors.
    -#  The default value for when() is \ref FL_WHEN_RELEASE (inherited from Fl_Widget).
    -#  If \ref FL_WHEN_RELEASE is the \em only flag specified, 
        the behavior will be as if (\ref FL_WHEN_RELEASE|\ref FL_WHEN_CHANGED) was specified.
    -#  The value of changed() will be valid during the callback.
    -#  If both \ref FL_WHEN_CHANGED and \ref FL_WHEN_NOT_CHANGED are specified, 
        the callback is invoked whether the tab has been changed or not.
	The changed() method can be used to determine the cause.
    -#  \ref FL_WHEN_NOT_CHANGED can happen if someone clicks on an already selected tab,
        or if a keyboard navigation attempt results in no change to the tabs,
	such as using the arrow keys while at the left or right end of the tabs.
*/
class FL_EXPORT Fl_Tabs : public Fl_Group {

  Fl_Widget *push_;

protected:

  int *tab_pos;		// array of x-offsets of tabs per child + 1
  int *tab_width;	// array of widths of tabs per child + 1
  int tab_count;	// array size
  Fl_Align tab_align_;	// tab label alignment

  virtual void redraw_tabs();
  virtual int tab_positions();	// allocate and calculate tab positions
  virtual void clear_tab_positions();
  virtual void draw_tab(int x1, int x2, int W, int H, Fl_Widget* o, int sel=0);
  virtual int tab_height();

  void draw();

public:

  Fl_Tabs(int X, int Y, int W, int H, const char *L = 0);
  virtual ~Fl_Tabs();

  int handle(int);
  Fl_Widget *value();
  int value(Fl_Widget *);
  /**
    Returns the tab group for the tab the user has currently down-clicked on
    and remains over until FL_RELEASE. Otherwise, returns NULL.

    While the user is down-clicked on a tab, the return value is the tab group
    for that tab. But as soon as the user releases, or drags off the tab with
    the button still down, the return value will be NULL.

    \see push(Fl_Widget*).
  */
  Fl_Widget *push() const {return push_;}
  int push(Fl_Widget *);

  // Returns the widget of the tab the user clicked on at event_x/event_y.
  virtual Fl_Widget *which(int event_x, int event_y);

  // Returns the position and size available to be used by its children.
  void client_area(int &rx, int &ry, int &rw, int &rh, int tabh=0);

  /**
    Sets the tab label alignment.

    The default is FL_ALIGN_CENTER so tab labels are centered, but since
    the label space is measured (per label) to fit the labels, there
    wouldn't be any difference if labels were aligned left or right.

    If you want to show an image (icon) next to the group's label you can
    set a different label alignment. FL_ALIGN_IMAGE_NEXT_TO_TEXT is the
    recommended alignment to show the icon left of the text.
  */
  void tab_align(Fl_Align a) {tab_align_ = a;}
  /**
    Gets the tab label alignment.

    \see tab_align(Fl_Align)
  */
  Fl_Align tab_align() const {return tab_align_;}
};

#endif

//
// End of "$Id$".
//
