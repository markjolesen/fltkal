/*
  app.cxx

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
#include "app.hxx"
//
#if !defined(__DOS__)
#  include <FL/Fl_Pack.H>
#  include <FL/Fl_Pixmap.H>
#  include <FL/Fl_Tile.H>
#else
#  include <fl/imgpix.h>
#  include <fl/pack.h>
#  include <fl/tile.h>
#endif

//
#include "open.xpm"
Fl_Pixmap g_open_pxm(open_xpm);

//
#include "first.xpm"
Fl_Pixmap g_first_pxm(first_xpm);

//
#include "last.xpm"
Fl_Pixmap g_last_pxm(last_xpm);

//
#include "next.xpm"
Fl_Pixmap g_next_pxm(next_xpm);

//
#include "prev.xpm"
Fl_Pixmap g_prev_pxm(prev_xpm);

#define _(msg) msg

Fl_Pack *
  kv3::app::nav_create_once(int const i_pos_x, int const i_pos_y)
{
  Fl_Pack *pktv = new Fl_Pack(i_pos_x, i_pos_y, w(), 48);
  pktv->type(Fl_Pack::VERTICAL);
  pktv->box(FL_UP_FRAME);

  Fl_Pack *pkth = new Fl_Pack(i_pos_x, i_pos_y, pktv->w(), pktv->h());
  pkth->type(Fl_Pack::HORIZONTAL);
  pkth->spacing(48);

  Fl_Button *btn = new Fl_Button(i_pos_x, i_pos_y, 48, 48);
  btn->image(g_open_pxm);
  btn->callback(open_cb, this);

  Fl_Pack *pknav = new Fl_Pack(i_pos_x, i_pos_y, 48, 48);
  pknav->type(Fl_Pack::HORIZONTAL);

  m_nav_first = new Fl_Button(pknav->x(), pknav->y(), 48, 48);
  m_nav_first->image(g_first_pxm);
  m_nav_first->deactivate();
  m_nav_first->callback(first_cb, this);

  m_nav_next = new Fl_Button(pknav->x(), pknav->y(), 48, 48);
  m_nav_next->image(g_next_pxm);
  m_nav_next->deactivate();
  m_nav_next->callback(next_cb, this);

  m_nav_prev = new Fl_Button(pknav->x(), pknav->y(), 48, 48);
  m_nav_prev->image(g_prev_pxm);
  m_nav_prev->deactivate();
  m_nav_prev->callback(prev_cb, this);

  m_nav_last = new Fl_Button(pknav->x(), pknav->y(), 48, 48);
  m_nav_last->image(g_last_pxm);
  m_nav_last->deactivate();
  m_nav_last->callback(last_cb, this);

  pknav->end();
  pkth->end();
  pktv->resizable(pkth);

  return pktv;
}

Fl_Pack *
  kv3::app::browser_create_once(int const i_pos_x, int const i_pos_y)
{
  Fl_Pack *pk = new Fl_Pack(i_pos_x, i_pos_y, 180, h() - i_pos_y);
  pk->type(Fl_Pack::VERTICAL);
  pk->begin();

  m_inf_filter = new Fl_Input(pk->x(), pk->y(), pk->w(), 32);
  m_inf_filter->box(FL_DOWN_BOX);
  m_inf_filter->tab_nav(1);
  m_inf_filter->textfont(FL_COURIER);
  m_inf_filter->textsize(18);
  m_inf_filter->when(FL_WHEN_CHANGED);
  m_inf_filter->callback(filter_cb, this);

  Fl_Tile *t2 = new Fl_Tile(m_inf_filter->x(),
                            m_inf_filter->y() + m_inf_filter->h(),
                            m_inf_filter->w(),
                            pk->h());
  t2->begin();

  m_inf_browser = new Fl_Hold_Browser(t2->x(), t2->y(), t2->w(), 180);
  m_inf_browser->textfont(FL_COURIER);
  m_inf_browser->textsize(18);
  m_inf_browser->callback(browser_cb, this);

  m_inf_tree = new Fl_Tree(m_inf_browser->x(),
                           m_inf_browser->y() + m_inf_browser->h(),
                           m_inf_browser->w(),
                           pk->h() - (180 + 32));
  m_inf_tree->clear();
  m_inf_tree->showroot(0);
  m_inf_tree->when(FL_WHEN_RELEASE);
  m_inf_tree->labelfont(FL_COURIER);
  m_inf_tree->labelsize(18);
  m_inf_tree->callback_reason(FL_TREE_REASON_SELECTED);
  m_inf_tree->callback(tree_cb, this);

  t2->end();

  pk->resizable(t2);

  return pk;
}

kv3::app::app(int W, int H, char const *l) :
  Fl_Double_Window(W, H, l), m_nav_first(0), m_nav_last(0), m_nav_next(0),
  m_nav_prev(0), m_inf_tree(0), m_inf_browser(0), m_inf_filter(0), m_view(0),
  m_trove()
{
  kv3_db_trove_assign(&m_trove);

  begin();

  Fl_Pack *pn = nav_create_once(0, 0);
  pn->end();

  Fl_Pack *p0 = new Fl_Pack(pn->x(), pn->y() + pn->h(), w(), h() - pn->h());
  p0->type(Fl_Pack::HORIZONTAL);

  Fl_Pack *ph = new Fl_Pack(p0->x(), p0->y(), 120, p0->h());
  ph->type(Fl_Pack::HORIZONTAL);

  Fl_Pack *pq = new Fl_Pack(ph->x(), ph->y(), 120, p0->h());
  pq->type(Fl_Pack::VERTICAL);

  m_view = new view(pq->x(), pq->y(), pq->w(), pq->h());
  m_view->color(FL_BACKGROUND_COLOR);
  m_view->box(FL_UP_BOX);
  m_view->callback(view_cb, this);

  ph->end();

  Fl_Pack *pv = new Fl_Pack(pn->x(), pn->y() + pn->h(), 180, p0->h());
  pv->type(Fl_Pack::VERTICAL);

  Fl_Pack *pb = browser_create_once(pv->x(), pv->y());
  pb->end();

  pv->resizable(pb);
  pv->end();

  Fl_Pack *pz = new Fl_Pack(
    p0->x(), p0->y(), p0->y() + p0->h(), p0->h() - Fl::scrollbar_size());
  pz->type(Fl_Pack::VERTICAL);

  m_sheet = new sheet(pz->x(), pz->y(), pz->w(), pz->h());
  m_sheet->box(FL_UP_BOX);

  p0->resizable(m_sheet);

  end();

  return;
}

kv3::app::~app()
{
  kv3_db_trove_discharge(&m_trove);

  return;
}
