/*
  sheet_scroll_configure.cxx

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
#include "sheet.hxx"
//
#if !defined(__DOS__)
#  include <FL/Fl.H>
#else
#  include <fl/fl.h>
#endif

void
  kv3::sheet::scroll_configure()
{
  do
    {
      if ((0 == m_trove) || (0 == m_trove->m_head))
        {
          m_sx.value(0, 0, 0, 0);
          break;
        }

      ssize_t l_pos = m_sx.value();
      ssize_t l_len_x = (w() - Fl::scrollbar_size() - 4);

      if ((l_pos + l_len_x) > static_cast<int>(m_extent_x))
        {
          l_pos = (static_cast<int>(m_extent_x) - l_len_x);
          if (0 >= l_pos)
            {
              l_pos = 0;
            }
        }

      m_sx.value(static_cast<int>(l_pos),
                 static_cast<int>(l_len_x),
                 0,
                 static_cast<int>(m_extent_x));
    }
  while (0);

  return;
}
