/*
 * cfg_lib.h
 *
 * "$Id: config_lib.h 12969 2018-06-23 17:04:18Z matt $"
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
 *
 */
#ifndef FL_CONFIG_LIB_H
#define FL_CONFIG_LIB_H

#include "config.h"


/* find the right graphics configuration */
#if !defined(FL_CFG_GFX_XLIB) && !defined(FL_CFG_GFX_QUARTZ) && !defined(FL_CFG_GFX_GDI)

#ifdef __APPLE__ /* default configurations */
# define FL_CFG_GFX_QUARTZ
# ifdef HAVE_GL
#  define FL_CFG_GFX_OPENGL
# endif
#elif defined(_WIN32)
# define FL_CFG_GFX_GDI
# ifdef HAVE_GL
#  define FL_CFG_GFX_OPENGL
# endif
#elif defined(USE_X11) /* X11 */
# define FL_CFG_GFX_XLIB
# ifdef HAVE_GL
#  define FL_CFG_GFX_OPENGL
# endif
#elif defined(USE_ALLEGRO)
# define FL_CFG_GFX_ALLEGRO
#endif

#endif


/* find the right printer driver configuration */
#if !defined(FL_CFG_PRN_PS) && !defined(FL_CFG_PRN_QUARTZ) && !defined(FL_CFG_PRN_WIN32)

#ifdef __APPLE__ /* default configurations */
# define FL_CFG_PRN_QUARTZ
#elif defined(_WIN32)
# define FL_CFG_PRN_WIN32
#elif defined(USE_X11) /* X11 */
# define FL_CFG_PRN_PS
#endif

#endif


/* find the right window manager configuration */
#if !defined(FL_CFG_WIN_X11) && !defined(FL_CFG_WIN_COCOA) && !defined(FL_CFG_WIN_WIN32)

#ifdef __APPLE__ /* default configurations */
# define FL_CFG_WIN_COCOA
#elif defined(_WIN32)
# define FL_CFG_WIN_WIN32
#elif defined(USE_X11) /* X11 */
# define FL_CFG_WIN_X11
#elif defined(USE_ALLEGRO)
# define FL_CFG_WIN_ALLEGRO
#endif

#endif


/* find the right system configuration */
#if !defined(FL_CFG_SYS_POSIX) && !defined(FL_CFG_SYS_WIN32)

#ifdef __APPLE__ /* default configurations */
# define FL_CFG_SYS_POSIX
#elif defined(_WIN32)
# define FL_CFG_SYS_WIN32
#elif defined(USE_X11) /* X11 */
# define FL_CFG_SYS_POSIX
#elif defined(USE_ALLEGRO)
# define FL_CFG_SYS_ALLEGRO
#endif

#endif


#endif

/*
 * End of "$Id: config_lib.h 11716 2016-05-08 06:42:57Z manolo $".
 */
