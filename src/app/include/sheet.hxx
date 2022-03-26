/*
  sheet.hxx

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
#if !defined(__sheet_h__)

#  include "dbtrove.h"
//
#  if !defined(__DOS__)
#    include <FL/Enumerations.H>
#    include <FL/Fl_Scrollbar.H>
#    include <FL/Fl_Widget.H>
#    include <FL/fl_draw.H>
#  else
#    include <fl/fl_draw.h>
#    include <fl/fl_enums.h>
#    include <fl/scrlbar.h>
#    include <fl/widget.h>
#  endif

namespace kv3
{
class sheet : public Fl_Widget
{
public:
  sheet(int, int, int, int, const char *l = 0);

  virtual ~sheet();

  virtual void
    draw();

  virtual int
    handle(int);

  void
    reference(struct kv3_db_trove *const);

  virtual void
    resize(int, int, int, int);

  void
    view_changed();

  void
    popdown_configure();

protected:
  Fl_Scrollbar m_sx;
  size_t m_extent_x;
  size_t m_pushed_x;
  size_t *m_pushed_col;
  struct kv3_db_trove *m_trove;

private:
  static Fl_Boxtype const m_box_default = FL_DOWN_BOX;
  static Fl_Boxtype const m_header_box = FL_UP_BOX;
  static Fl_Color const m_header_color_bg = FL_BACKGROUND_COLOR;
  static Fl_Color const m_header_color_fg = FL_FOREGROUND_COLOR;
  static Fl_Font const m_header_font = FL_COURIER_BOLD;
  static Fl_Fontsize const m_header_size = 18;
  static Fl_Font const m_cell_font = FL_COURIER;

  sheet();

  sheet(sheet const &);

  sheet &
    operator=(sheet const &);

  static void
    scroll_cb(Fl_Widget *, void *);

  size_t
    header_len_y() const;

  void
    draw_header() const;

  void
    draw_rows();

  void
    draw_cell(struct kv3_text &,
              size_t const,
              size_t const,
              ssize_t const,
              ssize_t const,
              size_t const,
              size_t const);

  void
    extent_calculate();

  int
    handle_push();

  void
    handle_push_cell();

  int
    handle_push_col();

  void
    scroll_configure();
};

}; // namespace kv3

inline void
  kv3::sheet::extent_calculate()
{
  m_extent_x = 0;

  if (m_trove && m_trove->m_head)
    {
      for (struct kv3_db_datum const *l_datum = m_trove->m_head; l_datum;
           l_datum = l_datum->m_next)
        {
          if (0 == l_datum->m_table.m_text.m_is_hidden)
            {
              for (size_t l_col = 0; kv3_dict_row_cell_count_used > l_col;
                   l_col++)
                {
                  m_extent_x += l_datum->m_table.m_text.m_len_x[l_col];
                }
            }
        }
    }

  return;
}

inline size_t
  kv3::sheet::header_len_y() const
{
  size_t l_len_y = fl_height(m_header_font, m_header_size);

  l_len_y += fl_descent();
  l_len_y += 8;

  return l_len_y;
}

inline void
  kv3::sheet::reference(struct kv3_db_trove *const i_trove)
{
  m_trove = i_trove;
  extent_calculate();
  scroll_configure();
  popdown_configure();

  return;
}

inline void
  kv3::sheet::view_changed()
{
  extent_calculate();
  scroll_configure();
  popdown_configure();

  return;
}

#  define __sheet_h__
#endif
