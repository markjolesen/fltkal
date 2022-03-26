/*
  kv3_db_xref_open.c

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
#include <stdlib.h>
/**/
#include "msysstat.h"
/**/
#include "mdirect.h"
#include "mfcntl.h"
#include "mr7.h"
#include "mstdlib.h"
#include "mstring.h"
#include "munistd.h"
/**/
#include "dbsuffix.h"
#include "dbxref.h"

#define kv3_db_xref_table_max 2

static void
  kv3_db_xref_insert(struct kv3_db_xref *const io_xref,
                     struct kv3_db_xref_table *const o_xtable)
{
  if ((*io_xref).m_head)
    {
      (*io_xref).m_tail->m_next = o_xtable;
      (*io_xref).m_tail = o_xtable;
    }
  else
    {
      (*io_xref).m_head = o_xtable;
      (*io_xref).m_tail = o_xtable;
    }

  return;
}

static void
  kv3_db_xref_table_malloc(struct kv3_db_xref_table **const o_xtable,
                           unsigned char const *i_prefix,
                           unsigned char const *i_lang,
                           unsigned char const *i_xlang)
{
  unsigned char *l_path;
  int l_handle;

  (*o_xtable) = 0;

  l_path = 0;

  do
    {
      mjo_path_join(&l_path, i_prefix, i_lang, i_xlang);

      if (0 == l_path)
        {
          break;
        }

      l_handle = open((char const *)l_path, O_RDONLY | O_BINARY);

      if (-1 == l_handle)
        {
          break;
        }

      mjo_malloc((void **const)o_xtable, 1, sizeof(**o_xtable));
      memset(*o_xtable, 0, sizeof(**o_xtable));

      mjo_strdup(&(*o_xtable)->m_lang, i_xlang);
      (*o_xtable)->m_handle = l_handle;
    }
  while (0);

  mjo_free((void **const) & l_path);

  return;
}

static void
  kv3_db_xref_load(struct kv3_db_xref *const io_xref,
                   DIR *const io_dir,
                   unsigned char const *i_prefix,
                   unsigned char const *i_lang)
{
  size_t l_count;
  struct dirent *l_entry;
  char *l_ptr;
  int l_rc;
  struct kv3_db_xref_table *l_xtable;

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

          l_rc = strcmp((char const *)i_lang, (*l_entry).d_name);

          if (l_rc)
            {
              break;
            }

          l_rc = strcmp(kv3_db_suffix_inf, l_ptr);

          if (0 == l_rc)
            {
              break;
            }

          l_rc = strcmp(kv3_db_suffix_table, l_ptr);

          if (0 == l_rc)
            {
              break;
            }

          kv3_db_xref_table_malloc(
            &l_xtable, i_prefix, i_lang, (unsigned char const *)l_ptr);

          if (0 == l_xtable)
            {
              break;
            }

          kv3_db_xref_insert(io_xref, l_xtable);
          l_count++;
        }
      while (0);

      if (kv3_db_xref_table_max <= l_count)
        {
          break;
        }
    }
  while (1);

  return;
}

extern void
  kv3_db_xref_open(struct kv3_db_xref *const io_xref,
                   unsigned char const *i_prefix,
                   unsigned char const *i_lang)
{
  DIR *l_dir;
  unsigned char const *l_prefix;

  do
    {
      if (0 == io_xref)
        {
          break;
        }

      kv3_db_xref_discharge(io_xref);
      kv3_db_xref_assign(io_xref);

      l_prefix
        = ((i_prefix && i_prefix[0]) ? i_prefix : (unsigned char const *)".");

      l_dir = opendir((char const *)l_prefix);

      if (0 == l_dir)
        {
          break;
        }

      kv3_db_xref_load(io_xref, l_dir, l_prefix, i_lang);

      closedir(l_dir);
    }
  while (0);

  return;
}
