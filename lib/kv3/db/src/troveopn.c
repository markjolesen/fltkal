/*
  kv3_db_trove_open.c

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
#include <stdio.h>
/**/
#include "msysstat.h"
/**/
#include "mdirect.h"
#include "mfcntl.h"
#include "mr7.h"
#include "mstdlib.h"
#include "mstring.h"
/**/
#include "dbsuffix.h"
#include "dbtrove.h"

#define kv3_db_trove_datum_max 3

static void
  kv3_db_datum_free(struct kv3_db_datum **const io_datum)
{
  if (io_datum && (*io_datum))
    {
      kv3_db_datum_discharge((*io_datum));
      mjo_free((void **const)io_datum);
    }

  return;
}

static void
  kv3_db_datum_malloc(struct kv3_db_datum **const o_datum,
                      unsigned char const *i_prefix,
                      unsigned char const *i_lang)
{
  if (o_datum)
    {
      mjo_malloc((void **const)o_datum, 1, sizeof(**o_datum));
      kv3_db_datum_assign((*o_datum));
      kv3_db_datum_open((*o_datum), i_prefix, i_lang);
    }

  return;
}

static void
  kv3_db_trove_insert(struct kv3_db_trove *const io_trove,
                      struct kv3_db_datum *const io_datum)
{
  if (0 == (*io_trove).m_head)
    {
      (*io_trove).m_head = io_datum;
      (*io_trove).m_tail = io_datum;
    }
  else
    {
      (*io_datum).m_prev = (*io_trove).m_tail;
      (*(*io_trove).m_tail).m_next = io_datum;
      (*io_trove).m_tail = io_datum;
    }

  return;
}

static void
  kv3_db_trove_load(struct kv3_db_trove *const io_trove, DIR *const io_dir)
{
  size_t l_count;
  struct kv3_db_datum *l_datum;
  struct dirent *l_entry;
  char *l_ptr;
  int l_rc;

  l_count = 0;

  do
    {
      l_entry = readdir(io_dir);

      if (0 == l_entry)
        {
          break;
        }

      do
        {
          if (mjo_r7_period == (*l_entry).d_name[0])
            {
              break;
            }

          l_ptr = strrchr((*l_entry).d_name, mjo_r7_period);

          if (0 == l_ptr)
            {
              break;
            }

          *l_ptr++ = 0;

          l_rc = strcmp(kv3_db_suffix_table, l_ptr);

          if (l_rc)
            {
              break;
            }

          kv3_db_datum_malloc(&l_datum,
                              (*io_trove).m_prefix,
                              (unsigned char const *)(*l_entry).d_name);

          if (-1 == l_datum->m_table.m_handle)
            {
              kv3_db_datum_free(&l_datum);
              break;
            }

          kv3_db_trove_insert(io_trove, l_datum);
          l_count++;
        }
      while (0);

      if (kv3_db_trove_datum_max <= l_count)
        {
          break;
        }
    }
  while (1);

  return;
}

extern void
  kv3_db_trove_open(struct kv3_db_trove *const io_trove,
                    unsigned char const *i_prefix)
{
  DIR *l_dir;
  unsigned char const *l_prefix;

  do
    {
      if (0 == io_trove)
        {
          break;
        }

      kv3_db_trove_discharge(io_trove);
      kv3_db_trove_assign(io_trove);

      l_prefix
        = ((i_prefix && i_prefix[0]) ? i_prefix : (unsigned char const *)".");

      mjo_strdup(&(*io_trove).m_prefix, l_prefix);

      l_dir = opendir((char const *)(*io_trove).m_prefix);

      if (0 == l_dir)
        {
          break;
        }

      kv3_db_trove_load(io_trove, l_dir);
      closedir(l_dir);
    }
  while (0);

  return;
}
