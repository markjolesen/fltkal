/*
  kv3_db_trove_read.c

  Copyright (c) 2014, 2020 Dante University Foundation and Contributors

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
/**/
#include "dbtrove.h"

static void
  kv3_db_inf_compare(int *const o_result,
                     char const *i_obj_to_find,
                     struct kv3_dict_cell const *const i_obj_to_compare)
{
  *o_result = strcmp(i_obj_to_find, (char const *)(*i_obj_to_compare).m_text);

  return;
}

extern void
  kv3_db_trove_read(struct kv3_db_trove *const io_trove, size_t const i_record)
{
  struct kv3_db_datum *l_datum;
  int l_found;
  int l_rc;
  size_t l_slot;
  struct kv3_db_xref_table const *l_xtable;

  do
    {
      if ((0 == io_trove) || (0 == (*io_trove).m_head))
        {
          break;
        }

      l_datum = (*io_trove).m_head;
      kv3_db_datum_read(l_datum, i_record);
      kv3_db_xref_read(&(*l_datum).m_xref, i_record);

      do
        {
          l_datum = (*l_datum).m_next;

          if (0 == l_datum)
            {
              break;
            }

          memset(&(*l_datum).m_table.m_text.m_dict,
                 0,
                 sizeof((*l_datum).m_table.m_text.m_dict));
          memset(&(*l_datum).m_table.m_text.m_cell,
                 0,
                 sizeof((*l_datum).m_table.m_text.m_cell));

          l_xtable = (*io_trove).m_head->m_xref.m_head;

          do
            {
              if (0 == l_xtable)
                {
                  break;
                }

              l_rc = strcmp((char const *)(*l_datum).m_table.m_lang,
                            (char const *)(*l_xtable).m_lang);

              if (0 == l_rc)
                {
                  mjo_search_binary(&l_found,
                                    &l_slot,
                                    (*l_datum).m_inf.m_array,
                                    sizeof(struct kv3_dict_cell),
                                    (*l_datum).m_inf.m_count,
                                    (void (*)(int *const,
                                              void const *,
                                              void const *))kv3_db_inf_compare,
                                    (*l_xtable).m_xref.m_cell[1].m_text);

                  if (l_found)
                    {
                      kv3_db_datum_read(l_datum, l_slot);
                    }

                  break;
                }

              l_xtable = (*l_xtable).m_next;
            }
          while (1);
        }
      while (1);
    }
  while (0);

  return;
}
