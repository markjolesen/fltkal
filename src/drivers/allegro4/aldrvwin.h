// aldrvwin.h
//
// Allegro4 Window handling code for the Fast Light Tool Kit (FLTK).
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
#if !defined(FL_ALLEGRO_WINDOW_DRIVER_H)

#  include "../../drvwin.h"
#  include <fl/fl_enums.h>

#  if defined(USE_ALLEGRO)
#    include <allegro.h>
#  else
#    include "bitmap.h"
#    include "cursor.h"
#  endif

class Fl_Allegro_Window_Driver : public Fl_Window_Driver
{
protected:
#  if defined(USE_ALLEGRO)
  struct
  {
    Fl_Cursor pointer_;
    struct
    {
      BITMAP *bmp_;
      int hot_x_;
      int hot_y_;
    } custom_;
  } cursor_;
#  else
  struct
  {
    Fl_Cursor pointer_;
    struct cursor *current_;
    struct cursor custom_;
  } cursor_;
#  endif

  struct
  {
    int x_;
    int y_;
#  if defined(USE_ALLEGRO)
    BITMAP *bmp_;
#  else
    struct bitmap *bmp_;
#  endif
  } store_;

  bool
    nca_title_bbox(signed &, signed &, unsigned &, unsigned &) const;

  bool
    nca_frame_bbox(signed &, signed &, unsigned &, unsigned &) const;

  void
    nca_draw() const;

public:
  enum
  {
    title_bar_height = 24,
    window_min_height = 50,
    window_min_width = 50
  };

  Fl_Allegro_Window_Driver(Fl_Window *);

  virtual ~Fl_Allegro_Window_Driver();

  virtual int
    decorated_w();

  virtual int
    decorated_h();

  virtual void
    draw_begin();

  virtual void
    draw_end();

  virtual Fl_X *
    makeWindow();

  virtual void
    take_focus();

  virtual void
    show();

  virtual void
    hide();

  virtual void
    resize(int X, int Y, int W, int H);

  virtual int
    scroll(int src_x,
           int src_y,
           int src_w,
           int src_h,
           int dest_x,
           int dest_y,
           void (*draw_area)(void *, int, int, int, int),
           void *data);

  virtual Fl_Cursor
    get_cursor() const;

  virtual int set_cursor(Fl_Cursor);

  virtual int
    set_cursor(const Fl_RGB_Image *, int, int);
};

inline bool
  Fl_Allegro_Window_Driver::nca_title_bbox(signed &pos_x,
                                           signed &pos_y,
                                           unsigned &len_x,
                                           unsigned &len_y) const
{
  bool has_frame = true;

  pos_x = pWindow->x() - 1;
  pos_y = pWindow->y() - (Fl_Allegro_Window_Driver::title_bar_height + 2);
  len_x = pWindow->w() + 2;
  len_y = (Fl_Allegro_Window_Driver::title_bar_height + 2);

  return has_frame;
}

inline bool
  Fl_Allegro_Window_Driver::nca_frame_bbox(signed &pos_x,
                                           signed &pos_y,
                                           unsigned &len_x,
                                           unsigned &len_y) const
{
  bool has_frame = true;

  pos_x = pWindow->x() - 1;
  pos_y = pWindow->y() - (Fl_Allegro_Window_Driver::title_bar_height + 2);
  len_x = pWindow->w() + 2;
  len_y = pWindow->h() + (Fl_Allegro_Window_Driver::title_bar_height + 2);

  return has_frame;
}

#  define FL_ALLEGRO_WINDOW_DRIVER_H
#endif
