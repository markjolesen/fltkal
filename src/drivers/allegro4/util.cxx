// util.cxx
//
// Utility code for the Fast Light Tool Kit (FLTK)
//
// Copyright 2018, 2021 The fltkal authors
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
#include "util.h"

#include <sys/stat.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fl/filename.h>

class util
{
private:
  char program_path_[FL_PATH_MAX];

  void
    init_once_program_path();

public:
  util();

  ~util();

  char const *
    program_path() const;
};

#undef ARGV0

#if defined(__DJGPP__)
extern char **__crt0_argv;
#  define ARGV0 __crt0_argv[0]
#elif defined(__WATCOMC__)
#  define ARGV0 __argv[0]
#endif

void
  util::init_once_program_path()
{
#if defined(ARGV0)
  strlcpy(program_path_, ARGV0, FL_PATH_MAX);
#elif defined(__LINUX__)
  readlink("/proc/self/exe", program_path_, FL_PATH_MAX);
#else
  getcwd(program_path_, FL_PATH_MAX);
#endif
  size_t len = strlen(program_path_);
  char *eos = &program_path_[len - 1];

  do
    {
      if (0 == len)
        {
          eos[0] = 0;
          break;
        }

      if (*eos == ':')
        {
          eos[1] = 0;
          break;
        }

      if (*eos == '\\' || *eos == '/')
        {
          eos[0] = 0;
          break;
        }

      len--;
      eos--;
    }
  while (1);

  return;
}

util::util()
{
  init_once_program_path();
  return;
}

util::~util()
{
  return;
}

char const *
  util::program_path() const
{
  return program_path_;
}

static util _util;

extern char const *
  program_path()
{
  return _util.program_path();
}

extern char const *
  filename_extract(char const *path)
{
  size_t size = strlen(path);
  char const *filename = path;
  char const *eos = &path[size - 1];

  do
    {
      if (0 == size)
        {
          break;
        }

#if defined(__DOS__)
      if (*eos == '\\' || *eos == ':')
#else
      if (*eos == '/')
#endif
        {
          filename = &eos[1];
          break;
        }

      size--;
      eos--;
    }
  while (1);

  return filename;
}

#if defined(__DJGPP__)
extern unsigned short _djstat_flags;
#endif

extern Fl_Preferences *
  fltkcfg()
{
  Fl_Preferences *pref = 0;
#if defined(__DJGPP__)
  unsigned short flags_saved = _djstat_flags;
  _djstat_flags = 0;
#endif
  struct stat sbuf;
  int rc;
  char *path = 0;

  do
    {
      rc = stat("fltk.cfg", &sbuf);

      if (0 == rc && S_ISREG(sbuf.st_mode))
        {
          pref = new Fl_Preferences("fltk.cfg", 0, 0);
          break;
        }

      path = reinterpret_cast<char *>(malloc(FL_PATH_MAX));
      char const *prgpath = program_path();
      snprintf(path, FL_PATH_MAX, "%s/fltk.cfg", prgpath);

      rc = stat(path, &sbuf);

      if (0 == rc && S_ISREG(sbuf.st_mode))
        {
          pref = new Fl_Preferences(path, 0, 0);
          break;
        }

      pref = new Fl_Preferences(Fl_Preferences::USER, "fltk", "fltk");

      rc = stat(pref->getFileName(), &sbuf);

      if (0 == rc && S_ISREG(sbuf.st_mode))
        {
          break;
        }

      delete pref;
      pref = new Fl_Preferences(Fl_Preferences::SYSTEM, "fltk", "fltk");
    }
  while (0);

#if defined(__DJGPP__)
  _djstat_flags = flags_saved;
#endif

  free(path);

  return pref;
}
