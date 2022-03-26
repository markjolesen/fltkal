/*
  menu_popup.cxx

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
//
#include "kv3.hxx"
//
#if !defined(__DOS__)
#  include <FL/Fl_Menu.H>
#else
#  include <fl/menu.h>
#endif

extern int
  kv3::menu_popup(size_t &o_grpn, size_t &o_blkn, struct kv3_text_set &io_set)
{
  static size_t const l_items_max
    = 1 + (kv3_text_set_max_blocks * kv3_text_set_max_groups);
  size_t l_count = 0;
  int l_exit = 0;
  Fl_Menu_Item *l_item;
  Fl_Menu_Item *l_menu;
  Fl_Menu_Item *l_selected = 0;

  o_grpn = -1;
  o_blkn = -1;

  mjo_calloc(
    reinterpret_cast<void **const>(&l_menu), l_items_max, sizeof(*l_menu));

  l_item = l_menu;

  for (size_t l_grpn = 0; io_set.m_count > l_grpn; l_grpn++)
    {
      struct kv3_text_set_group const &l_group = io_set.m_group[l_grpn];

      for (size_t l_blkn = 0; l_group.m_count > l_blkn; l_blkn++)
        {
          l_item->text
            = reinterpret_cast<char const *>(l_group.m_block[l_blkn]);

          size_t l_bits = l_grpn;

          l_bits <<= 8;
          l_bits |= l_blkn;

          l_item->labelfont(FL_COURIER);
          l_item->labelsize(24);
          l_item->user_data_ = reinterpret_cast<void *>(l_bits);

          if (l_grpn == io_set.m_selected && l_blkn == l_group.m_selected)
            {
              l_selected = l_item;
            }

          l_item++;
          l_count++;
        }
    }

  do
    {
      if (0 == l_count)
        {
          break;
        }

      l_item = l_menu;
      for (size_t l_slot = 0; (l_count - 1) > l_slot; l_slot++, l_item++)
        {
          size_t l_grpn0 = reinterpret_cast<size_t>(l_item[0].user_data_);

          l_grpn0 >>= 8;

          size_t l_grpn1 = reinterpret_cast<size_t>(l_item[1].user_data_);

          l_grpn1 >>= 8;

          if (l_grpn0 != l_grpn1)
            {
              l_item->flags = FL_MENU_DIVIDER;
            }
        }

      Fl_Menu_Item const *l_picked
        = l_menu[0].pulldown(Fl::event_x(), Fl::event_y(), 0, 0, l_selected);

      if (l_picked && l_picked != l_selected)
        {
          size_t l_bits = reinterpret_cast<size_t>(l_picked->user_data_);

          o_grpn = (l_bits >> 8);
          o_blkn = (0xf & l_bits);

          io_set.m_selected = o_grpn;
          io_set.m_group[o_grpn].m_selected = o_blkn;

          unsigned char const *l_chunk
            = io_set.m_group[o_grpn].m_block[o_blkn];

          int l_width = 0;
          int l_height = 0;

          fl_font(FL_COURIER, 18);
          fl_measure(
            reinterpret_cast<char const *>(l_chunk), l_width, l_height, 0);

          io_set.m_bbox.m_len_x = 18 + l_width;

          l_exit = 1;
        }
    }
  while (0);

  mjo_free(reinterpret_cast<void **const>(&l_menu));

  return l_exit;
}
