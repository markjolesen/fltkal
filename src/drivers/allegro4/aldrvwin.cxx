// aldrvwin.cxx
//
// Allegro4 Window handling code for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2019 The fltkal authors
//
//                              FLTK License
//                            December 11, 2001
//
// The FLTK library and included programs are provided under the terms
// of the GNU Library General Public License (LGPL) with the following
// exceptions:
//
//     1. Modifications to the FLTK configure script, config
//        header file, and makefiles by themselves to support
//        a specific platform do not constitute a modified or
//        derivative work.
//
//       The authors do request that such modifications be
//       contributed to the FLTK project - send all contributions
//       through the "Software Trouble Report" on the following page:
//
//            http://www.fltk.org/str.php
//
//     2. Widgets that are subclassed from FLTK widgets do not
//        constitute a derivative work.
//
//     3. Static linking of applications and widgets to the
//        FLTK library does not constitute a derivative work
//        and does not require the author to provide source
//        code for the application or widget, use the shared
//        FLTK libraries, or link their applications or
//        widgets against a user-supplied version of FLTK.
//
//        If you link the application or widget to a modified
//        version of FLTK, then the changes to FLTK must be
//        provided under the terms of the LGPL in sections
//        1, 2, and 4.
//
//     4. You do not have to provide a copy of the FLTK license
//        with programs that are linked to the FLTK library, nor
//        do you have to identify the FLTK license in your
//        program or documentation as required by section 6
//        of the LGPL.
//
//        However, programs must still identify their use of FLTK.
//        The following example statement can be included in user
//        documentation to satisfy this requirement:
//
//            [program/widget] is based in part on the work of
//            the FLTK project (http://www.fltk.org).
//
//     This library is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Library General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.
//
//     This library is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Library General Public License for more details.
//
//     You should have received a copy of the GNU Library General Public
//     License along with FLTK.  If not, see <http://www.gnu.org/licenses/>.
//
#include <fl/fl.h>
#include <fl/fl_enums.h>
#include <fl/platform.h>
#include <fl/win.h>
#include "aldrvwin.h"
#include "aldrvgr.h"
#include "../../drvwin.h"

#if defined(USE_ALLEGRO)
#include "imgconv.h"
#else
#include "mouse.h"
#endif

Window fl_window = 0;

extern void cursor_set(Fl_Cursor const c);

Fl_Window_Driver*
Fl_Window_Driver::newWindowDriver(Fl_Window* w)
{
  return new Fl_Allegro_Window_Driver(w);
}

void
Fl_Window_Driver::default_icons(const Fl_RGB_Image* icons[], int count)
{

}

Fl_Allegro_Window_Driver::Fl_Allegro_Window_Driver(Fl_Window* w) :
  Fl_Window_Driver(w),
  cursor_(),
  store_()
{
  memset(&cursor_, 0, sizeof(cursor_));
  cursor_.pointer_ = FL_CURSOR_DEFAULT;
  memset(&store_, 0, sizeof(store_));
  return;
}


Fl_Allegro_Window_Driver::~Fl_Allegro_Window_Driver()
{

#if defined(USE_ALLEGRO)

  if (cursor_.custom_.bmp_)
  {
    fl_graphics_driver->mouse_hide();
    set_cursor(FL_CURSOR_DEFAULT);
    destroy_bitmap(cursor_.custom_.bmp_);
    fl_graphics_driver->mouse_show();
  }

#endif

  if (store_.bmp_)
  {
#if defined(USE_ALLEGRO)
    destroy_bitmap(store_.bmp_);
#else
    bitmap_free(store_.bmp_);
#endif
  }

  return;
}

int
Fl_Allegro_Window_Driver::decorated_w()
{
  return w();
}

void
Fl_Allegro_Window_Driver::draw_begin()
{
  Fl_Allegro_Graphics_Driver* gr = reinterpret_cast<Fl_Allegro_Graphics_Driver*>
                                   (fl_graphics_driver);
  // Fl_Window_Driver::draw_begin(); - does nothing
  gr->mouse_hide();
  Fl::window_draw_offset_x = pWindow->x();
  Fl::window_draw_offset_y = pWindow->y();

  if (FL_CHILD_WINDOW == pWindow->type())
  {
    Fl_Group* p = pWindow->parent();
    Fl_Window* w = p->as_window();

    while (w)
    {
      Fl::window_draw_offset_x += w->x();
      Fl::window_draw_offset_y += w->y();
      p = w->parent();

      if (p)
      {
        w = p->as_window();
      }

      else
      {
        break;
      }
    }
  }

  if (FL_DAMAGE_ALL & pWindow->damage())
  {
    if (FL_WINDOW == pWindow->type() ||
        FL_DOUBLE_WINDOW == pWindow->type())
    {
      gr->nca_draw_frame(
        pWindow->x() - 1,
        pWindow->y() - title_bar_height,
        pWindow->w() + 2,
        pWindow->h() + title_bar_height + 2,
        title_bar_height,
        pWindow->label());
    }
  }
}

void
Fl_Allegro_Window_Driver::draw_end()
{
  // Fl_Window_Driver::draw_end(); - does nothing
  fl_graphics_driver->mouse_show();
}

int
Fl_Allegro_Window_Driver::decorated_h()
{
  return h();
}

Fl_X*
Fl_Allegro_Window_Driver::makeWindow()
{
  bool takefocus = true;
  Fl_Group::current(0);
  Fl_X* x = new Fl_X;
  i(x);
  other_xid = 0;
  x->w = pWindow;
  x->region = 0;
  x->next = Fl_X::first;
  Fl_X::first = x;

  if (FL_WINDOW == pWindow->type() ||
      FL_DOUBLE_WINDOW == pWindow->type())
  {
    if (0 == pWindow->parent())
    {
      if (title_bar_height > pWindow->y())
      {
        pWindow->position(pWindow->x(), title_bar_height);
      }
    }

    else
    {
      pWindow->type(FL_CHILD_WINDOW);
      takefocus = false;
    }
  }

  pWindow->set_visible();
  pWindow->redraw();
  int old_event = Fl::e_number;
  pWindow->handle(Fl::e_number = FL_SHOW);
  Fl::e_number = old_event;

  if (takefocus)
  {
    pWindow->take_focus();
  }

  return x;
}

void
Fl_Allegro_Window_Driver::take_focus()
{
  if (!shown())
  {
    pWindow->show();
  }
}

void
Fl_Allegro_Window_Driver::show()
{
  if (!shown())
  {
    fl_open_display();
    makeWindow();
  }
}

void
Fl_Allegro_Window_Driver::hide()
{
  hide_common();

  if (0 == store_.bmp_)
  {
    Fl::redraw();
    Fl_Allegro_Graphics_Driver* gr = reinterpret_cast<Fl_Allegro_Graphics_Driver*>
                                     (fl_graphics_driver);
    bool buffered = gr->flip_to_offscreen(true);
    Fl::flush(); // _mjo TODO: investigate move flip screen to flush

    if (buffered)
    {
      gr->flip_to_onscreen();
    }
  }
}

void
Fl_Allegro_Window_Driver::backing_show()
{

  if (store_.bmp_)
  {
    fl_graphics_driver->mouse_hide();
#if defined(USE_ALLEGRO)
    blit(store_.bmp_, screen, 0, 0, store_.x_, store_.y_, store_.bmp_->w,
         store_.bmp_->h);
#else
    bitmap_32bpp_blt(_screen, store_.x_, store_.y_, store_.bmp_);
#endif
    fl_graphics_driver->mouse_show();
  }

  return;
}

void
Fl_Allegro_Window_Driver::backing_create()
{

  if (store_.bmp_)
  {
#if defined(USE_ALLEGRO)
    destroy_bitmap(store_.bmp_);
#else
    bitmap_free(store_.bmp_);
#endif
    store_.bmp_ = 0;
  }

  fl_graphics_driver->push_no_clip();

  int bmp_x = pWindow->x();
  int bmp_y = pWindow->y();
  int bmp_w = pWindow->w();
  int bmp_h = pWindow->h();

  fl_graphics_driver->clip_box(bmp_x, bmp_y, bmp_w, bmp_h,
                               bmp_x, bmp_y, bmp_w, bmp_h);

#if defined(USE_ALLEGRO)
  store_.bmp_ = create_bitmap(bmp_w, bmp_h);
  fl_graphics_driver->mouse_hide();
  set_clip_state(store_.bmp_, 1);
  blit(screen, store_.bmp_, bmp_x, bmp_y, 0, 0, store_.bmp_->w, store_.bmp_->h);
  fl_graphics_driver->mouse_show();
#else
  fl_graphics_driver->mouse_hide();
  store_.bmp_ = bitmap_new_from_image(_screen, bmp_x, bmp_y, bmp_w, bmp_h);
  fl_graphics_driver->mouse_show();
#endif

  store_.x_ = bmp_x;
  store_.y_ = bmp_y;

  fl_graphics_driver->pop_clip();

  return;
}

void
Fl_Allegro_Window_Driver::resize(int X, int Y, int W, int H)
{

  int x1 = pWindow->x();
  int y1 = pWindow->y();
  int w1 = pWindow->w();
  int h1 = pWindow->h();

  pWindow->Fl_Group::resize(X, Y, W, H);

  if (shown())
  {
    int x2 = pWindow->x();
    int y2 = pWindow->y();
    int w2 = pWindow->w();
    int h2 = pWindow->h();

    if (x1 != x2 || y1 != y2 || w1 != w2 || h1 != h2)
    {
      if (0 == store_.bmp_ && (x1 != x2 || y1 != y2))
      {
        Fl_Allegro_Graphics_Driver* gr = reinterpret_cast<Fl_Allegro_Graphics_Driver*>
                                         (fl_graphics_driver);
        gr->surface_clear();
        Fl::redraw();
      }

      else
      {
        pWindow->redraw();
      }
    }

  }

  return;
}

#if defined(USE_ALLEGRO)

int
Fl_Allegro_Window_Driver::scroll(int src_x, int src_y, int src_w, int src_h,
                                 int dest_x, int dest_y, void (*draw_area)(void*, int, int, int, int),
                                 void* data)
{
  int rc = 1;

  do
  {

    BITMAP* bmp = create_bitmap(src_w, src_h);

    if (0 == bmp)
    {
      break;
    }

    {
      int sx = (src_x + Fl::window_draw_offset_x);
      int dx = (dest_x + Fl::window_draw_offset_x);
      int sy = (src_y + Fl::window_draw_offset_y);
      int dy = (dest_y + Fl::window_draw_offset_y);

      set_clip_state(bmp, 1);
      Fl_Allegro_Graphics_Driver* gr = reinterpret_cast<Fl_Allegro_Graphics_Driver*>
                                       (fl_graphics_driver);
      blit(gr->surface(), bmp, sx, sy, 0, 0, src_w, src_h);
      blit(bmp, gr->surface(), 0, 0, dx, dy, src_w, src_h);
      destroy_bitmap(bmp);
    }

    rc = 0;

  }
  while (0);

  return rc;
}

#else

int
Fl_Allegro_Window_Driver::scroll(int src_x, int src_y, int src_w, int src_h,
                                 int dest_x, int dest_y, void (*draw_area)(void*, int, int, int, int),
                                 void* data)
{
  return 0;
}

#endif


void
Fl_Allegro_Window_Driver::redisplay_cursor() const
{

#if defined(USE_ALLEGRO)

  if (0 == cursor_.custom_.bmp_)
  {
    cursor_set(cursor_.pointer_);
  }

  else
  {
    fl_graphics_driver->mouse_hide();
    set_mouse_sprite(cursor_.custom_.bmp_);
    set_mouse_sprite_focus(cursor_.custom_.hot_x_, cursor_.custom_.hot_y_);
    fl_graphics_driver->mouse_show();
  }

#else

  struct cursor* cursor = cursor_.current_;

  if (cursor)
  {
    cursor_backing_to_image(_screen);
    unsigned x;
    unsigned y;
    unsigned state;
    mouse_get_position(&x, &y, &state);
    x -= cursor->hot_x;
    y -= cursor->hot_y;
    cursor_image_to_backing(_screen, x, y, cursor->width, cursor->height);
    cursor_blt(_screen, x, y, cursor);
  }

#endif

  return;
}

Fl_Cursor
Fl_Allegro_Window_Driver::get_cursor() const
{
  return cursor_.pointer_;
}

#if defined(USE_ALLEGRO)

int
Fl_Allegro_Window_Driver::set_cursor(Fl_Cursor c)
{

  if (cursor_.pointer_ != c)
  {
    cursor_set(c);
    cursor_.pointer_ = c;
  }

  if (cursor_.custom_.bmp_)
  {
    destroy_bitmap(cursor_.custom_.bmp_);
    cursor_.custom_.bmp_ = 0;
  }

  return 1;
}

#else

int
Fl_Allegro_Window_Driver::set_cursor(Fl_Cursor c)
{

  do
  {

    // if (cursor_.custom_.bmp_)
    // {
    //    TODO
    // }

    if (c == cursor_.pointer_)
    {
      break;
    }

    cursor_.pointer_ = c;
    cursor_.current_ = 0;
    struct cursor* cursor = 0;

    switch (c)
    {
      case FL_CURSOR_DEFAULT:
      case FL_CURSOR_ARROW:
        cursor = &_cursor_arrow;
        break;

      case FL_CURSOR_CROSS:
        cursor = &_cursor_crossh;
        break;

      case FL_CURSOR_WAIT:
        cursor = &_cursor_wait;
        break;

      case FL_CURSOR_INSERT:
        cursor = &_cursor_insert;
        break;

      case FL_CURSOR_HAND:
        cursor = &_cursor_hand;
        break;

      case FL_CURSOR_HELP:
        cursor = &_cursor_help;
        break;

      case FL_CURSOR_MOVE:
        cursor = &_cursor_move;
        break;

      case FL_CURSOR_NS:
        cursor = &_cursor_ns;
        break;

      case FL_CURSOR_WE:
        cursor = &_cursor_ew;
        break;

      case FL_CURSOR_NWSE:
        cursor = &_cursor_nwse;
        break;

      case FL_CURSOR_NESW:
        cursor = &_cursor_nesw;
        break;

      case FL_CURSOR_N:
        cursor = &_cursor_n;
        break;

      case FL_CURSOR_NE:
        cursor = &_cursor_ne;
        break;

      case FL_CURSOR_E:
        cursor = &_cursor_e;
        break;

      case FL_CURSOR_SE:
        cursor = &_cursor_se;
        break;

      case FL_CURSOR_S:
        cursor = &_cursor_s;
        break;

      case FL_CURSOR_SW:
        cursor = &_cursor_sw;
        break;

      case FL_CURSOR_W:
        cursor = &_cursor_w;
        break;

      case FL_CURSOR_NW:
        cursor = &_cursor_nw;
        break;

      case FL_CURSOR_NONE:
      default:
        break;
    }

    cursor_.current_ = cursor;

    cursor_backing_to_image(_screen);

    if (0 == cursor)
    {
      break;
    }

    unsigned x;
    unsigned y;
    unsigned state;
    mouse_get_position(&x, &y, &state);
    x -= cursor->hot_x;
    y -= cursor->hot_y;
    cursor_image_to_backing(_screen, x, y, cursor->width, cursor->height);
    cursor_blt(_screen, x, y, cursor);

  }
  while (0);

  return 0;
}

#endif

#if defined(USE_ALLEGRO)

int
Fl_Allegro_Window_Driver::set_cursor(const Fl_RGB_Image* img, int hot_x,
                                     int hot_y)
{
  BITMAP* bmp = rgb_image_to_bitmap((*img));

  fl_graphics_driver->mouse_hide();

  cursor_.pointer_ = FL_CURSOR_DEFAULT;
  set_cursor(FL_CURSOR_DEFAULT);

  if (cursor_.custom_.bmp_)
  {
    destroy_bitmap(cursor_.custom_.bmp_);
    cursor_.custom_.bmp_ = 0;
  }

  if (bmp)
  {
    cursor_.custom_.bmp_ = bmp;
    cursor_.custom_.hot_x_ = hot_x;
    cursor_.custom_.hot_y_ = hot_y;
    set_mouse_sprite(bmp);
    set_mouse_sprite_focus(hot_x, hot_y);
  }

  fl_graphics_driver->mouse_show();

  return (bmp ? 1 : 0);
}

#else

int
Fl_Allegro_Window_Driver::set_cursor(const Fl_RGB_Image* img, int hot_x,
                                     int hot_y)
{
  return 0;
}

#endif
