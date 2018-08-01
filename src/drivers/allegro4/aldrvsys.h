// aldrvsys.h
//
// Allegro4 System Driver for the Fast Light Tool Kit (FLTK)
//
// Copyright 2017-2018 The fltkal authors
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
#if !defined(FL_ALLEGRO_SYSTEM_DRIVER_H)

#include "../..//drvsys.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#if defined(__DJGPP__)
#include <dos.h>
#else
#include <sys/time.h>
#endif

class FL_EXPORT Fl_Allegro_System_Driver : public Fl_System_Driver
{

public:

    Fl_Allegro_System_Driver();

    virtual ~Fl_Allegro_System_Driver();

    virtual char *getenv(const char *v);

    virtual int putenv(char *v);

    virtual int open(const char *f, int oflags, int pmode);

    virtual int system(const char *cmd);

    virtual int chmod(const char *f, int mode);

    virtual int access(const char *f, int mode);

    virtual int stat(const char *f, struct stat *b);

    virtual char *getcwd(char *b, int l);

    virtual int chdir(const char *path);

    virtual int unlink(const char *fname);

    virtual int mkdir(const char *f, int mode);

    virtual int rmdir(const char *f);

    virtual int rename(const char *f, const char *n);

    virtual int colon_is_drive();

    virtual int dot_file_hidden();

    virtual int case_insensitive_filenames();

    virtual void gettime(time_t *sec, int *usec);

    virtual int filename_list(const char *d, dirent ***list, int (*sort)(struct dirent **, struct dirent **));

    virtual void copy(const char *stuff, int len, int clipboard, const char *type);

    virtual void paste(Fl_Widget &receiver, int clipboard, const char *type);

    virtual int clipboard_contains(const char *type);

    virtual void clipboard_notify_change();

protected:

    struct blob
    {
        void *data;
        size_t alloc_length;
        size_t data_length;
        char const *type;
    };

    struct blob clipboard_[2]; // clip[0]=selection text clip[1]=clipboard

};

inline char *Fl_Allegro_System_Driver::getenv(const char *v)
{
    return ::getenv(v);
}

inline int Fl_Allegro_System_Driver::putenv(char *v)
{
    return ::putenv(v);
}

inline int Fl_Allegro_System_Driver::open(const char *f, int oflags, int)
{
    return ::open(f, oflags);
}

inline int Fl_Allegro_System_Driver::system(const char *cmd)
{
    return ::system(cmd);
}

inline int Fl_Allegro_System_Driver::chmod(const char *f, int mode)
{
    return ::chmod(f, mode);
}

inline int Fl_Allegro_System_Driver::access(const char *f, int mode)
{
    return ::access(f, mode);
}

inline int Fl_Allegro_System_Driver::stat(const char *f, struct stat *b)
{
    return ::stat(f, b);
}

inline char *Fl_Allegro_System_Driver::getcwd(char *b, int l)
{
    return ::getcwd(b, l);
}

inline int Fl_Allegro_System_Driver::chdir(const char *path)
{
    return ::chdir(path);
}

inline int Fl_Allegro_System_Driver::unlink(const char *fname)
{
    return ::unlink(fname);
}

inline int Fl_Allegro_System_Driver::mkdir(const char *f, int mode)
{
    return ::mkdir(f, mode);
}

inline int Fl_Allegro_System_Driver::rmdir(const char *f)
{
    return ::rmdir(f);
}

inline int Fl_Allegro_System_Driver::rename(const char *f, const char *n)
{
    return ::rename(f, n);
}

inline int Fl_Allegro_System_Driver::colon_is_drive()
{
#if defined(__DJGPP__)
    return 1;
#else
    return 0;
#endif
}

inline int Fl_Allegro_System_Driver::dot_file_hidden()
{
    return 0;
}

inline int Fl_Allegro_System_Driver::case_insensitive_filenames()
{
#if defined(__DJGPP__)
    return 1;
#else
    return 0;
#endif
}

inline void Fl_Allegro_System_Driver::gettime(time_t *sec, int *usec)
{
#if defined(__DJGPP__)
    struct time tv;
    ::gettime(&tv);
    (*sec) = tv.ti_sec;
    (*usec) = 0;
#else
    struct timeval tv;
    ::gettimeofday(&tv, NULL);
    (*sec) = tv.tv_sec;
    (*usec) = tv.tv_usec;
#endif
}

extern "C" int
fl_scandir(const char *dir, struct dirent ***namelist,
           int (*sel)(struct dirent *),
           int (*compar)(struct dirent **, struct dirent **));

inline int Fl_Allegro_System_Driver::filename_list(const char *d, dirent ***list, int (*sort)(struct dirent **, struct dirent **))
{
    return fl_scandir(d, list, 0, sort);
}

#define FL_ALLEGRO_SYSTEM_DRIVER_H
#endif
