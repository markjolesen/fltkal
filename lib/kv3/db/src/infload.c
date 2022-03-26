/*
  kv3_db_inf_load.c

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
#include "mstdlib.h"
#include "munistd.h"
/**/
#include "dbinf.h"
#include "dbsuffix.h"
#include "dict.h"

static int
  _kv3_db_inf_load(struct kv3_db_inf *const io_inf,
                   unsigned char const *i_path)
{
  off_t l_bytes;
  int l_exit;
  int l_handle;
  size_t l_size;

  l_handle = -1;

  do
    {
      errno = 0;
      l_handle = open((char const *)i_path, O_RDONLY | O_BINARY);

      if (-1 == l_handle)
        {
          l_exit = errno;
          break;
        }

      errno = 0;
      l_bytes = lseek(l_handle, 0, SEEK_END);

      if ((off_t)-1 == l_bytes)
        {
          l_exit = errno;
          break;
        }

      l_exit = mjo_mul_size_t(
        &l_size, sizeof(struct kv3_dict_cell), kv3_dict_records_max);

      if (l_exit)
        {
          break;
        }

      if (l_bytes > (off_t)l_size)
        {
          l_bytes = (off_t)l_size;
        }

      (*io_inf).m_count = (l_bytes / sizeof(struct kv3_dict_cell));

      if (0 == (*io_inf).m_count)
        {
          l_exit = 0;
          break;
        }

      errno = 0;
      l_bytes = lseek(l_handle, 0, SEEK_SET);

      if ((off_t)-1 == l_bytes)
        {
          l_exit = errno;
          break;
        }

      mjo_malloc((void **const) & (*io_inf).m_array,
                 (*io_inf).m_count,
                 sizeof(struct kv3_dict_cell));

      l_size = ((*io_inf).m_count * sizeof(struct kv3_dict_cell));

      errno = 0;
      l_bytes = read(l_handle, (*io_inf).m_array, l_size);

      if ((off_t)l_size != l_bytes)
        {
          mjo_free((void **const) & (*io_inf).m_array);
          (*io_inf).m_count = 0;
          l_exit = errno;
          break;
        }

      l_exit = 0;
    }
  while (0);

  if (-1 != l_handle)
    {
      close(l_handle);
    }

  errno = l_exit;

  return l_exit;
}

extern void
  kv3_db_inf_load(struct kv3_db_inf *const io_inf,
                  unsigned char const *i_prefix,
                  unsigned char const *i_lang)
{
  struct kv3_dict_cell *l_cell;
  unsigned char *l_path;
  int l_rc;
  size_t l_slot;

  l_path = 0;

  do
    {
      if (0 == io_inf)
        {
          break;
        }

      kv3_db_inf_discharge(io_inf);
      kv3_db_inf_assign(io_inf);

      mjo_path_join(
        &l_path, i_prefix, i_lang, (unsigned char const *)kv3_db_suffix_inf);

      if (0 == l_path)
        {
          break;
        }

      l_rc = _kv3_db_inf_load(io_inf, l_path);

      if (l_rc)
        {
          kv3_db_inf_discharge(io_inf);
          kv3_db_inf_assign(io_inf);
          break;
        }

      l_cell = (*io_inf).m_array;

      for (l_slot = 0; (*io_inf).m_count > l_slot; l_slot++)
        {
          kv3_dict_cell_set_internal(l_cell);
          l_cell++;
        }
    }
  while (0);

  mjo_free((void **const) & l_path);

  return;
}
