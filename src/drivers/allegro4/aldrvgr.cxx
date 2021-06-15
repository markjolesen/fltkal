// aldrvgr.cxx
//
// Graphics Driver for the Fast Light Tool Kit (FLTK)
//
// Copyright 2017-2021 The fltkal authors
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
#include "aldrvgr.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "imgconv.h"
#include <fl/fl.h>

#if defined(USE_OWD32)
#  define SCREEN_W _screen->len_x
#  define SCREEN_H _screen->len_y
#endif

#if !defined(M_PI)
#  define M_PI 3.14159
#endif

struct _XRegion
{
  int x1;
  int y1;
  int x2;
  int y2;
};

Fl_Graphics_Driver *
  Fl_Graphics_Driver::newMainGraphicsDriver()
{
  return new Fl_Allegro_Graphics_Driver();
}

Fl_Allegro_Graphics_Driver::Fl_Allegro_Graphics_Driver() :
  Fl_Graphics_Driver(), ft_(), active_(0), backing_(0), hidden_count_(0),
  flipped_count_(0)
{
  return;
}

Fl_Allegro_Graphics_Driver::~Fl_Allegro_Graphics_Driver()
{
  return;
}

void
  Fl_Allegro_Graphics_Driver::draw(const char *str, int n, int x, int y)
{
  x += Fl::window_draw_offset_x;
  y += Fl::window_draw_offset_y;

  if (n > 0)
    {
#if defined(USE_ALLEGRO)
      unsigned char r, g, b;
      Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
      unsigned color = makecol(r, g, b);
#else
      unsigned color = Fl::get_color(Fl_Graphics_Driver::color());
      color >>= 8;
#endif
      ft_.draw(surface(), str, n, x, y, font_, size_, color);
    }

  return;
}

void
  Fl_Allegro_Graphics_Driver::point(int x, int y)
{
  x += Fl::window_draw_offset_x;
  y += Fl::window_draw_offset_y;
#if defined(USE_ALLEGRO)
  unsigned char r, g, b;
  Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
  int color = makecol(r, g, b);
  ::putpixel(surface(), x, y, color);
#else
  unsigned color = Fl::get_color(Fl_Graphics_Driver::color());
  color >>= 8;
  image_pixel_put(surface(), x, y, color);
#endif
  return;
}

void
  Fl_Allegro_Graphics_Driver::rect(int x, int y, int w, int h)
{
  x += Fl::window_draw_offset_x;
  y += Fl::window_draw_offset_y;
#if defined(USE_ALLEGRO)
  unsigned char r, g, b;
  Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
  int color = makecol(r, g, b);
  ::rect(surface(), x, y, x + w - 1, y + h - 1, color);
#else
  unsigned color = Fl::get_color(Fl_Graphics_Driver::color());
  color >>= 8;
  image_lineh(surface(), x, y, w, color);
  image_lineh(surface(), x, y + h, w, color);
  image_linev(surface(), x, y, h, color);
  image_linev(surface(), x + w, y, h, color);
#endif
  return;
}

void
  Fl_Allegro_Graphics_Driver::rectf(int x, int y, int w, int h)
{
  x += Fl::window_draw_offset_x;
  y += Fl::window_draw_offset_y;
#if defined(USE_ALLEGRO)
  unsigned char r, g, b;
  Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
  int color = makecol(r, g, b);
  ::rectfill(surface(), x, y, x + w - 1, y + h - 1, color);
#else
  unsigned color = Fl::get_color(Fl_Graphics_Driver::color());
  color >>= 8;
  image_fill_area(surface(), x, y, w, h, color);
#endif
  return;
}

void
  Fl_Allegro_Graphics_Driver::line(int x, int y, int x1, int y1)
{
  x += Fl::window_draw_offset_x;
  x1 += Fl::window_draw_offset_x;
  y += Fl::window_draw_offset_y;
  y1 += Fl::window_draw_offset_y;
#if defined(USE_ALLEGRO)
  unsigned char r, g, b;
  Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
  int color = makecol(r, g, b);
  ::line(surface(), x, y, x1, y1, color);
#else
  unsigned color = Fl::get_color(Fl_Graphics_Driver::color());
  color >>= 8;
  image_line(surface(), x, y, x1, y1, color);
#endif
  return;
}

void
  Fl_Allegro_Graphics_Driver::polygon(
    int x0, int y0, int x1, int y1, int x2, int y2)
{
  int points[6];
  points[0] = x0 + Fl::window_draw_offset_x;
  points[1] = y0 + Fl::window_draw_offset_y;
  points[2] = x1 + Fl::window_draw_offset_x;
  points[3] = y1 + Fl::window_draw_offset_y;
  points[4] = x2 + Fl::window_draw_offset_x;
  points[5] = y2 + Fl::window_draw_offset_y;
#if defined(USE_ALLEGRO)
  unsigned char r, g, b;
  Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
  int color = makecol(r, g, b);
  ::polygon(surface(), 3, points, color);
#endif
  return;
}

void
  Fl_Allegro_Graphics_Driver::polygon(
    int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
  int points[8];
  points[0] = x0 + Fl::window_draw_offset_x;
  points[1] = y0 + Fl::window_draw_offset_y;
  points[2] = x1 + Fl::window_draw_offset_x;
  points[3] = y1 + Fl::window_draw_offset_y;
  points[4] = x2 + Fl::window_draw_offset_x;
  points[5] = y2 + Fl::window_draw_offset_y;
  points[6] = x3 + Fl::window_draw_offset_x;
  points[7] = y3 + Fl::window_draw_offset_y;
#if defined(USE_ALLEGRO)
  unsigned char r, g, b;
  Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
  int color = makecol(r, g, b);
  ::polygon(surface(), 4, points, color);
#endif
  return;
}

void
  Fl_Allegro_Graphics_Driver::circle(double x, double y, double rad)
{
  x += Fl::window_draw_offset_x;
  y += Fl::window_draw_offset_y;
#if defined(USE_ALLEGRO)
  unsigned char r, g, b;
  Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
  int color = makecol(r, g, b);
  ::circle(surface(),
           static_cast<int>(x),
           static_cast<int>(y),
           static_cast<int>(rad),
           color);
#endif
  return;
}

// Fl_Pico_Graphics_Driver::arc
// Fl_Android_Graphics_driver::arc
void
  Fl_Allegro_Graphics_Driver::arc(
    int xi, int yi, int w, int h, double a1, double a2)
{
  xi += Fl::window_draw_offset_x;
  yi += Fl::window_draw_offset_y;
#if defined(USE_ALLEGRO)
  unsigned char r, g, b;
  Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
  int color = makecol(r, g, b);
#else
  unsigned color = Fl::get_color(Fl_Graphics_Driver::color());
  color >>= 8;
#endif

  if (a2 <= a1)
    {
      return;
    }

  double rx = w / 2.0;
  double ry = h / 2.0;
  double x = xi + rx;
  double y = yi + ry;
  double circ = M_PI * 0.5 * (rx + ry);
  int i, segs = static_cast<int>(
           circ * (a2 - a1) / 1000); // every line is about three pixels long

  if (segs < 3)
    {
      segs = 3;
    }

  int px, py;
  a1 = a1 / 180 * M_PI;
  a2 = a2 / 180 * M_PI;
  double step = (a2 - a1) / segs;

  double sina1 = sin(a1);
  double cosa1 = cos(a1);
  int nx = static_cast<int>(x + sina1 * rx);
  int ny = static_cast<int>(y - cosa1 * ry);

  for (i = segs; i > 0; i--)
    {
      a1 += step;
      px = nx;
      py = ny;
      int nx = static_cast<int>(x + sina1 * rx);
      int ny = static_cast<int>(y - cosa1 * ry);
#if defined(USE_ALLEGRO)
      ::line(surface(), px, py, nx, ny, color);
#else
      image_line(surface(), px, py, nx, ny, color);
#endif
    }

  return;
}

// Fl_Android_Graphics_driver::pie
void
  Fl_Allegro_Graphics_Driver::pie(
    int xi, int yi, int w, int h, double b1, double b2)
{
  // quick access to bounding box size
  double rx = w / 2.0;
  double ry = h / 2.0;
  double x = xi + rx;
  double y = yi + ry;

  double a1 = b1 / 180 * M_PI;
  double a2 = b2 / 180 * M_PI;

  // invert to make b1 always the smaller value
  if (b1 > b2)
    {
      b1 -= 360.0;
    }

  if (b1 == b2)
    {
      return;
    }

  // make the top the zero degree origin, turning CCW
  b1 -= 90.0;
  b2 -= 90.0;

  // find the delta between angles
  double delta = b2 - b1;

  if (delta >= 360.0)
    {
      b1 = 0.0;
      b2 = 360.0;
      delta = 360.0;
    }

  // make sure that b2 is always in the range [0.0..360.0]
  if (b2 > 360.0)
    {
      b2 -= 360.0; // FIXME: fmod(...)
    }

  if (b2 < 0.0)
    {
      b2 += 360.0;
    }

  b1 = b2 - delta;
  // now b1 is [-360...360] and b2 is [0..360] and b1<b2;

  a1 = b1 / 180 * M_PI;
  a2 = b2 / 180 * M_PI;
  double b1o = b1;
  bool flipped = false;

  if (a1 < 0.0)
    {
      a1 += 2 * M_PI;
      b1 += 360.0;
      flipped = true;
    }

  //  Fl_Android_Application::log_e(" %g %g %d", b1, b2, flipped);

  double a1Slope = tan(a1);
  double a2Slope = tan(a2);

  // draw the pie line by line
  for (double iy = y - ry; iy <= y + ry; iy++)
    {
      double a = acos((iy - y) / ry);
      double aL = M_PI - a; // 0..PI
      double aR = a + M_PI; // 2PI..PI
      double sinALrx = sin(aL) * rx;

      //    fl_color(FL_RED);

      if (aL < 0.5 * M_PI)
        {
          // rasterize top left quadrant
          bool loInside = false, hiInside = false;
          double loLeft = 0.0, loRight = 0.0;
          double hiLeft = 0.0, hiRight = 0.0;

          if (b1 >= 0 && b1 < 90)
            {
              loInside = true;
              loLeft = -sinALrx;
              loRight = a1Slope * (iy - y);
            }

          if (b2 >= 0 && b2 < 90)
            {
              hiInside = true;

              if (aL < a2)
                {
                  hiLeft = -sinALrx;
                }

              else
                {
                  hiLeft = a2Slope * (iy - y);
                }
            }

          if (loInside && hiInside && !flipped)
            {
              //        fl_color(FL_GREEN);
              if (a1 < aL)
                {
                  xyline(x + hiLeft, iy, x + loRight);
                }
            }

          else
            {
              if ((!loInside) && (!hiInside))
                {
                  //          fl_color(FL_MAGENTA);
                  if ((b1o <= 0.0 && b2 >= 90.0)
                      || (b1o <= (0.0 - 360.0) && b2 >= (90.0 - 360.0)))
                    {
                      xyline(x - sinALrx, iy, x);
                    }
                }

              else
                {
                  if (loInside)
                    {
                      //            fl_color(FL_BLUE);
                      if (a1 < aL)
                        {
                          xyline(x + loLeft, iy, x + loRight);
                        }
                    }

                  if (hiInside)
                    {
                      //            fl_color(FL_YELLOW);
                      xyline(x + hiLeft, iy, x);
                    }
                }
            }
        }

      else
        {
          // rasterize bottom left quadrant
          bool loInside = false, hiInside = false;
          double loLeft = 0.0, loRight = 0.0;
          double hiLeft = 0.0, hiRight = 0.0;

          if (b1 >= 90 && b1 < 180)
            {
              loInside = true;

              if (aL >= a1)
                {
                  loLeft = -sinALrx;
                }

              else
                {
                  loLeft = a1Slope * (iy - y);
                }
            }

          if (b2 >= 90 && b2 < 180)
            {
              hiInside = true;
              hiLeft = -sinALrx;
              hiRight = a2Slope * (iy - y);
            }

          if (loInside && hiInside && !flipped)
            {
              //        fl_color(FL_GREEN);
              if (a2 > aL)
                {
                  xyline(x + loLeft, iy, x + hiRight);
                }
            }

          else
            {
              if ((!loInside) && (!hiInside))
                {
                  //          fl_color(FL_MAGENTA);
                  if ((b1o <= 90.0 && b2 >= 180.0)
                      || (b1o <= (90.0 - 360.0) && b2 >= (180.0 - 360.0)))
                    {
                      xyline(x - sinALrx, iy, x);
                    }
                }

              else
                {
                  if (loInside)
                    {
                      //            fl_color(FL_BLUE);
                      xyline(x + loLeft, iy, x);
                    }

                  if (hiInside)
                    {
                      //            fl_color(FL_YELLOW);
                      if (a2 > aL)
                        {
                          xyline(x + hiLeft, iy, x + hiRight);
                        }
                    }
                }
            }
        }

      if (aR < 1.5 * M_PI)
        {
          // rasterize bottom right quadrant
          bool loInside = false, hiInside = false;
          double loLeft = 0.0, loRight = 0.0;
          double hiLeft = 0.0, hiRight = 0.0;

          if (b1 >= 180 && b1 < 270)
            {
              loInside = true;
              loLeft = sinALrx;
              loRight = a1Slope * (iy - y);
            }

          if (b2 >= 180 && b2 < 270)
            {
              hiInside = true;

              if (aR < a2)
                {
                  hiLeft = sinALrx;
                }

              else
                {
                  hiLeft = a2Slope * (iy - y);
                }
            }

          if (loInside && hiInside && !flipped)
            {
              //        fl_color(FL_GREEN);
              if (a1 < aR)
                {
                  xyline(x + hiLeft, iy, x + loRight);
                }
            }

          else
            {
              if ((!loInside) && (!hiInside))
                {
                  //          fl_color(FL_MAGENTA);
                  if ((b1o <= 180.0 && b2 >= 270.0)
                      || (b1o <= (180.0 - 360.0) && b2 >= (270.0 - 360.0)))
                    {
                      xyline(x + sinALrx, iy, x);
                    }
                }

              else
                {
                  if (loInside)
                    {
                      //            fl_color(FL_BLUE);
                      if (a1 < aR)
                        {
                          xyline(x + loLeft, iy, x + loRight);
                        }
                    }

                  if (hiInside)
                    {
                      //            fl_color(FL_YELLOW);
                      xyline(x + hiLeft, iy, x);
                    }
                }
            }
        }

      else
        {
          // rasterize top right quadrant
          bool loInside = false, hiInside = false;
          double loLeft = 0.0, loRight = 0.0;
          double hiLeft = 0.0, hiRight = 0.0;

          if (b1 >= 270 && b1 < 360)
            {
              loInside = true;

              if (aR >= a1)
                {
                  loLeft = sinALrx;
                }

              else
                {
                  loLeft = a1Slope * (iy - y);
                }
            }

          if (b2 >= 270 && b2 < 360)
            {
              hiInside = true;
              hiLeft = sinALrx;
              hiRight = a2Slope * (iy - y);
            }

          if (loInside && hiInside && !flipped)
            {
              //        fl_color(FL_GREEN);
              if (a2 > aR)
                {
                  xyline(x + loLeft, iy, x + hiRight);
                }
            }

          else
            {
              if ((!loInside) && (!hiInside))
                {
                  //          fl_color(FL_MAGENTA);
                  if ((b1o <= 270.0 && b2 >= 360.0)
                      || (b1o <= (270.0 - 360.0) && b2 >= (360.0 - 360.0)))
                    {
                      xyline(x + sinALrx, iy, x);
                    }
                }

              else
                {
                  if (loInside)
                    {
                      //            fl_color(FL_BLUE);
                      xyline(x + loLeft, iy, x);
                    }

                  if (hiInside)
                    {
                      //            fl_color(FL_YELLOW);
                      if (a2 > aR)
                        {
                          xyline(x + hiLeft, iy, x + hiRight);
                        }
                    }
                }
            }
        }
    }

  return;
}

void
  Fl_Allegro_Graphics_Driver::push_clip(int x, int y, int w, int h)
{
  Fl_Region r;

  r = reinterpret_cast<Fl_Region>(malloc(sizeof(*r)));

  if (w > 0 && h > 0)
    {
      int cx, cy, cw, ch;
      clip_box(x, y, w, h, cx, cy, cw, ch);
      r->x1 = cx;
      r->y1 = cy;
      r->x2 = (cx + cw);
      r->y2 = (cy + ch);
    }

  else
    {
      r->x1 = 0;
      r->y1 = 0;
      r->x2 = (SCREEN_W - 1);
      r->y2 = (SCREEN_H - 1);
    }

  if (rstackptr < region_stack_max)
    {
      rstack[++rstackptr] = r;
    }

  else
    {
      Fl::warning(
        "Fl_Allegro_Graphics_Driver::push_clip: clip stack overflow!\n");
      free(r);
    }

  restore_clip();

  return;
}

int
  Fl_Allegro_Graphics_Driver::clip_box(
    int x, int y, int w, int h, int &X, int &Y, int &W, int &H)
{
  struct _XRegion xscr;

  X = x;
  Y = y;
  W = w;
  H = h;

  Fl_Region r = rstack[rstackptr];

  if (!r)
    {
      xscr.x1 = 0;
      xscr.y1 = 0;
      xscr.x2 = (SCREEN_W - 1);
      xscr.y2 = (SCREEN_H - 1);
      r = &xscr;
    }

  if (X < r->x1)
    {
      W -= r->x1 - X;

      if (0 > W)
        {
          W = 0;
        }

      X = r->x1;
    }

  else if (X > r->x2)
    {
      X = r->x2;
    }

  if ((X + W) > r->x2)
    {
      if (X < r->x2)
        {
          W = (r->x2 - X);
        }

      else
        {
          W = 0;
        }
    }

  if (Y < r->y1)
    {
      H -= (r->y1 - Y);

      if (0 > H)
        {
          H = 0;
        }

      Y = r->y1;
    }

  else if (Y > r->y2)
    {
      Y = r->y2;
    }

  if ((Y + H) > r->y2)
    {
      if (Y < r->y2)
        {
          H = (r->y2 - Y);
        }

      else
        {
          H = 0;
        }
    }

  return (X != x || Y != y || W != w || H != h);
}

int
  Fl_Allegro_Graphics_Driver::not_clipped(int x, int y, int w, int h)
{
  if (x + w <= 0 || y + h <= 0)
    {
      return 0;
    }

  Fl_Region r = rstack[rstackptr];

  if (!r)
    {
      return 1;
    }

  return ((x < r->x2) && ((x + w) > r->x1) && (y < r->y2)
          && ((y + h) > r->y1));
}

void
  Fl_Allegro_Graphics_Driver::push_no_clip()
{
  if (rstackptr < region_stack_max)
    {
      rstack[++rstackptr] = 0;
    }

  else
    {
      Fl::warning(
        "Fl_Xlib_Graphics_Driver::push_no_clip: clip stack overflow!\n");
    }

  restore_clip();

  return;
}

void
  Fl_Allegro_Graphics_Driver::pop_clip()
{
  if (rstackptr > 0)
    {
      Fl_Region oldr = rstack[rstackptr--];
      free(oldr);
    }

  else
    {
      Fl::warning(
        "Fl_Xlib_Graphics_Driver::pop_clip: clip stack underflow!\n");
    }

  restore_clip();

  return;
}

void
  Fl_Allegro_Graphics_Driver::restore_clip()
{
#if defined(USE_ALLEGRO)
  BITMAP *bmp = surface();
#else
  struct image *bmp = surface();
#endif

  if ((rstackptr > 0) && rstack[rstackptr])
    {
      Fl_Region r = rstack[rstackptr];
      int x1 = (r->x1 + Fl::window_draw_offset_x);
      int x2 = (r->x2 + Fl::window_draw_offset_x);
      int y1 = (r->y1 + Fl::window_draw_offset_y);
      int y2 = (r->y2 + Fl::window_draw_offset_y);
#if defined(USE_ALLEGRO)

      if (0 > x1)
        x1 = 0;

      if (bmp->w < (unsigned)x2)
        x2 = bmp->w;

      if (0 > y1)
        y1 = 0;

      if (bmp->h < (unsigned)y2)
        y2 = bmp->h;

      ::set_clip_rect(surface(), x1, y1, x2, y2);
#else

      if (0 > x1)
        x1 = 0;

      if (bmp->len_x <= (unsigned)x2)
        x2 = (bmp->len_x - 1);

      if (0 > y1)
        y1 = 0;

      if (bmp->len_y <= (unsigned)y2)
        y2 = (bmp->len_y - 1);

      image_set_clip(surface(), x1, y1, x2, y2);
#endif
    }

  else
    {
#if defined(USE_ALLEGRO)
      ::set_clip_rect(bmp, 0, 0, (bmp->w - 1), (bmp->h - 1));
#else
      image_set_clip(bmp, 0, 0, (bmp->len_x - 1), (bmp->len_y - 1));
#endif
    }

  return;
}

double
  Fl_Allegro_Graphics_Driver::width(const char *str, int n)
{
  double width = 0.0f;

  if (n && *str)
    {
      width = ft_.width(str, n, font_, size_);
    }

  return width;
}

void
  Fl_Allegro_Graphics_Driver::flip_to_offscreen(bool clear)
{
  do
    {
      if (flipped_count_)
        {
          break;
        }

      if (0 == backing_)
        {
#if defined(USE_ALLEGRO)
          int depth = bitmap_color_depth(screen);

          backing_ = create_bitmap_ex(depth, SCREEN_W, SCREEN_H);
#else
          backing_
            = image_new(::_screen->len_x, ::_screen->len_y, ::_screen->stride);
#endif

          if (0 == backing_)
            {
              break;
            }
        }

      // TODO: _mjo if backing dimensions differ from screen
      // destroy and rebuild

      active_ = backing_;

      if (clear)
        {
          surface_clear();
        }
      else
        {
#if defined(USE_ALLEGRO)
          blit(::screen, backing_, 0, 0, 0, 0, backing_->w, backing_->h);
#else
          image_blt_exact(backing_, ::_screen);
#endif
        }
    }
  while (0);

  flipped_count_++;

  return;
}

void
  Fl_Allegro_Graphics_Driver::flip_to_onscreen()
{
  if (flipped_count_)
    {
      if (1 == flipped_count_)
        {
#if defined(USE_ALLEGRO)
          blit(backing_, ::screen, 0, 0, 0, 0, backing_->w, backing_->h);
#else
          image_blt_exact(::_screen, backing_);
#endif
          active_ = ::_screen;
        }

      flipped_count_--;
    }

  return;
}

int
  Fl_Allegro_Graphics_Driver::height()
{
  int height2 = ft_.height(font_, size_);
  return height2;
}

int
  Fl_Allegro_Graphics_Driver::descent()
{
  int descent2 = ft_.descent(font_, size_);
  return descent2;
}

void
  Fl_Allegro_Graphics_Driver::font(Fl_Font font, Fl_Fontsize fsize)
{
  font_ = font;
  size_ = fsize;
  return;
}

void
  Fl_Allegro_Graphics_Driver::draw_image(
    const uchar *buf, int X, int Y, int W, int H, int D, int L)
{
  BITMAP *bmp = rgb_data_to_bitmap(static_cast<unsigned int>(W),
                                   static_cast<unsigned int>(H),
                                   static_cast<unsigned int>(D),
                                   static_cast<unsigned int>(L),
                                   buf);
  X += Fl::window_draw_offset_x;
  Y += Fl::window_draw_offset_y;

  if (bmp)
    {
#if defined(USE_ALLEGRO)
      masked_blit(bmp, surface(), 0, 0, X, Y, bmp->w, bmp->h);
      destroy_bitmap(bmp);
#else
      struct slice slice;
      slice.pos_x = 0;
      slice.pos_y = 0;
      slice.len_x = W;
      slice.len_y = H;
      bitmap_blt(surface(), X, Y, bmp, &slice, 0, 0);
      bitmap_free(bmp);
#endif
    }

  return;
}

void
  Fl_Allegro_Graphics_Driver::draw_image(
    Fl_Draw_Image_Cb cb, void *data, int X, int Y, int W, int H, int D)
{
  X += Fl::window_draw_offset_x;
  Y += Fl::window_draw_offset_y;

  BITMAP *bmp = rgb_staged_to_image(cb,
                                    data,
                                    static_cast<unsigned int>(W),
                                    static_cast<unsigned int>(H),
                                    static_cast<unsigned int>(D));

  if (bmp)
    {
#if defined(USE_ALLEGRO)
      masked_blit(bmp, surface(), 0, 0, X, Y, bmp->w, bmp->h);
      destroy_bitmap(bmp);
#else
      struct slice slice;
      slice.pos_x = 0;
      slice.pos_y = 0;
      slice.len_x = W;
      slice.len_y = H;
      bitmap_blt(surface(), X, Y, bmp, &slice, 0, 0);
      bitmap_free(bmp);
#endif
    }
  return;
}

void
  Fl_Allegro_Graphics_Driver::draw_fixed(
    Fl_RGB_Image *rgb, int XP, int YP, int WP, int HP, int cx, int cy)
{
  int X = XP + Fl::window_draw_offset_x;
  int Y = YP + Fl::window_draw_offset_y;

  BITMAP *bmp = rgb_image_to_bitmap((*rgb));

  if (bmp)
    {
#if defined(USE_ALLEGRO)
      masked_blit(bmp, surface(), cx, cy, X, Y, WP, HP);
      destroy_bitmap(bmp);
#else
      struct slice slice;
      slice.pos_x = cx;
      slice.pos_y = cy;
      slice.len_x = WP;
      slice.len_y = HP;
      bitmap_blt(surface(), X, Y, bmp, &slice, 0, 0);
      bitmap_free(bmp);
#endif
    }
}

void
  Fl_Allegro_Graphics_Driver::draw_fixed(
    Fl_Pixmap *pxm, int XP, int YP, int WP, int HP, int cx, int cy)
{
  int X = XP + Fl::window_draw_offset_x;
  int Y = YP + Fl::window_draw_offset_y;
  BITMAP *bmp = pxm_to_bitmap((*pxm));

  if (bmp)
    {
#if defined(USE_ALLEGRO)
      masked_blit(bmp, surface(), cx, cy, X, Y, bmp->w, bmp->h);
      destroy_bitmap(bmp);
#else
      struct slice slice;
      slice.pos_x = cx;
      slice.pos_y = cy;
      slice.len_x = WP;
      slice.len_y = HP;
      bitmap_blt(surface(), X, Y, bmp, &slice, true, 0xFF00FF);
      bitmap_free(bmp);
#endif
    }
}

void
  Fl_Allegro_Graphics_Driver::draw_fixed(
    Fl_Bitmap *bm, int XP, int YP, int WP, int HP, int cx, int cy)
{
  int X = XP + Fl::window_draw_offset_x;
  int Y = YP + Fl::window_draw_offset_y;
  BITMAP *bmp = bitmap_to_bitmap((*bm));

  if (bmp)
    {
#if defined(USE_ALLEGRO)
      masked_blit(bmp, surface(), cx, cy, X, Y, WP, HP);
      destroy_bitmap(bmp);
#else
      struct slice slice;
      slice.pos_x = cx;
      slice.pos_y = cy;
      slice.len_x = WP;
      slice.len_y = HP;
      bitmap_blt(surface(), X, Y, bmp, &slice, 0, 0);
      bitmap_free(bmp);
#endif
    }
}
