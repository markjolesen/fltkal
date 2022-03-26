/*
  main.cxx

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
#include "marg.h"
#include "mstdlib.h"
//
#include "app.hxx"
#include "version.h"

extern void
  kv3_open(unsigned char **o_path, unsigned char const *i_path);

static void
  arg_malloc(mjo_arg_t *const o_arg)
{
  mjo_arg_malloc(o_arg, mjo_arg_rule_mask_none);

  mjo_arg_option(
    (*o_arg),
    static_cast<enum mjo_arg_option_mask>(mjo_arg_option_mask_required_no
                                          | mjo_arg_option_mask_vector_no
                                          | mjo_arg_option_mask_long),
    reinterpret_cast<unsigned char const *>("help"),
    reinterpret_cast<unsigned char const *>("display program options"),
    static_cast<enum mjo_arg_argument_mask>(mjo_arg_argument_mask_required_no),
    mjo_vector_variant_bool);

  mjo_arg_option(
    (*o_arg),
    static_cast<enum mjo_arg_option_mask>(mjo_arg_option_mask_required_no
                                          | mjo_arg_option_mask_vector_no
                                          | mjo_arg_option_mask_long),
    reinterpret_cast<unsigned char const *>("version"),
    reinterpret_cast<unsigned char const *>("display program version"),
    static_cast<enum mjo_arg_argument_mask>(mjo_arg_argument_mask_required_no),
    mjo_vector_variant_bool);

  mjo_arg_option(
    (*o_arg),
    static_cast<enum mjo_arg_option_mask>(mjo_arg_option_mask_required_no
                                          | mjo_arg_option_mask_vector_no
                                          | mjo_arg_option_mask_long),
    reinterpret_cast<unsigned char const *>("path"),
    reinterpret_cast<unsigned char const *>("path to kv3 database"),
    static_cast<enum mjo_arg_argument_mask>(mjo_arg_argument_mask_required),
    mjo_vector_variant_char);

  return;
}

static kv3::app *const
  app_new(int argc, char *argv[])
{
  kv3::app *l_app;
  mjo_arg_t l_arg;
  size_t l_slot;
  size_t l_slots;
  int l_exit;
  mjo_vector_t l_value;
  unsigned char *l_path;
  int l_qflag;

  l_app = 0;
  arg_malloc(&l_arg);
  l_path = 0;
  l_qflag = 0;

  do
    {
      if (1 < argc)
        {
          l_exit = mjo_arg_parse_vector(
            l_arg, &((unsigned char *const *const)argv)[1], (size_t)argc - 1);

          if (l_exit)
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
        }

      if (l_qflag)
        {
          break;
        }

      Fl::visual(FL_DOUBLE | FL_INDEX);

      l_app = new kv3::app(640, 480, "kv3");
      l_app->resizable(l_app);

      l_value = mjo_arg_value(&l_slots, l_arg, (unsigned char const *)"path");
      l_qflag = 0;

      for (l_slot = 0; l_slots > l_slot; l_slot++)
        {
          kv3_open(&l_path, ((unsigned char const **)l_value)[l_slot]);
          l_app->open(l_path);
          mjo_free(reinterpret_cast<void **>(&l_path));

          if (l_app->open())
            {
              l_qflag = 1;
              break;
            }
        }

      if (l_qflag)
        {
          break;
        }

      kv3_open(&l_path, 0);

      if (0 == l_path)
        {
          break;
        }

      l_app->open(l_path);
    }
  while (0);

  mjo_free(reinterpret_cast<void **>(&l_path));
  mjo_arg_free(&l_arg);

  return l_app;
}

int
  main(int argc, char *argv[])
{
  int l_exit;
  kv3::app *l_app;

  do
    {
      l_app = app_new(argc, argv);

      if (0 == l_app)
        {
          break;
        }

      l_app->show();
      l_exit = Fl::run();
      delete l_app;
    }
  while (0);

  return l_exit;
}
