/*
  kv3_dict_str_set_internal.c

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
#include "mstddef.h"
#include "mstring.h"
#include "mu8.h"
/**/
#include "dictstr.h"

extern void
  kv3_dict_str_set_internal(unsigned char *io_str, size_t const i_octets)
{
  size_t l_left;
  unsigned char *l_src;

  do
    {
      if (0 == io_str)
        {
          break;
        }

      if (0 == i_octets)
        {
          break;
        }

      l_left = i_octets;
      l_src = io_str;

      do
        {
          if (0 == l_left)
            {
              break;
            }

          if (0 == *l_src)
            {
              break;
            }

          if (kv3_dict_str_epsilon == (*l_src))
            {
              break;
            }

          l_src++;
          l_left--;
        }
      while (1);

      *l_src = 0;
      mjo_u8_trim(io_str);
    }
  while (0);

  return;
}
