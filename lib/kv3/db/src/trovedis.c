/*
  kv3_db_trove_discharge.c

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
#include "mstdlib.h"
#include "mstring.h"
/**/
#include "dbtrove.h"

extern void
  kv3_db_trove_discharge(struct kv3_db_trove *const io_trove)
{
  struct kv3_db_datum *l_head;
  struct kv3_db_datum *l_tail;

  do
    {
      if (0 == io_trove)
        {
          break;
        }

      mjo_free((void **const) & (*io_trove).m_prefix);
      l_head = (*io_trove).m_head;

      do
        {
          if (0 == l_head)
            {
              break;
            }

          l_tail = (*l_head).m_next;
          kv3_db_datum_discharge(l_head);
          mjo_free((void **const) & l_head);
          l_head = l_tail;
        }
      while (1);

      memset(io_trove, 0, sizeof(*io_trove));
    }
  while (0);

  return;
}
