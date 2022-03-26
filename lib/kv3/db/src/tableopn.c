/*
  kv3_db_table_open.c

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
/**/
#include "msysstat.h"
/**/
#include "mfcntl.h"
#include "mstdlib.h"
#include "mstring.h"
#include "munistd.h"
/**/
#include "dbsuffix.h"
#include "dbtable.h"

extern void
  kv3_db_table_open(struct kv3_db_table *const io_table,
                    unsigned char const *i_prefix,
                    unsigned char const *i_lang)
{
  ssize_t l_bytes;
  unsigned char *l_path;

  l_path = 0;

  do
    {
      if (0 == io_table)
        {
          break;
        }

      kv3_db_table_discharge(io_table);
      kv3_db_table_assign(io_table);

      mjo_path_join(
        &l_path, i_prefix, i_lang, (unsigned char const *)kv3_db_suffix_table);

      if (0 == l_path)
        {
          break;
        }

      mjo_strdup(&(*io_table).m_lang, i_lang);

      (*io_table).m_handle = open((char const *)l_path, O_RDONLY | O_BINARY);

      if (-1 == (*io_table).m_handle)
        {
          break;
        }

      l_bytes = read((*io_table).m_handle,
                     &(*io_table).m_header,
                     sizeof((*io_table).m_header));

      if ((ssize_t)sizeof((*io_table).m_header) == l_bytes)
        {
          kv3_dict_set_internal(&(*io_table).m_header);
        }
      else
        {
          memset(&(*io_table).m_header, 0, sizeof((*io_table).m_header));
        }
    }
  while (0);

  mjo_free((void **const) & l_path);

  return;
}
