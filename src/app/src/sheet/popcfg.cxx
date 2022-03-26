/*
  sheet_popdown_configure.cxx

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

void
  kv3::sheet::popdown_configure()
{
  size_t const l_header_len_y = header_len_y();
  ssize_t l_pos_y = y() + static_cast<int>(l_header_len_y);
  size_t const l_len_y = 18 + static_cast<int>(l_header_len_y);
  ssize_t l_scroll_x = 0;

  if (m_sx.visible())
    {
      l_scroll_x = m_sx.value();
    }

  fl_font(m_cell_font, m_header_size);

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
                  struct kv3_text &l_text = l_datum->m_table.m_text;
                  struct kv3_text_cell &l_cell = l_text.m_cell[l_row][l_col];

                  for (size_t l_slot = 0; l_cell.m_count > l_slot; l_slot++)
                    {
                      struct kv3_text_seg &l_seg = l_cell.m_seg[l_slot];

                      if (kv3_text_block_variant_set == l_seg.m_variant)
                        {
                          struct kv3_text_set &l_set = l_seg.m_block.m_set;
                          struct kv3_text_set_group const &l_group
                            = l_set.m_group[l_set.m_selected];
                          unsigned char const *l_chunk
                            = l_group.m_block[l_group.m_selected];
                          int l_width = 0;
                          int l_height = 0;

                          fl_measure(reinterpret_cast<char const *>(l_chunk),
                                     l_width,
                                     l_height,
                                     0);
                          l_set.m_bbox.m_pos_x = l_pos_x;
                          l_set.m_bbox.m_pos_y = l_pos_y + 4;
                          l_set.m_bbox.m_len_x = 18 + l_width;
                          l_set.m_bbox.m_len_y = l_len_y - 8;
                        }
                    }
                  l_pos_x += static_cast<ssize_t>(l_len_x);
                }
            }
        }

      l_pos_y += static_cast<ssize_t>(l_len_y);
    }

  return;
}
