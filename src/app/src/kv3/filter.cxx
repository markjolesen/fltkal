/*
  filter.cxx

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
#include "kv3.hxx"

extern int
  kv3::filter(unsigned char const *i_text, unsigned char const *i_filter)
{
  int l_exit = 0;

  do
    {
      if ((i_text == i_filter) || (0 == i_text) || (0 == i_filter))
        {
          break;
        }

      unsigned char const *l_ptr1 = i_text;
      unsigned char const *l_ptr2 = i_filter;

      for (; *l_ptr1 && *l_ptr2; l_ptr1++, l_ptr2++)
        {
          l_exit = (l_ptr1[0] - l_ptr2[0]);
          if (l_exit)
            {
              break;
            }
        }
    }
  while (0);

  return l_exit;
}
