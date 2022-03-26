/*
  kv3_db_table_assign.c

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
#include "mstring.h"
/**/
#include "dbtable.h"

extern void
  kv3_db_table_assign(struct kv3_db_table *const o_table)
{
  size_t l_col;

  do
    {
      if (0 == o_table)
        {
          break;
        }

      memset(o_table, 0, sizeof(*o_table));

      (*o_table).m_handle = -1;
      (*o_table).m_record = (size_t)-1;

      for (l_col = 0; kv3_dict_row_cell_count_used > l_col; l_col++)
        {
          (*o_table).m_text.m_len_x[l_col] = 180;
        }
    }
  while (0);

  return;
}
