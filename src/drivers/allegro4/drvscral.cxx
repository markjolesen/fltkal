// drvscral.cxx
//
// Allegro4 Screen Driver for the Fast Light Tool Kit (FLTK)
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
#include "aldrvscr.h"
#include "aldrvwin.h"
#include "utf8proc.h"

#include <allegro.h>

extern void cursor_create();

extern void cursor_destroy();

// extern void cursor_set(Fl_Cursor const);

#define __halt()

Fl_Allegro_Screen_Driver::~Fl_Allegro_Screen_Driver()
{
  cursor_destroy();
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  allegro_exit();
  return;
}

void
Fl_Allegro_Screen_Driver::init()
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

  num_screens = 1;
  cursor_create();
  show_mouse(screen);

  return;
}

int
Fl_Allegro_Screen_Driver::screen_init()
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

static inline int
keyboard_get_press_state()
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

static inline int
keyboard_get_altcode(int const scancode)
{
  int sym = 0;

  switch (scancode)
  {
    case (KEY_0):
    {
      sym = '0';
      break;
    }

    case (KEY_1):
    {
      sym = '1';
      break;
    }

    case (KEY_2):
    {
      sym = '2';
      break;
    }

    case (KEY_3):
    {
      sym = '3';
      break;
    }

    case (KEY_4):
    {
      sym = '4';
      break;
    }

    case (KEY_5):
    {
      sym = '5';
      break;
    }

    case (KEY_6):
    {
      sym = '6';
      break;
    }

    case (KEY_7):
    {
      sym = '7';
      break;
    }

    case (KEY_8):
    {
      sym = '8';
      break;
    }

    case (KEY_9):
    {
      sym = '9';
      break;
    }

    case (KEY_A):
    {
      sym = 'A';
      break;
    }

    case (KEY_B):
    {
      sym = 'B';
      break;
    }

    case (KEY_C):
    {
      sym = 'C';
      break;
    }

    case (KEY_D):
    {
      sym = 'D';
      break;
    }

    case (KEY_E):
    {
      sym = 'E';
      break;
    }

    case (KEY_F):
    {
      sym = 'F';
      break;
    }

    case (KEY_G):
    {
      sym = 'G';
      break;
    }

    case (KEY_H):
    {
      sym = 'H';
      break;
    }

    case (KEY_I):
    {
      sym = 'I';
      break;
    }

    case (KEY_J):
    {
      sym = 'J';
      break;
    }

    case (KEY_K):
    {
      sym = 'K';
      break;
    }

    case (KEY_L):
    {
      sym = 'L';
      break;
    }

    case (KEY_M):
    {
      sym = 'M';
      break;
    }

    case (KEY_N):
    {
      sym = 'N';
      break;
    }

    case (KEY_O):
    {
      sym = 'O';
      break;
    }

    case (KEY_P):
    {
      sym = 'P';
      break;
    }

    case (KEY_Q):
    {
      sym = 'Q';
      break;
    }

    case (KEY_R):
    {
      sym = 'R';
      break;
    }

    case (KEY_S):
    {
      sym = 'S';
      break;
    }

    case (KEY_T):
    {
      sym = 'T';
      break;
    }

    case (KEY_U):
    {
      sym = 'U';
      break;
    }

    case (KEY_V):
    {
      sym = 'V';
      break;
    }

    case (KEY_W):
    {
      sym = 'W';
      break;
    }

    case (KEY_X):
    {
      sym = 'X';
      break;
    }

    case (KEY_Y):
    {
      sym = 'Y';
      break;
    }

    case (KEY_Z):
    {
      sym = 'Z';
      break;
    }

    default:
      break;
  }

  return sym;
}

bool
Fl_Allegro_Screen_Driver::wait_keyboard(Fl_Window* window)
{
  static char buf[7];
  int triggered = false;
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
      (void)readkey();

      if (FL_Escape == sym)
      {
        while (window->parent())
        {
          window = window->window();
        }
      }

      Fl::e_keysym = sym;
      Fl::e_number = FL_KEYBOARD;
      Fl::handle(FL_KEYBOARD, window);
      triggered = true;
      break;
    }

    if (keypressed())
    {
      int scan;
      int sym = ureadkey(&scan);

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

      Fl::e_length = utf8proc_encode_char(sym,
                                          reinterpret_cast<utf8proc_uint8_t*>(buf));
      buf[Fl::e_length] = 0;

      if (0 == Fl::e_length)
      {
        break;
      }

      Fl::e_keysym = sym;
      Fl::e_number = FL_KEYBOARD;
      Fl::handle(FL_KEYBOARD, window);
      triggered = true;
      break;
    }

  }
  while (0);

  return triggered;
}

bool
Fl_Allegro_Screen_Driver::wait_keyboard(Fl_Window* window)
{
  int triggered = false;
  int rc;

  do
  {

    rc = keyboard_query();

    if (0 == rc)
    {
      break;
    }

    unsigned char ascii;
    unsigned char scan;

    keyboard_read(&scan, &ascii);

    char buf[2];
    int sym = 0;

    char kb0 = *(char*)0x0417;
    char kb1 = *(char*)0x0418;

    if (0x3 & kb0)
    {
      Fl::e_state |= FL_SHIFT;
    }

    if (0x4 & kb0)
    {
      Fl::e_state |= FL_CTRL;
    }

    if (0x8 & kb0)
    {
      Fl::e_state |= FL_ALT;
    }

    if (0x1 & kb1)
    {
      Fl::e_state |= FL_CTRL;
    }

    if (0x2 & kb1)
    {
      Fl::e_state |= FL_ALT;
    }

    buf[0] = 0;
    buf[1] = 0;
    Fl::e_text = buf;
    Fl::e_length = 0;

    if (ascii)
    {
      switch (ascii)
      {
        case ASCII_BS:
          sym = FL_BackSpace;
          break;

        case ASCII_TAB:
          sym = FL_Tab;
          break;

        case ASCII_ENTER:
          sym = FL_Enter;
          break;

        case ASCII_ESC:
          sym = FL_Escape;

          while (window->parent())
          {
            window = window->window();
          }

          break;

        default:
          sym = ascii;
          break;
      }
    }

    else
    {
      switch (scan)
      {
#if 0

        case SCAN_F1:
        case SCAN_F2:
        case SCAN_F3:
        case SCAN_F4:
        case SCAN_F5:
        case SCAN_F6:
        case SCAN_F7:
        case SCAN_F8:
        case SCAN_F9:
        case SCAN_F10:
#endif
        case SCAN_HOME:
          sym = FL_Home;
          break;

        case SCAN_UP:
          sym = FL_Up;
          break;

        case SCAN_PGUP:
          sym = FL_Page_Up;
          break;

        case SCAN_LEFT:
          sym = FL_Left;
          break;

        case SCAN_RIGHT:
          sym = FL_Right;
          break;

        case SCAN_END:
          sym = FL_End;
          break;

        case SCAN_DOWN:
          sym = FL_Down;
          break;

        case SCAN_PGDN:
          sym = FL_Page_Down;
          break;

        case SCAN_INS:
          sym = FL_Insert;
          break;

        case SCAN_DEL:
          sym = FL_Delete;
          break;

        case SCAN_SHIFT_TAB:
          sym = FL_Tab;
          Fl::e_state |= FL_SHIFT;
          break;
#if 0

        case SCAN_SHIFT_F1:
        case SCAN_SHIFT_F2:
        case SCAN_SHIFT_F3:
        case SCAN_SHIFT_F4:
        case SCAN_SHIFT_F5:
        case SCAN_SHIFT_F6:
        case SCAN_SHIFT_F7:
        case SCAN_SHIFT_F8:
        case SCAN_SHIFT_F9:
        case SCAN_SHIFT_F10:
#endif
        case SCAN_ALT_1:
          sym = '1';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_2:
          sym = '2';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_3:
          sym = '3';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_4:
          sym = '4';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_5:
          sym = '5';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_6:
          sym = '6';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_7:
          sym = '7';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_8:
          sym = '8';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_9:
          sym = '9';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_0:
          sym = '0';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_MINUS:
          sym = '-';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_PLUS:
          sym = '+';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_Q:
          sym = 'q';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_W:
          sym = 'w';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_E:
          sym = 'e';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_R:
          sym = 'r';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_T:
          sym = 't';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_Y:
          sym = 'y';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_U:
          sym = 'u';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_I:
          sym = 'i';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_O:
          sym = 'o';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_P:
          sym = 'p';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_A:
          sym = 'a';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_S:
          sym = 's';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_D:
          sym = 'd';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_F:
          sym = 'f';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_G:
          sym = 'g';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_H:
          sym = 'h';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_J:
          sym = 'j';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_K:
          sym = 'k';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_L:
          sym = 'l';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_Z:
          sym = 'z';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_X:
          sym = 'x';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_C:
          sym = 'c';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_V:
          sym = 'v';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_B:
          sym = 'r';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_N:
          sym = 'n';
          Fl::e_state |= FL_ALT;
          break;

        case SCAN_ALT_M:
          sym = 'm';
          Fl::e_state |= FL_ALT;
          break;
#if 0

        case SCAN_ALT_F1:
        case SCAN_ALT_F2:
        case SCAN_ALT_F3:
        case SCAN_ALT_F4:
        case SCAN_ALT_F5:
        case SCAN_ALT_F6:
        case SCAN_ALT_F7:
        case SCAN_ALT_F8:
        case SCAN_ALT_F9:
        case SCAN_ALT_F10:
        case SCAN_CTL_F1:
        case SCAN_CTL_F2:
        case SCAN_CTL_F3:
        case SCAN_CTL_F4:
        case SCAN_CTL_F5:
        case SCAN_CTL_F6:
        case SCAN_CTL_F7:
        case SCAN_CTL_F8:
        case SCAN_CTL_F9:
        case SCAN_CTL_F10:
#endif
        case SCAN_CTL_HOME:
          sym = FL_Home;
          Fl::e_state |= FL_CTRL;
          break;

        case SCAN_CTL_PGUP:
          sym = FL_Page_Up;
          Fl::e_state |= FL_CTRL;
          break;

        case SCAN_CTL_LEFT:
          sym = FL_Left;
          Fl::e_state |= FL_CTRL;
          break;

        case SCAN_CTL_RIGHT:
          sym = FL_Right;
          Fl::e_state |= FL_CTRL;
          break;

        case SCAN_CTL_END:
          sym = FL_End;
          Fl::e_state |= FL_CTRL;
          break;

        case SCAN_CTL_PGDN:
          sym = FL_Page_Down;
          Fl::e_state |= FL_CTRL;
          break;
      }
    }

    if (0x20 <= sym && 0x7f > sym)
    {
      buf[0] = sym;
      Fl::e_length = 1;
    }

    Fl::e_keysym = sym;
    Fl::e_number = FL_KEYBOARD;
    Fl::handle(FL_KEYBOARD, window);

  }
  while (0);

  return triggered;
}

bool
Fl_Allegro_Screen_Driver::wait_mouse(Fl_Window* window)
{
  int triggered = false;

  static wm::hit_type what_prev = wm::HIT_NONE;

  do
  {

    if (mouse_needs_poll())
    {
      poll_mouse();
    }

    int x = (mouse_pos >> 16);
    int y = (0xffff & mouse_pos);
    int movement = (abs(Fl::e_x_root - x) + abs(Fl::e_y_root - y));

    if (Fl::e_is_click)
    {
      bool wiggle = (movement > 1);

      if (wiggle)
      {
        Fl::e_is_click = 0;
      }
    }

    Fl::e_x_root = x;
    Fl::e_y_root = y;
    Fl::e_x = x - window->x();
    Fl::e_y = y - window->y();

    int btn = mouse_b;

    Fl::e_state = 0;
    Fl::e_keysym = 0;

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

    if (btn_state_)
    {
      if (btn)
      {
        if (movement)
        {
          Fl::handle(FL_DRAG, window);
          triggered = true;
        }
      }

      else
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

      break;
    }

    wm::hit_type what = what_prev;

    if (movement)
    {

      if (0 == Fl::grab_)
      {
        what = hit(window, Fl::e_x_root, Fl::e_y_root);
      }

      if (what != what_prev)
      {
        if (mouse_needs_poll())
        {
          poll_mouse();
        }

        x = (mouse_pos >> 16);
        y = (0xffff & mouse_pos);
        Fl::e_x_root = x;
        Fl::e_y_root = y;
        Fl::e_x = x - window->x();
        Fl::e_y = y - window->y();
        what_prev = what;
      }

      if (0 == btn)
      {
        Fl::handle(FL_MOVE, window);
        triggered = true;
        break;
      }
    }

    if (btn)
    {
      if ((0 == Fl::grab_) &&
          (FL_WINDOW == window->type()) ||
          (FL_DOUBLE_WINDOW == window->type()))
      {
        if (wm::HIT_NONE != what && wm::HIT_WINDOW != what)
        {
          triggered = wm_.handle_push(
                        (*window),
                        what,
                        Fl::e_x_root,
                        Fl::e_y_root);

          if (triggered)
          {
            break;
          }

        }
      }

      Fl::e_is_click++;
      btn_state_ = btn;
      Fl::handle(FL_PUSH, window);
      triggered = true;
    }

  }
  while (0);

  return triggered;
}

int
Fl_Allegro_Screen_Driver::get_mouse(int& x, int& y)
{
  int pos = mouse_pos;
  x = (pos >> 16);
  y = (0xffff & pos);
  return 1;
}
