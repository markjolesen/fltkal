/*
  view_handle.cxx

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
#include <stdlib.h>
//
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

int
  kv3::view::handle(int i_event)
{
  int l_exit = 0;

  switch (i_event)
    {
    case FL_PUSH:
      memset(&m_event, 0, sizeof(m_event));

      if (m_list.m_head)
        {
          handle_push();
        }

      l_exit = 1;
      break;
    case FL_DRAG:
      if (m_event.m_item)
        {
          int l_delta = Fl::event_y() - m_event.m_event_y;

          if (l_delta)
            {
              m_event.m_item->m_box.m_pos_y += l_delta;

              if (y() > m_event.m_item->m_box.m_pos_y)
                {
                  m_event.m_item->m_box.m_pos_y = y();
                }
              else
                {
                  ssize_t l_max_y
                    = y() + h()
                      - static_cast<int>(m_event.m_item->m_box.m_len_y);

                  if (l_max_y < m_event.m_item->m_box.m_pos_y)
                    {
                      m_event.m_item->m_box.m_pos_y = l_max_y;
                    }
                }
              m_event.m_dragged = true;
              redraw();
            }
        }

      m_event.m_event_y = Fl::event_y();
      l_exit = 1;
      break;
    case FL_RELEASE:
      if (m_event.m_item)
        {
          if (m_event.m_dragged)
            {
              snap();
              redraw();
              do_callback();
            }
          else
            {
              bool l_toggled = toggle(m_event.m_item, m_list.m_head);
              if (l_toggled)
                {
                  damage(FL_DAMAGE_CHILD,
                         static_cast<int>(m_event.m_item->m_box.m_pos_x),
                         static_cast<int>(m_event.m_item->m_box.m_pos_y),
                         static_cast<int>(m_event.m_item->m_box.m_len_x),
                         static_cast<int>(m_event.m_item->m_box.m_len_y));
                  do_callback();
                }
            }
        }

      memset(&m_event, 0, sizeof(m_event));
      fl_cursor(FL_CURSOR_DEFAULT);
      l_exit = 1;

      break;
    }

  return l_exit;
}
