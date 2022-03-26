/*
  sheet_draw_rows.cxx

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

void
  kv3::sheet::draw_rows()
{
  size_t const l_header_len_y = header_len_y();
  ssize_t l_pos_y = y() + static_cast<int>(l_header_len_y);
  size_t const l_len_y = 18 + static_cast<int>(l_header_len_y);
  ssize_t l_scroll_x = 0;

  fl_push_clip(x(), y(), w(), h());

  if (m_sx.visible())
    {
      l_scroll_x = m_sx.value();
    }

  for (size_t l_row = 1; kv3_dict_row_count_used > l_row; l_row++)
    {
      ssize_t l_pos_x = x() - l_scroll_x;

      for (size_t l_col = 0; kv3_dict_row_cell_count_used > l_col; l_col++)
        {
          for (struct kv3_db_datum *l_datum = m_trove->m_head; l_datum;
               l_datum = l_datum->m_next)
            {
              if (0 == l_datum->m_table.m_text.m_is_hidden)
                {
                  size_t const l_len_x
                    = l_datum->m_table.m_text.m_len_x[l_col];

                  if (x() <= (l_pos_x + l_len_x))
                    {
                      if ((x() + w()) < l_pos_x)
                        {
                          break;
                        }

                      struct kv3_text &l_text = l_datum->m_table.m_text;

                      draw_cell(l_text,
                                l_row,
                                l_col,
                                l_pos_x,
                                l_pos_y,
                                l_len_x,
                                l_len_y);
                    }

                  l_pos_x += static_cast<ssize_t>(l_len_x);
                }
            }
        }

      l_pos_y += static_cast<ssize_t>(l_len_y);
    }

  fl_pop_clip();

  return;
}
