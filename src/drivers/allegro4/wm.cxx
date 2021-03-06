// wm.cxx
//
// Window manager for the Fast Light Tool Kit (FLTK)
//
// Copyright 2018-2019 The fltkal authors
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
#include "wm.h"

#include "aldrvgr.h"
#include "aldrvscr.h"
#include "aldrvwin.h"
#include <fl/platform.h>

#if defined(USE_ALLEGRO)
#  include "algfx.h"
#else
#  include "cursor.h"
#  include "image.h"
#  include "mouse.h"
#  define screen _screen
#  pragma aux __halt = "hlt";
#endif

#if defined(USE_OWD32)
inline void
  rect_xor(struct image *const bmp,
           int const x,
           int const y,
           unsigned int const width,
           unsigned int const height)
{
  image_lineh_xor(bmp, x, y, width);
  image_lineh_xor(bmp, x, y + height - 1, width);
  image_linev_xor(bmp, x, y + 1, height - 1);
  image_linev_xor(bmp, x + width - 1, y + 1, height - 1);
  return;
}
#endif

static inline void
  resize_east(int &left,
              int &top,
              int &width,
              int &height,
              int const delta_x,
              int const delta_y)
{
  width += delta_x;

  if (Fl_Allegro_Window_Driver::window_min_width > width)
    {
      width = Fl_Allegro_Window_Driver::window_min_width;
    }
}

static inline void
  resize_west(int &left,
              int &top,
              int &width,
              int &height,
              int const delta_x,
              int const delta_y)
{
  width -= delta_x;

  if (Fl_Allegro_Window_Driver::window_min_width < width)
    {
      left += delta_x;
    }

  else
    {
      width += delta_x;
    }
}

static inline void
  resize_north(int &left,
               int &top,
               int &width,
               int &height,
               int const delta_x,
               int const delta_y)
{
  height -= delta_y;

  if (Fl_Allegro_Window_Driver::window_min_height < height)
    {
      top += delta_y;
    }

  else
    {
      height += delta_y;
    }
}

static inline void
  resize_south(int &left,
               int &top,
               int &width,
               int &height,
               int const delta_x,
               int const delta_y)
{
  height += delta_y;

  if (Fl_Allegro_Window_Driver::window_min_height > height)
    {
      height = Fl_Allegro_Window_Driver::window_min_height;
    }
}

static inline void
  resize_north_east(int &left,
                    int &top,
                    int &width,
                    int &height,
                    int const delta_x,
                    int const delta_y)
{
  resize_north(left, top, width, height, delta_x, delta_y);
  resize_east(left, top, width, height, delta_x, delta_y);
}

static inline void
  resize_north_west(int &left,
                    int &top,
                    int &width,
                    int &height,
                    int const delta_x,
                    int const delta_y)
{
  resize_north(left, top, width, height, delta_x, delta_y);
  resize_west(left, top, width, height, delta_x, delta_y);
}

static inline void
  resize_south_east(int &left,
                    int &top,
                    int &width,
                    int &height,
                    int const delta_x,
                    int const delta_y)
{
  resize_south(left, top, width, height, delta_x, delta_y);
  resize_east(left, top, width, height, delta_x, delta_y);
}

static inline void
  resize_south_west(int &left,
                    int &top,
                    int &width,
                    int &height,
                    int const delta_x,
                    int const delta_y)
{
  resize_south(left, top, width, height, delta_x, delta_y);
  resize_west(left, top, width, height, delta_x, delta_y);
}

static void
  handle_push(Fl_Window &window, hit_type const what)
{
  int left = window.x() - 1;
  int top = window.y() - Fl_Allegro_Window_Driver::title_bar_height;
  int width = window.w() + 1;
  int height = window.h() + Fl_Allegro_Window_Driver::title_bar_height + 1;
  int left_orig = left;
  int top_orig = top;
  int width_orig = width;
  int height_orig = height;
#if defined(USE_OWD32)
  struct mouse_event mouse;
#endif

  fl_graphics_driver->mouse_hide();
  rect_xor(screen, left, top, width, height);
  fl_graphics_driver->mouse_show();

  do
    {
#if defined(USE_ALLEGRO)

      if (mouse_needs_poll())
        {
          poll_mouse();
        }

      int btn = mouse_b;

#else

      int rc = mouse_get_event(&mouse);

      if (0 == rc)
        {
          __halt();
          continue;
        }

      int btn = mouse.m_btn_state;

#endif

      if (0 == btn)
        {
          if (left_orig == left && top_orig == top && width_orig == width
              && height_orig == height)
            {
              fl_graphics_driver->mouse_hide();
              rect_xor(screen, left, top, width, height);
              fl_graphics_driver->mouse_show();
              break;
            }

          window.resize(left + 1,
                        top + Fl_Allegro_Window_Driver::title_bar_height,
                        width - 1,
                        height - Fl_Allegro_Window_Driver::title_bar_height
                          - 1);

          break;
        }

#if defined(USE_ALLEGRO)
      int pos = mouse_pos;
      int x = (pos >> 16);
      int y = (0xffff & pos);
#else
      int x = mouse.m_curs_col;
      int y = mouse.m_curs_row;
#endif
      int delta_x = (x - Fl::e_x_root);
      int delta_y = (y - Fl::e_y_root);
      int movement = (abs(delta_x) + abs(delta_y));

      Fl::e_x_root = x;
      Fl::e_y_root = y;

      if (movement)
        {
#if defined(USE_OWD32)
          cursor_pos(x, y);
#endif
          int left1 = left;
          int top1 = top;
          int width1 = width;
          int height1 = height;

          switch (what)
            {
            case HIT_MOVE:
              {
                top += delta_y;
                left += delta_x;
                break;
              }

            case HIT_EAST:
              {
                resize_east(left, top, width, height, delta_x, delta_y);
                break;
              }

            case HIT_WEST:
              {
                resize_west(left, top, width, height, delta_x, delta_y);
                break;
              }

            case HIT_NORTH:
              {
                resize_north(left, top, width, height, delta_x, delta_y);
                break;
              }

            case HIT_SOUTH:
              {
                resize_south(left, top, width, height, delta_x, delta_y);
                break;
              }

            case HIT_NORTH_EAST:
              {
                resize_north_east(left, top, width, height, delta_x, delta_y);
                break;
              }

            case HIT_NORTH_WEST:
              {
                resize_north_west(left, top, width, height, delta_x, delta_y);
                break;
              }

            case HIT_SOUTH_EAST:
              {
                resize_south_east(left, top, width, height, delta_x, delta_y);
                break;
              }

            case HIT_SOUTH_WEST:
              {
                resize_south_west(left, top, width, height, delta_x, delta_y);
                break;
              }

            default:
              break;
            }

          if (left1 != left || top1 != top || width1 != width
              || height1 != height)
            {
              fl_graphics_driver->mouse_hide();
              rect_xor(screen, left1, top1, width1, height1);
              rect_xor(screen, left, top, width, height);
              fl_graphics_driver->mouse_show();
            }
        }
    }
  while (1);

  return;
}

bool
  wm::handle_push(Fl_Window &window,
                  hit_type const what,
                  int const x,
                  int const y)
{
  bool handled = false;

  do
    {
      if (!(FL_WINDOW == window.type() || FL_DOUBLE_WINDOW == window.type()))
        {
          break;
        }

      if (HIT_WINDOW == what)
        {
          break;
        }

      if (HIT_NONE != what)
        {
          ::handle_push(window, what);
          handled = true;
          break;
        }

      if (window.modal())
        {
          break;
        }

      Fl_X *i;

      for (Fl_X **pp = &Fl_X::first; (i = *pp); pp = &i->next)
        {
          Fl_Window *wi = i->w;

          if (wi != &window)
            {
              hit_type what2 = Fl_Allegro_Screen_Driver::hit((*wi), x, y);

              if (what2)
                {
                  *pp = i->next;
                  i->next = Fl_X::first;
                  Fl_X::first = i;
                  wi->take_focus();
                  Fl::focus(wi); // force focus (empty windows)
                  wi->redraw();  // paint above all other windows
                  break;
                }
            }
        }
    }
  while (0);

  return handled;
}
