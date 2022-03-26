/*
  app_read.cxx

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
#include "kv3.hxx"
//
#include "app.hxx"

void
  kv3::app::read(size_t const i_record)
{
  do
    {
      if (0 == m_trove.m_head)
        {
          break;
        }

      struct kv3_db_datum const *l_datum = m_trove.m_head;

      if (0 == l_datum->m_inf.m_count)
        {
          break;
        }

      if (i_record == l_datum->m_table.m_record)
        {
          break;
        }

      kv3_db_trove_read(&m_trove, i_record);
      m_sheet->redraw();
      kv3::tree_load((*m_inf_tree), m_trove);

      char const *l_filter = m_inf_filter->value();

      if (l_filter && *l_filter)
        {
          m_inf_filter->value(0);
          kv3::browser_load((*m_inf_browser), l_datum->m_inf);
        }

      size_t l_have = static_cast<size_t>(m_inf_browser->value());

      size_t l_want = (1 + i_record);

      if (l_have != l_want)
        {
          m_inf_browser->value(static_cast<int>(l_want));
          int l_rc = m_inf_browser->displayed(static_cast<int>(l_want));

          if (0 == l_rc)
            {
              m_inf_browser->topline(static_cast<int>(l_want));
            }
        }
    }
  while (0);

  return;
}

static void
  inf_compare(int *const o_result,
              void const *const i_obj_to_compare,
              void const *const i_obj_to_find)
{
  struct kv3_dict_cell const *l_cell;
  unsigned char const *l_find;

  l_cell = (struct kv3_dict_cell const *)i_obj_to_compare;
  l_find = (unsigned char const *)i_obj_to_find;
  *o_result = strcmp(reinterpret_cast<char const *>(l_find),
                     reinterpret_cast<char const *>((*l_cell).m_text));

  return;
}

void
  kv3::app::read(unsigned char const *i_lang, unsigned char const *i_inf)
{
  for (struct kv3_db_datum *l_datum = m_trove.m_head; l_datum;
       l_datum = l_datum->m_next)
    {
      int l_rc
        = strcmp(reinterpret_cast<char const *>(i_lang),
                 reinterpret_cast<char const *>(l_datum->m_table.m_lang));

      if (0 == l_rc)
        {
          int l_found;
          size_t l_slot;
          mjo_search_binary(
            &l_found,
            &l_slot,
            l_datum->m_inf.m_array,
            sizeof(struct kv3_dict_cell),
            l_datum->m_inf.m_count,
            (void (*)(int *const, void const *, void const *))inf_compare,
            i_inf);

          if (l_found)
            {
              if (l_slot != l_datum->m_table.m_record)
                {
                  kv3_db_table_read(&l_datum->m_table, l_slot);
                  m_sheet->view_changed();
                  m_sheet->redraw();
                }
            }
          break;
        }
    }

  return;
}
