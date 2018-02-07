// filechn.h
//
// "$Id: Fl_Native_File_Chooser.H 11681 2016-04-23 06:27:31Z manolo $"
//
// FLTK native OS file chooser widget
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
// Copyright 2004 Greg Ercolano.
//

/** \file
   Fl_Native_File_Chooser widget. */

/* Implementation note:
 
 class Fl_Native_File_Chooser  <== public API used by applications
 
 class Fl_Native_File_Chooser_Driver   <== virtual API that a platform may implement
                                           this API has a do-nothing default implementation
 
        class Fl_Native_File_Chooser_FLTK_Driver   <== this API implementation is the default FLTK file chooser
                class Fl_GTK_Native_File_Chooser_Driver  <== this API implementation runs a GTK file chooser
                                        it is determined at run-time if the GTK dynamic libraries are available
 
        class Fl_Quartz_Native_File_Chooser_Driver  <== this API implementation runs a Mac OS X file chooser

        class Fl_WinAPI_Native_File_Chooser_Driver  <== this API implementation runs a MSWindows file chooser
 
 
 Each platform must implement the constructor of the Fl_Native_File_Chooser class.
 This particular implementation:
 
 Fl_Native_File_Chooser::Fl_Native_File_Chooser(int val) {
  platform_fnfc = new Fl_Native_File_Chooser_FLTK_Driver(val);
 }
 
 can be used by any platform. 
 No more code is required. The cross-platform Fl_Native_File_Chooser_FLTK.cxx file must be compiled in libfltk,
 and the default FLTK file chooser will be used.
 
 This other implementation:
 Fl_Native_File_Chooser::Fl_Native_File_Chooser(int val) {
   platform_fnfc = 0;
 }
 can be used by a platform that needs no file chooser.
 */

#ifndef FL_NATIVE_FILE_CHOOSER_H
#define FL_NATIVE_FILE_CHOOSER_H

#include <fl/export.h>
#include <fl/filech.h>

class Fl_Native_File_Chooser_Driver;

/**
 This class lets an FLTK application easily and consistently access 
 the operating system's native file chooser. Some operating systems 
 have very complex and specific file choosers that many users want 
 access to specifically, instead of FLTK's default file chooser(s). 
 
 In cases where there is no native file browser, FLTK's own file browser
 is used instead.
 
 To use this widget, use the following include in your code:
 \code
 #include <FL/Fl_Native_File_Chooser.H>
 \endcode
 
 The following example shows how to pick a single file:
 \code
 // Create and post the local native file chooser
 #include <FL/Fl_Native_File_Chooser.H>
 [..]
 Fl_Native_File_Chooser fnfc;
 fnfc.title("Pick a file");
 fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
 fnfc.filter("Text\t*.txt\n"
             "C Files\t*.{cxx,h,c}");
 fnfc.directory("/var/tmp");           // default directory to use
 // Show native chooser
 switch ( fnfc.show() ) {
   case -1: printf("ERROR: %s\n", fnfc.errmsg());    break;  // ERROR
   case  1: printf("CANCEL\n");                      break;  // CANCEL
   default: printf("PICKED: %s\n", fnfc.filename()); break;  // FILE CHOSEN
 }
 \endcode
 
 The Fl_Native_File_Chooser widget transmits UTF-8 encoded filenames to its user. It is
 recommended to open files that may have non-ASCII names with the fl_fopen() or
 fl_open() utility functions that handle these names in a cross-platform way 
 (whereas the standard fopen()/open() functions fail on the MSWindows platform 
 to open files with a non-ASCII name).
 
 <B>Platform Specific Caveats</B>
 
 - Under X windows, and if Fl::OPTION_FNFC_USES_GTK has not been switched off,
 the widget attempts to use standard GTK file chooser dialogs if they are
 available at run-time on the platform, and falls back to use FLTK's Fl_File_Chooser if they are not.
 In the latter case, it's best if you call Fl_File_Icon::load_system_icons()
 at the start of main(), to enable the nicer looking file browser widgets.
 Use the static public attributes of class Fl_File_Chooser to localize
 the browser.
 - Some operating systems support certain OS specific options; see 
 Fl_Native_File_Chooser::options() for a list.
 
 \image html Fl_Native_File_Chooser.png "The Fl_Native_File_Chooser on different platforms."
 \image latex Fl_Native_File_Chooser.png "The Fl_Native_File_Chooser on different platforms" width=14cm
 
 */
class FL_EXPORT Fl_Native_File_Chooser {
private:
  Fl_Native_File_Chooser_Driver *platform_fnfc;
public:
  enum Type {
    BROWSE_FILE = 0,			///< browse files (lets user choose one file)
    BROWSE_DIRECTORY,			///< browse directories (lets user choose one directory)
    BROWSE_MULTI_FILE,			///< browse files (lets user choose multiple files)
    BROWSE_MULTI_DIRECTORY,		///< browse directories (lets user choose multiple directories)
    BROWSE_SAVE_FILE,			///< browse to save a file
    BROWSE_SAVE_DIRECTORY		///< browse to save a directory
  };
  enum Option {
    NO_OPTIONS     = 0x0000,		///< no options enabled
    SAVEAS_CONFIRM = 0x0001,		///< Show native 'Save As' overwrite confirm dialog
    NEW_FOLDER     = 0x0002,		///< Show 'New Folder' icon (if supported)
    PREVIEW        = 0x0004,		///< enable preview mode (if supported)
    USE_FILTER_EXT = 0x0008		///< Chooser filter pilots the output file extension (if supported)
  };
  static const char *file_exists_message;
  
  /**
   The constructor. Internally allocates the native widgets.
   Optional \p val presets the type of browser this will be,
   which can also be changed with type().
   */
  Fl_Native_File_Chooser(int val = BROWSE_FILE); // each platorm implements it
  ~Fl_Native_File_Chooser();
  void type(int t);
  int type() const ;
  void options(int o);
  int options() const;
  int count() const;
  const char *filename() const ;
  const char *filename(int i) const ;
  void directory(const char *val) ;
  const char *directory() const;
  void title(const char *t);
  const char* title() const;
  const char *filter() const ;
  void filter(const char *f);
  int filters() const ;
  void filter_value(int i) ;
  int filter_value() const ;
  void preset_file(const char*f) ;
  const char* preset_file() const;
  const char *errmsg() const ;
  int show() ;
  };

/** Represents the interface between FLTK and a native file chooser.
 This class is only for internal use by the FLTK library.
 A platform that wants to provide a native file chooser implements all virtual methods
 of this class. Each platform supported by FLTK must also implement the constructor of the
 Fl_Native_File_Chooser class.
 */
class Fl_Native_File_Chooser_Driver {
protected:
  static void chrcat(char *s, char c);
  static char *strapp(char *s, const char *val);
  static char *strfree(char *val);
  static char *strnew(const char *val);
public:
  Fl_Native_File_Chooser_Driver(int val) {}
  virtual ~Fl_Native_File_Chooser_Driver() {}
  virtual void type(int t) {}
  virtual int type() const  {return 0;}
  virtual void options(int o) {}
  virtual int options() const {return 0;}
  virtual int count() const {return 0;}
  virtual const char *filename() const  {return 0;}
  virtual const char *filename(int i) const  {return 0;}
  virtual void directory(const char *val)  {}
  virtual const char *directory() const {return 0;}
  virtual void title(const char *t) {}
  virtual const char* title() const {return 0;}
  virtual const char *filter() const  {return 0;}
  virtual void filter(const char *f) {}
  virtual int filters() const  {return 0;}
  virtual void filter_value(int i)  {}
  virtual int filter_value() const  {return 0;}
  virtual void preset_file(const char*f)  {}
  virtual const char* preset_file() const {return 0;}
  virtual const char *errmsg() const  {return 0;}
  virtual int show()  {return 1;}
};

/** A cross-platform implementation of Fl_Native_File_Chooser_Driver.
 This implementation uses a Fl_File_Chooser object as file chooser.
 
 Any platform can support the Fl_Native_File_Chooser class by implementing
 its constructor as follows:
 \code
 Fl_Native_File_Chooser::Fl_Native_File_Chooser(int type) {
   platform_fnfc = new Fl_Native_File_Chooser_FLTK_Driver(type);
 }
\endcode
 */
class Fl_Native_File_Chooser_FLTK_Driver : public Fl_Native_File_Chooser_Driver {
private:
  void errmsg(const char *msg);
  int type_fl_file(int val);
  int exist_dialog();
  void parse_filter();
protected:
  int   _btype;			// kind-of browser to show()
  int   _options;		// general options
  int   _nfilters;
  char *_filter;		// user supplied filter
  char *_parsedfilt;		// parsed filter
  int   _filtvalue;		// selected filter
  char *_preset_file;
  char *_prevvalue;		// Returned filename
  char *_directory;
  char *_errmsg;		// error message
  Fl_File_Chooser *_file_chooser;
public:
  Fl_Native_File_Chooser_FLTK_Driver(int val);
  virtual ~Fl_Native_File_Chooser_FLTK_Driver();
  virtual void type(int t);
  virtual int type() const ;
  virtual void options(int o);
  virtual int options() const;
  virtual int count() const;
  virtual const char *filename() const ;
  virtual const char *filename(int i) const ;
  virtual void directory(const char *val) ;
  virtual const char *directory() const;
  virtual void title(const char *t);
  virtual const char* title() const;
  virtual const char *filter() const ;
  virtual void filter(const char *f);
  virtual int filters() const ;
  virtual void filter_value(int i) ;
  virtual int filter_value() const ;
  virtual void preset_file(const char*f) ;
  virtual const char* preset_file() const;
  virtual const char *errmsg() const ;
  virtual int show() ;
};


#endif /*FL_NATIVE_FILE_CHOOSER_H*/

//
// End of "$Id: Fl_Native_File_Chooser.H 11681 2016-04-23 06:27:31Z manolo $".
//