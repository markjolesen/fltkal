/*
  app_view_changed.cxx

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
//
#include "app.hxx"

void
  kv3::app::view_changed()
{
  for (struct kv3_db_datum *l_datum = m_trove.m_head; l_datum;
       l_datum = l_datum->m_next)
    {
      if (0 == l_datum->m_table.m_text.m_is_hidden)
        {
          kv3::browser_load((*m_inf_browser), l_datum->m_inf);
          break;
        }
    }

  kv3::tree_load((*m_inf_tree), m_trove);
  m_sheet->view_changed();
  m_sheet->redraw();

  return;
}
