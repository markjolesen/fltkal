/*
  app_open_cb.cxx

  Copyright (c) 2014, 2020 Dante University Foundation and Contributors

    Permission to use, copy, modify, and distribute this software for any
    purpose with or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

  This file is part of kv3

  DANTE UNIVERSITY OF AMERICA FOUNDATION INC
  P.O. Box 812158
  Wellesley, MA 02482
  USA
  <http://danteuniversity.org/>
*/
#include "mr7.h"
#include "mstdlib.h"
#include "mstring.h"
//
#include "dbsuffix.h"
//
#include "app.hxx"
//
#if !defined(__DOS__)
#  include <FL/Fl_Native_File_Chooser.H>
#else
#  include <fl/filechn.h>
#endif

#define _(msg) msg

static void
  kv3_file_open_chooser(unsigned char **o_path)
{
  Fl_Native_File_Chooser l_browser;

  l_browser.title(_("open database"));
  l_browser.type(Fl_Native_File_Chooser::BROWSE_FILE);
  l_browser.options(Fl_Native_File_Chooser::NO_OPTIONS);
  l_browser.filter("kv3\t*." kv3_db_suffix_table);

  int l_rc = l_browser.show();

  if (0 == l_rc && 0 < l_browser.count())
    {
      unsigned char const *l_name
        = reinterpret_cast<unsigned char const *>(l_browser.filename());
      mjo_strdup(o_path, l_name);
    }
  else
    {
      (*o_path) = 0;
    }

  return;
}

void
  kv3::app::open_cb(Fl_Widget *io_widget, void *io_user)
{
  unsigned char *l_path;

  kv3_file_open_chooser(&l_path);

  if (l_path)
    {
      unsigned char *l_ptr = reinterpret_cast<unsigned char *>(
        strrchr(reinterpret_cast<char *>(l_path), mjo_r7_dirsep));

      if (l_ptr)
        {
          *l_ptr = 0;
        }

      kv3::app &l_app = (*reinterpret_cast<kv3::app *>(io_user));
      l_app.open(l_path);
      mjo_free(reinterpret_cast<void **>(&l_path));
    }

  return;
}
