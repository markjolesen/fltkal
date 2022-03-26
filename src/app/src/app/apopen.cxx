/*
  app_open.cxx

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
#include "kv3.hxx"
//
#include "app.hxx"

void
  kv3::app::open(unsigned char const *i_path)
{
  m_inf_tree->clear();
  m_inf_browser->clear();
  m_inf_filter->value(0);

  kv3_db_trove_open(&m_trove, i_path);
  kv3_db_trove_read(&m_trove, 0);

  m_sheet->reference(&m_trove);
  m_view->reference(&m_trove);

  struct kv3_db_datum const *l_datum = m_trove.m_head;

  if (l_datum)
    {
      kv3::browser_load((*m_inf_browser), l_datum->m_inf);
      kv3::tree_load((*m_inf_tree), m_trove);
      m_nav_first->activate();
      m_nav_last->activate();
      m_nav_next->activate();
      m_nav_prev->activate();
    }
  else
    {
      m_inf_tree->clear();
      m_inf_browser->clear();
      m_nav_first->deactivate();
      m_nav_last->deactivate();
      m_nav_next->deactivate();
      m_nav_prev->deactivate();
    }

  damage(FL_DAMAGE_ALL);

  return;
}
