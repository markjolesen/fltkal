/*
  sheet_draw_cell.cxx

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
#include "mstring.h"
//
#include "sheet.hxx"

void
  kv3::sheet::draw_cell(struct kv3_text &io_text,
                        size_t const i_row,
                        size_t const i_col,
                        ssize_t const i_pos_x,
                        ssize_t const i_pos_y,
                        size_t const i_len_x,
                        size_t const i_len_y)
{
  fl_draw_box(box(),
              i_pos_x,
              i_pos_y,
              static_cast<int>(i_len_x),
              static_cast<int>(i_len_y),
              color());

  if (1 & i_col)
    {
      fl_rectf(i_pos_x + 1,
               i_pos_y + 1,
               static_cast<int>(i_len_x) - 2,
               static_cast<int>(i_len_y) - 2,
               204,
               242,
               255);
    }

  fl_push_clip(i_pos_x + 1,
               i_pos_y + 1,
               static_cast<int>(i_len_x) - 2,
               static_cast<int>(i_len_y) - 2);

  ssize_t l_pos_x = 4 + i_pos_x;
  size_t l_len_x = i_len_x - 8;

  struct kv3_text_cell &l_cell = io_text.m_cell[i_row][i_col];

  for (size_t l_slot = 0; (0 < l_len_x) && l_cell.m_count > l_slot; l_slot++)
    {
      struct kv3_text_seg &l_seg = l_cell.m_seg[l_slot];

      switch (l_seg.m_variant)
        {
        case kv3_text_block_variant_text:
        case kv3_text_block_variant_subject:
          do
            {
              unsigned char const *l_chunk = l_seg.m_block.m_str;

              fl_font(m_cell_font, m_header_size);
              fl_color(FL_FOREGROUND_COLOR);
              fl_draw(reinterpret_cast<char const *>(l_chunk),
                      l_pos_x,
                      i_pos_y,
                      static_cast<int>(l_len_x),
                      static_cast<int>(i_len_y),
                      FL_ALIGN_LEFT);

              int l_width = 0;
              int l_height = 0;

              fl_measure(
                reinterpret_cast<char const *>(l_chunk), l_width, l_height, 0);
              int l_space_width = static_cast<int>(fl_width(mjo_r7_space));

              l_pos_x += (l_width + l_space_width);
              l_len_x -= (l_width + l_space_width);
            }
          while (0);
          break;
        case kv3_text_block_variant_link:
          do
            {
              size_t l_col = l_seg.m_block.m_link.m_slot;
              struct kv3_text_cell const &l_link
                = io_text.m_cell[i_row][l_col];
              unsigned char const *l_chunk = 0;
              struct kv3_text_seg const &l_seg = l_link.m_seg[0];

              if (kv3_text_block_variant_set == l_seg.m_variant)
                {
                  struct kv3_text_set const &l_set = l_seg.m_block.m_set;

                  struct kv3_text_set_group const &l_group
                    = l_set.m_group[l_set.m_selected];

                  l_chunk = l_group.m_block[l_group.m_selected];
                }
              else
                {
                  l_chunk = l_seg.m_block.m_str;
                  for (size_t l_slot2 = 1; l_link.m_count > l_slot2; l_slot2++)
                    {
                      struct kv3_text_seg const &l_seg2
                        = l_link.m_seg[l_slot2];

                      if (kv3_text_block_variant_subject == l_seg2.m_variant)
                        {
                          l_chunk = l_seg2.m_block.m_str;
                          break;
                        }
                    }
                }

              if (('D' - 'A') == l_col)
                {
                  fl_color(FL_BLUE);
                  fl_font(m_cell_font | FL_BOLD, m_header_size);
                }
              else if (('Q' - 'A') == l_col)
                {
                  fl_color(128, 0, 128);
                  fl_font(m_cell_font | FL_BOLD, m_header_size);
                }
              else
                {
                  fl_color(FL_FOREGROUND_COLOR);
                  fl_font(m_cell_font | FL_ITALIC, m_header_size);
                }

              fl_draw(reinterpret_cast<char const *>(l_chunk),
                      l_pos_x,
                      i_pos_y,
                      static_cast<int>(l_len_x),
                      static_cast<int>(i_len_y),
                      FL_ALIGN_LEFT);

              int l_width = 0;
              int l_height = 0;

              fl_measure(
                reinterpret_cast<char const *>(l_chunk), l_width, l_height, 0);
              int l_space_width = static_cast<int>(fl_width(mjo_r7_space));

              l_pos_x += (l_width + l_space_width);
              l_len_x -= (l_width + l_space_width);
            }
          while (0);
          break;
        case kv3_text_block_variant_set:
          do
            {
              struct kv3_text_set &l_set = l_seg.m_block.m_set;

              struct kv3_text_set_group const &l_group
                = l_set.m_group[l_set.m_selected];

              unsigned char const *l_chunk
                = l_group.m_block[l_group.m_selected];

              int l_width = 0;
              int l_height = 0;

              fl_font(m_cell_font, m_header_size);
              fl_measure(
                reinterpret_cast<char const *>(l_chunk), l_width, l_height, 0);
              int l_space_width = static_cast<int>(fl_width(mjo_r7_space));

              fl_draw_box(FL_FLAT_BOX,
                          l_pos_x,
                          i_pos_y + 4,
                          l_width + 8,
                          static_cast<int>(i_len_y) - 8,
                          FL_BACKGROUND_COLOR);

              fl_color(FL_FOREGROUND_COLOR);

              fl_draw(reinterpret_cast<char const *>(l_chunk),
                      l_pos_x,
                      i_pos_y + 4,
                      l_width + 8,
                      static_cast<int>(i_len_y) - 8,
                      FL_ALIGN_CENTER);

              l_pos_x += (l_width + l_space_width + 8);
              l_len_x -= (l_width + l_space_width + 8);
            }
          while (0);
          break;
        default:
          break;
        }
    }

  fl_pop_clip();

  return;
}
