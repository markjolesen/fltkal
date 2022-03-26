/*
  kv3_dict_set_external.c

  Copyright (c) 2008-2010, 2019 Dante University Foundation and Contributors

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
#include "mstddef.h"
#include "mstring.h"
/**/
#include "dict.h"

extern void
  kv3_dict_set_external(struct kv3_dict *const io_dict)
{
  struct kv3_dict_row *l_row;
  size_t l_slot;

  do
    {
      if (0 == io_dict)
        {
          break;
        }

      l_row = &(*io_dict).m_row[0];
      l_slot = 0;

      do
        {
          if (kv3_dict_row_count_used <= l_slot)
            {
              break;
            }

          kv3_dict_row_set_external(l_row);

          l_row++;
          l_slot++;
        }
      while (1);

      do
        {
          if (kv3_dict_row_count <= l_slot)
            {
              break;
            }

          memset(l_row, 0, sizeof(*l_row));

          kv3_dict_row_set_external(l_row);
          l_row++;
          l_slot++;
        }
      while (1);
    }
  while (0);

  return;
}
