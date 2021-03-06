//
// FLTK images library core.
//
// Copyright 1997-2010 by Easy Software Products.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     https://www.fltk.org/COPYING.php
//
// Please see the following page on how to report bugs and issues:
//
//     https://www.fltk.org/bugs.php
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
#ifdef FLTK_USE_SVG
#include <FL/Fl_SVG_Image.H>
#endif
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

static Fl_Image *fl_check_images(const char *name, uchar *header, int headerlen);


/**
\brief Register the image formats.

 This function is provided in the fltk_images library and
 registers all of the "extra" image file formats that are not part
 of the core FLTK library.
*/
void fl_register_images() {
  Fl_Shared_Image::add_handler(fl_check_images);
  Fl_Image::register_images_done = true;
}


//
// 'fl_check_images()' - Check for a supported image format.
//

Fl_Image *                                      // O - Image, if found
fl_check_images(const char *name,               // I - Filename
                uchar      *header,             // I - Header data from file
                int headerlen) {                // I - Amount of data
  if (memcmp(header, "GIF87a", 6) == 0 ||
      memcmp(header, "GIF89a", 6) == 0) // GIF file
    return new Fl_GIF_Image(name);

  if (memcmp(header, "BM", 2) == 0)     // BMP file
    return new Fl_BMP_Image(name);

  if (header[0] == 'P' && header[1] >= '1' && header[1] <= '7')
                                        // Portable anymap
    return new Fl_PNM_Image(name);

#ifdef HAVE_LIBPNG
  if (memcmp(header, "\211PNG", 4) == 0)// PNG file
    return new Fl_PNG_Image(name);
#endif // HAVE_LIBPNG

#ifdef HAVE_LIBJPEG
  if (memcmp(header, "\377\330\377", 3) == 0 && // Start-of-Image
      header[3] >= 0xc0 && header[3] <= 0xfe)   // APPn .. comment for JPEG file
    return new Fl_JPEG_Image(name);
#endif // HAVE_LIBJPEG

#ifdef FLTK_USE_SVG
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
#endif // FLTK_USE_SVG

  return 0;
}
