/*
  tree_load.cxx

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
#include <stdio.h>
//
#include "mstdlib.h"
#include "mstring.h"
//
#include "kv3.hxx"

extern void
  kv3::tree_load(Fl_Tree &io_tree, struct kv3_db_trove const &i_trove)
{
  static size_t const l_tree_path_size = (2 * kv3_dict_cell_octets_max);
  unsigned char *l_path = 0;

  io_tree.clear();

  do
    {
      if (0 == i_trove.m_head)
        {
          break;
        }

      mjo_malloc(reinterpret_cast<void **const>(&l_path), l_tree_path_size, 1);

      if (0 == l_path)
        {
          break;
        }

      struct kv3_db_datum const *l_datum = i_trove.m_head;

      for (; l_datum; l_datum = l_datum->m_next)
        {
          if (0 == l_datum->m_table.m_text.m_is_hidden)
            {
              break;
            }
        }

      if (0 == l_datum)
        {
          break;
        }

      snprintf(reinterpret_cast<char *>(l_path),
               l_tree_path_size,
               "%s/%s",
               l_datum->m_table.m_lang,
               l_datum->m_table.m_text.m_dict.m_row[0].m_cell[0].m_text);

      io_tree.add(reinterpret_cast<char const *>(l_path));

      for (struct kv3_db_datum const *l_datum2 = i_trove.m_head; l_datum2;
           l_datum2 = l_datum2->m_next)
        {
          if (l_datum2 != l_datum)
            {
              if (0 == l_datum2->m_table.m_text.m_is_hidden)
                {
                  for (struct kv3_db_xref_table *l_xtable
                       = l_datum->m_xref.m_head;
                       l_xtable;
                       l_xtable = l_xtable->m_next)
                    {
                      int l_rc = strcmp(
                        reinterpret_cast<char const *>(
                          l_datum2->m_table.m_lang),
                        reinterpret_cast<char *const>((*l_xtable).m_lang));

                      if (0 == l_rc)
                        {
                          struct kv3_dict_cell const *l_cell
                            = &l_xtable->m_xref.m_cell[1];

                          for (size_t l_slot = 1;
                               kv3_dict_xref_cell_count > l_slot;
                               l_slot++)
                            {
                              if (0 == l_cell->m_text[0])
                                {
                                  break;
                                }

                              snprintf(reinterpret_cast<char *>(l_path),
                                       l_tree_path_size,
                                       "%s/%s",
                                       (*l_xtable).m_lang,
                                       l_cell->m_text);

                              Fl_Tree_Item *l_item = io_tree.add(
                                reinterpret_cast<char const *>(l_path));
                              l_item->user_data(l_xtable);
                              l_cell++;
                            }
                        }
                    }
                }
            }
        }
    }
  while (0);

  mjo_free(reinterpret_cast<void **const>(&l_path));
  io_tree.redraw();

  return;
}
