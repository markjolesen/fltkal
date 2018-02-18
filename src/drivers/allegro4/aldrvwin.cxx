// aldrvwin.cxx
//
// Allegro4 Window handling code for the Fast Light Tool Kit (FLTK).
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
#include "aldrvwin.h"
#include "aldrvgr.h"
#include <fl/fl.h>
#include <fl/platform.h>
#include <fl/win.h>

Window fl_window = 0;

extern void cursor_set(Fl_Cursor const c);

Fl_Window_Driver *
Fl_Window_Driver::newWindowDriver(Fl_Window *w)
{
    return new Fl_Allegro_Window_Driver(w);
}

void Fl_Window_Driver::default_icons(const Fl_RGB_Image *icons[], int count)
{

}

Fl_Allegro_Window_Driver::Fl_Allegro_Window_Driver(Fl_Window *w) :
    Fl_Window_Driver(w),
    cursor_(FL_CURSOR_DEFAULT),
    bmp_store(0)
{

}

Fl_Allegro_Window_Driver::~Fl_Allegro_Window_Driver()
{

    if (bmp_store)
    {
        destroy_bitmap(bmp_store);
    }

    return;
}

int Fl_Allegro_Window_Driver::decorated_w()
{
}

void Fl_Allegro_Window_Driver::draw_begin()
{
    Fl_Allegro_Graphics_Driver *gr = reinterpret_cast<Fl_Allegro_Graphics_Driver *>(fl_graphics_driver);
    // Fl_Window_Driver::draw_begin(); - does nothing
    gr->mouse_hide();
    Fl::window_draw_offset_x = pWindow->x();
    Fl::window_draw_offset_y = pWindow->y();

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

void Fl_Allegro_Window_Driver::draw_end()
{
    // Fl_Window_Driver::draw_end(); - does nothing
    fl_graphics_driver->mouse_show();
}

int Fl_Allegro_Window_Driver::decorated_h()
{
}

Fl_X *Fl_Allegro_Window_Driver::makeWindow()
{
    Fl_Group::current(0);
    Fl_X *x = new Fl_X;
    i(x);
    other_xid = 0;
    x->w = pWindow;
    x->region = 0;
    x->next = Fl_X::first;
    Fl_X::first = x;

    if (title_bar_height > pWindow->y())
    {
        pWindow->position(pWindow->x(), title_bar_height);
    }

    pWindow->set_visible();
    pWindow->redraw();
    int old_event = Fl::e_number;
    pWindow->handle(Fl::e_number = FL_SHOW);
    Fl::e_number = old_event;
    pWindow->take_focus();
    return x;
}

void Fl_Allegro_Window_Driver::show()
{
    if (!shown())
    {
        fl_open_display();
        makeWindow();
    }
}

void Fl_Allegro_Window_Driver::hide()
{
    hide_common();
    if (0 == bmp_store)
    {
        Fl::redraw();
        Fl_Allegro_Graphics_Driver *gr =
            reinterpret_cast<Fl_Allegro_Graphics_Driver *>(fl_graphics_driver);
        bool buffered = gr->flip_to_offscreen(true);
        Fl::flush();
        if (buffered)
        {
            gr->flip_to_onscreen();
        }
    }
}

void Fl_Allegro_Window_Driver::erase_menu()
{

    if (bmp_store)
    {
        int bmp_x = pWindow->x();
        int bmp_y = pWindow->y();
        fl_graphics_driver->mouse_hide();
        blit(bmp_store, screen, 0, 0, bmp_x, bmp_y, bmp_store->w, bmp_store->h);
        fl_graphics_driver->mouse_show();
    }

    return;
}

void Fl_Allegro_Window_Driver::show_menu()
{

    Fl_Window_Driver::show_menu();

    int bmp_x = pWindow->x();
    int bmp_y = pWindow->y();
    int bmp_w = pWindow->w();
    int bmp_h = pWindow->h();

    bmp_store = create_bitmap(bmp_w, bmp_h);

    if (bmp_store)
    {
        fl_graphics_driver->mouse_hide();
        set_clip_state(bmp_store, 1);
        blit(screen, bmp_store, bmp_x, bmp_y, 0, 0, bmp_store->w, bmp_store->h);
        fl_graphics_driver->mouse_show();
    }

    return;
}

void Fl_Allegro_Window_Driver::resize(int X, int Y, int W, int H)
{
    bool has_store = bmp_store ? true : false;

    if (shown() && has_store)
    {
        erase_menu();
    }

    pWindow->Fl_Group::resize(X, Y, W, H);

    if (shown())
    {
        if (has_store)
        {
            // BUG: _mjo
            // if backing stores are layered, this will copy the layer below it
            show_menu();
        }
        pWindow->redraw();
    }

    return;
}

int Fl_Allegro_Window_Driver::scroll(int src_x, int src_y, int src_w, int src_h, int dest_x, int dest_y, void (*draw_area)(void *, int, int, int, int), void *data)
{
    int rc = 1;

    do
    {

        BITMAP *bmp = create_bitmap(src_w, src_h);

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
            Fl_Allegro_Graphics_Driver *gr =
                reinterpret_cast<Fl_Allegro_Graphics_Driver *>(fl_graphics_driver);
            blit(gr->surface(), bmp, sx, sy, 0, 0, src_w, src_h);
            blit(bmp, gr->surface(), 0, 0, dx, dy, src_w, src_h);
            destroy_bitmap(bmp);
        }

#if 0
        int x, w, y, h;

        if (src_x <= dest_x)
        {
            x = (src_x + src_w);
            w = (dest_x - src_x);
        }
        else
        {
            x = dest_x;
            w = (src_x - dest_x);
        }

        if (w)
        {
            (*draw_area)(data, x, src_y, w, src_h);
        }

        if (src_y <= dest_y)
        {
            y = src_y;
            h = (dest_y - src_y);
        }
        else
        {
            y = (src_y + src_h);
            h = (src_y - dest_y);
        }

        if (h)
        {
            (*draw_area)(data, src_x, y, src_w, h);
        }
#endif
        rc = 0;

    }
    while (0);

    return rc;
}

Fl_Cursor Fl_Allegro_Window_Driver::get_cursor() const
{
    return cursor_;
}

int Fl_Allegro_Window_Driver::set_cursor(Fl_Cursor c)
{
    if (cursor_ != c)
    {
        cursor_set(c);
        cursor_ = c;
    }
    return 1;
}

int Fl_Allegro_Window_Driver::set_cursor(const Fl_RGB_Image *img, int hot_x, int hot_y)
{
    return 0;
}

