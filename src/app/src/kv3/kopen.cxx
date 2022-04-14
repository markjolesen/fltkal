/*
  kv3_open.cxx

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
#include "msysstat.h"
//
#include "mdirect.h"
#include "mfcntl.h"
#include "mr7.h"
#include "mstdlib.h"
#include "mstring.h"
#include "mvector.h"
//
#include "dbsuffix.h"

#define kv3_container "kv3"

static bool
  folder_contains_kv3(unsigned char const *i_prefix)
{
  bool l_exit = false;

  do
    {
      DIR *l_dir = opendir(reinterpret_cast<char const *>(i_prefix));

      if (0 == l_dir)
        {
          break;
        }

      do
        {
          struct dirent *l_entry = readdir(l_dir);

          if (0 == l_entry)
            {
              break;
            }

          if (mjo_r7_period == (*l_entry).d_name[0])
            {
              continue;
            }

          unsigned char *l_ptr = reinterpret_cast<unsigned char *>(
            strrchr((*l_entry).d_name, mjo_r7_period));

          if (0 == l_ptr)
            {
              continue;
            }

          *l_ptr++ = 0;

          int l_rc = strcmp(kv3_db_suffix_table,
                            reinterpret_cast<char const *>(l_ptr));

          if (0 == l_rc)
            {
              l_exit = true;
              break;
            }
        }
      while (1);

      closedir(l_dir);
    }
  while (0);

  return l_exit;
}

static bool
  prefix_order_contains_kv3(unsigned char **o_prefix,
                            unsigned char const *i_prefix)
{
  (*o_prefix) = 0;

  bool l_exit = false;
  unsigned char *l_prefix;

  mjo_strdup(&l_prefix, i_prefix);

  unsigned char *l_tail = l_prefix;

  do
    {
      unsigned char *l_delim = reinterpret_cast<unsigned char *>(
        strrchr(reinterpret_cast<char *>(l_tail), mjo_r7_colon));

      size_t l_octets = strlen(reinterpret_cast<char const *>(l_tail));

      if (l_delim)
        {
          *l_delim++ = 0;
        }

      l_exit = folder_contains_kv3(l_tail);

      if (0 == (1 + l_octets))
        {
          break;
        }

      l_octets++;

      if (l_exit)
        {
          if (l_tail != l_prefix)
            {
              memcpy(reinterpret_cast<char *>(l_prefix),
                     reinterpret_cast<char *>(l_tail),
                     l_octets);
            }
          break;
        }

      unsigned char *l_tmp;

      int l_rc = mjo_add_size_t(&l_octets, l_octets, strlen(kv3_container));

      if (l_rc)
        {
          break;
        }

      l_rc = mjo_add_size_t(&l_octets, l_octets, 4);

      if (l_rc)
        {
          break;
        }

      mjo_malloc(reinterpret_cast<void **const>(&l_tmp), l_octets, 1);

      l_rc = snprintf(reinterpret_cast<char *>(l_tmp),
                      l_octets,
                      "%s%c%s",
                      l_tail,
                      mjo_r7_dirsep,
                      kv3_container);

      if (0 < l_rc && l_octets > static_cast<size_t>(l_rc))
        {
          l_exit = folder_contains_kv3(l_tmp);

          if (l_exit)
            {
              mjo_free(reinterpret_cast<void **const>(&l_prefix));
              l_prefix = l_tmp;
              break;
            }

          mjo_free(reinterpret_cast<void **const>(&l_tmp));
          l_tmp = 0;
        }

      if (0 == l_delim)
        {
          break;
        }

      l_tail = l_delim;
    }
  while (1);

  if (l_exit)
    {
      (*o_prefix) = l_prefix;
    }
  else
    {
      mjo_free(reinterpret_cast<void **const>(&l_prefix));
    }

  return l_exit;
}

static bool
  kv3_open_search_env(unsigned char **o_prefix)
{
  (*o_prefix) = 0;

  bool l_exit = false;

  mjo_vector_t l_vector;

  mjo_vector_malloc(
    &l_vector, (1024 * 8), mjo_vector_variant_char, mjo_vector_size_auto, 0);

  do
    {
      unsigned char const *l_env = reinterpret_cast<unsigned char const *>(
        getenv(reinterpret_cast<char const *>("XDG_DATA_HOME")));

      if (l_env && *l_env)
        {
          l_exit = prefix_order_contains_kv3(o_prefix, l_env);

          if (l_exit)
            {
              break;
            }
        }

      l_env = reinterpret_cast<unsigned char const *>(
        getenv(reinterpret_cast<char const *>("HOME")));

      if (l_env && *l_env)
        {
          unsigned char const *l_xdg_data_home1
            = reinterpret_cast<unsigned char const *>("/.local/share");

          mjo_vector_clear(l_vector);

          mjo_vector_push(&l_vector,
                          reinterpret_cast<void const *>(l_env),
                          strlen(reinterpret_cast<char const *>(l_env)));

          mjo_vector_push(
            &l_vector,
            reinterpret_cast<void const *>(l_xdg_data_home1),
            strlen(reinterpret_cast<char const *>(l_xdg_data_home1)));

          l_exit = prefix_order_contains_kv3(
            o_prefix, reinterpret_cast<unsigned char const *>(l_vector));

          if (l_exit)
            {
              break;
            }

          unsigned char const *l_xdg_data_home2
            = reinterpret_cast<unsigned char const *>("/usr/local/share");

          mjo_vector_clear(l_vector);

          mjo_vector_push(&l_vector,
                          reinterpret_cast<void const *>(l_env),
                          strlen(reinterpret_cast<char const *>(l_env)));

          mjo_vector_push(
            &l_vector,
            reinterpret_cast<void const *>(l_xdg_data_home2),
            strlen(reinterpret_cast<char const *>(l_xdg_data_home2)));

          l_exit = prefix_order_contains_kv3(
            o_prefix, reinterpret_cast<unsigned char const *>(l_vector));

          if (l_exit)
            {
              break;
            }
        }

      l_env = reinterpret_cast<unsigned char const *>(
        getenv(reinterpret_cast<char const *>("XDG_DATA_DIRS")));

      if (l_env && *l_env)
        {
          l_exit = prefix_order_contains_kv3(o_prefix, l_env);

          if (l_exit)
            {
              break;
            }
        }

      unsigned char const *l_xdg_data_dirs
        = reinterpret_cast<unsigned char const *>(
          "/usr/local/share:/usr/share");

      l_exit = prefix_order_contains_kv3(o_prefix, l_xdg_data_dirs);
    }
  while (0);

  mjo_vector_free(&l_vector);

  return l_exit;
}

static bool
  prefix_is_dot(unsigned char const *i_prefix)
{
  bool l_is_dot = false;

  if ((i_prefix[0]) && (mjo_r7_period == i_prefix[0]))
    {
      if (0 == i_prefix[1])
        {
          l_is_dot = true;
        }
      else if (mjo_r7_dirsep == i_prefix[1])
        {
          if (0 == i_prefix[2])
            {
              l_is_dot = true;
            }
          else if (mjo_r7_period == i_prefix[2])
            {
              if (0 == i_prefix[3])
                {
                  l_is_dot = true;
                }
            }
        }
    }

  return l_is_dot;
}

extern void
  kv3_open(unsigned char **o_prefix, unsigned char const *i_prefix)
{
  bool l_exit;

  (*o_prefix) = 0;

  do
    {
      if (i_prefix)
        {
          bool l_is_dot = prefix_is_dot(i_prefix);

          if (false == l_is_dot)
            {
              l_exit = prefix_order_contains_kv3(o_prefix, i_prefix);

              if (l_exit)
                {
                  break;
                }
            }
        }

#  if !defined(__CYGWIN__)                                                    \
    && (defined(_WIN32) || defined(__NT__) || defined(__DOS__))
      l_exit= prefix_order_contains_kv3(o_prefix, reinterpret_cast<unsigned char const*>("."));
#else
      l_exit = kv3_open_search_env(o_prefix);
#endif
    }
  while (0);

  return;
}
