/*
 * typesplt.h
 *
 * "$Id: platform_types.h 12196 2017-03-13 23:31:38Z AlbrechtS $"
 *
 * Copyright 2017-2018 The fltkal authors
 * Copyright 2016 by Bill Spitzak and others.
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
/** \file
 Definitions of platform-dependent types.
 The exact nature of these types varies with the platform.
 Therefore, portable FLTK applications should not assume these types
 have a specific size, or that they are pointers.
 */

#ifdef FL_DOXYGEN

/** An integral type large enough to store a pointer or a long value.
 A pointer value can be safely cast to fl_intptr_t, and later cast back
 to its initial pointer type without change to the pointer value.
 A variable of type fl_intptr_t can also store a long int value. */
typedef opaque fl_intptr_t;
/** An unsigned integral type large enough to store a pointer or an unsigned long value.
 A pointer value can be safely cast to fl_uintptr_t, and later cast back
 to its initial pointer type without change to the pointer value.
 A variable of type fl_uintptr_t can also store an unsigned long int value. */
typedef opaque fl_uintptr_t;

typedef opaque Fl_Offscreen; /**< an offscreen drawing buffer */
typedef opaque Fl_Bitmask; /**< mask */
typedef opaque Fl_Region; /**< a region made of several rectangles */
typedef opaque FL_SOCKET; /**< socket or file descriptor */
typedef opaque GLContext; /**< an OpenGL graphics context, into which all OpenGL calls are rendered */

#  define FL_COMMAND  opaque   /**< An alias for FL_CTRL on Windows and X11, or FL_META on MacOS X */
#  define FL_CONTROL  opaque   /**< An alias for FL_META on Windows and X11, or FL_CTRL on MacOS X */

#else

#ifndef FL_PLATFORM_TYPES_H
#define FL_PLATFORM_TYPES_H

/* Platform-dependent types are defined here.
  These types must be defined by any platform:
  Fl_Offscreen, Fl_Bitmask, Fl_Region, FL_SOCKET, GLContext, struct dirent, struct stat,
  fl_intptr_t, fl_uintptr_t

  NOTE: *FIXME* AlbrechtS 13 Apr 2016 (concerning FL_SOCKET)
  ----------------------------------------------------------
    The Fl::add_fd() API is partially inconsistent because some of the methods
    explicitly use 'int', but the callback typedefs use FL_SOCKET. With the
    definition of FL_SOCKET below we can have different data sizes and
    different signedness of socket numbers on *some* platforms.
 */

#ifdef _WIN64

#if defined(_MSC_VER)
# include <stddef.h>  /* M$VC */
#else
# include <stdint.h>
#endif

typedef intptr_t fl_intptr_t;
typedef uintptr_t fl_uintptr_t;

#else /* ! _WIN64 */

typedef long fl_intptr_t;
typedef unsigned long fl_uintptr_t;

#endif /* _WIN64 */


#ifdef __APPLE__
typedef struct CGContext* Fl_Offscreen;
typedef struct CGImage* Fl_Bitmask;
typedef struct flCocoaRegion* Fl_Region;
typedef int FL_SOCKET;
#ifdef __OBJC__
  @class NSOpenGLContext;
  typedef NSOpenGLContext* GLContext;
#elif defined(__cplusplus)
  typedef class NSOpenGLContext* GLContext;
#endif /* __OBJC__ */

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#  define FL_COMMAND	FL_META
#  define FL_CONTROL 	FL_CTRL

#elif defined(_WIN32)
typedef struct HBITMAP__ *HBITMAP;
typedef HBITMAP Fl_Offscreen;
typedef HBITMAP Fl_Bitmask;
typedef struct HRGN__ *Fl_Region;
# if defined(_WIN64) && defined(_MSC_VER)
typedef  unsigned __int64 FL_SOCKET;	/* *FIXME* - FL_SOCKET (see above) */
# else
typedef  int FL_SOCKET;
# endif
typedef struct HGLRC__ *GLContext;
#include <sys/stat.h>
struct dirent {char d_name[1];};

#elif defined(FL_PORTING)
# pragma message "FL_PORTING: define OS-dependent types"
typedef void* Fl_Offscreen;
typedef void* Fl_Bitmask;
typedef void *Fl_Region;
typedef int FL_SOCKET;
typedef void *GLContext;
# pragma message "FL_PORTING: define struct dirent and implement scandir() for the platform"
struct dirent {char d_name[1];};
# pragma message "FL_PORTING: define struct stat and implement Fl_XXX_System_Driver::stat() for the platform"
struct stat { /* the FLTK source code uses part of the stat() API */
  unsigned st_mode;
  unsigned st_size;
};
#define        S_IFDIR  0040000  /* directory */
#define        S_IFREG  0100000  /* regular */

#else /* X11 */

typedef unsigned long Fl_Offscreen;
typedef unsigned long Fl_Bitmask;
typedef struct _XRegion *Fl_Region;
typedef int FL_SOCKET;
typedef struct __GLXcontextRec *GLContext;
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#endif /* __APPLE__ */


#ifndef __APPLE__
#  define FL_COMMAND	FL_CTRL   /**< An alias for FL_CTRL on Windows and X11, or FL_META on MacOS X */
#  define FL_CONTROL	FL_META   /**< An alias for FL_META on Windows and X11, or FL_CTRL on MacOS X */
#endif

#endif /* FL_PLATFORM_TYPES_H */

#endif // FL_DOXYGEN

/*
 * End of "$Id: platform_types.h 12665 2018-02-12 07:18:36Z manolo $".
 */
