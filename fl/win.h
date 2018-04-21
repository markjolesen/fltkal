// win.h
//
// "$Id: Fl_Window.H 12726 2018-03-10 00:46:12Z matt $"
//
// Window header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2016 by Bill Spitzak and others.
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

/** \file
   Fl_Window widget . */

#ifndef Fl_Window_H
#define Fl_Window_H

#include <fl/fl.h>
#include <fl/group.h>
#include <fl/imgbit.h>
#include <stdlib.h>

#define FL_WINDOW 0xF0		///< window type id all subclasses have type() >= this
#define FL_DOUBLE_WINDOW 0xF1   ///< double window type id
#define FL_CHILD_WINDOW         (FL_DOUBLE_WINDOW + 1) // ALLEGRO:
#define FL_MENU_WINDOW          (FL_DOUBLE_WINDOW + 2) // ALLEGRO:
#define FL_MENU_TITLE_WINDOW    (FL_DOUBLE_WINDOW + 3) // ALLEGRO:
#define FL_TOOLTIP_WINDOW       (FL_DOUBLE_WINDOW + 4) // ALLEGRO:

class Fl_X;
class Fl_Window_Driver;
class Fl_RGB_Image;
class Fl_Double_Window;

/**
  This widget produces an actual window.  This can either be a main
  window, with a border and title and all the window management controls,
  or a "subwindow" inside a window.  This is controlled by whether or not
  the window has a parent().

  Once you create a window, you usually add children Fl_Widget
  's to it by using window->add(child) for each new widget.
  See Fl_Group for more information on how to add and remove children.

  There are several subclasses of Fl_Window that provide
  double-buffering, overlay, menu, and OpenGL support.

  The window's callback is done if the user tries to close a window
  using the window manager and Fl::modal() is zero or equal to the
  window. Fl_Window has a default callback that calls Fl_Window::hide().
*/
class FL_EXPORT Fl_Window : public Fl_Group {
  friend int Fl::arg(int argc, char **argv, int &i);
  friend class Fl_X;
  friend class Fl_Window_Driver;
private:
  static char *default_xclass_;
  static char show_iconic_; // 1 means create next window in iconic form

  int no_fullscreen_x;
  int no_fullscreen_y;
  int no_fullscreen_w;
  int no_fullscreen_h;
  int fullscreen_screen_top;
  int fullscreen_screen_bottom;
  int fullscreen_screen_left;
  int fullscreen_screen_right;

  // TODO: it would make sense to merge the use of Fl_X and Fl_Window_Driver, maybe simply by
  // TODO: deriving Fl_Window_Driver from Fl_X. However, there are a lot of historic kldges for
  // TODO: some platforms around Fl_X.
  Fl_X *i; // points at the system-specific stuff, but exists only after the window is mapped
  Fl_Window_Driver *pWindowDriver; // points at the system-specific stuff at window creation time

  const char* iconlabel_;
  char* xclass_;
  // size_range stuff:
  int minw, minh, maxw, maxh;
  int dw, dh, aspect;
  uchar size_range_set;
  // cursor stuff
  Fl_Cursor cursor_default;
  
  void _Fl_Window(); // constructor innards

  // unimplemented copy ctor and assignment operator
  Fl_Window(const Fl_Window&);
  Fl_Window& operator=(const Fl_Window&);

protected:

  /** Stores the last window that was made current. See current() const */
  static Fl_Window *current_;
  void draw();
  /** Forces the window to be drawn, this window is also made current and calls draw(). */
  virtual void flush();

  /**
    Sets an internal flag that tells FLTK and the window manager to
    honor position requests.

    This is used internally and should not be needed by user code.

    \param[in] force 1 to set the FORCE_POSITION flag, 0 to clear it
  */
  void force_position(int force) {
    if (force) set_flag(FORCE_POSITION);
    else clear_flag(FORCE_POSITION);
  }
  /**
    Returns the internal state of the window's FORCE_POSITION flag.

    \retval 1 if flag is set
    \retval 0 otherwise

    \see force_position(int)
  */
  int force_position() const { return ((flags() & FORCE_POSITION)?1:0); }

  void free_icons();

public:

  /**
    Creates a window from the given size and title. 
    If Fl_Group::current() is not NULL, the window is created as a 
    subwindow of the parent window.
    
    The (w,h) form of the constructor creates a top-level window
    and asks the window manager to position the window. The (x,y,w,h)
    form of the constructor either creates a subwindow or a
    top-level window at the specified location (x,y) , subject to window
    manager configuration. If you do not specify the position of the
    window, the window manager will pick a place to show the window
    or allow the user to pick a location. Use position(x,y)
    or hotspot() before calling show() to request a
    position on the screen. See Fl_Window::resize() 
    for some more details on positioning windows.
    
    Top-level windows initially have visible() set to 0
    and parent() set to NULL. Subwindows initially
    have visible() set to 1 and parent() set to
    the parent window pointer.
    
    Fl_Widget::box() defaults to FL_FLAT_BOX. If you plan to
    completely fill the window with children widgets you should
    change this to FL_NO_BOX. If you turn the window border off
    you may want to change this to FL_UP_BOX.

    \see Fl_Window(int x, int y, int w, int h, const char* title)
  */
    Fl_Window(int w, int h, const char* title= 0);
  /** Creates a window from the given position, size and title.

    \see Fl_Window(int w, int h, const char *title)
  */
    Fl_Window(int x, int y, int w, int h, const char* title = 0);
  /**
    The destructor <I>also deletes all the children</I>. This allows a
    whole tree to be deleted at once, without having to keep a pointer to
    all the children in the user code. A kludge has been done so the 
    Fl_Window and all of its children can be automatic (local)
    variables, but you must declare the Fl_Window <I>first</I> so
    that it is destroyed last.
  */
    virtual ~Fl_Window();

  virtual int handle(int);

  /**
    Changes the size and position of the window.  If shown() is true,
    these changes are communicated to the window server (which may
    refuse that size and cause a further resize).  If shown() is
    false, the size and position are used when show() is called.
    See Fl_Group for the effect of resizing on the child widgets.

    You can also call the Fl_Widget methods size(x,y) and position(w,h),
    which are inline wrappers for this virtual function.

    A top-level window can not force, but merely suggest a position and 
    size to the operating system. The window manager may not be willing or 
    able to display a window at the desired position or with the given 
    dimensions. It is up to the application developer to verify window 
    parameters after the resize request.
  */
  virtual void resize(int X,int Y,int W,int H);
  /**
    Sets whether or not the window manager border is around the
    window.  The default value is true. void border(int) can be
    used to turn the border on and off. <I>Under most X window
    managers this does not work after show() has been called,
    although SGI's 4DWM does work.</I>
  */
  void border(int b);
  /**
    Fast inline function to turn the window manager border
    off. It only works before show() is called.
  */
  void clear_border()	{set_flag(NOBORDER);}
  /** See void Fl_Window::border(int) */
  unsigned int border() const	{return !(flags() & NOBORDER);}
  /** Activates the flags NOBORDER|FL_OVERRIDE */
  void set_override()	{set_flag(NOBORDER|OVERRIDE);}
  /** Returns non zero if FL_OVERRIDE flag is set, 0 otherwise. */
  unsigned int override() const  { return flags()&OVERRIDE; }
  /**
    A "modal" window, when shown(), will prevent any events from
    being delivered to other windows in the same program, and will also
    remain on top of the other windows (if the X window manager supports
    the "transient for" property).  Several modal windows may be shown at
    once, in which case only the last one shown gets events.  You can see
    which window (if any) is modal by calling Fl::modal().
  */
  void set_modal()	{set_flag(MODAL);}
  /**  Returns true if this window is modal.  */
  unsigned int modal() const	{return flags() & MODAL;}
  /**
    A "non-modal" window (terminology borrowed from Microsoft Windows)
    acts like a modal() one in that it remains on top, but it has
    no effect on event delivery.  There are <I>three</I> states for a
    window: modal, non-modal, and normal.
  */
  void set_non_modal()	{set_flag(NON_MODAL);}
  /**  Returns true if this window is modal or non-modal. */
  unsigned int non_modal() const {return flags() & (NON_MODAL|MODAL);}

  /**
    Clears the "modal" flags and converts a "modal" or "non-modal"
    window back into a "normal" window.

    Note that there are <I>three</I> states for a window: modal,
    non-modal, and normal.

    You can not change the "modality" of a window whilst
    it is shown, so it is necessary to first hide() the window,
    change its "modality" as required, then re-show the window
    for the new state to take effect.

    This method can also be used to change a "modal" window into a
    "non-modal" one. On several supported platforms, the "modal" state
    over-rides the "non-modal" state, so the "modal" state must be
    cleared before the window can be set into the "non-modal"
    state.
    In general, the following sequence should work:

    \code
    win->hide();
    win->clear_modal_states();
    //Set win to new state as desired, or leave "normal", e.g...
    win->set_non_modal();
    win->show();
    \endcode

    \note Under some window managers, the sequence of hiding the
    window and changing its modality will often cause it to be
    re-displayed at a different position when it is subsequently
    shown. This is an irritating feature but appears to be
    unavoidable at present.
    As a result we would advise to use this method only when
    absolutely necessary.

    \see void set_modal(), void set_non_modal()
  */
  void clear_modal_states() {clear_flag(NON_MODAL | MODAL);}

  /**
    Marks the window as a menu window.

    This is intended for internal use, but it can also be used if you
    write your own menu handling. However, this is not recommended.

    This flag is used for correct "parenting" of windows in communication
    with the windowing system. Modern X window managers can use different
    flags to distinguish menu and tooltip windows from normal windows.

    This must be called before the window is shown and cannot be changed
    later.
  */
  void set_menu_window()	{set_flag(MENU_WINDOW);}

  /**  Returns true if this window is a menu window. */
  unsigned int menu_window() const {return flags() & MENU_WINDOW;}
  
  /**
    Marks the window as a tooltip window.

    This is intended for internal use, but it can also be used if you
    write your own tooltip handling. However, this is not recommended.

    This flag is used for correct "parenting" of windows in communication
    with the windowing system. Modern X window managers can use different
    flags to distinguish menu and tooltip windows from normal windows.

    This must be called before the window is shown and cannot be changed
    later.

    \note Since Fl_Tooltip_Window is derived from Fl_Menu_Window, this
    also \b clears the menu_window() state.
  */
  void set_tooltip_window()	{ set_flag(TOOLTIP_WINDOW);
				  clear_flag(MENU_WINDOW); }
  /**  Returns true if this window is a tooltip window. */
  unsigned int tooltip_window() const {return flags() & TOOLTIP_WINDOW;}

  /**
    Positions the window so that the mouse is pointing at the given
    position, or at the center of the given widget, which may be the
    window itself.  If the optional offscreen parameter is
    non-zero, then the window is allowed to extend off the screen (this
    does not work with some X window managers). \see position()
  */
  void hotspot(int x, int y, int offscreen = 0);
  /** See void Fl_Window::hotspot(int x, int y, int offscreen = 0) */
  void hotspot(const Fl_Widget*, int offscreen = 0);
  /** See void Fl_Window::hotspot(int x, int y, int offscreen = 0) */
  void hotspot(const Fl_Widget& p, int offscreen = 0) {hotspot(&p,offscreen);}

  /**
    Undoes the effect of a previous resize() or show() so that the next time
    show() is called the window manager is free to position the window.

    This is for Forms compatibility only.

    \deprecated please use force_position(0) instead
  */
  void free_position()	{clear_flag(FORCE_POSITION);}
  void size_range(int minw, int minh, int maxw=0, int maxh=0, int dw=0, int dh=0, int aspect=0);

  /** See void Fl_Window::label(const char*)   */
  const char* label() const	{return Fl_Widget::label();}
  /**  See void Fl_Window::iconlabel(const char*)   */
  const char* iconlabel() const	{return iconlabel_;}
  /** Sets the window title bar label. */
  void label(const char*);
  /** Sets the icon label. */
  void iconlabel(const char*);
  /** Sets the icon label. */
  void label(const char* label, const char* iconlabel); // platform dependent
  void copy_label(const char* a);

  static void default_xclass(const char*);
  static const char *default_xclass();
  const char* xclass() const;
  void xclass(const char* c);

  static void default_icon(const Fl_RGB_Image*);
  static void default_icons(const Fl_RGB_Image*[], int);
  void icon(const Fl_RGB_Image*);
  void icons(const Fl_RGB_Image*[], int);

#if defined(_WIN32) && !defined(FL_DOXYGEN)
  typedef struct HICON__* HICON;
  // These 2 member functions break the driver model but are kept for back compatibility.
  // They are implemented in Fl_win32.cxx
  static void default_icons(HICON big_icon, HICON small_icon);
  void icons(HICON big_icon, HICON small_icon);
#endif

  /* for legacy compatibility */
  const void* icon() const;
  void icon(const void * ic);

  /**
    Returns non-zero if show() has been called (but not hide()
    ). You can tell if a window is iconified with (w->shown()
    && !w->visible()).
  */
  int shown() {return i != 0;}
  /**
    Puts the window on the screen. Usually (on X) this has the side
    effect of opening the display.

    If the window is already shown then it is restored and raised to the
    top.  This is really convenient because your program can call show()
    at any time, even if the window is already up.  It also means that
    show() serves the purpose of raise() in other toolkits.

    Fl_Window::show(int argc, char **argv) is used for top-level
    windows and allows standard arguments to be parsed from the
    command-line.

    \note For some obscure reasons Fl_Window::show() resets the current
    group by calling Fl_Group::current(0). The comments in the code
    say "get rid of very common user bug: forgot end()". Although
    this is true it may have unwanted side effects if you show() an
    unrelated window (maybe for an error message or warning) while
    building a window or any other group widget.

    \todo Check if we can remove resetting the current group in a later
    FLTK version (after 1.3.x). This may break "already broken" programs
    though if they rely on this "feature".

    \see Fl_Window::show(int argc, char **argv)
  */
  virtual void show();
  /**
    Removes the window from the screen.  If the window is already hidden or
    has not been shown then this does nothing and is harmless.
  */
  virtual void hide();
  /**
    Puts the window on the screen and parses command-line arguments.

    Usually (on X) this has the side effect of opening the display.

    This form should be used for top-level windows, at least for the
    first (main) window. It allows standard arguments to be parsed
    from the command-line. You can use \p argc and \p argv from
    main(int argc, char **argv) for this call.

    The first call also sets up some system-specific internal
    variables like the system colors.

    \todo explain which system parameters are set up.

    \param argc command-line argument count, usually from main()
    \param argv command-line argument vector, usually from main()

    \see virtual void Fl_Window::show()
  */
  void show(int argc, char **argv);

  // Enables synchronous show(), docs in Fl_Window.cxx
  void wait_for_expose();

  /**
    Makes the window completely fill one or more screens, without any
    window manager border visible.  You must use fullscreen_off() to
    undo this. 

    \note On some platforms, this can result in the keyboard being
    grabbed. The window may also be recreated, meaning hide() and
    show() will be called.

    \see void Fl_Window::fullscreen_screens()
  */
  void fullscreen();
  /**
    Turns off any side effects of fullscreen()
  */
  void fullscreen_off();
  /**
    Turns off any side effects of fullscreen() and does 
    resize(x,y,w,h).
  */
  void fullscreen_off(int X,int Y,int W,int H);
  /**
    Returns non zero if FULLSCREEN flag is set, 0 otherwise. 
  */
  unsigned int fullscreen_active() const { return flags() & FULLSCREEN; }
  /**
    Sets which screens should be used when this window is in fullscreen
    mode. The window will be resized to the top of the screen with index
    \p top, the bottom of the screen with index \p bottom, etc. 

    If this method is never called, or if any argument is < 0, then the
    window will be resized to fill the screen it is currently on.

    \see void Fl_Window::fullscreen()
    */
  void fullscreen_screens(int top, int bottom, int left, int right);
  /**
    Iconifies the window.  If you call this when shown() is false
    it will show() it as an icon.  If the window is already
    iconified this does nothing.

    Call show() to restore the window.

    When a window is iconified/restored (either by these calls or by the
    user) the handle() method is called with FL_HIDE and 
    FL_SHOW events and visible() is turned on and off.

    There is no way to control what is drawn in the icon except with the
    string passed to Fl_Window::xclass().  You should not rely on
    window managers displaying the icons.
  */
  void iconize();

  int x_root() const ;
  int y_root() const ;

 static Fl_Window *current();
  /**
    Sets things up so that the drawing functions in <FL/fl_draw.H> will go
    into this window. This is useful for incremental update of windows, such
    as in an idle callback, which will make your program behave much better
    if it draws a slow graphic. <B>Danger: incremental update is very hard to
    debug and maintain!</B>

    This method only works for the Fl_Window and Fl_Gl_Window derived classes.
  */
  void make_current();

  /**
    Changes the cursor for this window.  This always calls the system, if
    you are changing the cursor a lot you may want to keep track of how
    you set it in a static variable and call this only if the new cursor
    is different.

    The type Fl_Cursor is an enumeration defined in <FL/Enumerations.H>.

    \see cursor(const Fl_RGB_Image*, int, int), default_cursor()
  */
  void cursor(Fl_Cursor);
  void cursor(const Fl_RGB_Image*, int, int);
  void default_cursor(Fl_Cursor);

  /* for legacy compatibility */
  void cursor(Fl_Cursor c, Fl_Color, Fl_Color=FL_WHITE);
  void default_cursor(Fl_Cursor c, Fl_Color, Fl_Color=FL_WHITE);

  static void default_callback(Fl_Window*, void* v);
  
  /** Returns the window width including any frame added by the window manager.
   
   Same as w() if applied to a subwindow.
   */
  int decorated_w() const;

  /** Returns the window height including any window title bar and any frame 
   added by the window manager.
   
   Same as h() if applied to a subwindow.
   */
  int decorated_h() const;

  Fl_Window_Driver *driver() const { return pWindowDriver; }

  // Note: Doxygen docs in Fl_Widget.H to avoid redundancy.
  virtual Fl_Window* as_window() { return this; }

  /**
   Return non-null if this is an Fl_Overlay_Window object.
   */
  virtual class Fl_Overlay_Window *as_overlay_window() {return 0L; }

  /**
   Return non-null if this is an Fl_Double_Window object.
   */
  virtual class Fl_Double_Window *as_double_window() {return 0L;}
  
  void shape(const Fl_Image* img);
  void shape(const Fl_Image& b) ;
  int is_shaped();

};

#endif

//
// End of "$Id: Fl_Window.H 12726 2018-03-10 00:46:12Z matt $".
//
