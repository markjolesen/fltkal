/*
  sheet.cxx

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
#include "sheet.hxx"
//
#if !defined(__DOS__)
#  include <FL/Fl.H>
#else
#  include <fl/fl.h>
#endif

kv3::sheet::sheet(int X, int Y, int W, int H, const char *l) :
  Fl_Widget(X, Y, W, H, l),
  m_sx(X, Y + H - Fl::scrollbar_size(), W, Fl::scrollbar_size()),
  m_extent_x(0), m_pushed_x(0), m_pushed_col(0), m_trove(0)
{
  color(FL_BACKGROUND2_COLOR);
  box(FL_DOWN_BOX);

  m_sx.set_visible();
  m_sx.value(0, w(), 0, 100);
  m_sx.type(FL_HORIZONTAL);
  m_sx.align(FL_ALIGN_BOTTOM);
  m_sx.callback(scroll_cb, this);

  return;
}

kv3::sheet::~sheet()
{
  return;
}
