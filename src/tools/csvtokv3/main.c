/*
  main.c

  Copyright (c) 2020 Dante University Foundation and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

     1. Redistributions of source code must retain the above copyright notice,
        this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY Dante University Foundation ``AS IS'' AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL Dante University Foundation OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

  The views and conclusions contained in the software and documentation are
  those of the authors and should not be interpreted as representing official
  policies, either expressed or implied, of Dante University Foundation.

  Dante University Foundation
  P.O. Box 812158
  Wellesley, MA 02482
  USA
  www.danteuniversity.org
*/
#include <assert.h>
#include <errno.h>
#include <stdio.h>

#include "dbsuffix.h"
#include "dict.h"
#include "dictstr.h"
#include "dictxref.h"
#include "marg.h"
#include "mdirect.h"
#include "mfcntl.h"
#include "mread.h"
#include "mstdlib.h"
#include "mstring.h"
#include "msysstat.h"
#include "mu8.h"
#include "munistd.h"
#include "mutf8.h"
#include "mvector.h"
#include "text.h"
#include "version.h"

#if defined(TRUE)
#  undef TRUE
#endif

#if defined(FALSE)
#  undef FALSE
#endif

#define FALSE 0
#define TRUE 1

#define CREATE_OFLAGS (O_WRONLY | O_CREAT | O_TRUNC | O_BINARY)
#define CREATE_MFLAGS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define OPEN_FLAGS (O_RDONLY | O_BINARY)

enum
{
  cell_octets_max
  = (sizeof(struct kv3_dict_row) + sizeof(struct kv3_dict_cell))
};

static struct kv3_dict g_dict[kv3_dict_records_max];
static struct kv3_dict_cell g_inf[kv3_dict_records_max];
size_t g_records;

static void
  path_join(unsigned char **const o_path,
            unsigned char const *i_prefix,
            unsigned char const *i_name,
            unsigned char const *i_suffix,
            unsigned char const *i_ext)
{
  unsigned char *l_tmp;

  mjo_path_join(&l_tmp, i_prefix, i_name, i_suffix);
  mjo_path_join(o_path, 0, l_tmp, i_ext);
  mjo_free((void **const) & l_tmp);

  return;
}

static int
  cell_unicode_validate(unsigned long const i_unicode)
{
  static unsigned char const l_cell_invalid[] = "!@#$%^&*_+=<>?;'\"\\\0";
  int l_bool;
  unsigned char const *l_ptr;

  l_bool = FALSE;

  do
    {
      if (mjo_r7_space > i_unicode)
        {
          break;
        }

      if (mjo_r7_del == i_unicode)
        {
          break;
        }

      if ((0x2000 <= i_unicode) && (0x206F >= i_unicode))
        {
          break;
        }

      l_bool = TRUE;

      for (l_ptr = l_cell_invalid; *l_ptr; l_ptr++)
        {
          if (i_unicode == *l_ptr)
            {
              l_bool = FALSE;
              break;
            }
        }
    }
  while (0);

  return l_bool;
}

static int
  macro_text_validate(unsigned char const *i_str,
                      unsigned char const *i_context)
{
  static unsigned char const g_text_invalid[]
    = " `~!@#$%^&*()_+=,<.>/?{}[]:;'\"\\|\0";
  int l_bool;
  unsigned char const *l_scan;
  unsigned char const *l_last;
  unsigned char c;

  l_bool = FALSE;

  if (i_str)
    {
      l_scan = (unsigned char const *)strstr((char const *)i_str,
                                             (char const *)g_text_invalid);

      if (0 == l_scan)
        {
          mjo_u8_validate(&l_bool, (unsigned char **)&l_last, i_str);

          if (l_bool)
            {
              for (l_last = i_str; *l_last; l_last++)
                {
                  if ((mjo_r7_space > *l_last) || (mjo_r7_del == *l_last))
                    {
                      c = *l_last;
                      l_bool = FALSE;
                      break;
                    }
                }
            }
          else
            {
              c = *l_last;
            }
        }
      else
        {
          c = *l_scan;
        }

      if (FALSE == l_bool)
        {
          fprintf(stderr,
                  "Error: %s contains an invalid character\n\t'(%c)'\n",
                  i_context,
                  c);
        }
    }
  else
    {
      fprintf(stderr, "Error: %s is empty\n", i_context);
    }

  return l_bool;
}

static int
  text_subject_validate(unsigned char const *i_str)
{
  int l_bool;
  int l_count;
  unsigned char *l_head;
  unsigned char *l_left;
  unsigned char *l_right;
  unsigned char *l_str;

  l_bool = FALSE;
  l_count = 0;
  mjo_strdup(&l_str, i_str);
  l_head = l_str;

  do
    {
      l_left = (unsigned char *)strchr((char *)l_head, kv3_text_subject_open);

      l_right
        = (unsigned char *)strchr((char *)l_head, kv3_text_subject_close);

      if ((0 == l_left) && (0 == l_right))
        {
          l_bool = TRUE;
          break;
        }

      if (0 == l_left)
        {
          fprintf(stderr,
                  "Error: Subject macro is missing opening ('%c') bracket\n",
                  kv3_text_subject_open);
          break;
        }

      if (0 == l_right)
        {
          fprintf(stderr,
                  "Error: Subject macro is missing closing '%c' bracket\n",
                  kv3_text_subject_close);
          break;
        }

      *l_right++ = 0;
      l_count++;

      l_bool
        = macro_text_validate((l_left + 1), (unsigned char const *)"Subject");

      if (FALSE == l_bool)
        {
          break;
        }

      l_head = l_right;
    }
  while (1);

  if (1 < l_count)
    {
      strcpy((char *)l_str, (char const *)i_str);
      mjo_u8_trim(l_str);
      fprintf(
        stderr, "Error: Subject contains too many items\n\t'(%s)'\n", l_str);
      l_bool = 0;
    }

  mjo_free((void **const) & l_str);

  return l_bool;
}

static int
  link_cell2digit(unsigned char c)
{
  int l_digit;

  l_digit = -1;

  do
    {
      if (mjo_r7_upr_a > c)
        {
          break;
        }

      if (mjo_r7_upr_z < c)
        {
          break;
        }

      l_digit = (c - mjo_r7_upr_a);
    }
  while (0);

  return l_digit;
}

static int
  link_reference_validate(unsigned char const *i_str)
{
  int l_bool;
  int l_ones;
  int l_sum;
  int l_tens;
  unsigned char const *l_ptr;

  l_bool = FALSE;
  l_ptr = i_str;

  do
    {
      l_ones = link_cell2digit(*l_ptr++);

      if (0 > l_ones)
        {
          break;
        }

      if (0 == *l_ptr)
        {
          l_bool = TRUE;
          break;
        }

      l_tens = link_cell2digit(*l_ptr++);

      if (0 >= l_tens)
        {
          break;
        }

      if (0 != *l_ptr)
        {
          break;
        }

      l_sum = (l_ones + (10 * l_tens));

      if ((0 > l_sum) || (kv3_dict_row_cell_count <= (size_t)l_sum))
        {
          break;
        }

      l_bool = TRUE;
    }
  while (0);

  return l_bool;
}

static int
  link_validate(unsigned char const *i_str)
{
  int l_bool;
  unsigned char *l_head;
  unsigned char *l_left;
  unsigned char *l_ptr;
  unsigned char *l_right;
  unsigned char *l_str;

  mjo_strdup(&l_str, i_str);
  l_head = l_str;

  do
    {
      l_left = (unsigned char *)strchr((char *)l_head, kv3_text_link_open);

      l_right = (unsigned char *)strchr((char *)l_head, kv3_text_link_close);

      if (0 == l_left && 0 == l_right)
        {
          l_bool = TRUE;
          break;
        }

      l_bool = FALSE;

      if (0 == l_left)
        {
          fprintf(stderr,
                  "Error: Link macro is missing opening ('%c') bracket\n",
                  kv3_text_link_open);
          break;
        }

      if (0 == l_right)
        {
          fprintf(stderr,
                  "Error: Link macro is missing closing '%c' bracket\n",
                  kv3_text_link_close);
          break;
        }

      *l_left++ = 0;
      *l_right++ = 0;

      l_bool = link_reference_validate(l_left);

      if (FALSE == l_bool)
        {
          fprintf(stderr,
                  "Error: link macro contains invalid cell ('%s') "
                  "reference\n",
                  l_left);
          break;
        }

      l_head = l_right;
    }
  while (1);

  mjo_free((void **const) & l_str);

  return l_bool;
}

static int
  text_group_validate(unsigned char const *i_str)
{
  int l_bool;
  size_t l_count;
  unsigned char *l_head;
  unsigned char *l_str;
  unsigned char *l_ptr;

  l_bool = FALSE;
  l_count = 0;
  mjo_strdup(&l_str, i_str);
  l_head = l_str;

  do
    {
      l_ptr
        = (unsigned char *)strchr((char *)l_head, kv3_text_set_list_separator);

      if (0 == l_ptr)
        {
          l_bool = TRUE;
          break;
        }

      l_count++;
      *l_ptr++ = 0;

      l_bool = macro_text_validate(l_head, (unsigned char const *)"Group");

      if (FALSE == l_bool)
        {
          break;
        }

      l_head = l_ptr;
    }
  while (1);

  if ((0 == l_count) && (0 == *i_str))
    {
      fprintf(stderr, "Error: Group contains an empty item\n");
      l_bool = FALSE;
    }
  else if (kv3_text_set_max_blocks < l_count)
    {
      fprintf(
        stderr, "Error: Group contains too many items\n\t'(%s)'\n", i_str);
      l_bool = FALSE;
    }

  mjo_free((void **const) & l_str);

  return l_bool;
}

static int
  text_list_validate(unsigned char const *i_str)
{
  int l_bool;
  size_t l_count;
  unsigned char *l_head;
  unsigned char *l_ptr;
  unsigned char *l_str;

  l_bool = FALSE;
  l_count = 0;
  mjo_strdup(&l_str, i_str);
  l_head = l_str;

  do
    {
      l_ptr = (unsigned char *)strchr((char *)l_head,
                                      kv3_text_set_group_separator);

      if (0 == l_ptr)
        {
          l_bool = TRUE;
          break;
        }

      *l_ptr++ = 0;

      l_bool = text_group_validate(l_head);

      if (FALSE == l_bool)
        {
          break;
        }

      l_count++;
      l_head = l_ptr;
    }
  while (1);

  if (kv3_text_set_max_groups < l_count)
    {
      strcpy((char *)l_str, (char const *)i_str);
      mjo_u8_trim(l_str);
      fprintf(
        stderr, "Error: Group contains too many items\n\t'(%s)'\n", l_str);
      l_bool = FALSE;
    }

  mjo_free((void **const) & l_str);

  return l_bool;
}

static int
  text_set_validate(unsigned char const *i_str)
{
  int l_bool;
  size_t l_count;
  unsigned char *l_left;
  unsigned char *l_head;
  unsigned char *l_ptr;
  unsigned char *l_right;
  unsigned char *l_str;

  l_bool = FALSE;
  l_count = 0;
  mjo_strdup(&l_str, i_str);
  l_head = l_str;

  do
    {
      l_left = (unsigned char *)strchr((char *)l_head, kv3_text_set_open);

      l_right = (unsigned char *)strchr((char *)l_head, kv3_text_set_close);

      if (0 == l_left && 0 == l_right)
        {
          l_bool = 1;
          break;
        }

      if (0 == l_left)
        {
          fprintf(stderr,
                  "Error: Set macro is missing opening ('%c') bracket\n",
                  kv3_text_set_open);
          break;
        }

      if (0 == l_right)
        {
          fprintf(stderr,
                  "Error: Set macro is missing closing '%c' bracket\n",
                  kv3_text_set_close);
          break;
        }

      if ((ptrdiff_t)l_head != (ptrdiff_t)l_left)
        {
          *l_left = 0;
          fprintf(stderr,
                  "Error: Set macro contians leading characters\n'\t(%s)'\n",
                  l_str);
          break;
        }

      *l_right++ = 0;
      *l_left++ = 0;

      mjo_u8_trim(l_left);

      if (0 == *l_left)
        {
          fprintf(stderr, "Error: Set macro is empty\n");
          break;
        }

      l_bool = text_list_validate(l_left);

      if (FALSE == l_bool)
        {
          break;
        }

      l_count++;
      l_head = l_right;
    }
  while (1);

  mjo_free((void **const) & l_str);

  if (1 < l_count)
    {
      fprintf(stderr,
              "Error: Mulitple sets found (there can be only "
              "one)\n\t'(%s)'\n",
              i_str);
      l_bool = FALSE;
    }

  return l_bool;
}

static int
  cell_validate(unsigned char *io_str)
{
  int l_bool;
  unsigned char *l_ptr;
  unsigned char *l_ptr2;

  do
    {
      l_bool = text_subject_validate(io_str);

      if (FALSE == l_bool)
        {
          break;
        }

      l_bool = link_validate(io_str);

      if (FALSE == l_bool)
        {
          break;
        }

      l_bool = text_set_validate(io_str);
    }
  while (0);

  return l_bool;
}

static int
  g_dict_validate()
{
  int l_bool;
  struct kv3_dict_cell *l_cell;
  size_t l_col;
  size_t l_row;
  size_t l_record;

  l_bool = TRUE;

  for (l_record = 1; l_bool && g_records > l_record; l_record++)
    {
      kv3_dict_set_internal(&g_dict[l_record]);

      for (l_row = 0; l_bool && kv3_dict_row_count > l_row; l_row++)
        {
          for (l_col = 0; kv3_dict_row_cell_count > l_col; l_col++)
            {
              l_cell = &g_dict[l_record].m_row[l_row].m_cell[l_col];
              l_bool = cell_validate(l_cell->m_text);

              if (FALSE == l_bool)
                {
                  fprintf(stderr,
                          "Error: infinitive='%s' row='%lu' col='%lu'\n",
                          g_dict[l_record].m_row[0].m_cell[0].m_text,
                          l_row,
                          l_col);
                  break;
                }
            }
        }
    }

  return l_bool;
}

static int
  g_inf_load()
{
  int l_bool;
  struct kv3_dict_cell *l_cell;
  int l_rc;
  size_t l_slot;
  char *l_ptr;

  l_rc = 0;
  memset(g_inf, 0, sizeof(g_inf));

  fprintf(stdout, "Loading infinitives...\n");

  for (l_slot = 1; g_records > l_slot; l_slot++)
    {
      l_cell = &g_dict[l_slot].m_row[0].m_cell[0];

      kv3_dict_cell_set_internal(l_cell);

      l_bool = macro_text_validate(l_cell->m_text,
                                   (unsigned char const *)"Infinitive");

      if (FALSE == l_bool)
        {
          l_rc = MJO_FAIL;
          break;
        }

      strcpy((char *)g_inf[l_slot - 1].m_text, (char const *)l_cell->m_text);
    }

  fprintf(stdout, "...finished\n");

  return l_rc;
}

static int
  g_inf_dump(unsigned char const *i_name)
{
  struct kv3_dict_cell *l_cell;
  int l_rc;
  int l_fd_out;
  size_t l_slot;

  l_rc = MJO_OK;

  fprintf(stdout, "Writing infintive table...\n");

  do
    {
      errno = 0;
      l_fd_out = open((char const *)i_name, CREATE_OFLAGS, CREATE_MFLAGS);

      if (-1 == l_fd_out)
        {
          fprintf(stderr, "Error (%d): '%s'\n", errno, strerror(errno));
          fprintf(stderr, "\t(Unable to create file)\n");
          fprintf(stderr, "\t('%s')\n", i_name);
          l_rc = MJO_FAIL;
          break;
        }

      fprintf(stdout, "\t\tInfinitive table (output):\n");
      fprintf(stdout, "\t\t\t'%s'\n", i_name);

      l_cell = g_inf;

      for (l_slot = 1; g_records > l_slot; l_slot++)
        {
          kv3_dict_cell_set_external(l_cell);
          (*l_cell).m_comma_or_cr = mjo_r7_cr;
          (*l_cell).m_space_or_lf = mjo_r7_lf;
          write(l_fd_out, l_cell, sizeof(*l_cell));
          kv3_dict_cell_set_internal(l_cell);
          l_cell++;
        }

      close(l_fd_out);
    }
  while (0);

  fprintf(stdout, "...finished\n");

  return l_rc;
}

static int
  g_xref_dump(int const i_fd_out)
{
  struct kv3_dict_xref *l_xtab;
  size_t l_slot;

  l_xtab = (struct kv3_dict_xref *)g_dict;

  fprintf(stdout, "Writing cross reference table...\n");

  for (l_slot = 0; (g_records - 1) > l_slot; l_slot++, l_xtab++)
    {
      kv3_dict_xref_set_external(l_xtab);
      write(i_fd_out, l_xtab, sizeof(*l_xtab));
    }

  fprintf(stdout, "...finished\n");

  return 0;
}

static int
  dict_dump(int const i_fd_out)
{
  size_t l_slot;

  fprintf(stdout, "Writing dictionary table...\n");

  for (l_slot = 0; g_records > l_slot; l_slot++)
    {
      kv3_dict_set_external(&g_dict[l_slot]);
      write(i_fd_out, &g_dict[l_slot], sizeof(g_dict[0]));
    }

  fprintf(stdout, "...finished\n");

  return 0;
}

static void
  cell_compare(int *const o_result,
               struct kv3_dict_cell const *const i_obj_to_find,
               struct kv3_dict_cell const *const i_obj_to_compare)
{
  (*o_result) = strcmp((char const *)i_obj_to_find->m_text,
                       (char const *)i_obj_to_compare->m_text);
  return;
}

static int
  xref_compare(struct kv3_dict_xref const *l_xref1,
               struct kv3_dict_xref const *l_xref2)
{
  int l_rc;

  l_rc = strcmp((char const *)l_xref1->m_cell[0].m_text,
                (char const *)l_xref2->m_cell[0].m_text);

  return l_rc;
}

static int
  dict_compare(struct kv3_dict const *l_dict1, struct kv3_dict const *l_dict2)
{
  int l_rc;

  l_rc = strcmp((char const *)l_dict1->m_row[0].m_cell[0].m_text,
                (char const *)l_dict2->m_row[0].m_cell[0].m_text);

  return l_rc;
}

static int
  g_xref_lookup_validate()
{
  int l_bool;
  size_t l_slot;
  size_t l_where;
  struct kv3_dict_xref *l_xtab;

  l_xtab = (struct kv3_dict_xref *)g_dict;

  for (l_slot = 0; (g_records - 1) > l_slot; l_slot++)
    {
      mjo_search_binary(
        &l_bool,
        &l_where,
        g_inf,
        sizeof(g_inf[0]),
        (g_records - 1),
        (void (*)(int *const, void const *, void const *))cell_compare,
        &l_xtab[l_slot].m_cell[0]);

      if (FALSE == l_bool)
        {
          fprintf(stderr,
                  "Error: Cross reference table contains an unkown "
                  "infinitive\n");
          fprintf(stderr, "('%s')\n", l_xtab[l_slot].m_cell[0].m_text);
          break;
        }
    }

  return l_bool;
}

static int
  g_xref_validate()
{
  int l_bool;
  int l_rc2;
  unsigned char const *l_inf_kv3;
  unsigned char const *l_inf_xtab;
  size_t l_slot;
  struct kv3_dict_xref *l_xtab;

  l_bool = TRUE;
  l_xtab = (struct kv3_dict_xref *)g_dict;

  for (l_slot = 0; (g_records - 1) > l_slot; l_slot++, l_xtab++)
    {
      l_inf_kv3 = g_inf[l_slot].m_text;
      l_inf_xtab = l_xtab->m_cell[0].m_text;

      l_rc2 = strcmp((char *const)l_inf_kv3, (char *const)l_inf_xtab);

      if (l_rc2)
        {
          fprintf(stderr, "Error: Infinitives do not match\n");
          fprintf(stderr, "\t'(%s')' != '(%s)'\n", l_inf_kv3, l_inf_xtab);
          fprintf(stderr, "\trecord=%lu\n", l_slot);
          l_bool = FALSE;
          break;
        }
    }

  return l_bool;
}

static int
  cell_filter(unsigned char *io_str)
{
  int l_bool;
  int l_bool2;
  unsigned char const *l_head;
  unsigned char const *l_last;
  struct mjo_utf8 l_peek;
  enum mjo_status l_status;
  unsigned char *l_tail;
  unsigned long l_unicode;

  l_tail = (unsigned char *)strchr((char *)io_str, kv3_dict_str_epsilon);

  if (l_tail)
    {
      *l_tail = 0;
    }

  mjo_u8_trim(io_str);

  l_head = io_str;
  l_tail = io_str;

  do
    {
      mjo_utf8_compose(&l_status, &l_last, &l_peek, l_head);

      if (mjo_status_eof == l_status)
        {
          l_bool = 1;
          break;
          ;
        }

      if (l_status)
        {
          l_bool = 0;
          break;
        }

      mjo_utf8_is_whitespace(&l_bool, &l_peek);

      if (l_bool)
        {
          do
            {
              l_head = l_last;

              mjo_utf8_compose(&l_status, &l_last, &l_peek, l_head);

              if (l_status)
                {
                  if (mjo_status_eof != l_status)
                    {
                      l_bool = 0;
                    }
                  break;
                }

              mjo_utf8_is_whitespace(&l_bool2, &l_peek);

              if (0 == l_bool2)
                {
                  *l_tail++ = mjo_r7_space;
                  break;
                }
            }
          while (1);
        }
      else if (sizeof(l_unicode) >= l_peek.m_octets)
        {
          l_unicode = *(unsigned long *)l_peek.m_block;
          l_bool = cell_unicode_validate(l_unicode);
        }

      if (0 == l_bool)
        {
          break;
        }

      if ((ptrdiff_t)l_head != (ptrdiff_t)l_tail)
        {
          memcpy(l_tail, l_peek.m_block, l_peek.m_octets);
        }

      l_tail += l_peek.m_octets;
      l_head = l_last;
    }
  while (1);

  *l_tail = 0;

  mjo_u8_trim_right(io_str);

  if (0 == l_bool)
    {
      fprintf(stderr,
              "Error: Cell contains an invalid character\n\t'(%s)'\n",
              l_peek.m_block);
    }

  return l_bool;
}

static int
  csvtokv3_xref_handle_load(int const i_fd_in)
{
  int l_bool;
  size_t l_col;
  size_t l_count;
  int l_eol;
  int l_rc;
  size_t l_octets;
  char *l_ptr;
  size_t l_record;
  enum mjo_status l_status;
  struct kv3_dict_xref *l_xtab;
  mjo_vector_t l_scratch;

  memset(g_dict, 0, sizeof(g_dict));

  l_col = 0;
  l_rc = 0;
  l_record = 0;

  mjo_vector_malloc(&l_scratch,
                    cell_octets_max,
                    mjo_vector_variant_char,
                    mjo_vector_size_auto,
                    0);

  l_xtab = (struct kv3_dict_xref *)g_dict;
  fprintf(stdout, "Loading cross reference table...\n");

  do
    {
      if (kv3_dict_xref_cell_count < l_col)
        {
          fprintf(stderr,
                  "Error: Cross reference table contains too many columns\n");
          fprintf(
            stderr, "\t('%lu' > '%d')\n", l_col, kv3_dict_xref_cell_count);
          l_rc = MJO_FAIL;
          break;
        }

      l_rc = mjo_read_csv(&l_eol,
                          &l_status,
                          &l_scratch,
                          cell_octets_max,
                          (mjo_read_t)read,
                          (mjo_handle_t)i_fd_in);

      if (l_rc)
        {
          fprintf(stderr, "ERROR: Unable to read\n");
          fprintf(stderr, "\terrno(%d): %s)\n", errno, strerror(errno));
          fprintf(stderr, "\trecord: %lu)\n", l_record + 1);
          break;
        }

      if (l_status)
        {
          switch (l_status)
            {
            case mjo_status_eof:
              l_rc = MJO_OK;
              break;
            default:
              fprintf(stderr, "ERROR: Cell too large\n");
              fprintf(stderr, "\trecord: %lu)\n", l_record + 1);
              l_rc = MJO_FAIL;
              break;
            }
          break;
        }

      l_bool = cell_filter((unsigned char *)l_scratch);

      if (0 == l_bool)
        {
          l_rc = MJO_FAIL;
          break;
        }

      if (0 == l_col)
        {
          l_octets = strlen((char const *)l_scratch);

          if (0 == l_octets)
            {
              fprintf(stderr,
                      "Error: Cross reference table contains an invalid "
                      "infinity\n");
              fprintf(stderr, "\t(cell length is empty/zero)\n");
              l_rc = MJO_FAIL;
              break;
            }
        }

      kv3_dict_cell_copy_str(&l_xtab[l_record].m_cell[l_col],
                             (unsigned char *)l_scratch);

      if (0 == l_eol)
        {
          l_col++;
        }
      else
        {
          l_col = 0;
          l_record++;
        }
    }
  while (1);

  mjo_vector_free(&l_scratch);

  if ((g_records - 1) != l_record)
    {
      fprintf(stderr,
              "Error: The number of records in the dictonary(%lu)\n",
              (g_records - 1));
      fprintf(stderr,
              "\tdo not match the number of records (%lu) in the\n",
              l_record);
      fprintf(stderr, "\tcross reference table\n");
      l_rc = MJO_FAIL;
    }

  if (l_rc)
    {
      fprintf(stderr, "Error: Cross reference table is invalid\n");
      fprintf(stderr, "\tEnded (row='%lu', column='%lu')", l_record, l_col);
    }

  fprintf(stdout, "...finished\n");

  return l_rc;
}

static int
  csvtokv3_xref_handle_process(int const i_fd_out, int const i_fd_in)
{
  int l_bool;
  int l_rc;

  do
    {
      l_rc = csvtokv3_xref_handle_load(i_fd_in);

      if (l_rc)
        {
          break;
        }

      qsort(g_dict,
            (g_records - 1),
            sizeof(struct kv3_dict_xref),
            (int (*)(const void *, const void *))xref_compare);

      l_bool = g_xref_lookup_validate();

      if (0 == l_bool)
        {
          l_rc = -1;
          break;
        }

      l_bool = g_xref_validate();

      if (0 == l_bool)
        {
          l_rc = -1;
          break;
        }

      l_rc = g_xref_dump(i_fd_out);
    }
  while (0);

  return l_rc;
}

static int
  csvtokv3_table_handle_load(int const i_fd_out, int const i_fd_in)
{
  static unsigned char l_str[cell_octets_max];
  int l_bool;
  size_t l_col;
  size_t l_count;
  int l_eof;
  int l_eol;
  int l_rc;
  size_t l_octets;
  char *l_ptr;
  size_t l_row;
  enum mjo_status l_status;
  int l_truncated;
  mjo_vector_t l_scratch;

  memset(g_dict, 0, sizeof(g_dict));
  g_records = 0;

  l_col = 0;
  l_rc = 0;
  l_row = 0;

  mjo_vector_malloc(&l_scratch,
                    cell_octets_max,
                    mjo_vector_variant_char,
                    mjo_vector_size_auto,
                    0);

  fprintf(stdout, "Loading dictionary table...\n");

  do
    {
      if (kv3_dict_row_cell_count < l_col)
        {
          fprintf(stderr, "Error: table contains an invalid column\n");
          fprintf(stderr, "\t(too many columns)\n");
          fprintf(
            stderr, "\t('%lu' > '%d')\n", l_col, kv3_dict_row_cell_count);
          l_rc = MJO_FAIL;
          break;
        }

      if (kv3_dict_records_max < g_records)
        {
          fprintf(stderr, "Error: table contains too many records\n");
          fprintf(
            stderr, "\t('%lu' > '%d')\n", g_records, kv3_dict_records_max);
          l_rc = MJO_FAIL;
          break;
        }

      l_rc = mjo_read_csv(&l_eol,
                          &l_status,
                          &l_scratch,
                          cell_octets_max,
                          (mjo_read_t)read,
                          (mjo_handle_t)i_fd_in);

      if (l_rc)
        {
          fprintf(stderr, "ERROR: Unable to read\n");
          fprintf(stderr, "\trecord: %lu\n", g_records + 1);
          fprintf(stderr, "\tcolumn: %lu\n", l_col);
          fprintf(stderr, "\terrno(%d): %s)\n", errno, strerror(errno));
          break;
        }

      if (l_status)
        {
          switch (l_status)
            {
            case mjo_status_eof:
              l_rc = MJO_OK;
              break;
            default:
              fprintf(stderr, "ERROR: Cell too large\n");
              fprintf(stderr, "\trecord: %lu)\n", g_records + 1);
              l_rc = MJO_FAIL;
              break;
            }
          break;
        }

      l_bool = cell_filter((unsigned char *)l_scratch);

      if (0 == l_bool)
        {
          l_rc = MJO_FAIL;
          break;
        }

      kv3_dict_cell_copy_str(&g_dict[g_records].m_row[l_row].m_cell[l_col],
                             (unsigned char *)l_scratch);

      if (0 == l_eol)
        {
          l_col++;
        }
      else
        {
          l_col = 0;
          l_row++;

          if (kv3_dict_row_count <= l_row)
            {
              l_row = 0;
              g_records++;
            }
        }
    }
  while (1);

  mjo_vector_free(&l_scratch);

  if (l_rc)
    {
      fprintf(stderr, "Error: dictionary table is invalid\n");
      fprintf(stderr,
              "\tEnded (record='%lu' row='%lu', column='%lu')",
              g_records,
              l_row,
              l_col);
    }

  fprintf(stdout, "...finished\n");

  return l_rc;
}

static int
  csvtokv3_table_name_process(unsigned char const *i_name)
{
  int l_fd_out;
  int l_fd_in;
  unsigned char *l_name_out;
  unsigned char *l_ptr;
  int l_rc;

  l_fd_out = -1;
  l_fd_in = -1;
  mjo_strdup(&l_name_out, i_name);

  fprintf(stdout, "Processing CSV table...\n");
  fprintf(stdout, "\t\tCSV table (input):\n");
  fprintf(stdout, "\t\t\t'%s'\n", i_name);

  do
    {
      l_ptr = (unsigned char *)strrchr((char *)l_name_out, mjo_r7_period);

      if (0 == l_ptr)
        {
          fprintf(
            stderr, "Programming error: %s:%d\n", __FUNCTION__, __LINE__);
          l_rc = -1;
          break;
        }

      *l_ptr = 0;

      l_fd_out = open((char const *)l_name_out, CREATE_OFLAGS, CREATE_MFLAGS);

      if (-1 == l_fd_out)
        {
          fprintf(stderr, "Unable to create file: '%s'\n", l_name_out);
          l_rc = errno;
          break;
        }

      l_fd_in = open((char const *)i_name, OPEN_FLAGS);

      if (-1 == l_fd_in)
        {
          fprintf(stderr, "Unable to open file: '%s'\n", i_name);
          l_rc = errno;
          break;
        }

      fprintf(stdout, "\t\tdictionary (output):\n");
      fprintf(stdout, "\t\t\t'%s'\n", l_name_out);

      l_rc = csvtokv3_table_handle_load(l_fd_out, l_fd_in);

      if (l_rc)
        {
          break;
        }

      if (2 > g_records)
        {
          fprintf(stderr, "Error: dictionary is invalid\n");
          fprintf(stderr, "\t(Contains only '%lu' records)\n", g_records);
          l_rc = -1;
          break;
        }

      qsort(&g_dict[1],
            (g_records - 1),
            sizeof(g_dict[0]),
            (int (*)(const void *, const void *))dict_compare);

      dict_dump(l_fd_out);
    }
  while (0);

  mjo_free((void **const) & l_name_out);

  if (-1 != l_fd_out)
    {
      close(l_fd_out);
    }

  if (-1 != l_fd_in)
    {
      close(l_fd_in);
    }

  fprintf(stdout, "...finished\n");

  return l_rc;
}

static int
  csvtokv3_xref_name_process(unsigned char const *i_name)
{
  int l_fd_in;
  int l_fd_out;
  unsigned char *l_name_out;
  unsigned char *l_ptr;
  int l_rc;

  l_fd_out = -1;
  l_fd_in = -1;
  mjo_strdup(&l_name_out, i_name);

  fprintf(stdout, "Processing CSV Cross reference table...\n");
  fprintf(stdout, "\t\tCSV table (input):\n");
  fprintf(stdout, "\t\t\t'%s'\n", i_name);

  do
    {
      l_ptr = (unsigned char *)strrchr((char *)l_name_out, mjo_r7_period);

      if (0 == l_ptr)
        {
          fprintf(
            stderr, "Programming error: %s:%d\n", __FUNCTION__, __LINE__);
          l_rc = -1;
          break;
        }

      *l_ptr = 0;

      l_fd_out = open((char const *)l_name_out, CREATE_OFLAGS, CREATE_MFLAGS);

      if (-1 == l_fd_out)
        {
          fprintf(stderr, "Unable to create file: '%s'\n", l_name_out);
          l_rc = errno;
          break;
        }

      l_fd_in = open((char const *)i_name, OPEN_FLAGS);

      if (-1 == l_fd_in)
        {
          fprintf(stderr, "Unable to open file: '%s'\n", i_name);
          l_rc = errno;
          break;
        }

      fprintf(stdout, "\t\tCross reference table (output):\n");
      fprintf(stdout, "\t\t\t'%s'\n", l_name_out);

      l_rc = csvtokv3_xref_handle_process(l_fd_out, l_fd_in);
    }
  while (0);

  mjo_free((void **const) & l_name_out);

  if (-1 != l_fd_out)
    {
      close(l_fd_out);
    }

  if (-1 != l_fd_in)
    {
      close(l_fd_in);
    }

  fprintf(stdout, "...finished\n");

  return l_rc;
}

static int
  csvtokv3_xref_entry_process(unsigned char const *i_prefix,
                              unsigned char const *i_lang,
                              struct dirent const *const i_entry)
{
  unsigned char *l_name;
  unsigned char *l_tmp;
  unsigned char *l_ptr;
  int l_rc;
  int l_rc2;

  l_rc = 0;
  l_name = 0;
  l_tmp = 0;

  do
    {
      mjo_strdup(&l_name, (unsigned char const *)(*i_entry).d_name);

      if (mjo_r7_period == *l_name)
        {
          break;
        }

      l_ptr = (unsigned char *)strrchr((char const *)l_name, mjo_r7_period);

      if (0 == l_ptr)
        {
          break;
        }

      *l_ptr++ = 0;

      l_rc2 = strcmp(mjo_suffix_csv, (char const *)l_ptr);

      if (l_rc2)
        {
          break;
        }

      l_ptr = (unsigned char *)strrchr((char const *)l_name, mjo_r7_period);

      if (0 == l_ptr)
        {
          break;
        }

      *l_ptr++ = 0;

      l_rc2 = strcmp((char const *)i_lang, (char const *)l_name);

      if (l_rc2)
        {
          break;
        }

      l_rc2 = strcmp(kv3_db_suffix_table, (char const *)l_ptr);

      if (0 == l_rc2)
        {
          break;
        }

      l_rc2 = strcmp(kv3_db_suffix_inf, (char const *)l_ptr);

      if (0 == l_rc2)
        {
          break;
        }

      path_join(&l_tmp,
                i_prefix,
                i_lang,
                l_ptr,
                (unsigned char const *)mjo_suffix_csv);

      l_rc = csvtokv3_xref_name_process(l_tmp);

      mjo_free((void **const) & l_tmp);
    }
  while (0);

  mjo_free((void **const) & l_name);

  return l_rc;
}

static int
  csvtokv3_xref_dir_process(unsigned char const *i_prefix,
                            unsigned char const *i_lang)
{
  DIR *l_dir;
  struct dirent *l_entry;
  int l_rc;
  unsigned char *l_ptr;

  fprintf(stdout, "Scanning cross reference tables...\n");
  fprintf(stdout, "\t\tdirectory:\n");
  fprintf(stdout, "\t\t\t'%s'\n", i_prefix);
  fprintf(stdout, "\t\tlanguage:\n");
  fprintf(stdout, "\t\t\t'%s'\n", i_lang);

  do
    {
      errno = 0;
      l_dir = opendir((char const *)i_prefix);

      if (0 == l_dir)
        {
          fprintf(stderr, "Error (%d): '%s'\n", errno, strerror(errno));
          fprintf(stderr, "\t(Unable to open directory)\n");
          fprintf(stderr, "\t('%s')\n", i_prefix);
          l_rc = errno;
          break;
        }

      do
        {
          l_entry = readdir(l_dir);

          if (0 == l_entry)
            {
              break;
            }

          l_rc = csvtokv3_xref_entry_process(i_prefix, i_lang, l_entry);

          if (l_rc)
            {
              break;
            }
        }
      while (1);

      closedir(l_dir);
    }
  while (0);

  return l_rc;
}

static int
  csvtokv3_lang_process(unsigned char const *i_prefix,
                        unsigned char const *i_lang)
{
  int l_bool;
  DIR *l_dir;
  struct dirent *l_entry;
  unsigned char *l_name;
  char *l_ptr;
  int l_rc;
  size_t l_size;

  l_dir = 0;

  fprintf(stdout, "Processing language table...\n");
  fprintf(stdout, "\t\tdirectory:\n");
  fprintf(stdout, "\t\t\t'%s'\n", i_prefix);
  fprintf(stdout, "\t\tlanguage:\n");
  fprintf(stdout, "\t\t\t'%s'\n", i_lang);

  do
    {
      path_join(&l_name,
                i_prefix,
                i_lang,
                (unsigned char const *)kv3_db_suffix_table,
                (unsigned char const *)mjo_suffix_csv);

      l_rc = csvtokv3_table_name_process(l_name);

      mjo_free((void **const) & l_name);

      if (l_rc)
        {
          break;
        }

      l_bool = g_dict_validate();

      if (0 == l_bool)
        {
          break;
        }

      l_rc = g_inf_load();

      if (l_rc)
        {
          break;
        }

      mjo_path_join(
        &l_name, i_prefix, i_lang, (unsigned char const *)kv3_db_suffix_inf);

      l_rc = g_inf_dump(l_name);

      mjo_free((void **const) & l_name);

      if (l_rc)
        {
          break;
        }

      l_rc = csvtokv3_xref_dir_process(i_prefix, i_lang);
    }
  while (0);

  if (0 == l_rc)
    {
      fprintf(stdout, "Processed '%lu' records\n", (g_records - 1));
    }

  fprintf(stdout, "...finished\n");

  return l_rc;
}

static int
  csvtotokv3_dir_entry_process(unsigned char const *i_prefix,
                               struct dirent const *const i_entry)
{
  unsigned char *l_lang;
  unsigned char *l_ptr;
  int l_rc;
  int l_rc2;

  l_rc = MJO_OK;
  l_lang = 0;

  do
    {
      mjo_strdup(&l_lang, (unsigned char const *)(*i_entry).d_name);

      if (mjo_r7_period == *l_lang)
        {
          break;
        }

      l_ptr = (unsigned char *)strrchr((char const *)l_lang, mjo_r7_period);

      if (0 == l_ptr)
        {
          break;
        }

      *l_ptr++ = 0;

      l_rc2 = strcmp(mjo_suffix_csv, (char const *)l_ptr);

      if (l_rc2)
        {
          break;
        }

      l_ptr = (unsigned char *)strrchr((char const *)l_lang, mjo_r7_period);

      if (0 == l_ptr)
        {
          break;
        }

      *l_ptr++ = 0;

      l_rc2 = strcmp(kv3_db_suffix_table, (char const *)l_ptr);

      if (l_rc2)
        {
          break;
        }

      l_rc = csvtokv3_lang_process(i_prefix, l_lang);
    }
  while (0);

  mjo_free((void **const) & l_lang);

  return l_rc;
}

static int
  csvtokv3_dir_process(unsigned char const *i_prefix)
{
  DIR *l_dir;
  struct dirent *l_entry;
  int l_rc;

  l_dir = 0;

  fprintf(stdout, "Scanning CSV tables...\n");
  fprintf(stdout, "\t\tdirectory:\n");
  fprintf(stdout, "\t\t\t'%s'\n", i_prefix);

  do
    {
      l_dir = opendir((char const *)i_prefix);

      if (0 == l_dir)
        {
          fprintf(stderr, "Error (%d): '%s'\n", errno, strerror(errno));
          fprintf(stderr, "\t(Unable to open directory)\n");
          fprintf(stderr, "\t('%s')\n", i_prefix);
          l_rc = MJO_FAIL;
          break;
        }

      l_rc = MJO_OK;

      do
        {
          l_entry = readdir(l_dir);

          if (0 == l_entry)
            {
              break;
            }

          l_rc = csvtotokv3_dir_entry_process(i_prefix, l_entry);

          if (l_rc)
            {
              break;
            }
        }
      while (1);

      closedir(l_dir);
    }
  while (0);

  return l_rc;
}

static void
  arg_malloc(mjo_arg_t *const o_arg)
{
  mjo_arg_malloc(o_arg, mjo_arg_rule_mask_none);

  mjo_arg_option((*o_arg),
                 (mjo_arg_option_mask_required_no
                  | mjo_arg_option_mask_vector_no | mjo_arg_option_mask_long),
                 (unsigned char const *)"help",
                 (unsigned char const *)"display program options",
                 mjo_arg_argument_mask_required_no,
                 mjo_vector_variant_bool);

  mjo_arg_option((*o_arg),
                 (mjo_arg_option_mask_required_no
                  | mjo_arg_option_mask_vector_no | mjo_arg_option_mask_long),
                 (unsigned char *)"version",
                 (unsigned char *)"display program version",
                 mjo_arg_argument_mask_required_no,
                 mjo_vector_variant_bool);

  mjo_arg_option((*o_arg),
                 (mjo_arg_option_mask_required_no
                  | mjo_arg_option_mask_vector_no | mjo_arg_option_mask_long),
                 (unsigned char *)"path",
                 (unsigned char *)"path to kv3 database",
                 mjo_arg_argument_mask_required,
                 mjo_vector_variant_char);

  mjo_arg_option((*o_arg),
                 (mjo_arg_option_mask_required_no
                  | mjo_arg_option_mask_vector_no | mjo_arg_option_mask_long),
                 (unsigned char *)"lang",
                 (unsigned char *)"language to process",
                 mjo_arg_argument_mask_required,
                 mjo_vector_variant_char);

  return;
}

int
  main(int const argc, char const **argv)
{
  mjo_arg_t l_arg;
  int l_rc;
  int l_qflag;
  unsigned char const *l_lang;
  unsigned char const *l_prefix;
  size_t l_slots;
  mjo_vector_t l_value;

  arg_malloc(&l_arg);
  l_lang = 0;
  l_prefix = (unsigned char const *)".";
  l_qflag = 0;

  do
    {
      if (1 < argc)
        {
          l_rc = mjo_arg_parse_vector(
            l_arg, &((unsigned char *const *const)argv)[1], (size_t)argc - 1);

          if (l_rc)
            {
              fprintf(stderr, "'--help' for option information\n");
              break;
            }

          l_value
            = mjo_arg_value(&l_slots, l_arg, (unsigned char const *)"version");
          if (l_slots && ((unsigned int const **)l_value)[0])
            {
              version_print();
              l_qflag++;
            }

          l_value
            = mjo_arg_value(&l_slots, l_arg, (unsigned char const *)"help");

          if (l_slots && ((unsigned int const **)l_value)[0])
            {
              mjo_arg_print(stdout, l_arg);
              l_qflag++;
            }

          if (l_qflag)
            {
              break;
            }

          l_value
            = mjo_arg_value(&l_slots, l_arg, (unsigned char const *)"path");
          if (l_slots)
            {
              l_prefix = ((unsigned char const **)l_value)[0];
            }

          l_value
            = mjo_arg_value(&l_slots, l_arg, (unsigned char const *)"lang");
          if (l_slots)
            {
              l_lang = ((unsigned char const **)l_value)[0];
            }
        }

      if (l_lang)
        {
          l_rc = csvtokv3_lang_process(l_prefix, l_lang);
        }
      else
        {
          l_rc = csvtokv3_dir_process(l_prefix);
        }
    }
  while (0);

  mjo_arg_free(&l_arg);

  return l_rc;
}
