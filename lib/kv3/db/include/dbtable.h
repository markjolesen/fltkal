/*
  dbtable.h

  Copyright (c) 2020 Dante University Foundation and Contributors

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
#if !defined(__dbtable_h__)

#  include "dict.h"
#  include "text.h"

struct kv3_db_table
{
  unsigned char *m_lang;
  int m_handle;
  struct kv3_dict m_header;
  struct kv3_text m_text;
  size_t m_record;
};

#  if defined(__cplusplus)
extern "C"
{
#  endif

  extern void
    kv3_db_table_assign(struct kv3_db_table *const);

  extern void
    kv3_db_table_discharge(struct kv3_db_table *const);

  extern void
    kv3_db_table_open(struct kv3_db_table *const,
                      unsigned char const *,
                      unsigned char const *);

  extern void
    kv3_db_table_read(struct kv3_db_table *const, size_t const);

#  if defined(__cplusplus)
}
#  endif

#  define __dbtable_h__
#endif
