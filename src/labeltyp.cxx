// labeltyp.cxx
//
// "$Id: fl_labeltype.cxx 12181 2017-02-27 17:00:41Z AlbrechtS $"
//
// Label drawing routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2010 by Bill Spitzak and others.
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

// Drawing code for the (one) common label types.
// Other label types (symbols) are in their own source files
// to avoid linking if not used.

#include <fl/fl.h>
#include <fl/widget.h>
#include <fl/group.h>
#include <fl/fl_draw.h>
#include <fl/img.h>

void
fl_no_label(const Fl_Label*,int,int,int,int,Fl_Align) {}

void
fl_normal_label(const Fl_Label* o, int X, int Y, int W, int H, Fl_Align align)
{
  fl_font(o->font, o->size);
  fl_color((Fl_Color)o->color);
  fl_draw(o->value, X, Y, W, H, align, o->image);
}

void
fl_normal_measure(const Fl_Label* o, int& W, int& H) {
  fl_font(o->font, o->size);
  fl_measure(o->value, W, H);
  if (o->image) {
    int iw = o->image->w(), ih = o->image->h();
    if (o->align_ & FL_ALIGN_IMAGE_BACKDROP) {		// backdrop: ignore
      // ignore backdrop image for calculation
    } else if (o->align_ & FL_ALIGN_IMAGE_NEXT_TO_TEXT) { // text and image side by side
      W += iw;
      if (ih > H) H = ih;
    } else {
      if (iw > W) W = iw;
      H += ih;
    }
  }
}

#define MAX_LABELTYPE 16

static Fl_Label_Draw_F* table[MAX_LABELTYPE] = {
  fl_normal_label,
  fl_no_label,
  fl_normal_label,	// _FL_SHADOW_LABEL,
  fl_normal_label,	// _FL_ENGRAVED_LABEL,
  fl_normal_label,	// _FL_EMBOSSED_LABEL,
  fl_no_label,		// _FL_MULTI_LABEL,
  fl_no_label,		// _FL_ICON_LABEL,
  // FL_FREE_LABELTYPE+n:
  fl_no_label, fl_no_label, fl_no_label,
  fl_no_label, fl_no_label, fl_no_label,
  fl_no_label, fl_no_label, fl_no_label
};

static Fl_Label_Measure_F* measure[MAX_LABELTYPE];

/** Sets the functions to call to draw and measure a specific labeltype. */
void Fl::set_labeltype(Fl_Labeltype t,Fl_Label_Draw_F* f,Fl_Label_Measure_F*m) 
{
  table[t] = f; measure[t] = m;
}

////////////////////////////////////////////////////////////////

/** Draws a label with arbitrary alignment in an arbitrary box. */
void Fl_Label::draw(int X, int Y, int W, int H, Fl_Align align) const {
  if (!value && !image) return;
  table[type](this, X, Y, W, H, align);
}
/** 
    Measures the size of the label.
    \param[in,out] W, H : this is the requested size for the label text plus image;
         on return, this will contain the size needed to fit the label
*/
void Fl_Label::measure(int& W, int& H) const {
  if (!value && !image) {
    W = H = 0;
    return;
  }

  Fl_Label_Measure_F* f = ::measure[type]; if (!f) f = fl_normal_measure;
  f(this, W, H);
}

/** Draws the widget's label at the defined label position.
    This is the normal call for a widget's draw() method.
 */
void Fl_Widget::draw_label() const {
  int X = x_+Fl::box_dx(box());
  int W = w_-Fl::box_dw(box());
  if (W > 11 && align()&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) {X += 3; W -= 6;}
  draw_label(X, y_+Fl::box_dy(box()), W, h_-Fl::box_dh(box()));
}

/** Draws the label in an arbitrary bounding box.
    draw() can use this instead of draw_label(void) to change the bounding box
 */
void Fl_Widget::draw_label(int X, int Y, int W, int H) const {
  // quit if we are not drawing a label inside the widget:
  if ((align()&15) && !(align() & FL_ALIGN_INSIDE)) return;
  draw_label(X,Y,W,H,align());
}

/** Draws the label in an arbitrary bounding box with an arbitrary alignment.
    Anybody can call this to force the label to draw anywhere.
 */
void Fl_Widget::draw_label(int X, int Y, int W, int H, Fl_Align a) const {
  if (flags()&SHORTCUT_LABEL) fl_draw_shortcut = 1;
  Fl_Label l1 = label_;
  if (!active_r()) {
    l1.color = fl_inactive((Fl_Color)l1.color);
    if (l1.deimage) l1.image = l1.deimage;
  }
  l1.draw(X,Y,W,H,a);
  fl_draw_shortcut = 0;
}

// include these vars here so they can be referenced without including
// Fl_Input_ code:
#include <fl/input_.h>

//
// End of "$Id: fl_labeltype.cxx 12181 2017-02-27 17:00:41Z AlbrechtS $".
//