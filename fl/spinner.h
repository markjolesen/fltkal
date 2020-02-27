// spinner.h
//
// "$Id$"
//
// Spinner widget for the Fast Light Tool Kit (FLTK).
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
   Fl_Spinner widget . */

#ifndef Fl_Spinner_H
#define Fl_Spinner_H

#include <fl/fl_enums.h>
#include <fl/group.h>
#include <fl/input.h>
#include <fl/btnrpt.h>

/**
  This widget is a combination of a numerical input widget and repeat buttons.

  The user can either type into the input area or use the buttons to
  change the value.

  \image html Fl_Spinner.png "Fl_Spinner widget"
  \image latex Fl_Spinner.png "Fl_Spinner widget" width=6cm
*/
class FL_EXPORT Fl_Spinner : public Fl_Group {

  double	value_;			// Current value
  double	minimum_;		// Minimum value
  double	maximum_;		// Maximum value
  double	step_;			// Amount to add/subtract for up/down
  const char	*format_;		// Format string for input field
  int		wrap_;			// wrap around at bounds (1/0)

private:

  static void sb_cb(Fl_Widget *w, Fl_Spinner *sb); // internal callback
  void update();				   // update input field

protected:

  // This class works like Fl_Input but ignores FL_Up and FL_Down key
  // presses so they are handled by its parent, the Fl_Spinner widget.
  // See STR #2989.

  class FL_EXPORT Fl_Spinner_Input : public Fl_Input {
  public:
    Fl_Spinner_Input(int X, int Y, int W, int H)
    : Fl_Input(X, Y, W, H) {}
    int handle(int event);		// implemented in src/Fl_Spinner.cxx
  };

  Fl_Spinner_Input input_;		// Input field for the value
  Fl_Repeat_Button
		up_button_,		// Up button
		down_button_;		// Down button

public:

  // Constructor
  Fl_Spinner(int X, int Y, int W, int H, const char *L = 0);
  // Event handling
  int handle(int event);
  // Resize group and subwidgets
  void resize(int X, int Y, int W, int H);

  /** Returns the format string for the value. */
  const char *format() const { return (format_); }

  /** Sets the format string for the value. */
  void format(const char *f) { format_ = f; update(); }

  /** Gets the maximum value of the widget. */
  double maximum() const { return (maximum_); }

  /** Sets the maximum value of the widget. */
  void maximum(double m) { maximum_ = m; }

  /** Gets the minimum value of the widget. */
  double minimum() const { return (minimum_); }

  /** Sets the minimum value of the widget. */
  void minimum(double m) { minimum_ = m; }

  /** Sets the minimum and maximum values for the widget. */
  void range(double a, double b) { minimum_ = a; maximum_ = b; }

  // Sets the amount to change the value when the user clicks a button.
  // Docs in src/Fl_Spinner.cxx
  void step(double s);

  /**
    Gets the amount to change the value when the user clicks a button.
    \see Fl_Spinner::step(double)
  */
  double step() const { return (step_); }

  /** Sets whether the spinner wraps around at upper and lower bounds.

    If wrap mode is on the spinner value is set to the minimum() or
    maximum() if the value exceeds the upper or lower bounds, resp., if
    it was changed by one of the buttons or the FL_Up or FL_Down keys.

    The spinner stops at the upper and lower bounds if wrap mode is off.

    The default wrap mode is on for backwards compatibility with
    FLTK 1.3.x and older versions.

    \note Wrap mode does not apply to the input field if the input value
	  is edited directly as a number. The input value is always
	  clipped to the allowed range as if wrap mode was off when the
	  input field is left (i.e. loses focus).

    \see minimum(), maximum()

    \param[in] set non-zero sets wrap mode, zero resets wrap mode

    \since 1.4.0
  */
  void wrap(int set) { wrap_ = set ? 1 : 0; }

  /** Gets the wrap mode of the Fl_Spinner widget.
    \see void wrap(int)
    \since 1.4.0
  */
  int wrap() const { return wrap_; }

  /** Gets the color of the text in the input field. */
  Fl_Color textcolor() const { return (input_.textcolor()); }

  /** Sets the color of the text in the input field. */
  void textcolor(Fl_Color c) { input_.textcolor(c); }

  /** Gets the font of the text in the input field. */
  Fl_Font textfont() const { return (input_.textfont()); }

  /** Sets the font of the text in the input field. */
  void textfont(Fl_Font f) { input_.textfont(f); }

  /** Gets the size of the text in the input field. */
  Fl_Fontsize textsize() const { return (input_.textsize()); }

  /** Sets the size of the text in the input field. */
  void textsize(Fl_Fontsize s) { input_.textsize(s); }

  // Sets the numeric representation in the input field.
  // Docs see src/Fl_Spinner.cxx
  void type(uchar v);

  /** Gets the numeric representation in the input field.
    \see Fl_Spinner::type(uchar)
  */
  uchar type() const { return (input_.type()); }

  /** Gets the current value of the widget. */
  double value() const { return (value_); }

  /**
    Sets the current value of the input widget.
    Before setting value to a non-integer value, the spinner
    type() should be changed to floating point.
  */
  void value(double v) { value_ = v; update(); }

  /**
    Sets the background color of the spinner widget's input field.
  */
  void color(Fl_Color v) { input_.color(v); }

  /**
    Returns the background color of the spinner widget's input field.
  */
  Fl_Color color() const { return(input_.color()); }

  /**
    Sets the selection color of the spinner widget's input field.
  */
  void selection_color(Fl_Color val) { input_.selection_color(val); }

  /**
    Returns the selection color of the spinner widget's input field.
  */
  Fl_Color selection_color() const { return input_.selection_color(); }

  /**
   Sets the maximum width of the input field.
   */
  void maximum_size(int m) { if (m > 0) input_.maximum_size(m); }

  /**
   Returns the maximum width of the input field.
   */
  int maximum_size() const { return input_.maximum_size(); }
};

#endif // !Fl_Spinner_H


//
// End of "$Id$".
//
