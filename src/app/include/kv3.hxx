/*
  kv3.hxx

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
#if !defined(__kv3_h__)

#  include "dbtrove.h"
//
#  if !defined(__DOS__)
#    include <FL/Fl_Browser.H>
#    include <FL/Fl_Tree.H>
#  else
#    include <fl/browser.h>
#    include <fl/tree.h>
#  endif

namespace kv3
{
extern int
  filter(unsigned char const *, unsigned char const *);

extern void
  browser_load(Fl_Browser &, struct kv3_db_inf const &);

extern void
  browser_load(Fl_Browser &, struct kv3_db_inf const &, unsigned char const *);

extern void
  tree_load(Fl_Tree &, struct kv3_db_trove const &);

extern int
  menu_popup(size_t &, size_t &, struct kv3_text_set &);

extern void
  text_propogate(struct kv3_db_trove &,
                 size_t const,
                 size_t const,
                 size_t const,
                 size_t const,
                 struct kv3_db_datum const &);

}; // namespace kv3

#  define __kv3_h__
#endif
