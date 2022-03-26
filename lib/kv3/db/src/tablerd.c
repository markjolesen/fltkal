/*
  kv3_db_table_read.c

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
#include "dbtable.h"

extern void
  kv3_db_table_read(struct kv3_db_table *const io_table, size_t const i_record)
{
  int l_exit;
  ssize_t l_bytes;
  size_t l_offset;

  do
    {
      if (0 == io_table)
        {
          l_exit = EINVAL;
          break;
        }

      memset(&(*io_table).m_text.m_dict, 0, sizeof((*io_table).m_text.m_dict));
      memset(&(*io_table).m_text.m_cell, 0, sizeof((*io_table).m_text.m_cell));

      (*io_table).m_record = (size_t)-1;

      if (-1 == (*io_table).m_handle)
        {
          l_exit = EBADF;
          break;
        }

      l_exit = mjo_mul_size_t(&l_offset, sizeof(struct kv3_dict), i_record);

      if (l_exit)
        {
          break;
        }

      l_exit = mjo_add_size_t(&l_offset, l_offset, sizeof(struct kv3_dict));

      if (l_exit)
        {
          break;
        }

      errno = 0;
      l_bytes = lseek((*io_table).m_handle, (off_t)l_offset, SEEK_SET);

      if (-1 == l_bytes)
        {
          l_exit = errno;
          break;
        }

      errno = 0;
      l_bytes = read((*io_table).m_handle,
                     &(*io_table).m_text.m_dict,
                     sizeof((*io_table).m_text.m_dict));

      if (l_bytes != sizeof((*io_table).m_text.m_dict))
        {
          l_exit = errno;
          break;
        }

      kv3_dict_set_internal(&(*io_table).m_text.m_dict);
      kv3_text_parse_once(&(*io_table).m_text);
      (*io_table).m_record = i_record;

      l_exit = 0;
    }
  while (0);

  errno = l_exit;

  return;
}
