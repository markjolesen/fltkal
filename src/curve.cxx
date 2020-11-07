// curve.cxx
//
// "$Id: fl_curve.cxx 12970 2018-06-23 20:50:22Z matt $"
//
// Bezier curve functions for the Fast Light Tool Kit (FLTK).
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

/**
  \file fl_curve.cxx
  \brief Utility for drawing Bezier curves, adding the points to the
         current fl_begin/fl_vertex/fl_end path.

  Incremental math implementation:
  I very much doubt this is optimal!  From Foley/vanDam page 511.
  If anybody has a better algorithm, please send it!
*/

#include <fl/fl_draw.h>
#include <fl/fl_math.h>

/**
 \cond DriverDev
 \addtogroup DriverDeveloper
 \{
 */

/** see fl_curve() */
void Fl_Graphics_Driver::curve(double X0, double Y0,
	      double X1, double Y1,
	      double X2, double Y2,
	      double X3, double Y3) {

  double x = fl_transform_x(X0,Y0);
  double y = fl_transform_y(X0,Y0);

  // draw point 0:
  fl_transformed_vertex(x,y);

  double x1 = fl_transform_x(X1,Y1);
  double yy1 = fl_transform_y(X1,Y1);
  double x2 = fl_transform_x(X2,Y2);
  double y2 = fl_transform_y(X2,Y2);
  double x3 = fl_transform_x(X3,Y3);
  double y3 = fl_transform_y(X3,Y3);

  // find the area:
  double a = fabs((x-x2)*(y3-yy1)-(y-y2)*(x3-x1));
  double b = fabs((x-x3)*(y2-yy1)-(y-y3)*(x2-x1));
  if (b > a) a = b;

  // use that to guess at the number of segments:
  int n = int(sqrt(a)/4);
  if (n > 1) {
    if (n > 100) n = 100; // make huge curves not hang forever

    double e = 1.0/n;

    // calculate the coefficients of 3rd order equation:
    double xa = (x3-3*x2+3*x1-x);
    double xb = 3*(x2-2*x1+x);
    double xc = 3*(x1-x);
    // calculate the forward differences:
    double dx1 = ((xa*e+xb)*e+xc)*e;
    double dx3 = 6*xa*e*e*e;
    double dx2 = dx3 + 2*xb*e*e;

    // calculate the coefficients of 3rd order equation:
    double ya = (y3-3*y2+3*yy1-y);
    double yb = 3*(y2-2*yy1+y);
    double yc = 3*(yy1-y);
    // calculate the forward differences:
    double dy1 = ((ya*e+yb)*e+yc)*e;
    double dy3 = 6*ya*e*e*e;
    double dy2 = dy3 + 2*yb*e*e;

    // draw points 1 .. n-2:
    for (int m=2; m<n; m++) {
      x += dx1;
      dx1 += dx2;
      dx2 += dx3;
      y += dy1;
      dy1 += dy2;
      dy2 += dy3;
      fl_transformed_vertex(x,y);
    }

    // draw point n-1:
    fl_transformed_vertex(x+dx1, y+dy1);
  }

  // draw point n:
  fl_transformed_vertex(x3,y3);
}

/**
 \}
 \endcond
 */

//
// End of "$Id: fl_curve.cxx 12970 2018-06-23 20:50:22Z matt $".
//
