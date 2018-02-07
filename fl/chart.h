// chart.h
//
// "$Id: Fl_Chart.H 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Forms chart header file for the Fast Light Tool Kit (FLTK).
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

/* \file
   Fl_Chart widget . */

#ifndef Fl_Chart_H
#define Fl_Chart_H

#ifndef Fl_Widget_H
#include "widget.h"
#endif

// values for type()
#define FL_BAR_CHART		0	/**< type() for Bar Chart variant */
#define FL_HORBAR_CHART		1	/**< type() for Horizontal Bar Chart variant */
#define FL_LINE_CHART		2	/**< type() for Line Chart variant */
#define FL_FILL_CHART		3	/**< type() for Fill Line Chart variant */
#define FL_SPIKE_CHART		4	/**< type() for Spike Chart variant */
#define FL_PIE_CHART		5	/**< type() for Pie Chart variant */
#define FL_SPECIALPIE_CHART	6	/**< type() for Special Pie Chart variant */

#define FL_FILLED_CHART  FL_FILL_CHART	/**< for compatibility */

#define FL_CHART_MAX		128	/**< max entries per chart */
#define FL_CHART_LABEL_MAX	18	/**< max label length for entry */

/** For internal use only */
struct FL_CHART_ENTRY {
   float val;				/**< For internal use only. */
   unsigned col;			/**< For internal use only. */
   char str[FL_CHART_LABEL_MAX+1];	/**< For internal use only. */
};

/**
  \class Fl_Chart
  \brief Fl_Chart displays simple charts.
  It is provided for Forms compatibility.

  \image html charts.png  
  \image latex charts.png  "Fl_Chart" width=10cm
  \todo Refactor Fl_Chart::type() information.

  The type of an Fl_Chart object can be set using type(uchar t) to:
  \li \c FL_BAR_CHART: Each sample value is drawn as a vertical bar.
  \li \c FL_FILLED_CHART: The chart is filled from the bottom of the graph
         to the sample values.
  \li \c FL_HORBAR_CHART: Each sample value is drawn as a horizontal bar.
  \li \c FL_LINE_CHART: The chart is drawn as a polyline with vertices at
         each sample value.
  \li \c FL_PIE_CHART: A pie chart is drawn with each sample value being
         drawn as a proportionate slice in the circle.
  \li \c FL_SPECIALPIE_CHART: Like \c FL_PIE_CHART, but the first slice is
         separated from the pie.
  \li \c FL_SPIKE_CHART: Each sample value is drawn as a vertical line.
 */
class FL_EXPORT Fl_Chart : public Fl_Widget {
    int numb;
    int maxnumb;
    int sizenumb;
    FL_CHART_ENTRY *entries;
    double min,max;
    uchar autosize_;
    Fl_Font textfont_;
    Fl_Fontsize textsize_;
    Fl_Color textcolor_;
protected:
    void draw();
public:
    Fl_Chart(int X, int Y, int W, int H, const char *L = 0);

    ~Fl_Chart();

    void clear();

    void add(double val, const char *str = 0, unsigned col = 0);

    void insert(int ind, double val, const char *str = 0, unsigned col = 0);

    void replace(int ind, double val, const char *str = 0, unsigned col = 0);

    /**
      Gets the lower and upper bounds of the chart values.
      \param[out] a, b are set to lower, upper
     */
    void bounds(double *a,double *b) const {*a = min; *b = max;}

    void bounds(double a,double b);

    /**
      Returns the number of data values in the chart.
     */
    int size() const {return numb;}

    void size(int W, int H) { Fl_Widget::size(W, H); }

    /**
      Gets the maximum number of data values for a chart.
     */
    int maxsize() const {return maxnumb;}

    void maxsize(int m);

    /** Gets the chart's text font */
    Fl_Font textfont() const {return textfont_;}
    /** Sets the chart's text font to \p s. */
    void textfont(Fl_Font s) {textfont_ = s;}

    /** Gets the chart's text size */
    Fl_Fontsize textsize() const {return textsize_;}
    /** gets the chart's text size to \p s. */
    void textsize(Fl_Fontsize s) {textsize_ = s;}

    /** Gets the chart's text color */
    Fl_Color textcolor() const {return textcolor_;}
    /** gets the chart's text color to \p n. */
    void textcolor(Fl_Color n) {textcolor_ = n;}

    /**
      Get whether the chart will automatically adjust the bounds of the chart.
      \returns non-zero if auto-sizing is enabled and zero if disabled.
     */
    uchar autosize() const {return autosize_;}

    /**
      Set whether the chart will automatically adjust the bounds of the chart.
      \param[in] n non-zero to enable automatic resizing, zero to disable.
     */
    void autosize(uchar n) {autosize_ = n;}
};

#endif

//
// End of "$Id: Fl_Chart.H 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
