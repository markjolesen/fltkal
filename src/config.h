/*
 * config.h.  Generated from configh.in by configure. 
 *
 * "$Id: configh.in 12413 2017-09-03 13:14:25Z manolo $"
 *
 * Configuration file for the Fast Light Tool Kit (FLTK).
 *
 * Copyright 2017-2018 The fltkal authors
 * Copyright 1998-2016 by Bill Spitzak and others.
 *
 *                              FLTK License
 *                            December 11, 2001
 * 
 * The FLTK library and included programs are provided under the terms
 * of the GNU Library General Public License (LGPL) with the following
 * exceptions:
 * 
 *     1. Modifications to the FLTK configure script, config
 *        header file, and makefiles by themselves to support
 *        a specific platform do not constitute a modified or
 *        derivative work.
 * 
 *       The authors do request that such modifications be
 *       contributed to the FLTK project - send all contributions
 *       through the "Software Trouble Report" on the following page:
 *  
 *            http://www.fltk.org/str.php
 * 
 *     2. Widgets that are subclassed from FLTK widgets do not
 *        constitute a derivative work.
 * 
 *     3. Static linking of applications and widgets to the
 *        FLTK library does not constitute a derivative work
 *        and does not require the author to provide source
 *        code for the application or widget, use the shared
 *        FLTK libraries, or link their applications or
 *        widgets against a user-supplied version of FLTK.
 * 
 *        If you link the application or widget to a modified
 *        version of FLTK, then the changes to FLTK must be
 *        provided under the terms of the LGPL in sections
 *        1, 2, and 4.
 * 
 *     4. You do not have to provide a copy of the FLTK license
 *        with programs that are linked to the FLTK library, nor
 *        do you have to identify the FLTK license in your
 *        program or documentation as required by section 6
 *        of the LGPL.
 * 
 *        However, programs must still identify their use of FLTK.
 *        The following example statement can be included in user
 *        documentation to satisfy this requirement:
 * 
 *            [program/widget] is based in part on the work of
 *            the FLTK project (http://www.fltk.org).
 * 
 *     This library is free software; you can redistribute it and/or
 *     modify it under the terms of the GNU Library General Public
 *     License as published by the Free Software Foundation; either
 *     version 2 of the License, or (at your option) any later version.
 * 
 *     This library is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *     Library General Public License for more details.
 * 
 *     You should have received a copy of the GNU Library General Public
 *     License along with FLTK.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Where to find files...
 */

// #define FLTK_DATADIR "/usr/local/share/fltk"
// #define FLTK_DOCDIR "/usr/local/share/doc/fltk"

/*
 * BORDER_WIDTH:
 *
 * Thickness of FL_UP_BOX and FL_DOWN_BOX.  Current 1,2, and 3 are
 * supported.
 *
 * 3 is the historic FLTK look.
 * 2 is the default and looks like Microsoft Windows, KDE, and Qt.
 * 1 is a plausible future evolution...
 *
 * Note that this may be simulated at runtime by redefining the boxtypes
 * using Fl::set_boxtype().
 */

#define BORDER_WIDTH 2

/*
 * HAVE_GL:
 *
 * Do you have OpenGL? Set this to 0 if you don't have or plan to use
 * OpenGL, and FLTK will be smaller.
 */

#define HAVE_GL 0

/*
 * HAVE_GL_GLU_H:
 *
 * Do you have the OpenGL Utility Library header file?
 * (many broken Mesa RPMs do not...)
 */

#define HAVE_GL_GLU_H 0

/*
 * HAVE_GLXGETPROCADDRESSARB:
 *
 * Do you have the OpenGL glXGetProcAddressARB() function?
 */

#define HAVE_GLXGETPROCADDRESSARB 0

/*
 * USE_COLORMAP:
 *
 * Setting this to zero will save a good deal of code (especially for
 * fl_draw_image), but FLTK will only work on TrueColor visuals.
 */

#define USE_COLORMAP 1

/*
 * HAVE_XINERAMA
 *
 * Do we have the Xinerama library to support multi-head displays?
 */

#define HAVE_XINERAMA 0

/*
 * USE_XFT
 *
 * Use the Xft library to draw anti-aliased text.
 */

#define USE_XFT 0

/*
 * USE_PANGO
 *
 * Use the pango library to draw UTF-8 text.
 */

#define USE_PANGO 0

/*
 * HAVE_XDBE:
 *
 * Do we have the X double-buffer extension?
 */

#define HAVE_XDBE 0

/*
 * USE_XDBE:
 *
 * Actually try to use the double-buffer extension?
 */

// #define USE_XDBE HAVE_XDBE

/*
 * HAVE_XFIXES:
 *
 * Do we have the X fixes extension?
 */

#define HAVE_XFIXES 0

/*
 * HAVE_XCURSOR:
 *
 * Do we have the X cursor library?
 */

#define HAVE_XCURSOR 0

/*
 * HAVE_XRENDER:
 *
 * Do we have the X render library?
 */

#define HAVE_XRENDER 0

/*
 * HAVE_X11_XREGION_H:
 *
 * Do we have the X11 Xregion.h header file ?
 */

#define HAVE_X11_XREGION_H 0

/*
 * __APPLE_QUARTZ__:
 *
 * All Apple implementations are now based on Quartz and Cocoa,
 * so this flag should always be on for Mac OS X. This flag has
 * no meaning on operating systems other than Mac OS X.
 */

/* #undef __APPLE_QUARTZ__ */


/*
 * USE_X11
 *
 * Should we use X11 for the current platform
 *
 */

#undef USE_X11

/*
 * USE_SDL
 *
 * Should we use SDL for the current platform
 * *FIXME* Not yet implemented in configure !
 *
 */

/* #undef USE_SDL */

/*
 * FL_PORTING
 *
 * A little helper that points to locations in the core that still need
 * to be ported to the core driver setup.
 * *FIXME* Not yet implemented in configure !
 */

/* #undef FL_PORTING */

/*
 * HAVE_OVERLAY:
 *
 * Use the X overlay extension?  FLTK will try to use an overlay
 * visual for Fl_Overlay_Window, the Gl_Window overlay, and for the
 * menus.  Setting this to zero will remove a substantial amount of
 * code from FLTK.  Overlays have only been tested on SGI servers!
 */

#define HAVE_OVERLAY 0

/*
 * HAVE_GL_OVERLAY:
 *
 * It is possible your GL has an overlay even if X does not.  If so,
 * set this to 1.
 */

#define HAVE_GL_OVERLAY HAVE_OVERLAY 0

/*
 * WORDS_BIGENDIAN:
 *
 * Byte order of your machine: 1 = big-endian, 0 = little-endian.
 */

#ifdef __APPLE__
#include <mac_endianness.h>
#else
#define WORDS_BIGENDIAN 0
#endif

/*
 * U16, U32, U64:
 *
 * Types used by fl_draw_image.  One of U32 or U64 must be defined.
 * U16 is optional but FLTK will work better with it!
 */

#define U16 unsigned short
#define U32 unsigned
#define U64 unsigned long

/*
 * HAVE_DIRENT_H, HAVE_SYS_NDIR_H, HAVE_SYS_DIR_H, HAVE_NDIR_H,
 * HAVE_SCANDIR, HAVE_SCANDIR_POSIX:
 *
 * Where is <dirent.h> (used only by fl_file_chooser and scandir).
 */

#define HAVE_DIRENT_H 1
/* #undef HAVE_SYS_NDIR_H */
/* #undef HAVE_SYS_DIR_H */
/* #undef HAVE_NDIR_H */
// #define HAVE_SCANDIR 1
// #define HAVE_SCANDIR_POSIX 1

/*
 * Possibly missing sprintf-style functions:
 */

#define HAVE_VSNPRINTF 1
#define HAVE_SNPRINTF 1

/*
 * String functions and headers...
 */

#define HAVE_STRINGS_H 1
#define HAVE_STRCASECMP 1
/* #undef HAVE_STRLCAT */
/* #undef HAVE_STRLCPY */

/*
 * Do we have POSIX locale support?
 */

#define HAVE_LOCALE_H 0
#define HAVE_LOCALECONV 0

/*
 * HAVE_SYS_SELECT_H:
 *
 * Whether or not select() call has its own header file.
 */

#define HAVE_SYS_SELECT_H 0

/*
 * HAVE_SYS_STDTYPES_H:
 *
 * Whether or not we have the <sys/stdtypes.h> header file.
 */

#undef HAVE_SYS_STDTYPES_H

/*
 * USE_POLL:
 *
 * Use the poll() call provided on GNU/Linux and Irix instead of select()
 */

#define USE_POLL 0

/*
 * Do we have various image libraries?
 */

#define HAVE_LIBPNG 1
#define HAVE_LIBZ 1
#define HAVE_LIBJPEG 1
#undef FLTK_USE_NANOSVG 

/*
 * FLTK_USE_CAIRO
 *
 * Do we have the cairo library available and want extended cairo use in FLTK ?
 * This implies to link cairo.lib in all FLTK based apps.
 */

#undef FLTK_USE_CAIRO

/*
 * FLTK_HAVE_CAIRO
 *
 * Do we have the cairo library available?
 */

#undef FLTK_HAVE_CAIRO

/*
 * Which header file do we include for libpng?
 */

#define HAVE_PNG_H 1
/* #undef HAVE_LIBPNG_PNG_H */

/*
 * Do we have the png_xyz() functions?
 */

#define HAVE_PNG_GET_VALID 1
#define HAVE_PNG_SET_TRNS_TO_ALPHA 1

/*
 * Do we have POSIX threading?
 */

// #define HAVE_PTHREAD 1
// #define HAVE_PTHREAD_H 1

/*
 * Do we have the ALSA library?
 */

// #define HAVE_ALSA_ASOUNDLIB_H 1

/*
 * Do we have the long long type?
 */

#define HAVE_LONG_LONG 1

#ifdef HAVE_LONG_LONG
#  define FLTK_LLFMT	"%lld"
#  define FLTK_LLCAST	(long long)
#else
#  define FLTK_LLFMT	"%ld"
#  define FLTK_LLCAST	(long)
#endif /* HAVE_LONG_LONG */

/*
 * Do we have the dlsym() function and header?
 */

// #define HAVE_DLFCN_H 1
// #define HAVE_DLSYM 1

/*
 * Do we want print support?
 */

/* #undef FL_NO_PRINT_SUPPORT */

/*
 * Do we want filename handling and a filechooser?
 * *FIXME* Not yet implemented in configure !
 */

/* #undef FL_CFG_NO_FILESYSTEM_SUPPORT */

/*
 * End of "$Id: configh.in 12413 2017-09-03 13:14:25Z manolo $".
 */
