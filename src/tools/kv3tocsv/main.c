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
#include <errno.h>

#include "dbsuffix.h"
#include "dictrow.h"
#include "dictstr.h"
#include "marg.h"
#include "mdirect.h"
#include "mfcntl.h"
#include "mread.h"
#include "mstdio.h"
#include "mstdlib.h"
#include "mstring.h"
#include "msysstat.h"
#include "mu8.h"
#include "munistd.h"
#include "mvector.h"
#include "version.h"

enum
{
  cell_max_octets
  = (sizeof(struct kv3_dict_row) + sizeof(struct kv3_dict_cell))
};

static int
  kv3tocsv_process_handle(int const i_fd_out, int const i_fd_in)
{
  int l_eol;
  int l_rc;
  size_t l_line;
  size_t l_octets;
  unsigned char *l_ptr;
  enum mjo_status l_status;
  mjo_vector_t l_scratch;

  l_line = 1;

  mjo_vector_malloc(&l_scratch,
                    cell_max_octets,
                    mjo_vector_variant_char,
                    mjo_vector_size_auto,
                    0);

  do
    {
      l_rc = mjo_read_csv(&l_eol,
                          &l_status,
                          &l_scratch,
                          cell_max_octets,
                          (mjo_read_t)read,
                          (mjo_handle_t)i_fd_in);

      if (l_rc)
        {
          fprintf(stderr, "ERROR: Unable to read\n");
          fprintf(stderr, "\terrno(%d): %s\n", errno, strerror(errno));
          fprintf(stderr, "\tline: %lu\n", l_line);
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
              fprintf(stderr, "\tline: %lu\n", l_line);
              l_rc = MJO_FAIL;
              break;
            }
          break;
        }

      l_ptr = (unsigned char *)strchr((char const *)l_scratch,
                                      kv3_dict_str_epsilon);

      if (l_ptr)
        {
          *l_ptr = 0;
        }

      mjo_u8_trim((unsigned char *)l_scratch);

      write(i_fd_out, "\"", 1);

      if (*(unsigned char *)l_scratch)
        {
          write(i_fd_out, l_scratch, strlen((char const *)l_scratch));
        }

      write(i_fd_out, "\"", 1);

      if (0 == l_eol)
        {
          write(i_fd_out, ",", 1);
        }
      else
        {
          l_line++;
          write(i_fd_out, "\r\n", 2);
        }
    }
  while (1);

  mjo_vector_free(&l_scratch);

  return l_rc;
}

static int
  kv3tocsv_process_name(unsigned char const *i_name)
{
  int l_rc;
  int l_fd_in;
  int l_fd_out;
  int l_mflag;
  unsigned char *l_name_out;
  int l_oflag;

  l_fd_out = -1;
  l_fd_in = -1;
  l_name_out = 0;

  do
    {
      l_fd_in = open((char const *)i_name, (O_RDONLY | O_BINARY));

      if (-1 == l_fd_in)
        {
          fprintf(stderr, "Unable to open file: '%s'\n", i_name);
          l_rc = MJO_FAIL;
          break;
        }

      mjo_path_join(
        &l_name_out, 0, i_name, (unsigned char const *)mjo_suffix_csv);

      l_oflag = (O_WRONLY | O_CREAT | O_TRUNC | O_BINARY);
      l_mflag = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

      l_fd_out = open((char *const)l_name_out, l_oflag, l_mflag);

      if (-1 == l_fd_out)
        {
          fprintf(stderr, "Unable to create file: '%s'\n", l_name_out);
          l_rc = MJO_FAIL;
          break;
        }

      fprintf(stdout, "Processing file:\n");
      fprintf(stdout, "              <= '%s'\n", i_name);
      fprintf(stdout, "              => '%s'\n", l_name_out);

      l_rc = kv3tocsv_process_handle(l_fd_out, l_fd_in);
    }
  while (0);

  if (-1 != l_fd_out)
    {
      close(l_fd_out);
    }

  if (-1 != l_fd_in)
    {
      close(l_fd_in);
    }

  mjo_free((void **const) & l_name_out);

  return l_rc;
}

static int
  kv3tocsv_process_entry(unsigned char const *i_prefix,
                         struct dirent const *const i_entry,
                         unsigned char const *i_lang)
{
  int l_rc;
  int l_rc2;
  unsigned char *l_name;
  unsigned char *l_path;
  unsigned char *l_ptr;

  l_rc = MJO_OK;
  l_name = 0;
  l_path = 0;

  do
    {
      if (0 == i_entry)
        {
          break;
        }

      if (mjo_r7_period == (*i_entry).d_name[0])
        {
          break;
        }

      mjo_strdup(&l_name, (unsigned char const *)(*i_entry).d_name);

      l_ptr = (unsigned char *)strrchr((char *)l_name, mjo_r7_period);

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

      mjo_path_join(&l_path, i_prefix, i_lang, l_ptr);

      l_rc = kv3tocsv_process_name(l_path);
    }
  while (0);

  mjo_free((void **const) & l_path);
  mjo_free((void **const) & l_name);

  return l_rc;
}

static int
  kv3tocsv_process_lang(unsigned char const *i_prefix,
                        unsigned char const *i_lang)
{
  DIR *l_dir;
  struct dirent *l_entry;
  unsigned char *l_path;
  size_t l_octets;
  char *l_ptr;
  int l_rc;

  l_dir = 0;
  l_path = 0;

  do
    {
      mjo_path_join(
        &l_path, i_prefix, i_lang, (unsigned char const *)kv3_db_suffix_table);

      l_rc = kv3tocsv_process_name(l_path);

      if (l_rc)
        {
          break;
        }

      l_dir = opendir((char const *)i_prefix);

      if (0 == l_dir)
        {
          fprintf(stderr, "Unable to open: '%s'\n", i_prefix);
          l_rc = MJO_FAIL;
          break;
        }

      do
        {
          l_entry = readdir(l_dir);

          if (0 == l_entry)
            {
              break;
            }

          l_rc = kv3tocsv_process_entry(i_prefix, l_entry, i_lang);

          if (l_rc)
            {
              break;
            }
        }
      while (1);

      closedir(l_dir);
    }
  while (0);

  mjo_free((void **const) & l_path);

  return l_rc;
}

static int
  kv3tocsv_process_dir(unsigned char const *i_prefix)
{
  DIR *l_dir;
  struct dirent *l_entry;
  int l_rc;
  int l_rc2;
  unsigned char *l_ptr;

  l_rc = MJO_OK;
  l_dir = 0;

  do
    {
      l_dir = opendir((char const *)i_prefix);

      if (0 == l_dir)
        {
          fprintf(stderr, "Unable to open: '%s'\n", i_prefix);
          l_rc = MJO_FAIL;
          break;
        }

      fprintf(stdout, "Scanning database: '%s'\n", i_prefix);

      do
        {
          l_entry = readdir(l_dir);

          if (0 == l_entry)
            {
              break;
            }

          if (mjo_r7_period == (*l_entry).d_name[0])
            {
              continue;
            }

          l_ptr = (unsigned char *)strrchr((*l_entry).d_name, mjo_r7_period);

          if (0 == l_ptr)
            {
              continue;
            }

          *l_ptr++ = 0;

          l_rc2 = strcmp(kv3_db_suffix_table, (char const *)l_ptr);

          if (l_rc2)
            {
              continue;
            }

          l_rc = kv3tocsv_process_lang(
            i_prefix, (unsigned char const *)(*l_entry).d_name);

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
  main(int argc, char *argv[])
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
          l_rc = kv3tocsv_process_lang(l_prefix, l_lang);
        }
      else
        {
          l_rc = kv3tocsv_process_dir(l_prefix);
        }
    }
  while (0);

  mjo_arg_free(&l_arg);

  return l_rc;
}
