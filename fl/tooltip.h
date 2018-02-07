// tooltip.h
//
// "$Id: Fl_Tooltip.H 11163 2016-02-13 12:57:00Z matt $"
//
// Tooltip header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2011 by Bill Spitzak and others.
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
   Fl_Tooltip widget . */

#ifndef Fl_Tooltip_H
#define Fl_Tooltip_H

#include <fl/fl.h>
#include <fl/widget.h>

/**
  The Fl_Tooltip class provides tooltip support for
  all FLTK widgets. It contains only static methods.

  \image html tooltip-options.png "Fl_Tooltip Options"
  \image latex src/tooltip-options.png "Fl_Tooltip Options" width=6cm

*/
class FL_EXPORT Fl_Tooltip {
public:
  /**    Gets the tooltip delay. The default delay is 1.0 seconds.  */
  static float delay() { return delay_; }
  /**    Sets the tooltip delay. The default delay is 1.0 seconds.  */
  static void delay(float f) { delay_ = f; }
  /**
    Gets the tooltip hover delay, the delay between tooltips.
    The default delay is 0.2 seconds.
  */
  static float hoverdelay() { return hoverdelay_; }
  /**
    Sets the tooltip hover delay, the delay between tooltips.
    The default delay is 0.2 seconds.
  */
  static void hoverdelay(float f) { hoverdelay_ = f; }
  /**    Returns non-zero if tooltips are enabled.  */
  static int enabled() { return Fl::option(Fl::OPTION_SHOW_TOOLTIPS); }
  /**    Enables tooltips on all widgets (or disables if <i>b</i> is false).  */
  static void enable(int b = 1) { Fl::option(Fl::OPTION_SHOW_TOOLTIPS, (b!=0));}
  /**    Same as enable(0), disables tooltips on all widgets.  */
  static void disable() { enable(0); }
  static void (*enter)(Fl_Widget* w);
  static void enter_area(Fl_Widget* w, int X, int Y, int W, int H, const char* tip);
  static void (*exit)(Fl_Widget *w);
  /** Gets the current widget target */
  static Fl_Widget* current() {return widget_;}
  static void current(Fl_Widget*);

  /**    Gets the typeface for the tooltip text.  */
  static Fl_Font font() { return font_; }
  /**    Sets the typeface for the tooltip text.  */
  static void font(Fl_Font i) { font_ = i; }
  /**    Gets the size of the tooltip text.  */
  static Fl_Fontsize size() { return (size_ == -1 ? FL_NORMAL_SIZE : size_); }
  /**    Sets the size of the tooltip text.  */
  static void size(Fl_Fontsize s) { size_ = s; }
  /** Gets the background color for tooltips. The default background color is a pale yellow.  */
  static Fl_Color color() { return color_; }
  /** Sets the background color for tooltips. The default background color is a pale yellow.  */
  static void color(Fl_Color c) { color_ = c; }
  /** Gets the color of the text in the tooltip. The default is  black. */
  static Fl_Color textcolor() { return textcolor_; }
  /** Sets the color of the text in the tooltip. The default is  black. */
  static void textcolor(Fl_Color c) { textcolor_ = c; }
  /** Gets the amount of extra space left/right of the tooltip's text. Default is 3. */
  static int margin_width() { return margin_width_; }
  /** Sets the amount of extra space left/right of the tooltip's text. Default is 3. */
  static void margin_width(int v) { margin_width_ = v; }
  /** Gets the amount of extra space above and below the tooltip's text. Default is 3. */
  static int margin_height() { return margin_height_; }
  /** Sets the amount of extra space above and below the tooltip's text. Default is 3. */
  static void margin_height(int v) { margin_height_ = v; }
  /** Gets the maximum width for tooltip's text before it word wraps. Default is 400. */
  static int wrap_width() { return wrap_width_; }
  /** Sets the maximum width for tooltip's text before it word wraps. Default is 400. */
  static void wrap_width(int v) { wrap_width_ = v; }
  /** Returns the window that is used for tooltips */
  static Fl_Window* current_window(void);

  // These should not be public, but Fl_Widget::tooltip() needs them...
  // fabien: made it private with only a friend function access
private:
  friend void Fl_Widget::tooltip(const char *);
  friend void Fl_Widget::copy_tooltip(const char *);
  static void enter_(Fl_Widget* w);
  static void exit_(Fl_Widget *w);
  static void set_enter_exit_once_();

private:
  static float delay_; //!< delay before a tooltip is shown
  static float hoverdelay_; //!< delay between tooltips
  static Fl_Color color_;
  static Fl_Color textcolor_;
  static Fl_Font font_;
  static Fl_Fontsize size_;
  static Fl_Widget* widget_; //!< Keeps track of the current target widget
  static int margin_width_;	//!< distance around tooltip text left+right
  static int margin_height_;	//!< distance around tooltip text top+bottom
  static int wrap_width_;	//!< maximum width of tooltip text before it word wraps
};

#endif

//
// End of "$Id: Fl_Tooltip.H 11163 2016-02-13 12:57:00Z matt $".
//
