// treearr.h
//
// "$Id: Fl_Tree_Item_Array.H 11679 2016-04-23 04:30:39Z manolo $"
//
//////////////////////////
// FL/Fl_Tree_Item_Array.H
//////////////////////////
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
#ifndef _FL_TREE_ITEM_ARRAY_H
#define _FL_TREE_ITEM_ARRAY_H

#include <fl/fl.h>
#include "export.h"

class FL_EXPORT Fl_Tree_Item;	// forward decl must *precede* first doxygen comment block
				// or doxygen will not document our class..


///
/// \file
/// \brief This file defines a class that manages an array of Fl_Tree_Item pointers.
///

/// \brief Manages an array of Fl_Tree_Item pointers.
///
/// Because FLTK 1.x.x. has mandated that templates and STL not be used,
/// we use this class to dynamically manage the arrays.
///
/// None of the methods do range checking on index values; the caller
/// must be sure that index values are within the range 0<index<total()
/// (unless otherwise noted).
///

class FL_EXPORT Fl_Tree_Item_Array {
  Fl_Tree_Item **_items;	// items array
  int _total;			// #items in array
  int _size;			// #items *allocated* for array
  int _chunksize;		// #items to enlarge mem allocation
  enum {
    MANAGE_ITEM = 1,		///> manage the Fl_Tree_Item's internals (internal use only)
  };
  char _flags;			// flags to control behavior
  void enlarge(int count);
public:
  Fl_Tree_Item_Array(int new_chunksize = 10);		// CTOR
  ~Fl_Tree_Item_Array();				// DTOR
  Fl_Tree_Item_Array(const Fl_Tree_Item_Array *o);	// COPY CTOR
  /// Return the item and index \p i.
  Fl_Tree_Item *operator[](int i) {
    return(_items[i]);
  }
  /// Const version of operator[](int i)
  const Fl_Tree_Item *operator[](int i) const {
    return(_items[i]);
  }
  /// Return the total items in the array, or 0 if empty.
  int total() const {
    return(_total);
  }
  /// Swap the two items at index positions \p ax and \p bx.
  void swap(int ax, int bx);
  int move(int to, int from);
  int deparent(int pos);
  int reparent(Fl_Tree_Item *item, Fl_Tree_Item *newparent, int pos);
  void clear();
  void add(Fl_Tree_Item *val);
  void insert(int pos, Fl_Tree_Item *new_item);
  void replace(int pos, Fl_Tree_Item *new_item);
  void remove(int index);
  int  remove(Fl_Tree_Item *item);
  /// Option to control if Fl_Tree_Item_Array's destructor will also destroy the Fl_Tree_Item's.
  /// If set: items and item array is destroyed. 
  /// If clear: only the item array is destroyed, not items themselves.
  void manage_item_destroy(int val) {
    if ( val ) _flags |= MANAGE_ITEM; else _flags &= ~MANAGE_ITEM;
  }
  int manage_item_destroy() const {
    return _flags & MANAGE_ITEM ? 1 : 0;
  }
};

#endif /*_FL_TREE_ITEM_ARRAY_H*/

//
// End of "$Id: Fl_Tree_Item_Array.H 11679 2016-04-23 04:30:39Z manolo $".
//
