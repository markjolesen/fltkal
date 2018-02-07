// aldrvgr.h
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
#if !defined(FL_ALLEGRO_GRAPHICS_DRIVER_H)

#include <fl/drvgr.h>
#include <allegro.h>

class FL_EXPORT Fl_Allegro_Graphics_Driver : public Fl_Graphics_Driver
{

private:

    unsigned int hidden_count;
    BITMAP *active;
    BITMAP *backing;

public:

    Fl_Allegro_Graphics_Driver();

    virtual ~Fl_Allegro_Graphics_Driver();

    BITMAP *surface()
    {
        return ((active) ? active : (active = screen));
    };

    virtual void draw(const char *str, int n, int x, int y);

    virtual void point(int x, int y);

    virtual void rect(int x, int y, int w, int h);

    virtual void rectf(int x, int y, int w, int h);

    virtual void line(int x, int y, int x1, int y1);

    virtual void line(int x, int y, int x1, int y1, int x2, int y2);

    virtual void xyline(int x, int y, int x1);

    virtual void xyline(int x, int y, int x1, int y2);

    virtual void xyline(int x, int y, int x1, int y2, int x3);

    virtual void yxline(int x, int y, int y1);

    virtual void yxline(int x, int y, int y1, int x2);

    virtual void yxline(int x, int y, int y1, int x2, int y3);

    virtual void loop(int x0, int y0, int x1, int y1, int x2, int y2);

    virtual void loop(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);

    virtual void polygon(int x0, int y0, int x1, int y1, int x2, int y2);

    virtual void polygon(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);

    virtual void circle(double x, double y, double r);

    virtual void arc(int x, int y, int w, int h, double a1, double a2);

    virtual void pie(int x, int y, int w, int h, double a1, double a2);

    virtual void push_clip(int x, int y, int w, int h);

    virtual int clip_box(int x, int y, int w, int h, int &X, int &Y, int &W, int &H);

    virtual int not_clipped(int x, int y, int w, int h);

    virtual void push_no_clip();

    virtual void pop_clip();

    virtual void restore_clip();

    virtual double width(const char *str, int n);

    virtual bool flip_to_offscreen(bool clear);

    virtual bool flip_to_onscreen();

    virtual void mouse_hide();

    virtual void mouse_show();

    void nca_draw_frame(
        int const nca_x,
        int const nca_y,
        unsigned int const nca_w,
        unsigned int const nca_h,
        unsigned int const title_bar_height,
        char const *title);

protected:

    virtual void draw_image(const uchar *buf, int X, int Y, int W, int H, int D = 3, int L = 0);

    virtual void draw_image(Fl_Draw_Image_Cb cb, void *data, int X, int Y, int W, int H, int D = 3);

    virtual void draw(Fl_RGB_Image *rgb, int XP, int YP, int WP, int HP, int cx, int cy);

    virtual void draw(Fl_Pixmap *pxm, int XP, int YP, int WP, int HP, int cx, int cy);

    virtual void draw(Fl_Bitmap *bm, int XP, int YP, int WP, int HP, int cx, int cy);
};

inline void Fl_Allegro_Graphics_Driver::mouse_hide()
{
    scare_mouse();
    hidden_count++;
}

inline void Fl_Allegro_Graphics_Driver::mouse_show()
{
    if (hidden_count)
    {
        unscare_mouse();
        hidden_count--;
    }
}

#define FL_ALLEGRO_GRAPHICS_DRIVER_H
#endif
