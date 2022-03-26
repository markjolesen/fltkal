/*
  dbdatum.h

  Copyright (c) 2008-2010, 2014, 2020 Dante University Foundation and Contributors

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
#if !defined(__dbdatum_h__)

#  include "dbinf.h"
#  include "dbtable.h"
#  include "dbxref.h"

struct kv3_db_datum
{
  struct kv3_db_table m_table;
  struct kv3_db_inf m_inf;
  struct kv3_db_xref m_xref;
  struct kv3_db_datum *m_next;
  struct kv3_db_datum *m_prev;
};

#  if defined(__cplusplus)
extern "C"
{
#  endif

  extern void
    kv3_db_datum_assign(struct kv3_db_datum *const);

  extern void
    kv3_db_datum_discharge(struct kv3_db_datum *const);

  extern void
    kv3_db_datum_open(struct kv3_db_datum *const,
                      unsigned char const *,
                      unsigned char const *);

  extern void
    kv3_db_datum_read(struct kv3_db_datum *const, size_t const);

#  if defined(__cplusplus)
}
#  endif

#  define __dbdatum_h__
#endif
