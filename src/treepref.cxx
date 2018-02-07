// treepref.cxx
//
// "$Id: Fl_Tree_Prefs.cxx 11606 2016-04-14 20:58:20Z manolo $"
//
//////////////////////
// Fl_Tree_Prefs.cxx
//////////////////////
//
// Fl_Tree -- This file is part of the Fl_Tree widget for FLTK
// Copyright 2017-2018 The fltkal authors
// Copyright (C) 2009-2010 by Greg Ercolano.
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

#include "cfg_lib.h"

#include <fl/drvsys.h>
#include <fl/fl.h>
#include <fl/pixmap.h>
#include <fl/treepref.h>

#ifdef FL_CFG_WIN_COCOA
#include "drivers/Darwin/Fl_Darwin_System_Driver.H"
#endif

// INTERNAL: BUILT IN OPEN/STOW XPMS
//    These can be replaced via prefs.openicon()/closeicon()
//

#ifdef FL_CFG_WIN_COCOA

const char * const Fl_Darwin_System_Driver::tree_open_xpm_darwin[] = {
  "11 11 2 1",
  ".  c None",
  "@  c #000000",
  "...@.......",
  "...@@......",
  "...@@@.....",
  "...@@@@....",
  "...@@@@@...",
  "...@@@@@@..",
  "...@@@@@...",
  "...@@@@....",
  "...@@@.....",
  "...@@......",
  "...@......."
};

const char * const Fl_Darwin_System_Driver::tree_close_xpm_darwin[] = {
  "11 11 2 1",
  ".  c None",
  "@  c #000000",
  "...........",
  "...........",
  "...........",
  "@@@@@@@@@@@",
  ".@@@@@@@@@.",
  "..@@@@@@@..",
  "...@@@@@...",
  "....@@@....",
  ".....@.....",
  "...........",
  "..........."
};

Fl_Pixmap *Fl_Darwin_System_Driver::tree_openpixmap() {
  static Fl_Pixmap *pixmap = new Fl_Pixmap(tree_open_xpm_darwin);
  return pixmap;
}

Fl_Pixmap *Fl_Darwin_System_Driver::tree_closepixmap() {
  static Fl_Pixmap *pixmap = new Fl_Pixmap(tree_close_xpm_darwin);
  return pixmap;
}

int Fl_Darwin_System_Driver::tree_connector_style() {
  return FL_TREE_CONNECTOR_NONE;
}

#endif // FL_CFG_WIN_COCOA

const char * const Fl_System_Driver::tree_open_xpm[] = {
  "11 11 3 1",
  ".	c #fefefe",
  "#	c #444444",
  "@	c #000000",
  "###########",
  "#.........#",
  "#.........#",
  "#....@....#",
  "#....@....#",
  "#..@@@@@..#",
  "#....@....#",
  "#....@....#",
  "#.........#",
  "#.........#",
  "###########"
};

const char * const Fl_System_Driver::tree_close_xpm[] = {
"11 11 3 1",
".	c #fefefe",
"#	c #444444",
"@	c #000000",
"###########",
"#.........#",
"#.........#",
"#.........#",
"#.........#",
"#..@@@@@..#",
"#.........#",
"#.........#",
"#.........#",
"#.........#",
"###########"
};


Fl_Pixmap *Fl_System_Driver::tree_openpixmap() {
  static Fl_Pixmap *pixmap = new Fl_Pixmap(tree_open_xpm);
  return pixmap;
}

Fl_Pixmap *Fl_System_Driver::tree_closepixmap() {
  static Fl_Pixmap *pixmap = new Fl_Pixmap(tree_close_xpm);
  return pixmap;
}

int Fl_System_Driver::tree_connector_style() {
  return FL_TREE_CONNECTOR_DOTTED;
}


/// Sets the default icon to be used as the 'open' icon
/// when items are add()ed to the tree.
/// This overrides the built in default '[+]' icon.
///
/// \param[in] val -- The new image, or zero to use the default [+] icon.
///
void Fl_Tree_Prefs::openicon(Fl_Image *val) {
  _openimage = val ? val : Fl::system_driver()->tree_openpixmap();
  // Update deactivated version of icon..
  if ( _opendeimage ) delete _opendeimage;
  if ( _openimage ) {
    _opendeimage = _openimage->copy();
    _opendeimage->inactive();
  } else {
    _opendeimage = 0;
  }
}

/// Sets the icon to be used as the 'close' icon.
/// This overrides the built in default '[-]' icon.
///
/// \param[in] val -- The new image, or zero to use the default [-] icon.
///
void Fl_Tree_Prefs::closeicon(Fl_Image *val) {
  _closeimage = val ? val : Fl::system_driver()->tree_closepixmap();
  // Update deactivated version of icon..
  if ( _closedeimage ) delete _closedeimage;
  if ( _closeimage ) {
    _closedeimage = _closeimage->copy();
    _closedeimage->inactive();
  } else {
    _closedeimage = 0;
  }
}

/// Fl_Tree_Prefs constructor
Fl_Tree_Prefs::Fl_Tree_Prefs() {
  _labelfont              = FL_HELVETICA;
  _labelsize              = FL_NORMAL_SIZE;
  _marginleft             = 6;
  _margintop              = 3;
  _marginbottom           = 20;
  _openchild_marginbottom = 0;
  _usericonmarginleft     = 3;
  _labelmarginleft        = 3;
  _widgetmarginleft       = 3;
  _linespacing            = 0;
  _labelfgcolor           = FL_BLACK;
  _labelbgcolor           = 0xffffffff;		// we use this as 'transparent'
  _connectorcolor         = Fl_Color(43);
  _connectorstyle         = (Fl_Tree_Connector)Fl::system_driver()->tree_connector_style();
  _openimage              = Fl::system_driver()->tree_openpixmap();
  _closeimage             = Fl::system_driver()->tree_closepixmap();
  _userimage              = 0;
  _opendeimage = _openimage->copy();
  _opendeimage->inactive();
  _closedeimage = _closeimage->copy();
  _closedeimage->inactive();
  _userdeimage            = 0;
  _showcollapse           = 1;
  _showroot               = 1;
  _connectorwidth         = 17;
  _sortorder              = FL_TREE_SORT_NONE;
  _selectbox              = FL_FLAT_BOX;
  _selectmode             = FL_TREE_SELECT_SINGLE;
  _itemreselectmode       = FL_TREE_SELECTABLE_ONCE;
  _itemdrawmode           = FL_TREE_ITEM_DRAW_DEFAULT;
  _itemdrawcallback       = 0;
  _itemdrawuserdata       = 0;
  // Let fltk's current 'scheme' affect defaults
  if (Fl::is_scheme("gtk+")) {
    _selectbox = _FL_GTK_THIN_UP_BOX;
  } else if (Fl::is_scheme("plastic")) {
    _selectbox = _FL_PLASTIC_THIN_UP_BOX;
  }
}

/// Fl_Tree_Prefs destructor
Fl_Tree_Prefs::~Fl_Tree_Prefs() {
  if ( _opendeimage )  delete _opendeimage;
  if ( _closedeimage ) delete _closedeimage;
  if ( _userdeimage )  delete _userdeimage;
}

//
// End of "$Id: Fl_Tree_Prefs.cxx 11606 2016-04-14 20:58:20Z manolo $".
//
