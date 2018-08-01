// iconfile.cxx
//
// "$Id: Fl_File_Icon.cxx 12976 2018-06-26 14:12:43Z manolo $"
//
// Fl_File_Icon routines.
//
// KDE icon code donated by Maarten De Boer.
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1999-2010 by Michael Sweet.
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
//   Fl_File_Icon::Fl_File_Icon()       - Create a new file icon.
//   Fl_File_Icon::~Fl_File_Icon()      - Remove a file icon.
//   Fl_File_Icon::add()               - Add data to an icon.
//   Fl_File_Icon::find()              - Find an icon based upon a given file.
//   Fl_File_Icon::draw()              - Draw an icon.
//   Fl_File_Icon::label()             - Set the widgets label to an icon.
//   Fl_File_Icon::labeltype()         - Draw the icon label.
//

//
// Include necessary header files...
//

#include <stdio.h>
#include <stdlib.h>
#include <fl/fl_utf8.h>
#include "flstring.h"
#include <fl/fl.h>
#include "drvsys.h"
#include <fl/iconfile.h>
#include <fl/widget.h>
#include <fl/fl_draw.h>
#include <fl/filename.h>

//
// Icon cache...
//

Fl_File_Icon	*Fl_File_Icon::first_ = (Fl_File_Icon *)0;


// Registers the FL_ICON_LABEL drawing function
Fl_Labeltype fl_define_FL_ICON_LABEL() {
  Fl::set_labeltype(_FL_ICON_LABEL, Fl_File_Icon::labeltype, 0);
  return _FL_ICON_LABEL;
}


/**
  Creates a new Fl_File_Icon with the specified information.
  \param[in] p filename pattern
  \param[in] t file type
  \param[in] nd number of data values
  \param[in] d data values
*/
Fl_File_Icon::Fl_File_Icon(const char *p,	/* I - Filename pattern */
                	   int        t,	/* I - File type */
			   int        nd,	/* I - Number of data values */
			   short      *d)	/* I - Data values */
{
  // Initialize the pattern and type...
  pattern_ = p;
  type_    = t;

  // Copy icon data as needed...
  if (nd)
  {
    num_data_   = nd;
    alloc_data_ = nd + 1;
    data_       = (short *)calloc(sizeof(short), nd + 1);
    memcpy(data_, d, nd * sizeof(short));
  }
  else
  {
    num_data_   = 0;
    alloc_data_ = 0;
  }

  // And add the icon to the list of icons...
  next_  = first_;
  first_ = this;
}


/**
  The destructor destroys the icon and frees all memory that has been
  allocated for it.
*/
Fl_File_Icon::~Fl_File_Icon() {
  Fl_File_Icon	*current,	// Current icon in list
		*prev;		// Previous icon in list


  // Find the icon in the list...
  for (current = first_, prev = (Fl_File_Icon *)0;
       current != this && current != (Fl_File_Icon *)0;
       prev = current, current = current->next_) {/*empty*/}

  // Remove the icon from the list as needed...
  if (current)
  {
    if (prev)
      prev->next_ = current->next_;
    else
      first_ = current->next_;
  }

  // Free any memory used...
  if (alloc_data_)
    free(data_);
}


/**
  Adds a keyword value to the icon array, returning a pointer to it.
  \param[in] d data value
*/
short *				// O - Pointer to new data value
Fl_File_Icon::add(short d)	// I - Data to add
{
  short	*dptr;			// Pointer to new data value


  // Allocate/reallocate memory as needed
  if ((num_data_ + 1) >= alloc_data_)
  {
    alloc_data_ += 128;

    if (alloc_data_ == 128)
      dptr = (short *)malloc(sizeof(short) * alloc_data_);
    else
      dptr = (short *)realloc(data_, sizeof(short) * alloc_data_);

    if (dptr == NULL)
      return (NULL);

    data_ = dptr;
  }

  // Store the new data value and return
  data_[num_data_++] = d;
  data_[num_data_]   = END;

  return (data_ + num_data_ - 1);
}


/**
  Finds an icon that matches the given filename and file type.
  \param[in] filename name of file
  \param[in] filetype enumerated file type
  \return matching file icon or NULL
*/
Fl_File_Icon *				// O - Matching file icon or NULL
Fl_File_Icon::find(const char *filename,// I - Name of file */
                   int        filetype)	// I - Enumerated file type
{
  Fl_File_Icon	*current;		// Current file in list
  const char	*name;			// Base name of filename


  // Get file information if needed...
  if (filetype == ANY) {
    filetype = Fl::system_driver()->file_type(filename);
  }

  // Look at the base name in the filename
  name = fl_filename_name(filename);

  // Loop through the available file types and return any match that
  // is found...
  for (current = first_; current != (Fl_File_Icon *)0; current = current->next_)
    if ((current->type_ == filetype || current->type_ == ANY) &&
        (fl_filename_match(filename, current->pattern_) ||
	 fl_filename_match(name, current->pattern_)))
      break;

  // Return the match (if any)...
  return (current);
}

/**
  Draws an icon in the indicated area.
  \param[in] x, y, w, h position and size
  \param[in] ic icon color
  \param[in] active status, default is active [non-zero]
*/
void
Fl_File_Icon::draw(int      x,		// I - Upper-lefthand X
        	   int      y,		// I - Upper-lefthand Y
		   int      w,		// I - Width of bounding box
		   int      h,		// I - Height of bounding box
        	   Fl_Color ic,		// I - Icon color...
        	   int      active)	// I - Active or inactive?
{
  Fl_Color	c,		// Current color
		oc;		// Outline color
  short		*d,		// Pointer to data
		*dend;		// End of data...
  short		*prim;		// Pointer to start of primitive...
  double	scale;		// Scale of icon


  // Don't try to draw a NULL array!
  if (num_data_ == 0)
    return;

  // Setup the transform matrix as needed...
  scale = w < h ? w : h;

  fl_push_matrix();
  fl_translate((float)x + 0.5 * ((float)w - scale),
               (float)y + 0.5 * ((float)h + scale));
  fl_scale(scale, -scale);

  // Loop through the array until we see an unmatched END...
  d    = data_;
  dend = data_ + num_data_;
  prim = NULL;
  c    = ic;

  if (active)
    fl_color(c);
  else
    fl_color(fl_inactive(c));

  while (d < dend)
    switch (*d)
    {
      case END :
          if (prim)
            switch (*prim)
	    {
	      case LINE :
		  fl_end_line();
		  break;

	      case CLOSEDLINE :
		  fl_end_loop();
		  break;

	      case POLYGON :
		  fl_end_complex_polygon();
		  break;

	      case OUTLINEPOLYGON :
		  fl_end_complex_polygon();

        	  oc = (Fl_Color)((((unsigned short *)prim)[1] << 16) | 
	                	  ((unsigned short *)prim)[2]);
                  if (active)
		  {
                    if (oc == FL_ICON_COLOR)
		      fl_color(ic);
		    else
		      fl_color(oc);
		  }
		  else
		  {
                    if (oc == FL_ICON_COLOR)
		      fl_color(fl_inactive(ic));
		    else
		      fl_color(fl_inactive(oc));
		  }

		  fl_begin_loop();

		  prim += 3;
		  while (*prim == VERTEX)
		  {
		    fl_vertex(prim[1] * 0.0001, prim[2] * 0.0001);
		    prim += 3;
		  }

        	  fl_end_loop();
		  fl_color(c);
		  break;
	    }

          prim = NULL;
	  d ++;
	  break;

      case COLOR :
          c = (Fl_Color)((((unsigned short *)d)[1] << 16) | 
	                   ((unsigned short *)d)[2]);

          if (c == FL_ICON_COLOR)
	    c = ic;

          if (!active)
	    c = fl_inactive(c);

          fl_color(c);
	  d += 3;
	  break;

      case LINE :
          prim = d;
	  d ++;
	  fl_begin_line();
	  break;

      case CLOSEDLINE :
          prim = d;
	  d ++;
	  fl_begin_loop();
	  break;

      case POLYGON :
          prim = d;
	  d ++;
	  fl_begin_complex_polygon();
	  break;

      case OUTLINEPOLYGON :
          prim = d;
	  d += 3;
	  fl_begin_complex_polygon();
	  break;

      case VERTEX :
          if (prim)
	    fl_vertex(d[1] * 0.0001, d[2] * 0.0001);
	  d += 3;
	  break;

      default : // Ignore invalid data...
          d ++;
    }

  // If we still have an open primitive, close it...
  if (prim)
    switch (*prim)
    {
      case LINE :
	  fl_end_line();
	  break;

      case CLOSEDLINE :
	  fl_end_loop();
	  break;

      case POLYGON :
	  fl_end_polygon();
	  break;

      case OUTLINEPOLYGON :
	  fl_end_polygon();

          oc = (Fl_Color)((((unsigned short *)prim)[1] << 16) | 
	                  ((unsigned short *)prim)[2]);
          if (active)
	  {
            if (oc == FL_ICON_COLOR)
	      fl_color(ic);
	    else
	      fl_color(oc);
	  }
	  else
	  {
            if (oc == FL_ICON_COLOR)
	      fl_color(fl_inactive(ic));
	    else
	      fl_color(fl_inactive(oc));
	  }

	  fl_begin_loop();

	  prim += 3;
	  while (*prim == VERTEX)
	  {
	    fl_vertex(prim[1] * 0.0001, prim[2] * 0.0001);
	    prim += 3;
	  }

          fl_end_loop();
	  fl_color(c);
	  break;
    }

  // Restore the transform matrix
  fl_pop_matrix();
}

/**
  Applies the icon to the widget, registering the Fl_File_Icon
  label type as needed.
  \param[in] w widget for which this icon will become the label
*/
void Fl_File_Icon::label(Fl_Widget *w)	// I - Widget to label
{
  w->label(FL_ICON_LABEL, (const char*)this);
}


/**
  Draw the icon label.
  \param[in] o label data
  \param[in] x, y, w, h position and size of label
  \param[in] a label alignment [not used]
*/
void
Fl_File_Icon::labeltype(const Fl_Label *o,	// I - Label data
                	int            x,	// I - X position of label
			int            y,	// I - Y position of label
			int            w,	// I - Width of label
			int            h,	// I - Height of label
			Fl_Align       a)	// I - Label alignment (not used)
{
  Fl_File_Icon *icon;			// Pointer to icon data


  (void)a;

  icon = (Fl_File_Icon *)(o->value);
  if (icon) icon->draw(x, y, w, h, (Fl_Color)(o->color));
}


//
// End of "$Id: Fl_File_Icon.cxx 12976 2018-06-26 14:12:43Z manolo $".
//
