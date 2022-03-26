/*
  kv3_db_datum_open.c

  Copyright (c) 2008-2010, 2014, 2020 Dante University Foundation and Contributors

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
/**/
#include "dbdatum.h"

extern void
  kv3_db_datum_open(struct kv3_db_datum *const io_datum,
                    unsigned char const *i_prefix,
                    unsigned char const *i_lang)
{
  int l_rc;

  l_rc = 0;

  do
    {
      if (0 == io_datum)
        {
          break;
        }

      kv3_db_datum_discharge(io_datum);
      kv3_db_datum_assign(io_datum);

      kv3_db_table_open(&(*io_datum).m_table, i_prefix, i_lang);

      l_rc = -1;

      if (-1 == (*io_datum).m_table.m_handle)
        {
          break;
        }

      kv3_db_inf_load(&(*io_datum).m_inf, i_prefix, i_lang);

      if (0 == (*io_datum).m_inf.m_count)
        {
          break;
        }

      kv3_db_xref_open(&(*io_datum).m_xref, i_prefix, i_lang);

      l_rc = 0;
    }
  while (0);

  if (l_rc)
    {
      kv3_db_datum_discharge(io_datum);
      kv3_db_datum_assign(io_datum);
    }

  return;
}
