/*
  view_resize.cxx

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

void
  kv3::view::resize(int x, int y, int w, int h)
{
  if (false == m_event.m_dragged)
    {
      Fl_Widget::resize(x, y, w, h);
      ssize_t l_pos_y = Fl_Widget::y();

      for (struct view_item *l_item = m_list.m_head; l_item;
           l_item = l_item->m_next)
        {
          l_item->m_box.m_pos_x = Fl_Widget::x();
          l_item->m_box.m_pos_y = l_pos_y;
          l_item->m_box.m_len_x = Fl_Widget::w();
          l_pos_y += view_item::box_len_y;
        }
    }

  return;
}
