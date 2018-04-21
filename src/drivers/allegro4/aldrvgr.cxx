// aldrvgr.cxx
//
// Allegro4 Graphics Driver for the Fast Light Tool Kit (FLTK)
//
// Copyright 2017-2018 The fltkal authors
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
#include "aldrvgr.h"
#include "imgconv.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    Fl_Graphics_Driver(),
    active(0),
    backing(0)
{
    return;
}

Fl_Allegro_Graphics_Driver::~Fl_Allegro_Graphics_Driver()
{
    return;
}

void Fl_Allegro_Graphics_Driver::draw(const char *str, int n, int x, int y)
{
    if (n > 0)
    {
        x += Fl::window_draw_offset_x;
        y += Fl::window_draw_offset_y;
        unsigned char r, g, b;
        Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
        int color = makecol(r, g, b);
        char *buf = reinterpret_cast<char *>(::malloc((n + 1)));
        if (buf)
        {
            ::memcpy(buf, str, n);
            buf[n] = 0;
            ::textout_ex(surface(), ::font, buf, x, (y - 8), color, -1);
            ::free(buf);
        }
    }
    return;
}

void Fl_Allegro_Graphics_Driver::point(int x, int y)
{
    x += Fl::window_draw_offset_x;
    y += Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::putpixel(surface(), x, y, color);
    return;
}

void Fl_Allegro_Graphics_Driver::rect(int x, int y, int w, int h)
{
    x += Fl::window_draw_offset_x;
    y += Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::rect(surface(), x, y, x + w - 1, y + h - 1, color);
    return;
}

void Fl_Allegro_Graphics_Driver::rectf(int x, int y, int w, int h)
{
    x += Fl::window_draw_offset_x;
    y += Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::rectfill(surface(), x, y, x + w - 1, y + h - 1, color);
    return;
}

void Fl_Allegro_Graphics_Driver::line(int x, int y, int x1, int y1)
{
    x += Fl::window_draw_offset_x;
    x1 += Fl::window_draw_offset_x;
    y += Fl::window_draw_offset_y;
    y1 += Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::line(surface(), x, y, x1, y1, color);
    return;
}

void Fl_Allegro_Graphics_Driver::line(int x, int y, int x1, int y1, int x2, int y2)
{
    x += Fl::window_draw_offset_x;
    x1 += Fl::window_draw_offset_x;
    x2 += Fl::window_draw_offset_x;
    y += Fl::window_draw_offset_y;
    y1 += Fl::window_draw_offset_y;
    y2 += Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::line(surface(), x, y, x1, y1, color);
    ::line(surface(), x1, y1, x2, y2, color);
    return;
}

void Fl_Allegro_Graphics_Driver::xyline(int x, int y, int x1)
{
    x += Fl::window_draw_offset_x;
    x1 += Fl::window_draw_offset_x;
    y += Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::line(surface(), x, y, x1, y, color);
    return;
}

void Fl_Allegro_Graphics_Driver::xyline(int x, int y, int x1, int y2)
{
    xyline(x, y, x1);
    yxline(x1, y, y2);
    return;
}

void Fl_Allegro_Graphics_Driver::xyline(int x, int y, int x1, int y2, int x3)
{
    xyline(x, y, x1);
    yxline(x1, y, y2);
    xyline(x1, y2, x3);
    return;
}

void Fl_Allegro_Graphics_Driver::yxline(int x, int y, int y1)
{
    x += Fl::window_draw_offset_x;
    y += Fl::window_draw_offset_y;
    y1 += Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::line(surface(), x, y, x, y1, color);
    return;
}

void Fl_Allegro_Graphics_Driver::yxline(int x, int y, int y1, int x2)
{

    yxline(x, y, y1);
    xyline(x, y1, x2);

    return;
}

void Fl_Allegro_Graphics_Driver::yxline(int x, int y, int y1, int x2, int y3)
{

    yxline(x, y, y1);
    xyline(x, y1, x2);
    yxline(x2, y1, y3);

    return;
}

void Fl_Allegro_Graphics_Driver::loop(int x0, int y0, int x1, int y1, int x2, int y2)
{
    x0 += Fl::window_draw_offset_x;
    x1 += Fl::window_draw_offset_x;
    x2 += Fl::window_draw_offset_x;
    y0 += Fl::window_draw_offset_y;
    y1 += Fl::window_draw_offset_y;
    y2 += Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::line(surface(), x0, y0, x1, y1, color);
    ::line(surface(), x1, y1, x2, y2, color);
    ::line(surface(), x2, y2, x0, y0, color);
    return;
}

void Fl_Allegro_Graphics_Driver::loop(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
    x0 += Fl::window_draw_offset_x;
    x1 += Fl::window_draw_offset_x;
    x2 += Fl::window_draw_offset_x;
    x3 += Fl::window_draw_offset_x;
    y0 += Fl::window_draw_offset_y;
    y1 += Fl::window_draw_offset_y;
    y2 += Fl::window_draw_offset_y;
    y3 += Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::line(surface(), x0, y0, x1, y1, color);
    ::line(surface(), x0, y0, x1, y1, color);
    ::line(surface(), x1, y1, x2, y2, color);
    ::line(surface(), x2, y2, x3, y3, color);
    ::line(surface(), x3, y3, x0, y0, color);
    return;
}

void Fl_Allegro_Graphics_Driver::polygon(int x0, int y0, int x1, int y1, int x2, int y2)
{
    int points[6];
    points[0] = x0 + Fl::window_draw_offset_x;
    points[1] = y0 + Fl::window_draw_offset_y;
    points[2] = x1 + Fl::window_draw_offset_x;
    points[3] = y1 + Fl::window_draw_offset_y;
    points[4] = x2 + Fl::window_draw_offset_x;
    points[5] = y2 + Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::polygon(surface(), 3, points, color);
    return;
}

void Fl_Allegro_Graphics_Driver::polygon(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
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
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::polygon(surface(), 4, points, color);
    return;
}

void Fl_Allegro_Graphics_Driver::circle(double x, double y, double rad)
{
    x += Fl::window_draw_offset_x;
    y += Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);
    ::circle(surface(), x, y, rad, color);
    return;
}

// Fl_Pico_Graphics_Driver::arc
// Fl_Android_Graphics_driver::arc
void Fl_Allegro_Graphics_Driver::arc(int xi, int yi, int w, int h, double a1, double a2)
{
    xi += Fl::window_draw_offset_x;
    yi += Fl::window_draw_offset_y;
    unsigned char r, g, b;
    Fl::get_color(Fl_Graphics_Driver::color(), r, g, b);
    int color = makecol(r, g, b);

    if (a2 <= a1)
    {
        return;
    }

    double rx = w / 2.0;
    double ry = h / 2.0;
    double x = xi + rx;
    double y = yi + ry;
    double circ = M_PI * 0.5 * (rx + ry);
    int i, segs = circ * (a2 - a1) / 1000; // every line is about three pixels long
    if (segs < 3)
    {
        segs = 3;
    }

    int px, py;
    a1 = a1 / 180 * M_PI;
    a2 = a2 / 180 * M_PI;
    double step = (a2 - a1) / segs;

    int nx = x + cos(a1) * rx;
    int ny = y - sin(a1) * ry;
    for (i = segs; i > 0; i--)
    {
        a1 += step;
        px = nx;
        py = ny;
        nx = x + cos(a1) * rx;
        ny = y - sin(a1) * ry;
        ::line(surface(), px, py, nx, ny, color);
    }

    return;
}

// Fl_Android_Graphics_driver::pie
void Fl_Allegro_Graphics_Driver::pie(int xi, int yi, int w, int h, double b1, double b2)
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
        b2 -= 360.0;    // FIXME: fmod(...)
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
                    if ((b1o <= 0.0 && b2 >= 90.0) || (b1o <= (0.0 - 360.0) && b2 >= (90.0 - 360.0)))
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
                    if ((b1o <= 90.0 && b2 >= 180.0) || (b1o <= (90.0 - 360.0) && b2 >= (180.0 - 360.0)))
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
                    if ((b1o <= 180.0 && b2 >= 270.0) || (b1o <= (180.0 - 360.0) && b2 >= (270.0 - 360.0)))
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
                    if ((b1o <= 270.0 && b2 >= 360.0) || (b1o <= (270.0 - 360.0) && b2 >= (360.0 - 360.0)))
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

void Fl_Allegro_Graphics_Driver::push_clip(int x, int y, int w, int h)
{
    Fl_Region r;

    r = reinterpret_cast<Fl_Region>(malloc(sizeof(*r)));

    if (w > 0 && h > 0)
    {
        int cx, cy, cw, ch;
        clip_box(x, y, w, h, cx, cy, cw, ch);
        r->x1 = cx;
        r->y1 = cy;
        r->x2 = (cx + cw - 1);
        r->y2 = (cy + ch - 1);
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
        Fl::warning("Fl_Allegro_Graphics_Driver::push_clip: clip stack overflow!\n");
        free(r);
    }

    restore_clip();

    return;
}

int Fl_Allegro_Graphics_Driver::clip_box(int x, int y, int w, int h, int &X, int &Y, int &W, int &H)
{
    X = x;
    Y = y;
    W = w;
    H = h;

    Fl_Region r = rstack[rstackptr];

    if (!r)
    {
        return 0;
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
        W = (r->x2 - r->x1);
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
        H = (r->y2 - r->y1);
    }

    return (X != x || Y != y || W != w || H != h);
}

int Fl_Allegro_Graphics_Driver::not_clipped(int x, int y, int w, int h)
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

    return ((x < r->x2) &&
            ((x + w) > r->x1) &&
            (y < r->y2) &&
            ((y + h) > r->y1));
}

void Fl_Allegro_Graphics_Driver::push_no_clip()
{

    if (rstackptr < region_stack_max)
    {
        rstack[++rstackptr] = 0;
    }
    else
    {
        Fl::warning("Fl_Xlib_Graphics_Driver::push_no_clip: clip stack overflow!\n");
    }

    restore_clip();

    return;
}

void Fl_Allegro_Graphics_Driver::pop_clip()
{

    if (rstackptr > 0)
    {
        Fl_Region oldr = rstack[rstackptr--];
        free(oldr);
    }
    else
    {
        Fl::warning("Fl_Xlib_Graphics_Driver::pop_clip: clip stack underflow!\n");
    }

    restore_clip();

    return;
}

void Fl_Allegro_Graphics_Driver::restore_clip()
{

    if (rstackptr > 0)
    {
        Fl_Region r = rstack[rstackptr];
        int x1 = (r->x1 + Fl::window_draw_offset_x);
        int x2 = (r->x2 + Fl::window_draw_offset_x);
        int y1 = (r->y1 + Fl::window_draw_offset_y);
        int y2 = (r->y2 + Fl::window_draw_offset_y);
        ::set_clip_rect(surface(), x1, y1, x2, y2);
    }
    else
    {
        ::set_clip_rect(surface(), 0, 0, (SCREEN_W - 1), (SCREEN_H - 1));
    }

    return;
}

double Fl_Allegro_Graphics_Driver::width(const char *str, int n)
{
    return (8 * n);
}

bool Fl_Allegro_Graphics_Driver::flip_to_offscreen(bool clear)
{
    bool activated = false;

    do
    {

        if (backing == active)
        {
            break;
        }

        if (0 == backing)
        {
            int depth = bitmap_color_depth(screen);
            backing = create_bitmap_ex(depth, SCREEN_W, SCREEN_H);
            if (0 == backing)
            {
                break;
            }
        }

        // TODO: _mjo if backing dimensions differ from screen
        // destroy and rebuild

        if (clear)
        {
            // TODO: get background color from somewhere
            clear_to_color(backing, 0);
        }
        else
        {
            mouse_hide();
            blit(screen, backing, 0, 0, 0, 0, backing->w, backing->h);
            mouse_show();
        }

        active = backing;
        activated = true;

    }
    while (0);

    return activated;
}

bool Fl_Allegro_Graphics_Driver::flip_to_onscreen()
{
    bool activated = false;

    do
    {

        if (screen == active)
        {
            break;
        }

        mouse_hide();
        blit(backing, screen, 0, 0, 0, 0, backing->w, backing->h);
        active = screen;
        activated = true;
        mouse_show();

    }
    while (0);

    return activated;
}

void Fl_Allegro_Graphics_Driver::draw_image(const uchar *buf, int X, int Y, int W, int H, int D, int L)
{
    BITMAP *bmp = rgb_data_to_bitmap(
                      static_cast<unsigned int>(W),
                      static_cast<unsigned int>(H),
                      static_cast<unsigned int>(D),
                      static_cast<unsigned int>(L),
                      buf);

    if (bmp)
    {
        X += Fl::window_draw_offset_x;
        Y += Fl::window_draw_offset_y;
        masked_blit(bmp, surface(), 0, 0, X, Y, bmp->w, bmp->h);
        destroy_bitmap(bmp);
    }

    return;
}

void Fl_Allegro_Graphics_Driver::draw_image(Fl_Draw_Image_Cb cb, void *data, int X, int Y, int W, int H, int D)
{
    BITMAP *bmp = rgb_staged_to_image(
                      cb,
                      data,
                      static_cast<unsigned int>(W),
                      static_cast<unsigned int>(H),
                      static_cast<unsigned int>(D));

    if (bmp)
    {
        X += Fl::window_draw_offset_x;
        Y += Fl::window_draw_offset_y;
        masked_blit(bmp, surface(), 0, 0, X, Y, bmp->w, bmp->h);
        destroy_bitmap(bmp);
    }

    return;
}

void Fl_Allegro_Graphics_Driver::draw_rgb(Fl_RGB_Image *rgb, int XP, int YP, int WP, int HP, int cx, int cy)
{
    BITMAP *bmp = rgb_image_to_bitmap((*rgb));

    if (bmp)
    {
        int X = XP + Fl::window_draw_offset_x;
        int Y = YP + Fl::window_draw_offset_y;
        masked_blit(bmp, surface(), cx, cy, X, Y, bmp->w, bmp->h);
        destroy_bitmap(bmp);
    }

    return;
}

void Fl_Allegro_Graphics_Driver::draw_pixmap(Fl_Pixmap *pxm, int XP, int YP, int /*WP*/, int /*HP*/, int cx, int cy)
{
    BITMAP *bmp = pxm_to_bitmap((*pxm));

    if (bmp)
    {
        int X = XP + Fl::window_draw_offset_x;
        int Y = YP + Fl::window_draw_offset_y;
        masked_blit(bmp, surface(), cx, cy, X, Y, bmp->w, bmp->h);
        destroy_bitmap(bmp);
    }

    return;
}

void Fl_Allegro_Graphics_Driver::draw_bitmap(Fl_Bitmap *bm, int XP, int YP, int WP, int HP, int cx, int cy)
{
    BITMAP *bmp = bitmap_to_bitmap((*bm));

    if (bmp)
    {
        int X = XP + Fl::window_draw_offset_x;
        int Y = YP + Fl::window_draw_offset_y;
        masked_blit(bmp, surface(), cx, cy, X, Y, bmp->w, bmp->h);
        destroy_bitmap(bmp);
    }

    return;
}

void Fl_Allegro_Graphics_Driver::nca_draw_frame(
    int const nca_x,
    int const nca_y,
    unsigned int const nca_w,
    unsigned int const nca_h,
    unsigned int const title_bar_height,
    char const *title)
{
    int white = makecol(255, 255, 255);
    int black = makecol(45, 45, 45);

    ::rectfill(surface(), nca_x, nca_y, nca_x + nca_w, nca_y + title_bar_height - 1, black);
    ::rect(surface(), nca_x, nca_y, nca_x + nca_w, nca_y + nca_h - 1, black);
    ::line(surface(), nca_x, nca_y + title_bar_height - 2, nca_x + nca_w - 1, nca_y + title_bar_height - 2, black);
    if (title)
    {
        ::textout_centre_ex(surface(), ::font, title, nca_x + (nca_w / 2), nca_y + 8, white, -1);
    }

    return;
}
