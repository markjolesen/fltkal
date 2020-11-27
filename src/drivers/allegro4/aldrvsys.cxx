// aldrvsys.cxx
//
// Allegro4 System Driver for the Fast Light Tool Kit (FLTK)
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2017 by Bill Spitzak and others.
// (portions derived from Fl_x.cxx)
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
#include "aldrvsys.h"

#include <stdlib.h>
#include <string.h>

#include "../../flstring.h"
#include <fl/widget.h>

Fl_System_Driver *
  Fl_System_Driver::newSystemDriver()
{
  return new Fl_Allegro_System_Driver();
}

Fl_Allegro_System_Driver::Fl_Allegro_System_Driver() : Fl_System_Driver()
{
  memset(&clipboard_[0], 0, sizeof(clipboard_));
  return;
}

Fl_Allegro_System_Driver::~Fl_Allegro_System_Driver()
{
}

void
  Fl_Allegro_System_Driver::newUUID(char *uuidBuffer)
{
  // void Fl_X11_System_Driver::newUUID(char *uuidBuffer)
  // warning Unix implementation of Fl_Preferences::newUUID() incomplete!
  unsigned char b[16];
  unsigned char *p = &b[0];
  time_t t = time(0); // first 4 byte
  *p++ = (unsigned char)t;
  *p++ = (unsigned char)(t >> 8);
  *p++ = (unsigned char)(t >> 16);
  *p++ = (unsigned char)(t >> 24);
  int r = rand(); // four more bytes
  *p++ = (unsigned char)r;
  *p++ = (unsigned char)(r >> 8);
  *p++ = (unsigned char)(r >> 16);
  *p++ = (unsigned char)(r >> 24);
  unsigned long a = (unsigned long)&t; // four more bytes
  *p++ = (unsigned char)a;
  *p++ = (unsigned char)(a >> 8);
  *p++ = (unsigned char)(a >> 16);
  *p++ = (unsigned char)(a >> 24);
  // Now we try to find 4 more "random" bytes. We extract the
  // lower 4 bytes from the address of t - it is created on the
  // stack so *might* be in a different place each time...
  // This is now done via a union to make it compile OK on 64-bit systems.
  union
  {
    void *pv;
    unsigned char a[sizeof(void *)];
  } v;
  v.pv = (void *)(&t);
  *p++ = v.a[0];
  *p++ = v.a[1];
  *p++ = v.a[2];
  *p++ = v.a[3];
  // last four bytes
  *p++ = (r % 'F');
  *p++ = (r % 'D');
  *p++ = (r % 'O');
  *p++ = (r % 'S');
  sprintf(uuidBuffer,
          "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%"
          "02X",
          b[0],
          b[1],
          b[2],
          b[3],
          b[4],
          b[5],
          b[6],
          b[7],
          b[8],
          b[9],
          b[10],
          b[11],
          b[12],
          b[13],
          b[14],
          b[15]);
  return;
}

char const *
  Fl_Allegro_System_Driver::preference_ext() const
{
  return "cfg";
}

#if defined(__DJGPP__)

extern char **__crt0_argv;

char *
  Fl_Allegro_System_Driver::preference_rootnode(Fl_Preferences *prefs,
                                                Fl_Preferences::Root root,
                                                const char *vendor,
                                                const char *application)
{
  static char filename[FL_PATH_MAX];

  if (':' == __crt0_argv[0][1])
    {
      filename[0] = __crt0_argv[0][0];
      filename[1] = ':';
      filename[2] = 0;
    }

  else
    {
      filename[0] = 0;
    }

  strlcat(filename, "\\config", sizeof(filename));

  switch (root)
    {
    case Fl_Preferences::USER:
      strlcat(filename, "\\fltk\\user", sizeof(filename));
      break;

    case Fl_Preferences::SYSTEM:
      strlcat(filename, "\\fltk\\system", sizeof(filename));
      break;
    }

  snprintf(filename + strlen(filename),
           sizeof(filename) - strlen(filename),
           "\\%s\\%s.%s",
           vendor,
           application,
           preference_ext());

  return filename;
}

#else

char *
  Fl_Allegro_System_Driver::preference_rootnode(Fl_Preferences *prefs,
                                                Fl_Preferences::Root root,
                                                const char *vendor,
                                                const char *application)
{
  static char filename[FL_PATH_MAX];
  filename[0] = 0;
  const char *e;

  switch (root)
    {
    case Fl_Preferences::USER:
      if ((e = getenv("HOME")) != NULL)
        {
          strlcpy(filename, e, sizeof(filename));

          if (filename[strlen(filename) - 1] != '/')
            {
              strlcat(filename, "/.fltk/", sizeof(filename));
            }

          else
            {
              strlcat(filename, ".fltk/", sizeof(filename));
            }

          break;
        }

    case Fl_Preferences::SYSTEM:
      strcpy(filename, "/etc/fltk/");
      break;
    }

  snprintf(filename + strlen(filename),
           sizeof(filename) - strlen(filename),
           "%s/%s.%s",
           vendor,
           application,
           preference_ext());

  return filename;
}

#endif

void
  Fl_Allegro_System_Driver::copy(const char *stuff,
                                 int len,
                                 int clipboard,
                                 const char *type)
{
  do
    {
      if (0 == stuff)
        {
          break;
        }

      if (0 > len)
        {
          break;
        }

      if (0 == type)
        {
          break;
        }

      int rc = strcmp(Fl::clipboard_plain_text, type);

      if (rc)
        {
          break;
        }

      if (clipboard >= 2)
        {
          copy(stuff, len, 0, type);
          copy(stuff, len, 1, type);
        }

      struct blob *blob = &clipboard_[clipboard];

      if (static_cast<size_t>(len + 1) > blob->alloc_length)
        {
          void *data = realloc(blob->data, static_cast<size_t>(len + 1));

          if (0 == data)
            {
              blob->data_length = 0;
              break;
            }

          blob->data = data;
          blob->alloc_length = static_cast<size_t>(len + 1);
        }

      memset(blob->data, 0, blob->alloc_length);
      memcpy(blob->data, stuff, static_cast<size_t>(len));
      blob->data_length = static_cast<size_t>(len);
      blob->type = type;
    }
  while (0);

  return;
}

void
  Fl_Allegro_System_Driver::paste(Fl_Widget &receiver,
                                  int clipboard,
                                  const char *type)
{
  do
    {
      if (0 == type)
        {
          break;
        }

      if (0 > clipboard)
        {
          break;
        }

      if (2 <= clipboard)
        {
          break;
        }

      int rc = strcmp(Fl::clipboard_plain_text, type);

      if (rc)
        {
          break;
        }

      struct blob *blob = &clipboard_[clipboard];

      if (0 == blob->data_length)
        {
          break;
        }

      Fl::e_text = reinterpret_cast<char *>(blob->data);
      Fl::e_length = blob->data_length;
      receiver.handle(FL_PASTE);
    }
  while (0);

  return;
}

int
  Fl_Allegro_System_Driver::clipboard_contains(const char *type)
{
  return 0;
}

void
  Fl_Allegro_System_Driver::clipboard_notify_change()
{
  return;
}
