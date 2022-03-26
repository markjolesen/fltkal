/*
  view.hxx

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
#if !defined(__view_h__)

#  include "mxywh.h"
//
#  include "dbtrove.h"
//
#  if !defined(__DOS__)
#    include <FL/Fl_Widget.H>
#  else
#    include <fl/widget.h>
#  endif

namespace kv3
{
class view : public Fl_Widget
{
public:
  view(int, int, int, int, const char *l = 0);

  virtual ~view();

  virtual void
    draw();

  virtual int
    handle(int);

  void
    reference(struct kv3_db_trove *const);

  virtual void
    resize(int, int, int, int);

protected:
  struct view_item
  {
    enum
    {
      box_len_y = 50
    };

    struct kv3_db_datum *m_datum;
    struct mjo_xywh m_box;
    struct view_item *m_next;
    struct view_item *m_prev;
  };

  struct view_list
  {
    struct view_item *m_head;
    struct view_item *m_tail;
  };

  struct view_event
  {
    struct view_item *m_item;
    bool m_dragged;
    int m_event_x;
    int m_event_y;
  };

  struct view_event m_event;
  struct view_list m_list;
  struct kv3_db_trove *m_trove;

private:
  view();

  view(view const &);

  view &
    operator=(view const &);

  void
    handle_push();

  void
    snap();

  static void
    draw_item(struct view_item const &);

  static bool
    toggle(struct view_item *const, struct view_item const *const);
};

}; // namespace kv3

#  define __view_h__
#endif
