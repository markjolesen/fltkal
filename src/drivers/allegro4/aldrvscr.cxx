// aldrvscr.cxx
//
// Allegro4 Screen Driver for the Fast Light Tool Kit (FLTK)
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
#include "aldrvscr.h"
#include "aldrvwin.h"
#include <allegro.h>
#include <fl/fl.h>
#include <fl/x.h>

extern void cursor_create();

extern void cursor_destroy();

extern void cursor_set(Fl_Cursor const);

extern void fl_fix_focus(); // in Fl.cxx

Fl_Screen_Driver *
Fl_Screen_Driver::newScreenDriver()
{
    return new Fl_Allegro_Screen_Driver();
}

Fl_Allegro_Screen_Driver::Fl_Allegro_Screen_Driver() :
    Fl_Screen_Driver(),
    wm_(),
    timer_(),
    dclick_(),
    clock_(),
    grab_bounce_(false),
    btn_state_(0),
    cursor_(FL_CURSOR_DEFAULT)
{
    ticks_set(clock_);
    dclick_.set(0.25);
    return;
}

Fl_Allegro_Screen_Driver::~Fl_Allegro_Screen_Driver()
{
    cursor_destroy();
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    return;
}

void Fl_Allegro_Screen_Driver::init()
{

    allegro_init();

    if (install_keyboard())
    {
        allegro_message("Install keyboard error: %s", allegro_error);
        exit(-1);
    }

    if (-1 == install_mouse())
    {
        allegro_message("Install mouse error: %s", allegro_error);
        exit(-1);
    }

    if (screen_init())
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Unable to initialize graphics");
        exit(-1);
    }

    num_screens= 1;
    cursor_create();
    show_mouse(screen);

    return;
}

int Fl_Allegro_Screen_Driver::screen_init()
{
    static struct
    {
        int depth;
        int width;
        int height;
    } gfx_modes[] =
    {
        {32, 1024, 768},
        {32, 640, 480}
    };
    int rc;

    for (int mode = 0; mode < sizeof(gfx_modes) / sizeof(gfx_modes[0]); mode++)
    {
        int depth = gfx_modes[mode].depth;
        int width = gfx_modes[mode].width;
        int height = gfx_modes[mode].height;

        set_color_depth(depth);

#if defined(__DJGPP__)
        rc = set_gfx_mode(GFX_AUTODETECT, width, height, 0, 0);
#else
        rc = set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
#endif

        if (0 == rc)
        {
            return 0;
        }
    }

    return -1;
}

int Fl_Allegro_Screen_Driver::x()
{
    return 0;
}

int Fl_Allegro_Screen_Driver::y()
{
    return 0;
}

int Fl_Allegro_Screen_Driver::w()
{
    return SCREEN_W;
}

int Fl_Allegro_Screen_Driver::h()
{
    return SCREEN_H;
}

void Fl_Allegro_Screen_Driver::screen_xywh(int &X, int &Y, int &W, int &H, int /*n*/)
{
    X = 0;
    Y = 0;
    W = SCREEN_W;
    H = SCREEN_H;
    return;
}

void Fl_Allegro_Screen_Driver::screen_work_area(int &X, int &Y, int &W, int &H, int /*n*/)
{
    X = 0;
    Y = 0;
    W = SCREEN_W;
    H = SCREEN_H;
    return;
}

void Fl_Allegro_Screen_Driver::screen_dpi(float &h, float &v, int/*n*/)
{
    h = 72.0;
    v = 72.0;
}

void Fl_Allegro_Screen_Driver::beep(int type)
{
}

void Fl_Allegro_Screen_Driver::flush()
{
}

static inline int keyboard_get_press_state()
{
    int sym = 0;

    do
    {
        if (key[KEY_BACKSPACE])
        {
            key[KEY_BACKSPACE] = 0;
            sym = FL_BackSpace;
            break;
        }
        if (key[KEY_TAB])
        {
            key[KEY_TAB] = 0;
            sym = FL_Tab;
            break;
        }
        // FL_Iso_Key
        if (key[KEY_ENTER])
        {
            key[KEY_ENTER] = 0;
            sym = FL_Enter;
            break;
        }
        if (key[KEY_PAUSE])
        {
            key[KEY_PAUSE] = 0;
            sym = FL_Pause;
            break;
        }
        // if (key[KEY_SCRLOCK]) {sym= FL_Scroll_Lock; break;}
        if (key[KEY_ESC])
        {
            key[KEY_ESC] = 0;
            sym = FL_Escape;
            break;
        }
        if (key[KEY_KANA])
        {
            key[KEY_KANA] = 0;
            sym = FL_Kana;
            break;
        }
        // FL_Eisu
        if (key[KEY_YEN])
        {
            key[KEY_YEN] = 0;
            sym = FL_Yen;
            break;
        }
        // FL_JIS_Underscore
        if (key[KEY_HOME])
        {
            key[KEY_HOME] = 0;
            sym = FL_Home;
            break;
        }
        // FL_Eisu
        if (key[KEY_YEN])
        {
            key[KEY_YEN] = 0;
            sym = FL_Yen;
            break;
        }
        // FL_JIS_Underscore
        if (key[KEY_HOME])
        {
            key[KEY_HOME] = 0;
            sym = FL_Home;
            break;
        }
        if (key[KEY_LEFT])
        {
            key[KEY_LEFT] = 0;
            sym = FL_Left;
            break;
        }
        if (key[KEY_UP])
        {
            key[KEY_UP] = 0;
            sym = FL_Up;
            break;
        }
        if (key[KEY_RIGHT])
        {
            key[KEY_RIGHT] = 0;
            sym = FL_Right;
            break;
        }
        if (key[KEY_DOWN])
        {
            key[KEY_DOWN] = 0;
            sym = FL_Down;
            break;
        }
        if (key[KEY_PGUP])
        {
            key[KEY_PGUP] = 0;
            sym = FL_Page_Up;
            break;
        }
        if (key[KEY_PGDN])
        {
            key[KEY_PGDN] = 0;
            sym = FL_Page_Down;
            break;
        }
        if (key[KEY_END])
        {
            key[KEY_END] = 0;
            sym = FL_End;
            break;
        }
        // FL_Print
        if (key[KEY_INSERT])
        {
            key[KEY_INSERT] = 0;
            sym = FL_Insert;
            break;
        }
        if (key[KEY_MENU])
        {
            key[KEY_MENU] = 0;
            sym = FL_Menu;
            break;
        }
        // FL_Help
        // if (key[KEY_NUMLOCK]) {sym= FL_Num_Lock; break;}
        // FL_KP
        if (key[KEY_ENTER_PAD])
        {
            key[KEY_ENTER_PAD] = 0;
            sym = FL_KP_Enter;
            break;
        }
        // FL_F
        // if (key[KEY_LSHIFT]) {sym= FL_Shift_L; break;}
        // if (key[KEY_RSHIFT]) {sym= FL_Shift_R; break;}
        // if (key[KEY_LCONTROL]) {sym= FL_Control_L; break;}
        // if (key[KEY_RCONTROL]) {sym= FL_Control_R; break;}
        // if (key[KEY_CAPSLOCK]) {sym= FL_Caps_Lock; break;}
        // FL_Meta_L
        // FL_Meta_R
        // FL_Alt_L
        // FL_Alt_R
        if (key[KEY_DEL])
        {
            key[KEY_DEL] = 0;
            sym = FL_Delete;
            break;
        }
    }
    while (0);

    return sym;
}

static inline int keyboard_get_altcode(int const scancode)
{
    int sym = 0;

    switch (scancode)
    {
    case (KEY_0 << 8):
    {
        sym = '0';
        break;
    }
    case (KEY_1 << 8):
    {
        sym = '1';
        break;
    }
    case (KEY_2 << 8):
    {
        sym = '2';
        break;
    }
    case (KEY_3 << 8):
    {
        sym = '3';
        break;
    }
    case (KEY_4 << 8):
    {
        sym = '4';
        break;
    }
    case (KEY_5 << 8):
    {
        sym = '5';
        break;
    }
    case (KEY_6 << 8):
    {
        sym = '6';
        break;
    }
    case (KEY_7 << 8):
    {
        sym = '7';
        break;
    }
    case (KEY_8 << 8):
    {
        sym = '8';
        break;
    }
    case (KEY_9 << 8):
    {
        sym = '9';
        break;
    }
    case (KEY_A << 8):
    {
        sym = 'A';
        break;
    }
    case (KEY_B << 8):
    {
        sym = 'B';
        break;
    }
    case (KEY_C << 8):
    {
        sym = 'C';
        break;
    }
    case (KEY_D << 8):
    {
        sym = 'D';
        break;
    }
    case (KEY_E << 8):
    {
        sym = 'E';
        break;
    }
    case (KEY_F << 8):
    {
        sym = 'F';
        break;
    }
    case (KEY_G << 8):
    {
        sym = 'G';
        break;
    }
    case (KEY_H << 8):
    {
        sym = 'H';
        break;
    }
    case (KEY_I << 8):
    {
        sym = 'I';
        break;
    }
    case (KEY_J << 8):
    {
        sym = 'J';
        break;
    }
    case (KEY_K << 8):
    {
        sym = 'K';
        break;
    }
    case (KEY_L << 8):
    {
        sym = 'L';
        break;
    }
    case (KEY_M << 8):
    {
        sym = 'M';
        break;
    }
    case (KEY_N << 8):
    {
        sym = 'N';
        break;
    }
    case (KEY_O << 8):
    {
        sym = 'O';
        break;
    }
    case (KEY_P << 8):
    {
        sym = 'P';
        break;
    }
    case (KEY_Q << 8):
    {
        sym = 'Q';
        break;
    }
    case (KEY_R << 8):
    {
        sym = 'R';
        break;
    }
    case (KEY_S << 8):
    {
        sym = 'S';
        break;
    }
    case (KEY_T << 8):
    {
        sym = 'T';
        break;
    }
    case (KEY_U << 8):
    {
        sym = 'U';
        break;
    }
    case (KEY_V << 8):
    {
        sym = 'V';
        break;
    }
    case (KEY_W << 8):
    {
        sym = 'W';
        break;
    }
    case (KEY_X << 8):
    {
        sym = 'X';
        break;
    }
    case (KEY_Y << 8):
    {
        sym = 'Y';
        break;
    }
    case (KEY_Z << 8):
    {
        sym = 'Z';
        break;
    }
    default:
        break;
    }

    return sym;
}

bool Fl_Allegro_Screen_Driver::wait_keyboard(Fl_Window *window)
{
    int triggered = false;
    char buf[2];
    int sym = 0;

    do
    {

        buf[0] = 0;
        Fl::e_text = buf;
        Fl::e_length = 0;

        if (keyboard_needs_poll())
        {
            poll_keyboard();
        }

        if (key[KEY_LSHIFT])
        {
            Fl::e_state |= FL_SHIFT;
        }
        if (key[KEY_RSHIFT])
        {
            Fl::e_state |= FL_SHIFT;
        }
        if (key[KEY_LCONTROL])
        {
            Fl::e_state |= FL_CTRL;
        }
        if (key[KEY_RCONTROL])
        {
            Fl::e_state |= FL_CTRL;
        }
        if (key[KEY_CAPSLOCK])
        {
            Fl::e_state |= FL_CAPS_LOCK;
        }
        if (key[KEY_SCRLOCK])
        {
            Fl::e_state |= FL_SCROLL_LOCK;
        }
        if (key[KEY_NUMLOCK])
        {
            Fl::e_state |= FL_NUM_LOCK;
        }

        sym = keyboard_get_press_state();

        if (sym)
        {
            Fl::e_keysym = sym;
            Fl::e_number = FL_KEYBOARD;
            Fl::handle(FL_KEYBOARD, window);
            triggered = true;
            break;
        }

        if (keypressed())
        {
            int scan = readkey();
            sym = (0xff & scan);
            if (0 == sym)
            {
                sym = keyboard_get_altcode(scan);
                if (0 == sym)
                {
                    break;
                }
                Fl::e_state |= FL_ALT;
            }
            else if (27 >= sym)
            {
                sym += ('A' - 1);
                Fl::e_state |= FL_CTRL;
            }
            Fl::e_keysym = sym;
            buf[0] = sym;
            buf[1] = 0;
            Fl::e_text = buf;
            Fl::e_length = 1;
            Fl::e_number = FL_KEYBOARD;
            Fl::handle(FL_KEYBOARD, window);
            triggered = true;
            break;
        }

    }
    while (0);

    return triggered;
}

wm::hit_type Fl_Allegro_Screen_Driver::hit(Fl_Window* window, int const x, int const y)
{
        Fl_Cursor cursor = static_cast<Fl_Cursor>(window->driver()->current_cursor());
        wm::hit_type hit = wm_.hit((*window), x, y);

        switch (hit)
        {
        case wm::HIT_MOVE:
            cursor = FL_CURSOR_MOVE;
            break;
        case wm::HIT_EAST:
            cursor = FL_CURSOR_E;
            break;
        case wm::HIT_WEST:
            cursor = FL_CURSOR_W;
            break;
        case wm::HIT_NORTH:
            cursor = FL_CURSOR_N;
            break;
        case wm::HIT_NORTH_EAST:
            cursor = FL_CURSOR_NE;
            break;
        case wm::HIT_NORTH_WEST:
            cursor = FL_CURSOR_NW;
            break;
        case wm::HIT_SOUTH:
            cursor = FL_CURSOR_S;
            break;
        case wm::HIT_SOUTH_EAST:
            cursor = FL_CURSOR_SE;
            break;
        case wm::HIT_SOUTH_WEST:
            cursor = FL_CURSOR_SW;
            break;
        default:
            break;
        }

        if (cursor_ != cursor)
        {
            cursor_set(cursor);
            cursor_= cursor;
        }

        return hit;
}

bool Fl_Allegro_Screen_Driver::wait_mouse(Fl_Window *window)
{
    int triggered = false;

    do
    {

        if (mouse_needs_poll())
        {
            poll_mouse();
        }

        int pos, x, y;

        pos = mouse_pos;
        x = (pos >> 16);
        y = (0xffff & pos);

        int movement = (abs(Fl::e_x_root - x) + abs(Fl::e_y_root - y));

        if (Fl::e_is_click)
        {
#if defined (__DJGPP)
            bool wiggle = (movement > 1);
#else
            bool wiggle = (movement >= 3);
#endif
            if (wiggle)
            {
                Fl::e_is_click = 0;
            }

        }

        Fl::e_x_root = x;
        Fl::e_y_root = y;
        x -= window->x();
        y -= window->y();
        Fl::e_x = x;
        Fl::e_y = y;

        wm::hit_type what= wm::HIT_NONE;

        if ((FL_WINDOW == window->type() || FL_DOUBLE_WINDOW == window->type()))
        {
            what= hit(window, Fl::e_x_root, Fl::e_y_root);
        }

        int btn = mouse_b;

        if (1 & btn)
        {
            Fl::e_state |= FL_BUTTON1;
            Fl::e_keysym = (FL_Button | FL_LEFT_MOUSE);
        }

        if (2 & btn)
        {
            Fl::e_state |= FL_BUTTON2;
            Fl::e_keysym = (FL_Button | FL_RIGHT_MOUSE);
        }

        if (btn)
        {
            if (false == grab_bounce_)
            {
                if (btn_state_)
                {
                    if (movement)
                    {
                        btn_state_ = btn;
                        Fl::handle(FL_DRAG, window);
                        triggered = true;
                    }
                }
                else
                {
                    bool handled = wm_.handle_push((*window), what, Fl::e_x_root, Fl::e_y_root);
                    if (handled)
                    {
                        break;
                    }

                    if (Fl::e_is_click == Fl::e_keysym)
                    {
                        Fl::e_clicks++;
                    }
                    else
                    {
                        Fl::e_clicks = 0;
                        Fl::e_is_click = Fl::e_keysym;
                    }
                    btn_state_ = btn;
                    Fl::handle(FL_PUSH, window);
                    triggered = true;
                }
            }
            break;
        }
        else
        {
            if (btn_state_)
            {
                if (false == grab_bounce_)
                {
                    if (1 & btn_state_)
                    {
                        Fl::e_state |= FL_BUTTON1;
                        Fl::e_keysym = (FL_Button | FL_LEFT_MOUSE);
                    }

                    if (2 & btn_state_)
                    {
                        Fl::e_state |= FL_BUTTON2;
                        Fl::e_keysym = (FL_Button | FL_RIGHT_MOUSE);
                    }
                    btn_state_ = 0;
                    Fl::handle(FL_RELEASE, window);
                    triggered = true;
                }
                else
                {
                    btn_state_ = 0;
                    grab_bounce_ = false;
                }
                break;
            }
            else if (movement)
            {
                Fl::handle(FL_MOVE, window);
                triggered = true;
                break;
            }
        }

    }
    while (0);

    return triggered;
}

double Fl_Allegro_Screen_Driver::wait(double time_to_wait)
{
    bool triggered = false;
    ticker ticker_loop;

    ticker_loop.set(time_to_wait);

    do
    {

        Fl::run_checks();

        // idle processing
        static int in_idle= 0;
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

        if (0 == Fl::grab_)
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
        else
        {
            window = Fl::grab_;
        }

        if (0 == window)
        {
            break;
        }

        if (0 == Fl::focus_)
        {
            window->take_focus();
        }

        triggered = wait_keyboard(window);

        if (triggered)
        {
            break;
        }

        triggered = wait_mouse(window);

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

int Fl_Allegro_Screen_Driver::ready()
{
    return 1;
}

void Fl_Allegro_Screen_Driver::grab(Fl_Window *win)
{

    if (win)
    {
        Fl::grab_ = win;
        grab_bounce_ = true; // debounce the mouse - wait for release
    }
    else if (Fl::grab_)
    {
        grab_bounce_ = false;
        Fl::grab_ = 0;
        fl_fix_focus();
    }

    return;
}

void Fl_Allegro_Screen_Driver::get_system_colors()
{
}

const char *Fl_Allegro_Screen_Driver::get_system_scheme()
{
    return fl_getenv("FLTK_SCHEME");
}

void Fl_Allegro_Screen_Driver::add_timeout(double time, Fl_Timeout_Handler cb, void *argp)
{
    timer_.add(time, cb, argp);
}

void Fl_Allegro_Screen_Driver::repeat_timeout(double time, Fl_Timeout_Handler cb, void *argp)
{
    timer_.repeat(time, cb, argp);
}

int Fl_Allegro_Screen_Driver::has_timeout(Fl_Timeout_Handler cb, void *argp)
{
    return timer_.contains(cb, argp);
}

void Fl_Allegro_Screen_Driver::remove_timeout(Fl_Timeout_Handler cb, void *argp)
{
    timer_.remove(cb, argp);
}

int Fl_Allegro_Screen_Driver::get_mouse(int &x, int &y)
{
    int pos = mouse_pos;
    x = (pos >> 16);
    y = (0xffff & pos);
    return 1;
}

void Fl_Allegro_Screen_Driver::open_display_platform()
{
}

void Fl_Allegro_Screen_Driver::close_display()
{
}

int Fl_Allegro_Screen_Driver::compose(int &del)
{
    int condition;
    unsigned char ascii = (unsigned char)Fl::e_text[0];
    condition = (Fl::e_state & (FL_ALT | FL_META | FL_CTRL)) && !(ascii & 128) ;
    if (condition)
    {
        del = 0;    // this stuff is to be treated as a function key
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

