// drvsys.h
//
// "$Id: Fl_System_Driver.H 12976 2018-06-26 14:12:43Z manolo $"
//
// A base class for platform specific system calls
// for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2019 The fltkal authors
// Copyright 2010-2018 by Bill Spitzak and others.
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

/** \file Fl_System_Driver.H
 \brief declaration of class Fl_System_Driver.
*/

#ifndef FL_SYSTEM_DRIVER_H
#define FL_SYSTEM_DRIVER_H

#include <fl/fl.h>
#include <fl/export.h>
#include <fl/filename.h>
#include <fl/pref.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

class Fl_File_Icon;
class Fl_File_Browser;
class Fl_Pixmap;
class Fl_Widget;

/**
 \brief A base class for platform-specific system operations.
 This class is only for internal use by the FLTK library.
 Each supported platform implements several of the virtual methods of this class.
  */
class FL_EXPORT Fl_System_Driver {
  friend class Fl;
  friend class fl_cleanup;
public:
  struct Keyname {
    unsigned int key;
    const char* name;
  };
protected:
  // implement once for each platform
  static Fl_System_Driver *newSystemDriver();
  Fl_System_Driver();
  // key_table and key_table_size are used in fl_shortcut to translate key names
  Keyname *key_table;
  int key_table_size;
public:
  virtual ~Fl_System_Driver();
  // These flags are useful after calling XParseGeometry(). They indicate which of its arguments
  // contain meaningful data upon return.
  static const int fl_NoValue;
  static const int fl_WidthValue;
  static const int fl_HeightValue;
  static const int fl_XValue;
  static const int fl_YValue;
  static const int fl_XNegative;
  static const int fl_YNegative;

  // implement if the system adds unwanted program argument(s)
  virtual int single_arg(const char *arg) { return 0; }
  // implement if the system adds unwanted program argument pair(s)
  virtual int arg_and_value(const char *name, const char *value) { return 0; }
  // implement to process the -display argument
  virtual void display_arg(const char *arg) { }
  // default implementation should be enough
  virtual int XParseGeometry(const char* string, int* x, int* y, unsigned int* width, unsigned int* height);
  static void warning(const char* format, ...);
  // implement to set the default effect of Fl::warning()
  virtual void warning(const char* format, va_list args);
  static void error(const char* format, ...);
  // implement to set the default effect of Fl::error()
  virtual void error(const char* format, va_list args);
  static void fatal(const char* format, ...);
  // implement to set the default effect of Fl::error()
  virtual void fatal(const char* format, va_list args);

  // implement these to support cross-platform file operations
  virtual char *utf2mbcs(const char *s) {return (char*)s;}
  virtual char *getenv(const char* v) {return NULL;}
  virtual int putenv(const char *var) {return -1;}
  virtual int open(const char* f, int oflags, int pmode) {return -1;}

  // Note: the default implementation ignores the 'binary' argument.
  // Some platforms (notably Windows) may use this argument.
  virtual int open_ext(const char* f, int binary, int oflags, int pmode) {
    return this->open(f, oflags, pmode);
  }
  virtual FILE *fopen(const char* f, const char *mode);
  virtual int system(const char* cmd) {return -1;}
  virtual int execvp(const char *file, char *const *argv) {return -1;}
  virtual int chmod(const char* f, int mode) {return -1;}
  virtual int access(const char* f, int mode) { return -1;}
  virtual int stat(const char* f, struct stat *b) { return -1;}
  virtual char *getcwd(char* b, int l) {return NULL;}
  virtual int chdir(const char* path) {return -1;}
  virtual int unlink(const char* fname) {return -1;}
  virtual int mkdir(const char* f, int mode) {return -1;}
  virtual int rmdir(const char* f) {return -1;}
  virtual int rename(const char* f, const char *n) {return -1;}

  // the default implementation of these utf8... functions should be enough
  virtual unsigned utf8towc(const char* src, unsigned srclen, wchar_t* dst, unsigned dstlen);
  virtual unsigned utf8fromwc(char* dst, unsigned dstlen, const wchar_t* src, unsigned srclen);
  virtual int utf8locale() {return 1;}
  virtual unsigned utf8to_mb(const char* src, unsigned srclen, char* dst, unsigned dstlen);
  virtual unsigned utf8from_mb(char* dst, unsigned dstlen, const char* src, unsigned srclen);
  // implement to shield fprintf() from locale changes in decimal point
  virtual int clocale_printf(FILE *output, const char *format, va_list args);
  // implement functions telling whether a key is pressed
  virtual int event_key(int k) {return 0;}
  virtual int get_key(int k) {return 0;}
  // implement scandir-like function
  virtual int filename_list(const char *d, dirent ***list, int (*sort)(struct dirent **, struct dirent **) ) {return -1;}
  // the default implementation of filename_expand() may be enough
  virtual int filename_expand(char *to, int tolen, const char *from);
  // to implement
  virtual const char *getpwnam(const char *login) {return NULL;}
  // the default implementation of filename_relative() is in src/filename_absolute.cxx and may be enough
  virtual int filename_relative(char *to, int tolen, const char *from, const char *base);
  // the default implementation of filename_absolute() is in src/filename_absolute.cxx and may be enough
  virtual int filename_absolute(char *to, int tolen, const char *from);
  // the default implementation of filename_isdir() is in src/filename_isdir.cxx and may be enough
  virtual int filename_isdir(const char* n);
  // the default implementation of filename_isdir_quick() is in src/filename_isdir.cxx and may be enough
  virtual int filename_isdir_quick(const char* n);
  // the default implementation of filename_ext() is in src/filename_ext.cxx and may be enough
  virtual const char *filename_ext(const char *buf);
  // implement to support fl_filename_name()
  virtual const char *filename_name(const char *buf) {return buf;}
  // whether a platform uses additional code in Fl_Menu::handle(int e)
  virtual int need_menu_handle_part2() {return 0;}
  // whether a platform uses additional code in Fl_Menu::handle_part1(int e)
  virtual int need_menu_handle_part1_extra() {return 0;}
  // implement to support fl_open_uri()
  virtual int open_uri(const char *uri, char *msg, int msglen) {return 0;}
  // the default implementation of use_tooltip_timeout_condition() may be enough
  virtual int use_tooltip_timeout_condition() {return 0;}
  // the default implementation of use_recent_tooltip_fix() may be enough
  virtual int use_recent_tooltip_fix() {return 0;}
  // the default implementation of shortcut_add_key_name() is in src/fl_shortcut.cxx
  virtual const char *shortcut_add_key_name(unsigned key, char *p, char *buf, const char **);
  // the default implementation of need_test_shortcut_extra() may be enough
  virtual int need_test_shortcut_extra() {return 0;}
  // implement to support Fl_File_Browser::load()
  virtual int file_browser_load_filesystem(Fl_File_Browser *browser, char *filename, int lname, Fl_File_Icon *icon) {return 0;}
  // the default implementation of file_browser_load_directory() should be enough
  virtual int file_browser_load_directory(const char *directory, char *filename, size_t name_size, dirent ***pfiles, Fl_File_Sort_F *sort);
  // implement to support Fl_Preferences
  virtual void newUUID(char *uuidBuffer) { uuidBuffer[0] = 0; }
  // implement to support Fl_Preferences
  virtual char *preference_rootnode(Fl_Preferences *prefs, Fl_Preferences::Root root, const char *vendor,
                                    const char *application) {return NULL;}
  virtual char const* preference_ext() const {return "prefs";} // ALLEGRO:
  // the default implementation of preferences_need_protection_check() may be enough
  virtual int preferences_need_protection_check() {return 0;}
  // implement to support Fl_Plugin_Manager::load()
  virtual void *dlopen(const char *filename) {return NULL;}
  // the default implementation is most probably enough
  virtual void png_extra_rgba_processing(unsigned char *array, int w, int h) {}
  // the default implementation is most probably enough
  virtual const char *next_dir_sep(const char *start) { return strchr(start, '/');}
  // implement to support threading
  virtual void awake(void*) {}
  virtual int lock() {return 1;}
  virtual void unlock() {}
  virtual void* thread_message() {return NULL;}
  // implement to support Fl_File_Icon
  virtual int file_type(const char *filename);
  // implement to return the user's home directory name
  virtual const char *home_directory_name() { return ""; }
  // the default implementation is most probably enough
  virtual const char *filesystems_label() { return "File Systems"; }
  // return TRUE means \ same as / in file names
  virtual int backslash_as_slash() {return 0;}
  // return TRUE means : indicates a drive letter in file names
  virtual int colon_is_drive() {return 0;}
  // return TRUE means that files whose name begins with dot are hidden
  virtual int dot_file_hidden() {return 0;}
  // return TRUE when file names are case insensitive
  virtual int case_insensitive_filenames() {return 0;}
  // the implementations of local_to_latin1() and latin1_to_local() are in fl_encoding_latin1.cxx
  virtual const char *local_to_latin1(const char *t, int n);
  virtual const char *latin1_to_local(const char *t, int n);
  // the implementations of local_to_mac_roman() and mac_roman_to_local() are in fl_encoding_mac_roman.cxx
  virtual const char *local_to_mac_roman(const char *t, int n);
  virtual const char *mac_roman_to_local(const char *t, int n);
  // the default implementation is most probably enough
  virtual void own_colormap() {}
  // the default implementations of tree_openpixmap() and tree_closepixmap() are
  // in Fl_Tree_Prefs.cxx and can be enough
  virtual Fl_Pixmap *tree_openpixmap();
  virtual Fl_Pixmap *tree_closepixmap();
  static const char *const tree_open_xpm[]; // used by tree_openpixmap()
  static const char * const tree_close_xpm[]; // used by tree_closepixmap()
  // the default implementation of tree_connector_style() is in Fl_Tree_Prefs.cxx and can be enough
  virtual int tree_connector_style();
  // implement to support copy-to-clipboard
  virtual void copy(const char *stuff, int len, int clipboard, const char *type) {}
  // implement to support paste-from-clipboard
  virtual void paste(Fl_Widget &receiver, int clipboard, const char *type) {}
  // implement to support paste-from-clipboard
  virtual int clipboard_contains(const char *type) {return 0;}
  //  implement to support paste-from-clipboard
  virtual void clipboard_notify_change() {}
  virtual void add_fd(int fd, int when, Fl_FD_Handler cb, void* = 0);
  virtual void add_fd(int fd, Fl_FD_Handler cb, void* = 0);
  virtual void remove_fd(int, int when);
  virtual void remove_fd(int);
  // the default implementation of open_callback() may be enough
  virtual void open_callback(void (*)(const char *));
  // The default implementation may be enough.
  virtual void gettime(time_t *sec, int *usec);
  // The default implementation of the next 4 functions may be enough.
  virtual const char *shift_name() { return "Shift"; }
  virtual const char *meta_name() { return "Meta"; }
  virtual const char *alt_name() { return "Alt"; }
  virtual const char *control_name() { return "Ctrl"; }
};

#endif // FL_SYSTEM_DRIVER_H

/**
 \}
 \endcond
 */

//
// End of "$Id: Fl_System_Driver.H 12976 2018-06-26 14:12:43Z manolo $".
//
