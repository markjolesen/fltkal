/*
  browser_load.cxx

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
#include "kv3.hxx"

extern void
  kv3::browser_load(Fl_Browser &io_browser, struct kv3_db_inf const &i_inf)
{
  io_browser.clear();

  struct kv3_dict_cell *l_cell = i_inf.m_array;

  for (size_t l_slot = 0; i_inf.m_count > l_slot; l_slot++)
    {
      io_browser.add(reinterpret_cast<char const *>(l_cell->m_text));
      io_browser.data(static_cast<int>((1 + l_slot)), (void *)l_slot);
      l_cell++;
    }

  return;
}

extern void
  kv3::browser_load(Fl_Browser &io_browser,
                    struct kv3_db_inf const &i_inf,
                    unsigned char const *i_filter)
{
  do
    {
      if (0 == i_filter || 0 == i_filter[0])
        {
          kv3::browser_load(io_browser, i_inf);
          break;
        }

      io_browser.clear();

      struct kv3_dict_cell *l_cell = i_inf.m_array;
      int l_line = 1;

      for (size_t l_slot = 0; i_inf.m_count > l_slot; l_slot++)
        {
          int l_rc = kv3::filter(l_cell->m_text, i_filter);

          if (0 == l_rc)
            {
              io_browser.add(reinterpret_cast<char const *>(l_cell->m_text));
              io_browser.data(l_line, (void *)l_slot);
              l_line++;
            }

          l_cell++;
        }
    }
  while (0);

  return;
}
