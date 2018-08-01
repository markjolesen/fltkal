// arc.cxx
//
// "$Id: fl_arc.cxx 12970 2018-06-23 20:50:22Z matt $"
//
// Arc functions for the Fast Light Tool Kit (FLTK).
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

/**
  \file fl_arc.cxx
  \brief Utility functions for drawing arcs and circles.
*/

// Utility for drawing arcs and circles.  They are added to
// the current fl_begin/fl_vertex/fl_end path.
// Incremental math implementation:

#include <fl/fl_draw.h>
#include <fl/fl_math.h>

// avoid problems with some platforms that don't 
// implement hypot.
static double _fl_hypot(double x, double y) {
  return sqrt(x*x + y*y);
}

/**
 \cond DriverDev
 \addtogroup DriverDeveloper
 \{
 */

/**
 Draw an arc.

 The default implementation draws an arc using other calls into the graphics
 driver. There is no need to override the method unless the target platform
 supports drawing arcs directly.

 \see fl_arc(double x, double y, double r, double start, double end)
 */
void Fl_Graphics_Driver::arc(double x, double y, double r, double start, double end) {

  // draw start point accurately:
  
  double A = start*(M_PI/180);		// Initial angle (radians)
  double X =  r*cos(A);			// Initial displacement, (X,Y)
  double Y = -r*sin(A);			//   from center to initial point
  fl_vertex(x+X,y+Y);			// Insert initial point

  // Maximum arc length to approximate with chord with error <= 0.125
  
  double epsilon; {
    double r1 = _fl_hypot(fl_transform_dx(r,0), // Horizontal "radius"
		          fl_transform_dy(r,0));
    double r2 = _fl_hypot(fl_transform_dx(0,r), // Vertical "radius"
		          fl_transform_dy(0,r));
		      
    if (r1 > r2) r1 = r2;		// r1 = minimum "radius"
    if (r1 < 2.) r1 = 2.;		// radius for circa 9 chords/circle
    
    epsilon = 2*acos(1.0 - 0.125/r1);	// Maximum arc angle
  }
  A = end*(M_PI/180) - A;		// Displacement angle (radians)
  int i = int(ceil(fabs(A)/epsilon));	// Segments in approximation
  
  if (i) {
    epsilon = A/i;			// Arc length for equal-size steps
    double cos_e = cos(epsilon);	// Rotation coefficients
    double sin_e = sin(epsilon);
    do {
      double Xnew =  cos_e*X + sin_e*Y;
		Y = -sin_e*X + cos_e*Y;
      fl_vertex(x + (X=Xnew), y + Y);
    } while (--i);
  }
}

/**
 \}
 \endcond
 */

//
// End of "$Id: fl_arc.cxx 12970 2018-06-23 20:50:22Z matt $".
//
