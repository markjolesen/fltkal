// imgpnm.cxx
//
// "$Id: Fl_PNM_Image.cxx 10751 2015-06-14 17:07:31Z AlbrechtS $"
//
// Fl_PNM_Image routines.
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1997-2010 by Easy Software Products.
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
//   Fl_PNM_Image::Fl_PNM_Image() - Load a PNM image...
//

//
// Include necessary header files...
//

#include <fl/fl.h>
#include <fl/imgpnm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fl/fl_utf8.h>
#include "flstring.h"


//
// 'Fl_PNM_Image::Fl_PNM_Image()' - Load a PNM image...
//


/**
 The constructor loads the named PNM image.

 The destructor frees all memory and server resources that are used by
 the image.

 Use Fl_Image::fail() to check if Fl_PNM_Image failed to load. fail() returns
 ERR_FILE_ACCESS if the file could not be opened or read, ERR_FORMAT if the
 PNM format could not be decoded, and ERR_NO_IMAGE if the image could not
 be loaded for another reason.
 */
Fl_PNM_Image::Fl_PNM_Image(const char *name)	// I - File to read
  : Fl_RGB_Image(0,0,0) {
  FILE		*fp;		// File pointer
  int		x, y;		// Looping vars
  char		line[1024],	// Input line
		*lineptr;	// Pointer in line
  uchar		*ptr,		// Pointer to pixel values
		byte,		// Byte from file
		bit;		// Bit in pixel
  int		format,		// Format of PNM file
		val,		// Pixel value
		maxval;		// Maximum pixel value


  if ((fp = fl_fopen(name, "rb")) == NULL) {
    ld(ERR_FILE_ACCESS);
    return;
  }

  //
  // Read the file header in the format:
  //
  //   Pformat
  //   # comment1
  //   # comment2
  //   ...
  //   # commentN
  //   width
  //   height
  //   max sample
  //

  lineptr = fgets(line, sizeof(line), fp);
  if (!lineptr) {
    fclose(fp);
    Fl::error("Early end-of-file in PNM file \"%s\"!", name);
    ld(ERR_FILE_ACCESS);
    return;
  }

  lineptr ++;

  format = atoi(lineptr);
  while (isdigit(*lineptr)) lineptr ++;

  if (format == 7) lineptr = (char *)"";

  while (lineptr != NULL && w() == 0) {
    if (*lineptr == '\0' || *lineptr == '#') {
      lineptr = fgets(line, sizeof(line), fp);
    } else if (isdigit(*lineptr)) {
      w(strtol(lineptr, &lineptr, 10));
    } else lineptr ++;
  }

  while (lineptr != NULL && h() == 0) {
    if (*lineptr == '\0' || *lineptr == '#') {
      lineptr = fgets(line, sizeof(line), fp);
    } else if (isdigit(*lineptr)) {
      h(strtol(lineptr, &lineptr, 10));
    } else lineptr ++;
  }

  if (format != 1 && format != 4) {
    maxval = 0;

    while (lineptr != NULL && maxval == 0) {
      if (*lineptr == '\0' || *lineptr == '#') {
	lineptr = fgets(line, sizeof(line), fp);
      } else if (isdigit(*lineptr)) {
	maxval = strtol(lineptr, &lineptr, 10);
      } else lineptr ++;
    }
  } else maxval = 1;

  // Allocate memory...
  if (format == 1 || format == 2 || format == 4 || format == 5) d(1);
  else d(3);

//  printf("%s = %dx%dx%d\n", name, w(), h(), d());

  if (((size_t)w()) * h() * d() > max_size() ) {
    Fl::warning("PNM file \"%s\" is too large!\n", name);
    fclose(fp);
    w(0); h(0); d(0); ld(ERR_FORMAT);
    return;
  }
  array       = new uchar[w() * h() * d()];
  alloc_array = 1;

  // Read the image file...
  for (y = 0; y < h(); y ++) {
    ptr = (uchar *)array + y * w() * d();

    switch (format) {
      case 1 :
        for (x = w(); x > 0; x --)
          if (fscanf(fp, "%d", &val) == 1) *ptr++ = (uchar)(255 * (1-val));
        break;
        
      case 2 :
          for (x = w(); x > 0; x --)
            if (fscanf(fp, "%d", &val) == 1) *ptr++ = (uchar)(255 * val / maxval);
          break;

      case 3 :
          for (x = w(); x > 0; x --) {
            if (fscanf(fp, "%d", &val) == 1) *ptr++ = (uchar)(255 * val / maxval);
            if (fscanf(fp, "%d", &val) == 1) *ptr++ = (uchar)(255 * val / maxval);
            if (fscanf(fp, "%d", &val) == 1) *ptr++ = (uchar)(255 * val / maxval);
          }
          break;

      case 4 :
        for (x = w(), byte = (uchar)getc(fp), bit = 128; x > 0; x --) {
          if ((byte & bit) == 0) *ptr++ = 255; // 0 bit for white pixel
          else *ptr++ = 0; // 1 bit for black pixel
          
          if (bit > 1) bit >>= 1;
          else {
            bit  = 128;
            if (x > 1) byte = (uchar)getc(fp);
          }
        }
        break;
          
      case 5 :
      case 6 :
        if (maxval < 256) {
          if (fread(ptr, w(), d(), fp)) { /* ignored */ }
        } else {
          for (x = d() * w(); x > 0; x --) {
            val = (uchar)getc(fp);
            val = (val<<8)|(uchar)getc(fp);
            *ptr++ = (255*val)/maxval;
          }
        }
        break;
        
      case 7 : /* XV 3:3:2 thumbnail format */
        for (x = w(); x > 0; x --) {
          byte = (uchar)getc(fp);
          
          *ptr++ = (uchar)(255 * ((byte >> 5) & 7) / 7);
          *ptr++ = (uchar)(255 * ((byte >> 2) & 7) / 7);
          *ptr++ = (uchar)(255 * (byte & 3) / 3);
        }
        break;
    }
  }

  fclose(fp);
}


//
// End of "$Id: Fl_PNM_Image.cxx 10751 2015-06-14 17:07:31Z AlbrechtS $".
//
