/*
  view_reference.cxx

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
#include "mstdlib.h"
#include "mstring.h"
//
#include "view.hxx"

void
  kv3::view::reference(struct kv3_db_trove *const i_trove)
{
  do
    {
      struct view_item *l_head;
      struct view_item *l_tail;

      for (l_head = m_list.m_head; l_head; l_head = l_tail)
        {
          l_tail = l_head->m_next;
          mjo_free(reinterpret_cast<void **const>(&l_head));
        }
    }
  while (0);

  memset(&m_list, 0, sizeof(m_list));
  m_trove = i_trove;

  if (m_trove && m_trove->m_head)
    {
      ssize_t l_pos_y = y();
      struct kv3_db_datum *l_datum;

      for (l_datum = m_trove->m_head; l_datum; l_datum = l_datum->m_next)
        {
          struct view_item *l_item;
          mjo_calloc(
            reinterpret_cast<void **const>(&l_item), sizeof(*l_item), 1);

          l_item->m_datum = l_datum;
          l_item->m_box.m_pos_x = x();
          l_item->m_box.m_pos_y = l_pos_y;
          l_item->m_box.m_len_x = w();
          l_item->m_box.m_len_y = view_item::box_len_y;

          if (m_list.m_head)
            {
              (*l_item).m_prev = m_list.m_tail;
              m_list.m_tail->m_next = l_item;
              m_list.m_tail = l_item;
            }
          else
            {
              m_list.m_head = l_item;
              m_list.m_tail = l_item;
            }
          l_pos_y += view_item::box_len_y;
        }
    }

  redraw();

  return;
}
