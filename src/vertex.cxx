// vertex.cxx
//
// "$Id: fl_vertex.cxx 12970 2018-06-23 20:50:22Z matt $"
//
// Portable drawing routines for the Fast Light Tool Kit (FLTK).
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

/**
  \file fl_vertex.cxx
  \brief  Portable drawing code for drawing arbitrary shapes with
          simple 2D transformations.
*/

// Portable code for drawing arbitrary shapes with simple 2D transformations.
// See also fl_arc.cxx

// matt: the Quartz implementation purposely doesn't use the Quartz matrix
//       operations for reasons of compatibility and maintainability

// -----------------------------------------------------------------------------
// all driver code is now in drivers/XXX/Fl_XXX_Graphics_Driver_xyz.cxx
// -----------------------------------------------------------------------------

#include <fl/drvgr.h>
#include <fl/fl.h>
#include <fl/fl_math.h>
#include <stdlib.h>

/**
 \cond DriverDev
 \addtogroup DriverDeveloper
 \{
 */

/** see fl_push_matrix() */
void Fl_Graphics_Driver::push_matrix() {
  if (sptr==matrix_stack_size)
    Fl::error("fl_push_matrix(): matrix stack overflow.");
  else
    stack[sptr++] = m;
}

/** see fl_pop_matrix() */
void Fl_Graphics_Driver::pop_matrix() {
  if (sptr==0)
    Fl::error("fl_pop_matrix(): matrix stack underflow.");
  else
    m = stack[--sptr];
}

/** see fl_mult_matrix() */
void Fl_Graphics_Driver::mult_matrix(double a, double b, double c, double d, double x, double y) {
  matrix o;
  o.a = a*m.a + b*m.c;
  o.b = a*m.b + b*m.d;
  o.c = c*m.a + d*m.c;
  o.d = c*m.b + d*m.d;
  o.x = x*m.a + y*m.c + m.x;
  o.y = x*m.b + y*m.d + m.y;
  m = o;
}

/** see fl_rotate() */
void Fl_Graphics_Driver::rotate(double d) {
  if (d) {
    double s, c;
    if (d == 0) {s = 0; c = 1;}
    else if (d == 90) {s = 1; c = 0;}
    else if (d == 180) {s = 0; c = -1;}
    else if (d == 270 || d == -90) {s = -1; c = 0;}
    else {s = sin(d*M_PI/180); c = cos(d*M_PI/180);}
    mult_matrix(c,-s,s,c,0,0);
  }
}

/** see fl_translate() */
void Fl_Graphics_Driver::translate(double x,double y) {
  mult_matrix(1,0,0,1,x,y);
}

/** see fl_begin_points() */
void Fl_Graphics_Driver::begin_points() {
  n = 0;
  what = POINT_;
}

/** see fl_begin_line() */
void Fl_Graphics_Driver::begin_line() {
  n = 0;
  what = LINE;
}

/** see fl_begin_loop() */
void Fl_Graphics_Driver::begin_loop() {
  n = 0;
  what = LOOP;
}

/** see fl_begin_polygon() */
void Fl_Graphics_Driver::begin_polygon() {
  n = 0;
  what = POLYGON;
}

/** see fl_transform_x() */
double Fl_Graphics_Driver::transform_x(double x, double y) {
  return x*m.a + y*m.c + m.x;
}

/** see fl_transform_y() */
double Fl_Graphics_Driver::transform_y(double x, double y) {
  return x*m.b + y*m.d + m.y;
}

/** see fl_transform_dx() */
double Fl_Graphics_Driver::transform_dx(double x, double y) {
  return x*m.a + y*m.c;
}

/** see fl_transform_dy() */
double Fl_Graphics_Driver::transform_dy(double x, double y) {
  return x*m.b + y*m.d;
}

/**
 \}
 \endcond
 */

//
// End of "$Id: fl_vertex.cxx 12970 2018-06-23 20:50:22Z matt $".
//
