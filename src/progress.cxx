// progress.cxx
//
// "$Id: Fl_Progress.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Progress bar widget routines.
//
// Copyright 2017-2018 The fltkal authors
// Copyright 2000-2010 by Michael Sweet.
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
// Contents:

//
//   Fl_Progress::draw()        - Draw the check button.
//   Fl_Progress::Fl_Progress() - Construct a Fl_Progress widget.
//

//
// Include necessary header files...
//

#include <fl/fl.h>
#include <fl/progress.h>
#include <fl/fl_draw.h>


//
// Fl_Progress is a progress bar widget based off Fl_Widget that shows a
// standard progress bar...
//


//
// 'Fl_Progress::draw()' - Draw the progress bar.
//

/** Draws the progress bar. */
void Fl_Progress::draw()
{
  int	progress;	// Size of progress bar...
  int	bx, by, bw, bh;	// Box areas...
  int	tx, tw;		// Temporary X + width


  // Get the box borders...
  bx = Fl::box_dx(box());
  by = Fl::box_dy(box());
  bw = Fl::box_dw(box());
  bh = Fl::box_dh(box());

  tx = x() + bx;
  tw = w() - bw;

  // Draw the progress bar...
  if (maximum_ > minimum_)
    progress = (int)(w() * (value_ - minimum_) / (maximum_ - minimum_) + 0.5f);
  else
    progress = 0;

  // Draw the box and label...
  if (progress > 0) {
    Fl_Color c = labelcolor();
    labelcolor(fl_contrast(labelcolor(), selection_color()));

    fl_push_clip(x(), y(), progress + bx, h());
      draw_box(box(), x(), y(), w(), h(), active_r() ? selection_color() : fl_inactive(selection_color()));
      draw_label(tx, y() + by, tw, h() - bh);
    fl_pop_clip();

    labelcolor(c);

    if (progress<w()) {
      fl_push_clip(tx + progress, y(), w() - progress, h());
        draw_box(box(), x(), y(), w(), h(), active_r() ? color() : fl_inactive(color()));
        draw_label(tx, y() + by, tw, h() - bh);
      fl_pop_clip();
    }
  } else {
    draw_box(box(), x(), y(), w(), h(), active_r() ? color() : fl_inactive(color()));
    draw_label(tx, y() + by, tw, h() - bh);
  }
}


/**  
    The constructor creates the progress bar using the position, size, and label.
    
    You can set the background color with color() and the
    progress bar color with selection_color(), or you can set both colors
    together with color(unsigned bg, unsigned sel).
    
    The default colors are FL_BACKGROUND2_COLOR and FL_YELLOW, resp.
*/
Fl_Progress::Fl_Progress(int X, int Y, int W, int H, const char* L)
: Fl_Widget(X, Y, W, H, L) {
  align(FL_ALIGN_INSIDE);
  box(FL_DOWN_BOX);
  color(FL_BACKGROUND2_COLOR, FL_YELLOW);
  minimum(0.0f);
  maximum(100.0f);
  value(0.0f);
}


//
// End of "$Id: Fl_Progress.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
