/*
  kv3_db_xref_discharge.c

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
#include "mfcntl.h"
#include "mstdlib.h"
#include "mstring.h"
#include "munistd.h"
/**/
#include "dbxref.h"

extern void
  kv3_db_xref_discharge(struct kv3_db_xref *const io_xref)
{
  struct kv3_db_xref_table *l_table;
  struct kv3_db_xref_table *l_tail;

  do
    {
      if (0 == io_xref)
        {
          break;
        }

      l_table = (*io_xref).m_head;

      do
        {
          if (0 == l_table)
            {
              break;
            }

          mjo_free((void **const) & (*l_table).m_lang);
          close((*l_table).m_handle);

          l_tail = (*l_table).m_next;
          mjo_free((void **const) & l_table);
          l_table = l_tail;
        }
      while (1);

      memset(io_xref, 0, sizeof(*io_xref));
    }
  while (0);

  return;
}
