/*
  view_handle_push.cxx

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
#include "mstring.h"
//
#include "view.hxx"
//
#if !defined(__DOS__)
#  include <FL/Fl.H>
#  include <FL/fl_draw.H>
#else
#  include <fl/fL.h>
#  include <fl/fl_draw.h>
#endif

void
  kv3::view::handle_push()
{
  memset(&m_event, 0, sizeof(m_event));

  for (struct view_item *l_item = m_list.m_head; l_item;
       l_item = l_item->m_next)
    {
      bool l_hit = Fl::event_inside(static_cast<int>(l_item->m_box.m_pos_x),
                                    static_cast<int>(l_item->m_box.m_pos_y),
                                    static_cast<int>(l_item->m_box.m_len_x),
                                    static_cast<int>(l_item->m_box.m_len_y));

      if (l_hit)
        {
          m_event.m_item = l_item;
          m_event.m_event_x = Fl::event_x();
          m_event.m_event_y = Fl::event_y();
          fl_cursor(FL_CURSOR_MOVE);
          break;
        }
    }

  return;
}
