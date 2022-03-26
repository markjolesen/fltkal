/*
  app_tree_cb.cxx

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
#include "app.hxx"

void
  kv3::app::tree_cb(Fl_Widget *io_widget, void *io_user)
{
  Fl_Tree *l_tree = reinterpret_cast<Fl_Tree *>(io_widget);

  do
    {
      if (FL_TREE_REASON_SELECTED != l_tree->callback_reason())
        {
          break;
        }

      Fl_Tree_Item *l_item = l_tree->item_clicked();

      if (0 == l_item || l_item->children())
        {
          break;
        }

      Fl_Tree_Item *l_parent = l_item->parent();

      if (0 == l_parent)
        {
          break;
        }

      int l_count = l_parent->children();

      if (1 >= l_count)
        {
          break;
        }

      struct kv3_db_xref_table *l_xtable
        = reinterpret_cast<struct kv3_db_xref_table *>(l_item->user_data());

      if (0 == l_xtable)
        {
          break;
        }

      unsigned char const *l_inf
        = reinterpret_cast<unsigned char const *>(l_item->label());

      kv3::app *l_app = reinterpret_cast<kv3::app *>(io_user);
      l_app->read(l_xtable->m_lang, l_inf);
    }
  while (0);

  return;
}
