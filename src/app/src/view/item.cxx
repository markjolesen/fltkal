/*
  view_draw_item.cxx

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
#include "view.hxx"
//
#if !defined(__DOS__)
#  include <FL/Enumerations.H>
#  include <FL/fl_draw.H>
#else
#  include <fl/fl_draw.h>
#  include <fl/fl_enums.h>
#endif

void
  kv3::view::draw_item(struct kv3::view::view_item const &i_item)
{
  fl_draw_box(FL_EMBOSSED_BOX,
              static_cast<int>(i_item.m_box.m_pos_x),
              static_cast<int>(i_item.m_box.m_pos_y),
              static_cast<int>(i_item.m_box.m_len_x),
              static_cast<int>(i_item.m_box.m_len_y),
              FL_BACKGROUND_COLOR);

  unsigned char *const l_lang = i_item.m_datum->m_table.m_lang;
  fl_font(FL_COURIER_BOLD, 18);
  fl_color(FL_FOREGROUND_COLOR);

  fl_draw(reinterpret_cast<char const *>(l_lang),
          static_cast<int>(i_item.m_box.m_pos_x) + 20,
          static_cast<int>(i_item.m_box.m_pos_y) + 5,
          50,
          static_cast<int>(i_item.m_box.m_len_y) - 10,
          FL_ALIGN_LEFT);

  fl_draw_box(FL_DOWN_BOX,
              static_cast<int>(i_item.m_box.m_pos_x) + 5,
              static_cast<int>(i_item.m_box.m_pos_y) + 5,
              10,
              static_cast<int>(i_item.m_box.m_len_y) - 10,
              (i_item.m_datum->m_table.m_text.m_is_hidden ? FL_GRAY
                                                          : FL_GREEN));

  return;
}
