// plugin.h
//
// "$Id: Fl_Plugin.H 12196 2017-03-13 23:31:38Z AlbrechtS $"
//
// A Plugin system for FLTK, implemented in Fl_Preferences.cxx.
//
// Copyright 2017-2018 The fltkal authors
// Copyright 2002-2010 by Matthias Melcher.
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

/* \file
   Fl_Plugin class . */

#ifndef Fl_Plugin_H
#  define Fl_Plugin_H

#  include "pref.h"


/**
 \brief Fl_Plugin allows link-time and run-time integration of binary modules.
 
 Fl_Plugin and Fl_Plugin_Manager provide a small and simple solution for
 linking C++ classes at run-time, or optionally linking modules at compile
 time without the need to change the main application.

 Fl_Plugin_Manager uses static initialisation to create the plugin interface
 early during startup. Plugins are stored in a temporary database, organized
 in classes.
 
 Plugins should derive a new class from Fl_Plugin as a base:
 \code
 class My_Plugin : public Fl_Plugin {
 public:
   My_Plugin() : Fl_Plugin("effects", "blur") { }
   void do_something(...);
 };
 My_Plugin blur_plugin();
 \endcode
 
 Plugins can be put into modules and either linked before distribution, or loaded
 from dynamically linkable files. An Fl_Plugin_Manager is used to list and 
 access all currently loaded plugins.
 \code
 Fl_Plugin_Manager mgr("effects");
 int i, n = mgr.plugins();
 for (i=0; i<n; i++) {
   My_Plugin *pin = (My_Plugin*)mgr.plugin(i);
   pin->do_something();
 }
 \endcode
 */
class FL_EXPORT Fl_Plugin  {
  Fl_Preferences::ID id;
public:
  Fl_Plugin(const char *klass, const char *name);
  virtual ~Fl_Plugin();
};


/**
 \brief Fl_Plugin_Manager manages link-time and run-time plugin binaries.
 \see Fl_Plugin
 */
class FL_EXPORT Fl_Plugin_Manager : public Fl_Preferences {
public:
  Fl_Plugin_Manager(const char *klass);
  ~Fl_Plugin_Manager();
  
  /** \brief Return the number of plugins in the klass.
   */
  int plugins() { return groups(); }
  Fl_Plugin *plugin(int index);
  Fl_Plugin *plugin(const char *name);
  Fl_Preferences::ID addPlugin(const char *name, Fl_Plugin *plugin);
  
  static void removePlugin(Fl_Preferences::ID id);
  static int load(const char *filename);
  static int loadAll(const char *filepath, const char *pattern=0);
};


#endif // !Fl_Preferences_H

//
// End of "$Id: Fl_Plugin.H 12196 2017-03-13 23:31:38Z AlbrechtS $".
//
