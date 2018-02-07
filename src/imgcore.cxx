// imgcore.cxx
//
// "$Id: fl_images_core.cxx 12500 2017-10-15 12:34:24Z AlbrechtS $"
//
// FLTK images library core.
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
//   fl_register_images() - Register the image formats.
//   fl_check_images()    - Check for a supported image format.
//

//
// Include necessary header files...
//

#include <fl/imgshare.h>
#include <fl/imgbmp.h>
#include <fl/imggif.h>
#include <fl/imgjpeg.h>
#include <fl/imgpng.h>
#include <fl/imgpnm.h>
// #include <FL/Fl_SVG_Image.H>
#include <fl/fl_utf8.h>
#include <stdio.h>
#include <stdlib.h>
#include "flstring.h"
#if defined(HAVE_LIBZ)
#include <zlib.h>
#endif

//
// Define a simple global image registration function that registers
// the extra image formats that aren't part of the core FLTK library.
//

static Fl_Image	*fl_check_images(const char *name, uchar *header, int headerlen);


/**
\brief Register the image formats.
 *
 This function is provided in the fltk_images library and 
 registers all of the "extra" image file formats that are not part
 of the core FLTK library.
*/
void fl_register_images() {
  Fl_Shared_Image::add_handler(fl_check_images);
}


//
// 'fl_check_images()' - Check for a supported image format.
//

Fl_Image *					// O - Image, if found
fl_check_images(const char *name,		// I - Filename
                uchar      *header,		// I - Header data from file
		int headerlen) {		// I - Amount of data
  if (memcmp(header, "GIF87a", 6) == 0 ||
      memcmp(header, "GIF89a", 6) == 0)	// GIF file
    return new Fl_GIF_Image(name);

  if (memcmp(header, "BM", 2) == 0)	// BMP file
    return new Fl_BMP_Image(name);

  if (header[0] == 'P' && header[1] >= '1' && header[1] <= '7')
					// Portable anymap
    return new Fl_PNM_Image(name);

#ifdef HAVE_LIBPNG
  if (memcmp(header, "\211PNG", 4) == 0)// PNG file
    return new Fl_PNG_Image(name);
#endif // HAVE_LIBPNG

#ifdef HAVE_LIBJPEG
  if (memcmp(header, "\377\330\377", 3) == 0 &&
					// Start-of-Image
      header[3] >= 0xc0 && header[3] <= 0xef)
	   				// APPn for JPEG file
    return new Fl_JPEG_Image(name);
#endif // HAVE_LIBJPEG

#ifdef FLTK_USE_NANOSVG
#  if defined(HAVE_LIBZ)
  if (header[0] == 0x1f && header[1] == 0x8b) { // denotes gzip'ed data
    int fd = fl_open_ext(name, 1, 0);
    if (fd < 0) return NULL;
    gzFile gzf =  gzdopen(fd, "r");
    if (gzf) {
      gzread(gzf, header, headerlen);
      gzclose(gzf);
    }
  }
#  endif // HAVE_LIBZ
  if ( (headerlen > 5 && memcmp(header, "<?xml", 5) == 0) ||
      memcmp(header, "<svg", 4) == 0)
    return new Fl_SVG_Image(name);
#endif // FLTK_USE_NANOSVG

  return 0;
}


//
// End of "$Id: fl_images_core.cxx 12500 2017-10-15 12:34:24Z AlbrechtS $".
//
