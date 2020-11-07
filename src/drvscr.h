// drvscr.h
//
// "$Id: Fl_Screen_Driver.H 12975 2018-06-26 14:04:09Z manolo $"
//
// All screen related calls in a driver style class.
//
// Copyright 2017-2019 The fltkal authors
// Copyright 1998-2018 by Bill Spitzak and others.
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
//

/**
 \cond DriverDev
 \addtogroup DriverDeveloper
 \{
 */

#ifndef FL_SCREEN_DRIVER_H
#define FL_SCREEN_DRIVER_H

#include <fl/drvdev.h>
#include <fl/fl_types.h>
#include <fl/fl.h> // for Fl_Timeout_Handler
#include <fl/texted.h>


// TODO: add text composition?
// TODO: add Fl::display
// TODO: add copy/paste, drag/drop?
// TODO: get key/get mouse?
// TODO: system colors/colormaps
// TODO: system menu?
// TODO: native filechooser
// TODO: native message boxes
// TODO: read screen to image
// TODO: application shortcuts

class Fl_Window;
class Fl_RGB_Image;
class Fl_Group;
class Fl_Input;

/**
 A base class describing the interface between FLTK and screen-related operations.

 This class is only for internal use by the FLTK library.
 
 Each supported platform implements several of the virtual methods of this class.
 */
class FL_EXPORT Fl_Screen_Driver {

  friend class fl_cleanup;

protected:
  Fl_Screen_Driver();
  virtual ~Fl_Screen_Driver();

  static const int MAX_SCREENS = 16;

  int num_screens;
  static  float fl_intersection(int x1, int y1, int w1, int h1,
                                      int x2, int y2, int w2, int h2);

public:
  static char bg_set;
  static char bg2_set;
  static char fg_set;

public:
  virtual float scale(int n) {return 1;}
  virtual void scale(int n, float f) { }
  static Fl_Screen_Driver *newScreenDriver();
  // --- display management
  virtual void display(const char *disp);
  virtual int visual(int flags);
  // --- screen configuration
  virtual void init() {}
  virtual int x() { return 0; }
  virtual int y() { return 0; }
  virtual int w() { return 800; } // default, override in driver!
  virtual int h() { return 600; } // default, override in driver!
  virtual int screen_count();
  void screen_xywh(int &X, int &Y, int &W, int &H, int mx, int my);
  virtual void screen_xywh(int &X, int &Y, int &W, int &H, int n) { X=0; Y=0; W=800; H=600; }
  void screen_xywh(int &X, int &Y, int &W, int &H, int mx, int my, int mw, int mh);
  virtual int screen_num(int x, int y);
  virtual int screen_num(int x, int y, int w, int h);
  virtual void screen_dpi(float &h, float &v, int n=0) { h=72; v=72; } // override in driver!
  void screen_work_area(int &X, int &Y, int &W, int &H, int mx, int my);
  virtual void screen_work_area(int &X, int &Y, int &W, int &H, int n) { screen_xywh(X, Y, W, H, n); }
  // --- audible output
  virtual void beep(int type) { }
  // --- global events
  virtual void flush() { } // must override
  virtual double wait(double time_to_wait) { return 0.0; } // must override
  virtual int ready() { return 0; } // must override
  virtual void grab(Fl_Window* win) { }
  // --- global colors
  /* the default implementation of parse_color() may be enough */
  virtual int parse_color(const char* p, uchar& r, uchar& g, uchar& b);
  virtual void get_system_colors() { }
  virtual const char *get_system_scheme();
  // --- global timers
  virtual void add_timeout(double time, Fl_Timeout_Handler cb, void *argp) { }
  virtual void repeat_timeout(double time, Fl_Timeout_Handler cb, void *argp) { }
  virtual int has_timeout(Fl_Timeout_Handler cb, void *argp) { return 0; }
  virtual void remove_timeout(Fl_Timeout_Handler cb, void *argp) { }

  static int secret_input_character;
  /* Implement to indicate whether complex text input may involve marked text.
   When it does, has_marked_text returns non zero and reset_marked_text() and
   insertion_point_location() must also be implemented.
   */
  virtual int has_marked_text() { return 0; }
  virtual void reset_marked_text() {}
  virtual void insertion_point_location(int x, int y, int height) {}
  // implement so text-editing widgets support dead keys
  virtual int compose(int &del) {del = 0; return 0;}
  // default implementation may be enough
  virtual void compose_reset();
  // implement to support drag-n-drop. use_selection = 1 means the GUI is welcome to display
  // the selected text during the D&D operation
  virtual int dnd(int use_selection = 0) {return 0;}
  // null means no platform-specific key bindings for Fl_Text_Editor
  Fl_Text_Editor::Key_Binding *text_editor_extra_key_bindings;
  // default implementation may be enough
  virtual int text_display_can_leak() { return 0; }

  // if no keyboard is connected on a touch or pen device, the system on-screen keyboard is requested
  virtual void request_keyboard() { }
  // we no longer need the on-screen keyboard; it's up to the system to hide it
  virtual void release_keyboard() { }

  // read raw image from a window or an offscreen buffer
  /* Member function read_win_rectangle() supports the public function
   fl_read_image() which captures pixel data either from
   the current window or from an offscreen buffer.

   With fl_read_image() and for capture from a window, the returned pixel array
   also contains data from any embedded sub-window.
   
   In the case of read_win_rectangle() and for capture from a window, only data
   from the current window is collected.
   
   A platform may also use its read_win_rectangle() implementation to capture
   window decorations (e.g., title bar). In that case, it is called by
   Fl_XXX_Window_Driver::capture_titlebar_and_borders().
   */
  virtual Fl_RGB_Image *read_win_rectangle(int X, int Y, int w, int h) {return NULL;}
  static void write_image_inside(Fl_RGB_Image *to, Fl_RGB_Image *from, int to_x, int to_y);
  static Fl_RGB_Image *traverse_to_gl_subwindows(Fl_Group *g, int x, int y, int w, int h,
                                                 Fl_RGB_Image *full_img);
  // optional platform-specific key handling for Fl_Input widget
  // the default implementation may be enough
  virtual int input_widget_handle_key(int key, unsigned mods, unsigned shift, Fl_Input *input);
  // implement to support Fl::get_mouse()
  virtual int get_mouse(int &x, int &y) {return 0;}
  // optional methods to enable/disable input methods for complex scripts
  virtual void enable_im() {}
  virtual void disable_im() {}
  // calls open_display_platform() and then does platform-independent work
  void open_display();
  // implement to open access to the display
  virtual void open_display_platform() {}
  // optional method to close display access
  virtual void close_display() {}
  // compute dimensions of an Fl_Offscreen
  virtual void offscreen_size(Fl_Offscreen off, int &width, int &height) {}
  
  void rescale_all_windows_from_screen(int screen, float f);
  static void transient_scale_display(float f, int nscreen);
  static int scale_handler(int event);
  virtual void init_workarea() {}
  virtual float desktop_scale_factor() {return 1;}
  float use_startup_scale_factor();
  enum APP_SCALING_CAPABILITY {
    NO_APP_SCALING = 0, ///< The platform does not support rescaling.
    SYSTEMWIDE_APP_SCALING, ///< The platform supports rescaling with the same factor for all screens.
    PER_SCREEN_APP_SCALING ///< The platform supports rescaling with one factor for each screen.
  };
  /** Returns the platform's support for rescaling the application with ctrl-/+/-/0/ keys.
   */
  virtual APP_SCALING_CAPABILITY rescalable() { return NO_APP_SCALING; }
  /* Number of pixels per drawing unit for the display.
     The default implementation may be enough. */
  virtual float retina_factor() { return 1; }
};


#endif // !FL_SCREEN_DRIVER_H

/**
 \}
 \endcond
 */

//
// End of "$Id: Fl_Screen_Driver.H 12975 2018-06-26 14:04:09Z manolo $".
//
