// widget.cxx
//
// "$Id: Fl_Widget.cxx 12345 2017-07-20 15:16:37Z AlbrechtS $"
//
// Base widget class for the Fast Light Tool Kit (FLTK).
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

#include <fl/fl.h>
#include <fl/widget.h>
#include <fl/group.h>
#include <fl/tooltip.h>
#include <fl/fl_draw.h>
#include <stdlib.h>
#include "flstring.h"


////////////////////////////////////////////////////////////////
// for compatibility with Forms, all widgets without callbacks are
// inserted into a "queue" when they are activated, and the forms
// compatibility interaction functions (fl_do_events, etc.) will
// read one widget at a time from this queue and return it:

const int QUEUE_SIZE = 20;

static Fl_Widget *obj_queue[QUEUE_SIZE];
static int obj_head, obj_tail;

void Fl_Widget::default_callback(Fl_Widget *widget, void * /*v*/) {
  obj_queue[obj_head++] = widget;
  if (obj_head >= QUEUE_SIZE) obj_head = 0;
  if (obj_head == obj_tail) {
    obj_tail++;
    if (obj_tail >= QUEUE_SIZE) obj_tail = 0;
  }
}
/**
    Reads the default callback queue and returns the first widget.

    All Fl_Widgets that don't have a callback defined use the default
    callback \p static Fl_Widget::default_callback() that puts a pointer
    to the widget in a queue. This method reads the oldest widget out
    of this queue.

    The queue (FIFO) is limited (currently 20 items). If the queue
    overflows, the oldest entry (Fl_Widget *) is discarded.

    Relying on the default callback and reading the callback queue with
    Fl::readqueue() is not recommended. If you need a callback, you should
    set one with Fl_Widget::callback(Fl_Callback *cb, void *data)
    or one of its variants.

    \see Fl_Widget::callback()
    \see Fl_Widget::callback(Fl_Callback *cb, void *data)
    \see Fl_Widget::default_callback()
*/
Fl_Widget *Fl::readqueue() {
  if (obj_tail==obj_head) return 0;
  Fl_Widget *widget = obj_queue[obj_tail++];
  if (obj_tail >= QUEUE_SIZE) obj_tail = 0;
  return widget;
}
/*
    This static internal function removes all pending callbacks for a
    specific widget from the default callback queue (Fl::readqueue()).
    It is only called from Fl_Widget's destructor if the widget
    doesn't have an own callback.
    Note: There's no need to have this in the Fl:: namespace.
*/
static void cleanup_readqueue(Fl_Widget *w) {

  if (obj_tail==obj_head) return;

  // Read the entire queue and copy over all valid entries.
  // The new head will be determined after the last copied entry.

  int old_head = obj_head;	// save newest entry
  int entry = obj_tail;		// oldest entry
  obj_head = obj_tail;		// new queue start
  for (;;) {
    Fl_Widget *o = obj_queue[entry++];
    if (entry >= QUEUE_SIZE) entry = 0;
    if (o != w) { // valid entry
      obj_queue[obj_head++] = o;
      if (obj_head >= QUEUE_SIZE) obj_head = 0;
    } // valid entry
    if (entry == old_head) break;
  }
  return;
}
////////////////////////////////////////////////////////////////

int Fl_Widget::handle(int) {
  return 0;
}

/** Default font size for widgets */
Fl_Fontsize FL_NORMAL_SIZE = 14;

Fl_Widget::Fl_Widget(int X, int Y, int W, int H, const char* L) {

  x_ = X; y_ = Y; w_ = W; h_ = H;

  label_.value	 = L;
  label_.image   = 0;
  label_.deimage = 0;
  label_.type	 = FL_NORMAL_LABEL;
  label_.font	 = FL_HELVETICA;
  label_.size	 = FL_NORMAL_SIZE;
  label_.color	 = FL_FOREGROUND_COLOR;
  label_.align_	 = FL_ALIGN_CENTER;
  tooltip_       = 0;
  callback_	 = default_callback;
  user_data_ 	 = 0;
  type_		 = 0;
  flags_	 = VISIBLE_FOCUS;
  damage_	 = 0;
  box_		 = FL_NO_BOX;
  color_	 = FL_GRAY;
  color2_	 = FL_GRAY;
  when_		 = FL_WHEN_RELEASE;

  parent_ = 0;
  if (Fl_Group::current()) Fl_Group::current()->add(this);
  if (!fl_graphics_driver) {
    // Make sure fl_graphics_driver is initialized. Important if we are called by a static initializer.
    Fl_Display_Device::display_device();
  }
}

void Fl_Widget::resize(int X, int Y, int W, int H) {
  x_ = X; y_ = Y; w_ = W; h_ = H;
}

// this is useful for parent widgets to call to resize children:
int Fl_Widget::damage_resize(int X, int Y, int W, int H) {
  if (x() == X && y() == Y && w() == W && h() == H) return 0;
  resize(X, Y, W, H);
  redraw();
  return 1;
}

int Fl_Widget::take_focus() {
  if (!takesevents()) return 0;
  if (!visible_focus()) return 0;
  if (!handle(FL_FOCUS)) return 0; // see if it wants it
  if (contains(Fl::focus())) return 1; // it called Fl::focus for us
  Fl::focus(this);
  return 1;
}

extern void fl_throw_focus(Fl_Widget*); // in Fl_x.cxx

/**
   Destroys the widget, taking care of throwing focus before if any.
   Destruction removes the widget from any parent group! And groups when
   destroyed destroy all their children. This is convenient and fast.
*/
Fl_Widget::~Fl_Widget() {
  Fl::clear_widget_pointer(this);
  if (flags() & COPIED_LABEL) free((void *)(label_.value));
  if (flags() & COPIED_TOOLTIP) free((void *)(tooltip_));
  // remove from parent group
  if (parent_) parent_->remove(this);
#ifdef DEBUG_DELETE
  if (parent_) { // this should never happen
    printf("*** Fl_Widget: parent_->remove(this) failed [%p,%p]\n",parent_,this);
  }
#endif // DEBUG_DELETE
  parent_ = 0; // Don't throw focus to a parent widget.
  fl_throw_focus(this);
  // remove stale entries from default callback queue (Fl::readqueue())
  if (callback_ == default_callback) cleanup_readqueue(this);
}

/** Draws a focus box for the widget at the given position and size. */

void Fl_Widget::draw_focus(Fl_Boxtype B, int X, int Y, int W, int H) const {
  if (!Fl::visible_focus()) return;
  switch (B) {
    case FL_DOWN_BOX:
    case FL_DOWN_FRAME:
    case FL_THIN_DOWN_BOX:
    case FL_THIN_DOWN_FRAME:
      X ++;
      Y ++;
    default:
      break;
  }
  X += Fl::box_dx(B);
  Y += Fl::box_dy(B);
  W -= Fl::box_dw(B)+1;
  H -= Fl::box_dh(B)+1;

  fl_color(fl_contrast(FL_BLACK, color()));
  fl_focus_rect(X, Y, W, H);
}


void Fl_Widget::activate() {
  if (!active()) {
    clear_flag(INACTIVE);
    if (active_r()) {
      redraw();
      redraw_label();
      handle(FL_ACTIVATE);
      if (inside(Fl::focus())) Fl::focus()->take_focus();
    }
  }
}

void Fl_Widget::deactivate() {
  if (active_r()) {
    set_flag(INACTIVE);
    redraw();
    redraw_label();
    handle(FL_DEACTIVATE);
    fl_throw_focus(this);
  } else {
    set_flag(INACTIVE);
  }
}

int Fl_Widget::active_r() const {
  for (const Fl_Widget* o = this; o; o = o->parent())
    if (!o->active()) return 0;
  return 1;
}

void Fl_Widget::show() {
  if (!visible()) {
    clear_flag(INVISIBLE);
    if (visible_r()) {
      redraw();
      redraw_label();
      handle(FL_SHOW);
      if (inside(Fl::focus())) Fl::focus()->take_focus();
    }
  }
}

void Fl_Widget::hide() {
  if (visible_r()) {
    set_flag(INVISIBLE);
    for (Fl_Widget *p = parent(); p; p = p->parent())
      if (p->box() || !p->parent()) {p->redraw(); break;}
    handle(FL_HIDE);
    fl_throw_focus(this);
  } else {
    set_flag(INVISIBLE);
  }
}

int Fl_Widget::visible_r() const {
  for (const Fl_Widget* o = this; o; o = o->parent())
    if (!o->visible()) return 0;
  return 1;
}

// return true if widget is inside (or equal to) this:
// Returns false for null widgets.
int Fl_Widget::contains(const Fl_Widget *o) const {
  for (; o; o = o->parent_) if (o == this) return 1;
  return 0;
}


void Fl_Widget::label(const char *a) {
  if (flags() & COPIED_LABEL) {
    // reassigning a copied label remains the same copied label
    if (label_.value == a)
      return;
    free((void *)(label_.value));
    clear_flag(COPIED_LABEL);
  }
  label_.value=a;
  redraw_label();
}


void Fl_Widget::copy_label(const char *a) {
  // reassigning a copied label remains the same copied label
  if ((flags() & COPIED_LABEL) && (label_.value == a))
    return;
  if (a) {
    label(strdup(a));
    set_flag(COPIED_LABEL);
  } else {
    label(0);
  }
}

/** Calls the widget callback function with arbitrary arguments.

  All overloads of do_callback() call this method.
  It does nothing if the widget's callback() is NULL.
  It clears the widget's \e changed flag \b after the callback was
  called unless the callback is the default callback. Hence it is not
  necessary to call clear_changed() after calling do_callback()
  in your own widget's handle() method.

  \note It is legal to delete the widget in the callback (i.e. in user code),
	but you must not access the widget in the handle() method after
	calling do_callback() if the widget was deleted in the callback.
	We recommend to use Fl_Widget_Tracker to check whether the widget
	was deleted in the callback.

  \param[in] widget call the callback with \p widget as the first argument
  \param[in] arg use \p arg as the user data (second) argument

  \see default_callback()
  \see callback()
  \see class Fl_Widget_Tracker
*/

void Fl_Widget::do_callback(Fl_Widget *widget, void *arg) {
  if (!callback_) return;
  Fl_Widget_Tracker wp(this);
  callback_(widget, arg);
  if (wp.deleted()) return;
  if (callback_ != default_callback)
    clear_changed();
}

//
// End of "$Id: Fl_Widget.cxx 12345 2017-07-20 15:16:37Z AlbrechtS $".
//
