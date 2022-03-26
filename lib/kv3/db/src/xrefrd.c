/*
  kv3_db_xref_read.c

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
#include <errno.h>
#include <stdio.h>
/**/
#include "msysstat.h"
/**/
#include "mfcntl.h"
#include "mstddef.h"
#include "mstdlib.h"
#include "mstring.h"
#include "munistd.h"
/**/
#include "dbxref.h"

static void
  _kv3_db_xref_table_read(struct kv3_db_xref_table *const io_table,
                          size_t const i_record)
{
  int l_exit;
  ssize_t l_bytes;
  size_t l_offset;

  do
    {
      memset(&(*io_table).m_xref, 0, sizeof((*io_table).m_xref));

      l_exit
        = mjo_mul_size_t(&l_offset, sizeof(struct kv3_dict_xref), i_record);

      if (l_exit)
        {
          break;
        }

      if (0 == (1 + l_offset))
        {
          l_exit = ERANGE;
          break;
        }

      errno = 0;
      l_bytes = lseek((*io_table).m_handle, (off_t)l_offset, SEEK_SET);

      if ((off_t)-1 == l_bytes)
        {
          l_exit = errno;
          break;
        }

      if (l_bytes != (off_t)l_offset)
        {
          l_exit = EIO;
          break;
        }

      errno = 0;
      l_bytes = read(
        (*io_table).m_handle, &(*io_table).m_xref, sizeof((*io_table).m_xref));

      if (l_bytes != sizeof((*io_table).m_xref))
        {
          l_exit = errno;
          break;
        }

      kv3_dict_xref_set_internal(&(*io_table).m_xref);

      l_exit = 0;
    }
  while (0);

  errno = l_exit;

  return;
}

extern void
  kv3_db_xref_read(struct kv3_db_xref *const io_xref, size_t const i_record)
{
  struct kv3_db_xref_table *l_table;

  do
    {
      if (0 == io_xref)
        {
          break;
        }

      l_table = (*io_xref).m_head;

      do
        {
          if (0 == l_table)
            {
              break;
            }

          if (-1 != l_table->m_handle)
            {
              _kv3_db_xref_table_read(l_table, i_record);
            }

          l_table = (*l_table).m_next;
        }
      while (1);
    }
  while (0);

  return;
}
