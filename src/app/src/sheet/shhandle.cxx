/*
  sheet_handle.cxx

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
#include "sheet.hxx"
//
#if !defined(__DOS__)
#  include <FL/Fl.H>
#else
#  include <fl/fl.h>
#endif

int
  kv3::sheet::handle(int i_event)
{
  int l_exit = 0;

  switch (i_event)
    {
    case FL_PUSH:
      m_pushed_col = 0;

      if (m_trove && m_trove->m_head)
        {
          l_exit = handle_push_col();

          if (0 == l_exit)
            {
              handle_push_cell();
            }
        }

      l_exit = 1;
      break;
    case FL_DRAG:
      if (Fl::pushed() == this && m_pushed_col)
        {
          ssize_t l_delta = Fl::event_x() - static_cast<ssize_t>(m_pushed_x);

          if (l_delta)
            {
              (*m_pushed_col) += l_delta;
              redraw();
            }

          m_pushed_x = Fl::event_x();
        }
      l_exit = 1;
      break;
    case FL_RELEASE:
      if (Fl::pushed() == this && m_pushed_col)
        {
          int const l_len_x = (int)(*m_pushed_col);

          if (5 > l_len_x)
            {
              (*m_pushed_col) = 5;
              redraw();
            }
          else if (500 < l_len_x)
            {
              (*m_pushed_col) = 500;
              redraw();
            }

          extent_calculate();
          scroll_configure();
          popdown_configure();
        }

      m_pushed_col = 0;
      l_exit = 1;
      break;
    }

  return l_exit;
}
