// filechn.cxx
//
// "$Id: Fl_Native_File_Chooser.cxx 12363 2017-07-28 14:06:18Z manolo $"
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


#include <fl/filechn.h>

#if defined(USE_ALLEGRO)
Fl_Native_File_Chooser::Fl_Native_File_Chooser(int val) {
  platform_fnfc = new Fl_Native_File_Chooser_FLTK_Driver(val); // do this to use FLTK's default file chooser
}
#endif

#ifdef FL_PORTING
#  pragma message "Implement a native file chooser (see Fl_Native_File_Chooser_Driver), or use FLTK's chooser, or don't use any chooser"
Fl_Native_File_Chooser::Fl_Native_File_Chooser(int val) {
  //platform_fnfc = new Fl_Native_File_Chooser_FLTK_Driver(val); // do this to use FLTK's default file chooser
  platform_fnfc = 0; // do this so class Fl_Native_File_Chooser does nothing
}
#endif

/** Localizable message */
const char *Fl_Native_File_Chooser::file_exists_message = "File exists. Are you sure you want to overwrite?";

/**
 Destructor.
 Deallocates any resources allocated to this widget.
 */
Fl_Native_File_Chooser::~Fl_Native_File_Chooser() {
  delete platform_fnfc;
}

/**
 Sets the current Fl_Native_File_Chooser::Type of browser.
 */
void Fl_Native_File_Chooser::type(int t) {
  if (platform_fnfc) platform_fnfc->type(t);
}

/**
 Gets the current Fl_Native_File_Chooser::Type of browser.
 */
int Fl_Native_File_Chooser::type() const {
  return platform_fnfc->type();
}

/**
 Sets the platform specific chooser options to \p val.
 \p val is expected to be one or more Fl_Native_File_Chooser::Option flags ORed together.
 Some platforms have OS-specific functions that can be enabled/disabled via this method.
 <P>
 \code
 Flag              Description                                       Win       Mac       Other
 --------------    -----------------------------------------------   -------   -------   -------
 NEW_FOLDER        Shows the 'New Folder' button.                    Ignored   Used      Used
 PREVIEW           Enables the 'Preview' mode by default.            Ignored   Ignored   Used
 SAVEAS_CONFIRM    Confirm dialog if BROWSE_SAVE_FILE file exists.   Used      Used      Used
 USE_FILTER_EXT    Chooser filter pilots the output file extension.  Ignored   Used      Used (GTK)
 \endcode
 */
void Fl_Native_File_Chooser::options(int o) {
  if (platform_fnfc) platform_fnfc->options(o);
}

/**
 Gets the platform specific Fl_Native_File_Chooser::Option flags.
 */
int Fl_Native_File_Chooser::options() const {
  return platform_fnfc->options();
}

/**
 Returns the number of filenames (or directory names) the user selected.
 <P>
 \b Example:
 \code
 if ( fnfc->show() == 0 ) {
     // Print all filenames user selected
     for (int n=0; n<fnfc->count(); n++ ) {
         printf("%d) '%s'\n", n, fnfc->filename(n));
     }
 }
 \endcode
 */
int Fl_Native_File_Chooser::count() const {
  return platform_fnfc->count();
}

/**
 Return the filename the user chose.
 Use this if only expecting a single filename.
 If more than one filename is expected, use filename(int) instead.
 Return value may be "" if no filename was chosen (eg. user cancelled).
 */
const char *Fl_Native_File_Chooser::filename() const {
  return platform_fnfc->filename();
}

/**
 Return one of the filenames the user selected.
 Use count() to determine how many filenames the user selected.
 <P>
 \b Example:
 \code
 if ( fnfc->show() == 0 ) {
     // Print all filenames user selected
     for (int n=0; n<fnfc->count(); n++ ) {
         printf("%d) '%s'\n", n, fnfc->filename(n));
     }
 }
 \endcode
 */
const char *Fl_Native_File_Chooser::filename(int i) const {
  return platform_fnfc->filename(i);
}

/**
 Preset the directory the browser will show when opened.
 If \p val is NULL, or no directory is specified, the chooser will attempt
 to use the last non-cancelled folder.
 */
void Fl_Native_File_Chooser::directory(const char *val) {
  if (platform_fnfc) platform_fnfc->directory(val);
}

/**
 Returns the current preset directory() value.
 */
const char *Fl_Native_File_Chooser::directory() const {
  return platform_fnfc->directory();
}

/**
 Set the title of the file chooser's dialog window.
 Can be NULL if no title desired.
 The default title varies according to the platform, so you are advised to set the title explicitly.
 */
void Fl_Native_File_Chooser::title(const char *t) {
  if (platform_fnfc) platform_fnfc->title(t);
}

/**
 Get the title of the file chooser's dialog window.
 Return value may be NULL if no title was set.
 */
const char* Fl_Native_File_Chooser::title() const {
  return platform_fnfc->title();
}

/**
 Returns the filter string last set.
 Can be NULL if no filter was set.
 */
const char *Fl_Native_File_Chooser::filter() const {
  return platform_fnfc->filter();
}

/**
 Sets the filename filters used for browsing.
 The default is NULL, which browses all files.
 <P>
 The filter string can be any of:
 <P>
 - A single wildcard (eg. "*.txt")
 - Multiple wildcards (eg. "*.{cxx,h,H}")
 - A descriptive name followed by a "\t" and a wildcard (eg. "Text Files\t*.txt")
 - A list of separate wildcards with a "\n" between each (eg. "*.{cxx,H}\n*.txt")
 - A list of descriptive names and wildcards (eg. "C++ Files\t*.{cxx,H}\nTxt Files\t*.txt")
 <P>
 The format of each filter is a wildcard, or an optional user description
 followed by '\\t' and the wildcard.
 <P>
 On most platforms, each filter is available to the user via a pulldown menu
 in the file chooser. The 'All Files' option is always available to the user.
 */
void Fl_Native_File_Chooser::filter(const char *f) {
  if (platform_fnfc) platform_fnfc->filter(f);
}

/**
 Gets how many filters were available, not including "All Files"
 */
int Fl_Native_File_Chooser::filters() const {
  return platform_fnfc->filters();
}

/**
 Sets which filter will be initially selected.
 
 The first filter is indexed as 0.
 If filter_value()==filters(), then "All Files" was chosen.
 If filter_value() > filters(), then a custom filter was set.
 */
void Fl_Native_File_Chooser::filter_value(int i) {
  platform_fnfc->filter_value(i);
}

/**
 Returns which filter value was last selected by the user.
 This is only valid if the chooser returns success.
 */
int Fl_Native_File_Chooser::filter_value() const {
  return platform_fnfc->filter_value();
}

/**
 Sets the default filename for the chooser.
 Use directory() to set the default directory.
 Mainly used to preset the filename for save dialogs,
 and on most platforms can be used for opening files as well.
 */
void Fl_Native_File_Chooser::preset_file(const char*f) {
  if (platform_fnfc) platform_fnfc->preset_file(f);
}

/**
 Get the preset filename.
 */
const char* Fl_Native_File_Chooser::preset_file() const {
  return platform_fnfc->preset_file();
}

/**
 Returns a system dependent error message for the last method that failed.
 This message should at least be flagged to the user in a dialog box, or to some kind of error log.
 Contents will be valid only for methods that document errmsg() will have info on failures.
 */
const char *Fl_Native_File_Chooser::errmsg() const {
  return platform_fnfc->errmsg();
}

/**
 Post the chooser's dialog. Blocks until dialog has been completed or cancelled.
 \returns
 - 0  -- user picked a file
 - 1  -- user cancelled
 - -1 -- failed; errmsg() has reason
 */
int Fl_Native_File_Chooser::show() {
  return platform_fnfc ? platform_fnfc->show() : 1;
}

// COPY A STRING WITH 'new'
//    Value can be NULL
//
char *Fl_Native_File_Chooser_Driver::strnew(const char *val) {
  if ( val == NULL ) return(NULL);
  char *s = new char[strlen(val)+1];
  strcpy(s, val);
  return(s);
}

// FREE STRING CREATED WITH strnew(), NULLS OUT STRING
//    Value can be NULL
//
char *Fl_Native_File_Chooser_Driver::strfree(char *val) {
  if ( val ) delete [] val;
  return(NULL);
}

// 'DYNAMICALLY' APPEND ONE STRING TO ANOTHER
//    Returns newly allocated string, or NULL
//    if s && val == NULL.
//    's' can be NULL; returns a strnew(val).
//    'val' can be NULL; s is returned unmodified.
//
//    Usage:
//	char *s = strnew("foo");	// s = "foo"
//      s = strapp(s, "bar");		// s = "foobar"
//
char *Fl_Native_File_Chooser_Driver::strapp(char *s, const char *val) {
  if ( ! val ) {
    return(s);			// Nothing to append? return s
  }
  if ( ! s ) {
    return(strnew(val));	// New string? return copy of val
  }
  char *news = new char[strlen(s)+strlen(val)+1];
  strcpy(news, s);
  strcat(news, val);
  delete [] s;			// delete old string
  return(news);			// return new copy
}

// APPEND A CHARACTER TO A STRING
//     This does NOT allocate space for the new character.
//
void Fl_Native_File_Chooser_Driver::chrcat(char *s, char c) {
  char tmp[2] = { c, '\0' };
  strcat(s, tmp);
}

//
// End of "$Id: Fl_Native_File_Chooser.cxx 12363 2017-07-28 14:06:18Z manolo $".
//
