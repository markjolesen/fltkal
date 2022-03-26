/*
  app.hxx

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
#if !defined(__app_h__)

#  include "sheet.hxx"
#  include "view.hxx"
//
#  if !defined(__DOS__)
#    include <FL/Fl_Button.H>
#    include <FL/Fl_Double_Window.H>
#    include <FL/Fl_Hold_Browser.H>
#    include <FL/Fl_Input.H>
#    include <FL/Fl_Pack.H>
#    include <FL/Fl_Tree.H>
#  else
#    include <fl/browserh.h>
#    include <fl/btn.h>
#    include <fl/input.h>
#    include <fl/pack.h>
#    include <fl/tree.h>
#    include <fl/windbl.h>
#  endif

namespace kv3
{
class app : public Fl_Double_Window
{
public:
  app(int, int, char const *l = 0);

  virtual ~app();

  void
    open(unsigned char const *);

  bool
    open() const;

  void
    first();

  void
    last();

  void
    next();

  void
    prev();

  void
    read(size_t const);

  void
    read(unsigned char const *, unsigned char const *);

  void
    filter(unsigned char const *);

  void
    view_changed();

protected:
  Fl_Hold_Browser *m_inf_browser;
  Fl_Input *m_inf_filter;
  Fl_Tree *m_inf_tree;
  Fl_Button *m_nav_first;
  Fl_Button *m_nav_last;
  Fl_Button *m_nav_next;
  Fl_Button *m_nav_prev;
  sheet *m_sheet;
  view *m_view;
  struct kv3_db_trove m_trove;

private:
  app();

  app(app const &);

  app &
    operator=(app const &);

  app(int, int, int, int, const char *l = 0);

  Fl_Pack *
    nav_create_once(int const, int const);

  Fl_Pack *
    browser_create_once(int const, int const);

  static void
    browser_cb(Fl_Widget *, void *);

  static void
    filter_cb(Fl_Widget *, void *);

  static void
    open_cb(Fl_Widget *, void *);

  static void
    first_cb(Fl_Widget *io_widget, void *);

  static void
    next_cb(Fl_Widget *, void *);

  static void
    prev_cb(Fl_Widget *, void *);

  static void
    last_cb(Fl_Widget *, void *);

  static void
    view_cb(Fl_Widget *, void *);

  static void
    tree_cb(Fl_Widget *, void *);
};

}; // namespace kv3

inline bool
  kv3::app::open() const
{
  return (m_trove.m_head && m_trove.m_head->m_inf.m_count) ? 1 : 0;
}

inline void
  kv3::app::first()
{
  if (m_trove.m_head && m_trove.m_head->m_inf.m_count)
    {
      read(0);
    }

  return;
}

inline void
  kv3::app::last()
{
  if (m_trove.m_head && m_trove.m_head->m_inf.m_count)
    {
      size_t l_record = (m_trove.m_head->m_inf.m_count - 1);
      read(l_record);
    }

  return;
}

inline void
  kv3::app::next()
{
  if (m_trove.m_head && m_trove.m_head->m_inf.m_count)
    {
      size_t l_record = (1 + m_trove.m_head->m_table.m_record);
      if (m_trove.m_head->m_inf.m_count > l_record)
        {
          read(l_record);
        }
    }

  return;
}

inline void
  kv3::app::prev()
{
  if (m_trove.m_head && m_trove.m_head->m_inf.m_count)
    {
      size_t l_record = m_trove.m_head->m_table.m_record;
      if (l_record)
        {
          read((l_record - 1));
        }
    }

  return;
}

#  define __app_h__
#endif
