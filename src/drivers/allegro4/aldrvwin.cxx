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
#include "imgconv.h"
#include <fl/drvwin.h>
#include <fl/fl.h>
#include <fl/fl_enums.h>
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
    cursor_(),
    bmp_store_(0)
{
    cursor_.pointer_ = FL_CURSOR_DEFAULT;
    cursor_.custom_.bmp_ = 0;
    return;
}

Fl_Allegro_Window_Driver::~Fl_Allegro_Window_Driver()
{

    if (cursor_.custom_.bmp_)
    {
        fl_graphics_driver->mouse_hide();
        set_cursor(FL_CURSOR_DEFAULT);
        destroy_bitmap(cursor_.custom_.bmp_);
        fl_graphics_driver->mouse_show();
    }

    if (bmp_store_)
    {
        destroy_bitmap(bmp_store_);
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

    if (FL_CHILD_WINDOW == pWindow->type())
    {
        Fl_Group *p = pWindow->parent();
        Fl_Window *w = p->as_window();
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
    bool takefocus = true;
    Fl_Group::current(0);
    Fl_X *x = new Fl_X;
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

void Fl_Allegro_Window_Driver::take_focus()
{
    if (!shown())
    {
        pWindow->show();
    }
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
    if (0 == bmp_store_)
    {
        Fl::redraw();
        Fl_Allegro_Graphics_Driver *gr = reinterpret_cast<Fl_Allegro_Graphics_Driver *>(fl_graphics_driver);
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

    if (bmp_store_)
    {
        int bmp_x = pWindow->x();
        int bmp_y = pWindow->y();
        fl_graphics_driver->mouse_hide();
        blit(bmp_store_, screen, 0, 0, bmp_x, bmp_y, bmp_store_->w, bmp_store_->h);
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

    bmp_store_ = create_bitmap(bmp_w, bmp_h);

    if (bmp_store_)
    {
        fl_graphics_driver->mouse_hide();
        set_clip_state(bmp_store_, 1);
        blit(screen, bmp_store_, bmp_x, bmp_y, 0, 0, bmp_store_->w, bmp_store_->h);
        fl_graphics_driver->mouse_show();
    }

    return;
}

void Fl_Allegro_Window_Driver::resize(int X, int Y, int W, int H)
{
    bool has_store = bmp_store_ ? true : false;

    if (shown() && has_store)
    {
        erase_menu();
    }

    int x1 = pWindow->x();
    int y1 = pWindow->y();
    int w1 = pWindow->w();
    int h1 = pWindow->h();

    pWindow->Fl_Group::resize(X, Y, W, H);

    if (shown())
    {
        if (has_store)
        {
            // BUG: _mjo
            // if backing stores are layered, this will copy the layer below it
            show_menu();
        }

        int x2 = pWindow->x();
        int y2 = pWindow->y();
        int w2 = pWindow->w();
        int h2 = pWindow->h();

        if (x1 != x2 || y1 != y2 || w1 != w2 || h1 != h2)
        {
            if (false == has_store && (x1 != x2 || y1 != y2))
            {
                Fl_Allegro_Graphics_Driver *gr = reinterpret_cast<Fl_Allegro_Graphics_Driver *>(fl_graphics_driver);
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
            Fl_Allegro_Graphics_Driver *gr = reinterpret_cast<Fl_Allegro_Graphics_Driver *>(fl_graphics_driver);
            blit(gr->surface(), bmp, sx, sy, 0, 0, src_w, src_h);
            blit(bmp, gr->surface(), 0, 0, dx, dy, src_w, src_h);
            destroy_bitmap(bmp);
        }

        rc = 0;

    }
    while (0);

    return rc;
}

void Fl_Allegro_Window_Driver::redisplay_cursor() const
{

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

    return;
}

Fl_Cursor Fl_Allegro_Window_Driver::get_cursor() const
{
    return cursor_.pointer_;
}

int Fl_Allegro_Window_Driver::set_cursor(Fl_Cursor c)
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

int Fl_Allegro_Window_Driver::set_cursor(const Fl_RGB_Image *img, int hot_x, int hot_y)
{
    BITMAP *bmp = rgb_image_to_bitmap((*img));

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
