// treearr.cxx
//
// "$Id: Fl_Tree_Item_Array.cxx 11602 2016-04-13 19:18:56Z manolo $"
//
//////////////////////
// Fl_Tree_Item_Array.cxx
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fl/treearr.h>
#include <fl/treeitem.h>


/// Constructor; creates an empty array.
///
///     The optional 'chunksize' can be specified to optimize
///     memory allocation for potentially large arrays. Default chunksize is 10.
/// 
Fl_Tree_Item_Array::Fl_Tree_Item_Array(int new_chunksize) {
  _items     = 0;
  _total     = 0;
  _size      = 0;
  _flags     = 0;
  _chunksize = new_chunksize;
}

/// Destructor. Calls each item's destructor, destroys internal _items array.
Fl_Tree_Item_Array::~Fl_Tree_Item_Array() {
  clear();
}

/// Copy constructor. Makes new copy of array, with new instances of each item.
Fl_Tree_Item_Array::Fl_Tree_Item_Array(const Fl_Tree_Item_Array* o) {
  _items = (Fl_Tree_Item**)malloc(o->_size * sizeof(Fl_Tree_Item*));
  _total     = 0;
  _size      = o->_size;
  _chunksize = o->_chunksize;
  _flags     = o->_flags;
  for ( int t=0; t<o->_total; t++ ) {
    if ( _flags & MANAGE_ITEM ) {
      _items[t] = new Fl_Tree_Item(o->_items[t]);	// make new copy of item
      ++_total;
      _items[t]->update_prev_next(t);			// update uses _total's current value
    } else {
      _items[t] = o->_items[t];				// copy ptr only
      ++_total;
    }
  }
}

/// Clear the entire array.
///
///     Each item will be deleted (destructors will be called),
///     and the array will be cleared. total() will return 0.
///
void Fl_Tree_Item_Array::clear() {
  if ( _items ) {
    for ( int t=0; t<_total; t++ ) {
      if ( _flags & MANAGE_ITEM )
      {
        delete _items[t];
	_items[t] = 0;
      }
    }
    free((void*)_items); _items = 0;
  }
  _total = _size = 0;
}

// Internal: Enlarge the items array.
//
//    Adjusts size/items memory allocation as needed.
//    Does NOT change total.
//
void Fl_Tree_Item_Array::enlarge(int count) {
  int newtotal = _total + count;	// new total
  if ( newtotal >= _size ) {		// more than we have allocated?
    if ( (newtotal/150) > _chunksize ) _chunksize *= 10;
    // Increase size of array
    int newsize = _size + _chunksize;
    Fl_Tree_Item **newitems = (Fl_Tree_Item**)malloc(newsize * sizeof(Fl_Tree_Item*));
    if ( _items ) { 
      // Copy old array -> new, delete old
      memmove(newitems, _items, _size * sizeof(Fl_Tree_Item*));
      free((void*)_items); _items = 0;
    }
    // Adjust items/sizeitems
    _items = newitems;
    _size = newsize;
  }
}

/// Insert an item at index position \p pos.
///
///     Handles enlarging array if needed, total increased by 1.
///     If \p pos == total(), an empty item is appended to the array.
///
void Fl_Tree_Item_Array::insert(int pos, Fl_Tree_Item *new_item) {
  enlarge(1);
  // printf("*** POS=%d TOTAL-1=%d NITEMS=%d\n", pos, _total-1, (_total-pos));
  if ( pos <= (_total - 1) ) {	// need to move memory around?
    int nitems = _total - pos;
    memmove(&_items[pos+1], &_items[pos], sizeof(Fl_Tree_Item*) * nitems);
  } 
  _items[pos] = new_item;
  _total++;
  if ( _flags & MANAGE_ITEM )
  {
    _items[pos]->update_prev_next(pos);	// adjust item's prev/next and its neighbors
  }
}

/// Add an item* to the end of the array.
///
///     Assumes the item was created with 'new', and will remain
///     allocated.. Fl_Tree_Item_Array will handle calling the
///     item's destructor when the array is cleared or the item remove()'ed.
///
void Fl_Tree_Item_Array::add(Fl_Tree_Item *val) {
  insert(_total, val);
}

/// Replace the item at \p index with \p newitem.
///
/// Old item at index position will be destroyed,
/// and the new item will take it's place, and stitched into the linked list.
///
void Fl_Tree_Item_Array::replace(int index, Fl_Tree_Item *newitem) {
  if ( _items[index] ) {			// delete if non-zero
    if ( _flags & MANAGE_ITEM )
      // Destroy old item
      delete _items[index];
  }
  _items[index] = newitem;			// install new item
  if ( _flags & MANAGE_ITEM )
  {
    // Restitch into linked list
    _items[index]->update_prev_next(index);
  }
}

/// Remove the item at \param[in] index from the array.
///
///     The item will be delete'd (if non-NULL), so its destructor will be called.
///
void Fl_Tree_Item_Array::remove(int index) {
  if ( _items[index] ) {			// delete if non-zero
    if ( _flags & MANAGE_ITEM )
      delete _items[index];
  }
  _items[index] = 0;
  _total--;
  for ( int i=index; i<_total; i++ ) {		// reshuffle the array
    _items[i] = _items[i+1];
  }
  if ( _flags & MANAGE_ITEM )
  {
    if ( index < _total ) {			// removed item not last?
      _items[index]->update_prev_next(index);	// update next item's prev/next and neighbors
    } else if ( ((index-1) >= 0) &&		// removed item IS last?
	      ((index-1) < _total)) {
      _items[index-1]->update_prev_next(index-1);// update prev item's prev/next and neighbors
    }
  }
}

/// Remove the item from the array.
///
///     \returns 0 if removed, or -1 if the item was not in the array.
///
int Fl_Tree_Item_Array::remove(Fl_Tree_Item *item) {
  for ( int t=0; t<_total; t++ ) {
    if ( item == _items[t] ) {
      remove(t);
      return(0);
    }
  }
  return(-1);
}

/// Swap the two items at index positions \p ax and \p bx.
void Fl_Tree_Item_Array::swap(int ax, int bx) {
  Fl_Tree_Item *asave = _items[ax];
  _items[ax] = _items[bx];
  _items[bx] = asave;
  if ( _flags & MANAGE_ITEM )
  {
    // Adjust prev/next ptrs
    _items[ax]->update_prev_next(ax);
    _items[bx]->update_prev_next(bx);
  }
}

/// Move item at 'from' to new position 'to' in the array.
/// Due to how the moving an item shuffles the array around,
/// a positional 'move' implies things that may not be obvious:
/// - When 'from' moved lower in tree, appears BELOW item that was at 'to'.
/// - When 'from' moved higher in tree, appears ABOVE item that was at 'to'.
///
///     \returns 0 on success, -1 on range error (e.g. if \p 'to' or \p 'from' out of range)
///
int Fl_Tree_Item_Array::move(int to, int from) {
  if ( from == to ) return 0;    // nop
  if ( to<0 || to>=_total || from<0 || from>=_total ) return -1;
  Fl_Tree_Item *item = _items[from];
  // Remove item..
  if ( from < to )
    for ( int t=from; t<to && t<(_total+1); t++ )
      _items[t] = _items[t+1];
  else
    for ( int t=from; t>to && t>0; t-- )
      _items[t] = _items[t-1];
  // Move to new position
  _items[to] = item;
  // Update all children
  for ( int r=0; r<_total; r++ )	// XXX: excessive to do all children,
    _items[r]->update_prev_next(r);	// XXX: but avoids weird boundary issues
  return 0;
}

/// Deparent item at \p 'pos' from our list of children.
/// Similar to a remove() without the destruction of the item.
/// This creates an orphaned item (still allocated, has no parent)
/// which soon after is typically reparented elsewhere.
///
///     \returns 0 on success, -1 on error (e.g. if \p 'pos' out of range)
///
int Fl_Tree_Item_Array::deparent(int pos) {
  if ( pos>=_total || pos<0 ) return -1;
  // Save item being deparented, and its two nearest siblings
  Fl_Tree_Item *item = _items[pos];
  Fl_Tree_Item *prev = item->prev_sibling();
  Fl_Tree_Item *next = item->next_sibling();
  // Remove from parent's list of children
  _total -= 1;
  for ( int t=pos; t<_total; t++ )
    _items[t] = _items[t+1];            // delete, no destroy
  // Now an orphan: remove association with old parent and siblings
  item->update_prev_next(-1);           // become an orphan
  // Adjust bereaved siblings
  if ( prev ) prev->update_prev_next(pos-1);
  if ( next ) next->update_prev_next(pos);
  return 0;
}

/// Reparent specified item as a child of ourself.
/// Typically 'newchild' was recently orphaned with deparent().
///
///     \returns 0 on success, -1 on error (e.g. if \p 'pos' out of range)
///
int Fl_Tree_Item_Array::reparent(Fl_Tree_Item *item, Fl_Tree_Item* newparent, int pos) {
  if ( pos<0 || pos>_total ) return -1;
  // Add item to new parent
  enlarge(1);
  _total += 1;
  for ( int t=_total-1; t>pos; --t )    // shuffle array to make room for new entry
    _items[t] = _items[t-1];
  _items[pos] = item;                   // insert new entry
  // Attach to new parent and siblings
  _items[pos]->parent(newparent);       // reparent (update_prev_next() needs this)
  _items[pos]->update_prev_next(pos);   // find new siblings
  return 0;
}

//
// End of "$Id: Fl_Tree_Item_Array.cxx 11602 2016-04-13 19:18:56Z manolo $".
//
