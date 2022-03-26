/*
  kv3_dict_cell_copy_str.c

  Copyright (c) 2008-2011, 2019 Dante University Foundation and Contributors

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
#include "mr7.h"
#include "mstddef.h"
#include "mstring.h"
#include "mu8.h"
/**/
#include "dictcell.h"

extern void
  kv3_dict_cell_copy_str(struct kv3_dict_cell *const io_cell,
                         unsigned char const *i_str)
{
  size_t l_count;
  unsigned char *l_dst;
  unsigned char const *l_src;

  do
    {
      if (0 == io_cell)
        {
          break;
        }

      memset(&(*io_cell).m_text, 0, sizeof((*io_cell).m_text));

      if (0 == i_str)
        {
          break;
        }

      if (0 == (*i_str))
        {
          break;
        }

      l_src = i_str;

      do
        {
          if (mjo_r7_space != (*l_src))
            {
              break;
            }

          l_src++;
        }
      while (1);

      l_count = 0;
      l_dst = (*io_cell).m_text;

      do
        {
          if (sizeof((*io_cell).m_text) <= l_count)
            {
              break;
            }

          if (0 == (*l_src))
            {
              break;
            }

          *l_dst++ = *l_src++;
          l_count++;
        }
      while (1);

      *l_dst = 0;
      mjo_u8_trim((*io_cell).m_text);
    }
  while (0);

  return;
}
