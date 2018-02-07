// valuator.cxx
//
// "$Id: Fl_Valuator.cxx 11318 2016-03-08 13:51:01Z AlbrechtS $"
//
// Valuator widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2016 by Bill Spitzak and others.
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


// Base class for sliders and all other one-value "knobs"

#include <fl/fl.h>
#include <fl/valuator.h>
#include <fl/fl_math.h>
#include <stdio.h>
#include "flstring.h"

Fl_Valuator::Fl_Valuator(int X, int Y, int W, int H, const char* L)
/**
  Creates a new Fl_Valuator widget using the given position,
  size, and label string. The default boxtype is FL_NO_BOX.
*/
: Fl_Widget(X,Y,W,H,L) {
  align(FL_ALIGN_BOTTOM);
  when(FL_WHEN_CHANGED);
  value_ = 0;
  previous_value_ = 1;
  min = 0;
  max = 1;
  A = 0.0;
  B = 1;
}

const double epsilon = 4.66e-10;

/**  See double Fl_Valuator::step() const */
void Fl_Valuator::step(double s) {
  if (s < 0) s = -s;
  A = rint(s);
  B = 1;
  while (fabs(s-A/B) > epsilon && B<=(0x7fffffff/10)) {B *= 10; A = rint(s*B);}
}

/** Sets the step value to 1.0 / 10<SUP>digits</SUP>.

    Precision \p digits is limited to 0...9 to avoid internal overflow errors.
    Values outside this range are clamped.

    \note For negative values of \p digits the step value is set to
    \p A = 1.0 and \p B = 1, i.e. 1.0/1 = 1.
*/
void Fl_Valuator::precision(int digits) {
  if (digits > 9) digits = 9;
  else if (digits < 0) digits = 0;
  A = 1.0;
  for (B = 1; digits--;) B *= 10;
}

/**  Asks for partial redraw */
void Fl_Valuator::value_damage() {damage(FL_DAMAGE_EXPOSE);} // by default do partial-redraw

/**
    Sets the current value. The new value is \e not
    clamped or otherwise changed before storing it. Use
    clamp() or round() to modify the value before
    calling value(). The widget is redrawn if the new value
    is different than the current one. The initial value is zero.

    changed() will return true if the user has moved the slider,
    but it will be turned off by value(x) and just before doing a callback
    (the callback can turn it back on if desired).
*/
int Fl_Valuator::value(double v) {
  clear_changed();
  if (v == value_) return 0;
  value_ = v;
  value_damage();
  return 1;
}
/** Clamps the value, but accepts v if the previous value is not already out of range */
double Fl_Valuator::softclamp(double v) {
  int which = (min<=max);
  double p = previous_value_;
  if ((v<min)==which && p!=min && (p<min)!=which) return min;
  else if ((v>max)==which && p!=max && (p>max)!=which) return max;
  else return v;
}

// inline void Fl_Valuator::handle_push() {previous_value_ = value_;}
/** Called during a drag operation, after an FL_WHEN_CHANGED event is received and before the callback. */
void Fl_Valuator::handle_drag(double v) {
  if (v != value_) {
    value_ = v;
    value_damage();
    set_changed();
    if (when() & FL_WHEN_CHANGED) do_callback();
  }
}
/** Called after an FL_WHEN_RELEASE event is received and before the callback. */
void Fl_Valuator::handle_release() {
  if (when()&FL_WHEN_RELEASE) {
    // insure changed() is off even if no callback is done.  It may have
    // been turned on by the drag, and then the slider returned to it's
    // initial position:
    clear_changed();
    // now do the callback only if slider in new position or always is on:
    if (value_ != previous_value_ || when() & FL_WHEN_NOT_CHANGED) {
      do_callback();
    }
  }
}

/**
  Round the passed value to the nearest step increment.  Does
  nothing if step is zero.
*/
double Fl_Valuator::round(double v) {
  if (A) return rint(v*B/A)*A/B;
  else return v;
}

/**  Clamps the passed value to the valuator range.*/
double Fl_Valuator::clamp(double v) {
  if ((v<min)==(min<=max)) return min;
  else if ((v>max)==(min<=max)) return max;
  else return v;
}

/**
  Adds n times the step value to the passed value. If
  step was set to zero it uses fabs(maximum() - minimum()) /
  100.
*/
double Fl_Valuator::increment(double v, int n) {
  if (!A) return v+n*(max-min)/100;
  if (min > max) n = -n;
  return (rint(v*B/A)+n)*A/B;
}

/**
  Uses internal rules to format the fields numerical value into
  the character array pointed to by the passed parameter.
  
  The actual format used depends on the current step value. If
  the step value has been set to zero then a \%g format is used.
  If the step value is non-zero, then a \%.*f format is used,
  where the precision is calculated to show sufficient digits
  for the current step value. An integer step value, such as 1
  or 1.0, gives a precision of 0, so the formatted value will
  appear as an integer.

  This method is used by the Fl_Valuator_... group of widgets to
  format the current value into a text string.
  The return value is the length of the formatted text.
  The formatted value is written into \p buffer.
  \p buffer should have space for at least 128 bytes.

  You may override this function to create your own text formatting.
*/
int Fl_Valuator::format(char* buffer) {
  double v = value();
  // MRS: THIS IS A HACK - RECOMMEND ADDING BUFFER SIZE ARGUMENT
  if (!A || !B) return snprintf(buffer, 128, "%g", v);

  // Figure out how many digits are required to correctly format the
  // value.
  int i, c = 0;
  char temp[32];
  // output a number with many digits after the decimal point. This
  // seems to be needed to get high precission
  snprintf(temp, sizeof(temp), "%.12f", A/B);
  // strip all trailing 0's
  for (i=(int) strlen(temp)-1; i>0; i--) {
    if (temp[i]!='0') break;
  }
  // count digits until we find the decimal point (or comma or whatever
  // letter is set in the current locale)
  for (; i>0; i--, c++) {
    if (!isdigit(temp[i])) break;
  }

  // MRS: THIS IS A HACK - RECOMMEND ADDING BUFFER SIZE ARGUMENT
  return snprintf(buffer, 128, "%.*f", c, v);
}

//
// End of "$Id: Fl_Valuator.cxx 11318 2016-03-08 13:51:01Z AlbrechtS $".
//
