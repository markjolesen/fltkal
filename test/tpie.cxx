//
// Arc and Pie test program for the Fast Light Tool Kit (FLTK).
//
// Copyright 2017-2018 The fltkal authors
// Copyright 2017 by Bill Spitzak and others.
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
#include <fl/fl.h>
#include <fl/win.h>
#include <fl/fl_draw.h>
// resolve window clash with conio
#undef window
#define window _window

class mywin : public Fl_Window
{

public:

    mywin(int w, int h, const char* title= 0) : Fl_Window(w,h,title) {};
    mywin(int x, int y, int w, int h, const char* title = 0) : Fl_Window(x,y,w,h,title) {};

    void draw();

};

void mywin::draw()
{

    Fl_Window::draw();

    int a = x()+10, b = y()+10; fl_color(FL_BLACK); fl_rect(a, b, 100, 100);
    // test fl_arc for full circles
    fl_color(FL_GREEN); fl_rect(a+ 9, b+ 9, 33, 33);
    fl_color(FL_RED); fl_xyline(a+24, b+10, a+27); fl_xyline(a+24, b+40, a+27);
    fl_yxline(a+10, b+24, b+27); fl_yxline(a+40, b+24, b+27);
    fl_color(FL_BLACK); fl_arc(a+10, b+10, 31, 31, 0.0, 360.0);
    // test fl_arc segmet 1
    fl_color(FL_GREEN); fl_rect(a+54, b+ 4, 43, 43);
    fl_rect(a+54, b+4, 18, 18); fl_rect(a+79, b+29, 18, 18);
    fl_color(FL_RED); fl_point(a+55, b+30); fl_point(a+70, b+45);
    fl_point(a+80, b+5); fl_point(a+95, b+20);
    fl_color(FL_BLACK); fl_arc(a+65, b+ 5, 31, 31, -35.0, 125.0);
    // test fl_arc segmet 2
    fl_color(FL_BLACK); fl_arc(a+55, b+15, 31, 31, 145.0, 305.0);
    // test fl_pie for full circles
    fl_color(FL_RED); fl_xyline(a+24, b+60, a+27); fl_xyline(a+24, b+90, a+27);
    fl_yxline(a+10, b+74, b+77); fl_yxline(a+40, b+74, b+77);
    fl_color(FL_GREEN); fl_rect(a+ 9, b+59, 33, 33);
    fl_color(FL_BLACK); fl_pie(a+10, b+60, 31, 31, 0.0, 360.0);
    // test fl_pie segmet 1
    fl_color(FL_GREEN); fl_rect(a+54, b+54, 43, 43);
    fl_rect(a+54, b+54, 18, 18); fl_rect(a+79, b+79, 18, 18);
    fl_point(a+79, b+71); fl_point(a+71, b+79);
    fl_color(FL_RED); fl_point(a+55, b+80); fl_point(a+70, b+95);
    fl_point(a+80, b+55); fl_point(a+95, b+70);
    fl_point(a+81, b+69); fl_point(a+69, b+81);
    fl_color(FL_BLACK); fl_pie(a+65, b+55, 31, 31, -30.0, 120.0);
    // test fl_pie segmet 2
    fl_color(FL_BLACK); fl_pie(a+55, b+65, 31, 31, 150.0, 300.0);
    //---- oval testing (horizontal squish)
    a +=120; b += 0; fl_color(FL_BLACK); fl_rect(a, b, 100, 100);
    fl_color(FL_GREEN);
    fl_rect(a+19, b+9, 63, 33); fl_rect(a+19, b+59, 63, 33);
    fl_color(FL_BLACK);
    fl_arc(a+20, b+10, 61, 31, 0, 360); fl_pie(a+20, b+60, 61, 31, 0, 360);
    //---- oval testing (horizontal squish)
    a += 120; b += 0; fl_color(FL_BLACK); fl_rect(a, b, 100, 100);
    fl_color(FL_GREEN);
    fl_rect(a+9, b+19, 33, 63); fl_rect(a+59, b+19, 33, 63);
    fl_color(FL_BLACK);
    fl_arc(a+10, b+20, 31, 61, 0, 360); fl_pie(a+60, b+20, 31, 61, 0, 360);
}

int main(int argc, char **argv)
{
    mywin* w= new mywin(0,0,600,400, "Window");
    w->begin();
    w->end();
    w->show();
    return Fl::run();
}
