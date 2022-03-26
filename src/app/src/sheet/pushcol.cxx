/*
  sheet_handle_push_col.cxx

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
#include "sheet.hxx"
//
#if !defined(__DOS__)
#  include <FL/Fl.H>
#else
#  include <fl/fl.h>
#endif

int
  kv3::sheet::handle_push_col()
{
  int l_exit = 0;
  ssize_t l_scroll_x = 0;
  size_t const l_event_x = static_cast<size_t>(Fl::event_x());
  ssize_t l_pos_x = x();

  if (m_sx.visible())
    {
      l_scroll_x = m_sx.value();
    }

  l_pos_x -= l_scroll_x;

  for (size_t l_col = 0; 0 == l_exit && kv3_dict_row_cell_count_used > l_col;
       l_col++)
    {
      for (struct kv3_db_datum *l_datum = m_trove->m_head; l_datum;
           l_datum = l_datum->m_next)
        {
          if (0 == l_datum->m_table.m_text.m_is_hidden)
            {
              size_t const l_len_x = l_datum->m_table.m_text.m_len_x[l_col];

              l_pos_x += static_cast<ssize_t>(l_len_x);

              l_exit = (((l_pos_x - 2) <= l_event_x)
                        && ((l_pos_x + 2) >= l_event_x));

              if (l_exit)
                {
                  m_pushed_x = l_event_x;
                  m_pushed_col = &l_datum->m_table.m_text.m_len_x[l_col];
                  break;
                }
            }
        }
    }

  return l_exit;
}
