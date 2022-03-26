/*
  text_propogate.cxx

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
#include "kv3.hxx"

extern void
  kv3::text_propogate(struct kv3_db_trove &i_trove,
                      size_t const i_row,
                      size_t const i_col,
                      size_t const i_grpn,
                      size_t const i_blkn,
                      struct kv3_db_datum const &i_datum)
{
  for (struct kv3_db_datum *l_datum = i_trove.m_head; l_datum;
       l_datum = l_datum->m_next)
    {
      if (l_datum != (&i_datum))
        {
          struct kv3_text &l_text = l_datum->m_table.m_text;
          struct kv3_text_cell &l_cell = l_text.m_cell[i_row][i_col];

          for (size_t l_slot = 0; l_cell.m_count > l_slot; l_slot++)
            {
              struct kv3_text_seg &l_seg = l_cell.m_seg[l_slot];

              if (kv3_text_block_variant_set == l_seg.m_variant)
                {
                  struct kv3_text_set &l_set = l_seg.m_block.m_set;

                  if (l_set.m_count > i_grpn)
                    {
                      l_set.m_selected = i_grpn;
                    }
                }
            }
        }
    }

  return;
}
