/*
  dbxref.h

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
#if !defined(__dbxref_h__)

#  include "dictxref.h"
#  include "mstddef.h"

struct kv3_db_xref_table
{
  unsigned char *m_lang;
  int m_handle;
  struct kv3_dict_xref m_xref;
  struct kv3_db_xref_table *m_next;
};

struct kv3_db_xref
{
  struct kv3_db_xref_table *m_head;
  struct kv3_db_xref_table *m_tail;
};

#  if defined(__cplusplus)
extern "C"
{
#  endif

  extern void
    kv3_db_xref_assign(struct kv3_db_xref *const);

  extern void
    kv3_db_xref_discharge(struct kv3_db_xref *const);

  extern void
    kv3_db_xref_open(struct kv3_db_xref *const,
                     unsigned char const *,
                     unsigned char const *);

  extern void
    kv3_db_xref_read(struct kv3_db_xref *const, size_t const);

#  if defined(__cplusplus)
}
#  endif

#  define __dbxref_h__
#endif
