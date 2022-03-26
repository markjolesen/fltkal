/*
  kv3_text_link_parse.c

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
#include "mstddef.h"
#include "mstring.h"
/**/
#include "dictrow.h"
#include "textcell.h"

#ifdef __cplusplus
extern "C"
{
#endif

  extern void
    kv3_text_link_parse(struct kv3_text_link *const, unsigned char **const);

#ifdef __cplusplus
}
#endif

extern void
  kv3_text_link_parse(struct kv3_text_link *const io_link,
                      unsigned char **const io_block)
{
  unsigned char *l_head;
  size_t l_slot;
  unsigned char *l_tail;
  size_t l_value1;
  size_t l_value2;

  (*io_link).m_slot = -1;

  l_head = (*io_block);
  l_tail = (*io_block);

  do
    {
      if (0 == *l_tail)
        {
          break;
        }

      if (kv3_text_link_close == *l_tail)
        {
          *l_tail++ = 0;

          l_value1 = (l_head[0] - 'A');

          if (0 == l_head[1])
            {
              l_value2 = 0;
            }
          else
            {
              l_value2 = 10 * (l_head[1] - 'A');
            }

          l_slot = (l_value1 | l_value2);

          if (kv3_dict_row_cell_count_used > l_slot)
            {
              (*io_link).m_slot = l_slot;
            }

          break;
        }

      l_tail++;
    }
  while (1);

  (*io_block) = l_tail;

  return;
}
