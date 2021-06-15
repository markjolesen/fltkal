//
// Mouse cursor support for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2018 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     https://www.fltk.org/COPYING.php
//
// Please see the following page on how to report bugs and issues:
//
//     https://www.fltk.org/bugs.php
//

// Change the current cursor.
// Under X the cursor is attached to the X window.  I tried to hide
// this and pretend that changing the cursor is a drawing function.
// This avoids a field in the Fl_Window, and I suspect is more
// portable to other systems.

#include <fl/fl.h>
#include <fl/platform.h>
#include <fl/win.h>
#include <fl/imgpix.h>
#include <fl/imgrgb.h>
#include "drvwin.h"
#include <fl/fl_draw.h>

#if defined(USE_ALLEGRO)

#include <allegro.h>

//#include "fl_cursor_wait.xpm"
//#include "fl_cursor_help.xpm"
//#include "fl_cursor_nwse.xpm"
//#include "fl_cursor_nesw.xpm"
//#include "fl_cursor_none.xpm"

#include "curnone.xpm"

// ALLEGRO: cursor set
#include "cursors/crossh.xpm"
#include "cursors/e.xpm"
#include "cursors/fleur.xpm"
#include "cursors/help.xpm"
#include "cursors/nesw.xpm"
#include "cursors/ne.xpm"
#include "cursors/ns.xpm"
#include "cursors/nwse.xpm"
#include "cursors/nw.xpm"
#include "cursors/n.xpm"
#include "cursors/pointer.xpm"
#include "cursors/se.xpm"
#include "cursors/sw.xpm"
#include "cursors/s.xpm"
#include "cursors/text.xpm"
#include "cursors/wait.xpm"
#include "cursors/we.xpm"
#include "cursors/w.xpm"

enum xpm_index
{
  xpm_crossh,
  xpm_e,
  xpm_fleur,
  xpm_help,
  xpm_n,
  xpm_ne,
  xpm_nesw,
  xpm_ns,
  xpm_nw,
  xpm_nwse,
  xpm_pointer,
  xpm_s,
  xpm_se,
  xpm_sw,
  xpm_text,
  xpm_w,
  xpm_wait,
  xpm_we,
  xpm_none,
  xpm_last
};

BITMAP* _cursors[xpm_last];

BITMAP* xpm_to_bitmap(char const* const*);

extern void cursor_create()
{
  static char const** xpms[xpm_last]=
  {
    crossh_xpm,
    e_xpm,
    fleur_xpm,
    help_xpm,
    n_xpm,
    ne_xpm,
    nesw_xpm,
    ns_xpm,
    nw_xpm,
    nwse_xpm,
    pointer_xpm,
    s_xpm,
    se_xpm,
    sw_xpm,
    text_xpm,
    w_xpm,
    wait_xpm,
    we_xpm,
    fl_cursor_none_xpm
  };

  for (unsigned slot= 0; slot < xpm_last; slot++)
  {
    char const** xpm= xpms[slot];
    _cursors[slot]= xpm_to_bitmap(xpm);
  }

  return;
}

extern void cursor_destroy()
{

  for (unsigned slot= 0; slot < xpm_last; slot++)
  {
    destroy_bitmap(_cursors[slot]);
  }

  return;
}

extern BITMAP* cursor_get(int &hot_x, int &hot_y, Fl_Cursor const c)
{
  BITMAP* bmp= 0;

  hot_x= 0;
  hot_y= 0;

  switch(c)
  {
  case FL_CURSOR_DEFAULT: break;
  case FL_CURSOR_ARROW:   break;
  case FL_CURSOR_CROSS:   {bmp= _cursors[xpm_crossh];  hot_x= 15; hot_y= 15; break;}
  case FL_CURSOR_WAIT:    {bmp= _cursors[xpm_wait];    hot_x= 16; hot_y= 15; break;}
  case FL_CURSOR_INSERT:  {bmp= _cursors[xpm_text];    hot_x= 15; hot_y= 14; break;}
  case FL_CURSOR_HAND:    {bmp= _cursors[xpm_pointer]; hot_x= 12; hot_y= 8;break;}
  case FL_CURSOR_HELP:    {bmp= _cursors[xpm_help];    hot_x= 5;  hot_y= 6;break;}
  case FL_CURSOR_MOVE:    {bmp= _cursors[xpm_fleur];   hot_x= 16; hot_y= 16;break;}
  case FL_CURSOR_NS:      {bmp= _cursors[xpm_ns];      hot_x= 15; hot_y= 15; break;}
  case FL_CURSOR_WE:      {bmp= _cursors[xpm_we];      hot_x= 15; hot_y= 15; break;}
  case FL_CURSOR_NWSE:    {bmp= _cursors[xpm_nwse];    hot_x= 15; hot_y= 15; break;}
  case FL_CURSOR_NESW:    {bmp= _cursors[xpm_nesw];    hot_x= 15; hot_y= 15; break;}
  case FL_CURSOR_N:       {bmp= _cursors[xpm_n];       hot_x= 14; hot_y= 7; break;}
  case FL_CURSOR_NE:      {bmp= _cursors[xpm_ne];      hot_x= 23; hot_y= 7; break;}
  case FL_CURSOR_E:       {bmp= _cursors[xpm_e];       hot_x= 22; hot_y= 15; break;}
  case FL_CURSOR_SE:      {bmp= _cursors[xpm_se];      hot_x= 24; hot_y= 23; break;}
  case FL_CURSOR_S:       {bmp= _cursors[xpm_s];       hot_x= 15; hot_y= 24; break;}
  case FL_CURSOR_SW:      {bmp= _cursors[xpm_sw];      hot_x= 6;  hot_y= 24; break;}
  case FL_CURSOR_W:       {bmp= _cursors[xpm_w];       hot_x= 6;  hot_y= 15; break;}
  case FL_CURSOR_NW:      {bmp= _cursors[xpm_nw];      hot_x= 8;  hot_y= 7; break;}
  case FL_CURSOR_NONE:    {bmp= _cursors[xpm_none];    hot_x= 0;  hot_y= 0; break;}
  default: break;
  }

  return bmp;
}

extern void cursor_set(Fl_Cursor const c)
{
  static BITMAP* prev= 0;
  int hot_x;
  int hot_y;
  BITMAP* bmp= cursor_get(hot_x, hot_y, c);
  if (prev != bmp)
  {
     scare_mouse();
     set_mouse_sprite(bmp);
     set_mouse_sprite_focus(hot_x, hot_y);
     unscare_mouse();
     prev= bmp;
  }
  return;
}

#endif

/**
  Sets the cursor for the current window to the specified shape and colors.
  The cursors are defined in the <FL/Enumerations.H> header file.
  */
void fl_cursor(Fl_Cursor c) {
  if (Fl::first_window()) Fl::first_window()->cursor(c);
}

/* For back compatibility only. */
void fl_cursor(Fl_Cursor c, Fl_Color fg, Fl_Color bg) {
  fl_cursor(c);
}

/**
    Sets the default window cursor. This is the cursor that will be used
    after the mouse pointer leaves a widget with a custom cursor set.

    \see cursor(const Fl_RGB_Image*, int, int), default_cursor()
*/
void Fl_Window::default_cursor(Fl_Cursor c) {
  cursor_default = c;
  cursor(c);
}

#if 0
static void fallback_cursor(Fl_Window *w, Fl_Cursor c) {
  const char **xpm;
  int hotx, hoty;

  // The standard arrow is our final fallback, so something is broken
  // if we get called back here with that as an argument.
  if (c == FL_CURSOR_ARROW)
    return;

  switch (c) {
  case FL_CURSOR_WAIT:
    xpm = (const char**)fl_cursor_wait_xpm;
    hotx = 7;
    hoty = 9;
    break;
  case FL_CURSOR_HELP:
    xpm = (const char**)fl_cursor_help_xpm;
    hotx = 1;
    hoty = 3;
    break;
  case FL_CURSOR_NWSE:
    xpm = (const char**)fl_cursor_nwse_xpm;
    hotx = 7;
    hoty = 7;
    break;
  case FL_CURSOR_NESW:
    xpm = (const char**)fl_cursor_nesw_xpm;
    hotx = 7;
    hoty = 7;
    break;
  case FL_CURSOR_NONE:
    xpm = (const char**)fl_cursor_none_xpm;
    hotx = 0;
    hoty = 0;
    break;
  default:
    w->cursor(FL_CURSOR_ARROW);
    return;
  }

  Fl_Pixmap pxm(xpm);
  Fl_RGB_Image image(&pxm);

  w->cursor(&image, hotx, hoty);
}
#endif


void Fl_Window::cursor(Fl_Cursor c) {
  int ret;

  // the cursor must be set for the top level window, not for subwindows
  Fl_Window *w = window(), *toplevel = this;

  while (w) {
    toplevel = w;
    w = w->window();
  }

  if (toplevel != this) {
    toplevel->cursor(c);
    return;
  }

  if (c == FL_CURSOR_DEFAULT)
    c = cursor_default;

  if (!i)
    return;

  ret = pWindowDriver->set_cursor(c);
  if (ret)
    return;

//__mjo  fallback_cursor(this, c);
}

/**
  Changes the cursor for this window.  This always calls the system. If
  you are changing the cursor a lot you may want to keep track of how
  you set it in a static variable and call this only if the new cursor
  is different.

  The default cursor will be used if the provided image cannot be used
  as a cursor.

  \see cursor(Fl_Cursor), default_cursor()
*/
void Fl_Window::cursor(const Fl_RGB_Image *image, int hotx, int hoty) {
  int ret;

  // the cursor must be set for the top level window, not for subwindows
  Fl_Window *w = window(), *toplevel = this;

  while (w) {
    toplevel = w;
    w = w->window();
  }

  if (toplevel != this) {
    toplevel->cursor(image, hotx, hoty);
    return;
  }

  if (!i)
    return;

  ret = pWindowDriver->set_cursor(image, hotx, hoty);
  if (ret)
    return;

  cursor(FL_CURSOR_DEFAULT);
}

/**
 For back compatibility only.
 Same as Fl_Window::cursor(Fl_Cursor)
*/
void Fl_Window::cursor(Fl_Cursor c, Fl_Color, Fl_Color) {
  cursor(c);
};

/**
 For back compatibility only.
 same as Fl_Window::default_cursor(Fl_Cursor)
*/
void Fl_Window::default_cursor(Fl_Cursor c, Fl_Color, Fl_Color) {
  default_cursor(c);
};
