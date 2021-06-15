// aldrvscr.cxx
//
// Allegro4/OW32SVGA Screen Driver for the Fast Light Tool Kit (FLTK)
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
#include "aldrvscr.h"

#include "aldrvwin.h"
#include <fl/fl.h>
#include <fl/fl_enums.h>
#include <fl/platform.h>

#if defined(USE_OWD32)
#  include "cursor.h"
#  include "display.h"
#  include "keyboard.h"
#  include "mouse.h"
#  define SCREEN_W _screen->len_x
#  define SCREEN_H _screen->len_y
#  pragma aux __halt = "hlt";
#endif

extern void
  cleanup_dummy();

extern void
  fl_fix_focus(); // in Fl.cxx

Fl_Screen_Driver *
  Fl_Screen_Driver::newScreenDriver()
{
  return new Fl_Allegro_Screen_Driver();
}

Fl_Allegro_Screen_Driver::Fl_Allegro_Screen_Driver() :
  Fl_Screen_Driver(), timer_(), dclick_(), clock_(), btn_state_(0)
{
  ticks_set(clock_);
  dclick_.set(0.50);
  return;
}

Fl_Allegro_Screen_Driver::~Fl_Allegro_Screen_Driver()
{
  close_display();
  cleanup_dummy();
  return;
}

int
  Fl_Allegro_Screen_Driver::x()
{
  return 0;
}

int
  Fl_Allegro_Screen_Driver::y()
{
  return 0;
}

int
  Fl_Allegro_Screen_Driver::w()
{
  if (-1 == num_screens)
    {
      open_display();
    }

  return SCREEN_W;
}

int
  Fl_Allegro_Screen_Driver::h()
{
  if (-1 == num_screens)
    {
      open_display();
    }

  return SCREEN_H;
}

void
  Fl_Allegro_Screen_Driver::screen_xywh(int &X, int &Y, int &W, int &H, int n)
{
  if (0 == n)
    {
      if (-1 == num_screens)
        {
          open_display();
        }

      W = SCREEN_W;
      H = SCREEN_H;
    }
  else
    {
      W = 0;
      H = 0;
    }

  X = 0;
  Y = 0;

  return;
}

void
  Fl_Allegro_Screen_Driver::screen_work_area(
    int &X, int &Y, int &W, int &H, int n)
{
  if (0 == n)
    {
      if (-1 == num_screens)
        {
          open_display();
        }

      W = SCREEN_W;
      H = SCREEN_H;
    }
  else
    {
      W = 0;
      H = 0;
    }

  X = 0;
  Y = 0;

  return;
}

void
  Fl_Allegro_Screen_Driver::screen_dpi(float &h, float &v, int /*n*/)
{
  h = 72.0;
  v = 72.0;
}

void
  Fl_Allegro_Screen_Driver::beep(int type)
{
}

void
  Fl_Allegro_Screen_Driver::flush()
{
}

hit_type
  Fl_Allegro_Screen_Driver::hit(Fl_Window &window, int const x, int const y)
{
  hit_type what = HIT_NONE;

  do
    {
      if (reinterpret_cast<ptrdiff_t>(window.parent()))
        {
          break;
        }

      int top = window.y();
      int top_actual = top - Fl_Allegro_Window_Driver::title_bar_height;
      int left = window.x();
      int right = left + window.w() - 1;
      int bottom = top + window.h() - 1;

      if (x < (left - 2))
        {
          break;
        }

      if (x > (right + 2))
        {
          break;
        }

      if (y < (top_actual - 2))
        {
          break;
        }

      if (y > (bottom + 2))
        {
          break;
        }

      bool hit_left_edge = ((x >= (left - 2)) && (x <= (left + 2)));

      bool hit_right_edge = false;

      if (false == hit_left_edge)
        {
          hit_right_edge = ((x >= (right - 2)) && (x <= (right + 2)));
        }

      bool hit_top_edge = ((y >= (top_actual - 2)) && (y <= (top_actual + 2)));

      bool hit_bottom_edge = false;

      if (false == hit_top_edge)
        {
          hit_bottom_edge = ((y >= (bottom - 2)) && (y <= (bottom + 2)));
        }

      if (hit_left_edge)
        {
          if (hit_top_edge)
            {
              what = HIT_NORTH_WEST;
              break;
            }

          if (hit_bottom_edge)
            {
              what = HIT_SOUTH_WEST;
              break;
            }

          what = HIT_WEST;
          break;
        }

      if (hit_right_edge)
        {
          if (hit_top_edge)
            {
              what = HIT_NORTH_EAST;
              break;
            }

          if (hit_bottom_edge)
            {
              what = HIT_SOUTH_EAST;
              break;
            }

          what = HIT_EAST;
          break;
        }

      if (hit_top_edge)
        {
          what = HIT_NORTH;
          break;
        }

      if (hit_bottom_edge)
        {
          what = HIT_SOUTH;
          break;
        }

      if ((y > top_actual) && (y < top))
        {
          what = HIT_MOVE;
          break;
        }

      what = HIT_WINDOW;
    }
  while (0);

  switch (what)
    {
    case HIT_NONE:
    case HIT_MOVE:
    case HIT_WINDOW:
      break;
    default:
      if (0 == reinterpret_cast<ptrdiff_t>(window.resizable()))
        {
          what = HIT_NONE;
        }
      break;
    };

  return what;
}

hit_type
  Fl_Allegro_Screen_Driver::hit(Fl_Window *window, int const x, int const y)
{
  hit_type what = hit((*window), x, y);
  Fl_Cursor cursor;

  switch (what)
    {
    case HIT_MOVE:
      cursor = FL_CURSOR_MOVE;
      break;

    case HIT_EAST:
      cursor = FL_CURSOR_E;
      break;

    case HIT_WEST:
      cursor = FL_CURSOR_W;
      break;

    case HIT_NORTH:
      cursor = FL_CURSOR_N;
      break;

    case HIT_NORTH_EAST:
      cursor = FL_CURSOR_NE;
      break;

    case HIT_NORTH_WEST:
      cursor = FL_CURSOR_NW;
      break;

    case HIT_SOUTH:
      cursor = FL_CURSOR_S;
      break;

    case HIT_SOUTH_EAST:
      cursor = FL_CURSOR_SE;
      break;

    case HIT_SOUTH_WEST:
      cursor = FL_CURSOR_SW;
      break;

    default:
      cursor = FL_CURSOR_DEFAULT;
      break;
    }

  fl_cursor(cursor);

  return what;
}

double
  Fl_Allegro_Screen_Driver::wait(double time_to_wait)
{
  bool triggered = false;
  ticker ticker_loop;

  ticker_loop.set(time_to_wait);

  do
    {
      Fl::run_checks();

      // idle processing
      static int in_idle = 0;

      if (Fl::idle && !in_idle)
        {
          in_idle = 1;
          Fl::idle();
          in_idle = 0;
        }

      ticks_t cur;
      ticks_t elapsed;
      ticks_set(cur);
      ticks_subtract(elapsed, clock_, cur);
      clock_ = cur;
      timer_.elapse(elapsed);
      dclick_.elapse(elapsed);
      ticker_loop.elapse(elapsed);

      if (dclick_.expired())
        {
          Fl::e_is_click = 0;
          dclick_.reset();
        }

      Fl::flush();

      // Fl::compose_state= 0;
      Fl::e_state = 0;

      Fl_Window *window = 0;

      if (Fl::grab_)
        {
          window = Fl::grab_;
        }

      else
        {
          if (0 == Fl::focus_)
            {
              window = Fl::first_window();
            }

          else
            {
              window = Fl::focus_->as_window();

              if (0 == window)
                {
                  window = Fl::focus_->window();
                }
            }
        }

      if (0 == window)
        {
          break;
        }

      if (0 == Fl::focus_)
        {
          window->take_focus();
        }

      triggered = wait_mouse(window);

      if (triggered)
        {
          break;
        }

      triggered = wait_keyboard(window);

      if (triggered)
        {
          break;
        }

      if (ticker_loop.expired())
        {
          break;
        }

#if defined(USE_OWD32)
      if (0 == time_to_wait)
        {
          __halt();
        }
#endif
    }
  while (1);

  return 1;
}

int
  Fl_Allegro_Screen_Driver::ready()
{
  return 1;
}

void
  Fl_Allegro_Screen_Driver::grab(Fl_Window *win)
{
  if (win)
    {
      Fl::grab_ = win;
    }

  else if (Fl::grab_)
    {
      Fl::grab_ = 0;
      fl_fix_focus();
    }

  return;
}

void
  Fl_Allegro_Screen_Driver::get_system_colors()
{
}

const char *
  Fl_Allegro_Screen_Driver::get_system_scheme()
{
  return fl_getenv("FLTK_SCHEME");
}

void
  Fl_Allegro_Screen_Driver::add_timeout(double time,
                                        Fl_Timeout_Handler cb,
                                        void *argp)
{
  timer_.add(time, cb, argp);
}

void
  Fl_Allegro_Screen_Driver::repeat_timeout(double time,
                                           Fl_Timeout_Handler cb,
                                           void *argp)
{
  timer_.repeat(time, cb, argp);
}

int
  Fl_Allegro_Screen_Driver::has_timeout(Fl_Timeout_Handler cb, void *argp)
{
  return timer_.contains(cb, argp);
}

void
  Fl_Allegro_Screen_Driver::remove_timeout(Fl_Timeout_Handler cb, void *argp)
{
  timer_.remove(cb, argp);
}

int
  Fl_Allegro_Screen_Driver::compose(int &del)
{
  int condition;
  unsigned char ascii = (unsigned char)Fl::e_text[0];
  condition = (Fl::e_state & (FL_ALT | FL_META | FL_CTRL)) && !(ascii & 128);

  if (condition)
    {
      del = 0; // this stuff is to be treated as a function key
      return 0;
    }

  del = Fl::compose_state;
  Fl::compose_state = 0;

  // Only insert non-control characters:
  if ((!Fl::compose_state) && !(ascii & ~31 && ascii != 127))
    {
      return 0;
    }

  return 1;
}
