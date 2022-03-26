/*
  view_snap.cxx

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
  kv3::view::snap()
{
  if (0 == m_event.m_item->m_prev)
    {
      m_list.m_head = m_event.m_item->m_next;
    }
  else
    {
      m_event.m_item->m_prev->m_next = m_event.m_item->m_next;
    }

  if (0 == m_event.m_item->m_next)
    {
      m_list.m_tail = m_event.m_item->m_prev;
    }
  else
    {
      m_event.m_item->m_next->m_prev = m_event.m_item->m_prev;
    }

  struct view_item *l_link = 0;

  for (struct view_item *l_item = m_list.m_head; l_item;
       l_item = l_item->m_next)
    {
      if (m_event.m_item->m_box.m_pos_y <= l_item->m_box.m_pos_y)
        {
          l_link = l_item;
          break;
        }
    }

  do
    {
      if (l_link)
        {
          if (0 == l_link->m_prev)
            {
              m_event.m_item->m_next = l_link;
              m_event.m_item->m_prev = 0;
              l_link->m_prev = m_event.m_item;
              m_list.m_head = m_event.m_item;
            }
          else
            {
              m_event.m_item->m_prev = l_link->m_prev;
              m_event.m_item->m_next = l_link;
              l_link->m_prev->m_next = m_event.m_item;
              l_link->m_prev = m_event.m_item;
            }

          break;
        }

      if (m_list.m_tail)
        {
          m_event.m_item->m_next = 0;
          m_event.m_item->m_prev = m_list.m_tail;
          m_list.m_tail->m_next = m_event.m_item;
          m_list.m_tail = m_event.m_item;

          break;
        }

      m_list.m_head = m_event.m_item;
      m_list.m_tail = m_event.m_item;
      m_event.m_item->m_next = 0;
      m_event.m_item->m_prev = 0;
    }
  while (0);

  size_t l_pos_y = y();

  m_trove->m_head = 0;
  m_trove->m_tail = 0;

  for (struct view_item *l_item = m_list.m_head; l_item;
       l_item = l_item->m_next)
    {
      if (0 == m_trove->m_head)
        {
          m_trove->m_head = l_item->m_datum;
          m_trove->m_tail = l_item->m_datum;
          l_item->m_datum->m_next = 0;
          l_item->m_datum->m_prev = 0;
        }
      else
        {
          l_item->m_datum->m_next = 0;
          l_item->m_datum->m_prev = m_trove->m_tail;
          m_trove->m_tail->m_next = l_item->m_datum;
          m_trove->m_tail = l_item->m_datum;
        }

      l_item->m_box.m_pos_y = static_cast<ssize_t>(l_pos_y);
      l_pos_y += view_item::box_len_y;
    }

  return;
}
