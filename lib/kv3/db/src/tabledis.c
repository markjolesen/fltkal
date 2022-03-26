/*
  kv3_db_table_discharge.c

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
#include "mfcntl.h"
#include "mstdlib.h"
#include "mstring.h"
#include "munistd.h"
/**/
#include "dbtable.h"

extern void
  kv3_db_table_discharge(struct kv3_db_table *const io_table)
{
  if (io_table)
    {
      mjo_free((void **const) & (*io_table).m_lang);

      if (-1 != (*io_table).m_handle)
        {
          close((*io_table).m_handle);
        }

      memset(io_table, 0, sizeof(*io_table));

      (*io_table).m_handle = -1;
      (*io_table).m_record = (size_t)-1;
    }

  return;
}
