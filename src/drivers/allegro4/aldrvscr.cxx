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
#  define SCREEN_W _screen->width
#  define SCREEN_H _screen->height
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
  Fl_Screen_Driver(), wm_(), timer_(), dclick_(), clock_(), btn_state_(0),
  cursor_(FL_CURSOR_DEFAULT)
{
  ticks_set(clock_);
  dclick_.set(0.50);
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

wm::hit_type
  Fl_Allegro_Screen_Driver::hit(Fl_Window *window, int const x, int const y)
{
  wm::hit_type hit = wm_.hit((*window), x, y);
  Fl_Window_Driver &wdriver = *Fl_Window_Driver::driver(window);
  Fl_Cursor curwin = wdriver.get_cursor();
  Fl_Cursor curnew = curwin;

  switch (hit)
    {
    case wm::HIT_MOVE:
      curnew = FL_CURSOR_MOVE;
      break;

    case wm::HIT_EAST:
      curnew = FL_CURSOR_E;
      break;

    case wm::HIT_WEST:
      curnew = FL_CURSOR_W;
      break;

    case wm::HIT_NORTH:
      curnew = FL_CURSOR_N;
      break;

    case wm::HIT_NORTH_EAST:
      curnew = FL_CURSOR_NE;
      break;

    case wm::HIT_NORTH_WEST:
      curnew = FL_CURSOR_NW;
      break;

    case wm::HIT_SOUTH:
      curnew = FL_CURSOR_S;
      break;

    case wm::HIT_SOUTH_EAST:
      curnew = FL_CURSOR_SE;
      break;

    case wm::HIT_SOUTH_WEST:
      curnew = FL_CURSOR_SW;
      break;

    default:
      curnew = FL_CURSOR_DEFAULT;
      break;
    }

  if (cursor_ != curnew)
    {
      if (curnew != curwin)
        {
          wdriver.set_cursor(curnew);
        }

      else
        {
          wdriver.redisplay_cursor();
        }

      cursor_ = curnew;
    }

  return hit;
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

void
  Fl_Allegro_Screen_Driver::open_display_platform()
{
  int rc = display_init_once();

  if (rc)
    {
      fprintf(stderr, "Unable to initialize display\n");
      exit(-1);
    }

  num_screens = 1;

  mouse_init();

  unsigned x;
  unsigned y;
  unsigned state;

  mouse_set_range(_screen->width - 1, _screen->height - 1);
  mouse_get_position(&x, &y, &state);
  cursor_image_to_backing(
    _screen, x, y, _cursor_arrow.width, _cursor_arrow.height);
  cursor_blt(_screen, x, y, &_cursor_arrow);
}

void
  Fl_Allegro_Screen_Driver::close_display()
{
  mouse_deinit();
  display_deinit_once();
  cleanup_dummy();
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
