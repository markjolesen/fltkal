/*
flCalc v 0.1
Copyright (C) 2008 Andy Le Galle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    This program uses muParser muparser.sourceforge.net
*/

#ifndef _FL_CALCINPUT_
#define _FL_CALCINPUT_

#if !defined(__DJGPP__)
#include <FL/Fl.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Window.H>
#include <FL/fl_draw.H>
#else
#include <fl/fl.h>
#include <fl/inpvalue.h>
#include <fl/box.h>
#include <fl/winmenu.h>
#include <fl/fl_draw.h>
#endif

#include <iostream>
#include <list>
#include "muparser/parser.h"

using namespace mu;
using namespace std;

class PopupWindow : public Fl_Menu_Window {
    Fl_Box *output;
    
    void SizeToText() {
        int W=0, H=0;
        fl_font(output->labelfont(), output->labelsize());
        fl_measure(output->label(), W, H, 0);
        resize(x(), y(), W+10, H+10);                          
        output->resize(0, 0, W+10, H+10);
    }
public:
    PopupWindow() : Fl_Menu_Window(10,10) {
      output = new Fl_Box(0,0, w(), h());                    
        output->box(FL_UP_BOX);                                 
        end();
        hide();
        border(0);                                              
        output->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);           
        output->label("No text defined");                       
        SizeToText();
    }
    
    void text(const char*s) {
        output->label(s);                                       
        SizeToText();                                           
    }
    
    void popup() {
        position(Fl::event_x_root(), Fl::event_y_root());      
        show();
    }

    int handle(int e) {
        int ret = Fl_Window::handle(e);
        switch (e) {
	case    FL_PUSH: hide(); return(1);
        }
        return(ret);
    }
};

class FL_CalcInput : public Fl_Input
{
 public:
  FL_CalcInput (int x, int y, int w, int h, const char *label);
  int handle(int event);
  void right_click(FL_CalcInput *w, void *v);

  Parser *p;
  vector<string> history;
  int hist_pos;

  PopupWindow *_about;
  PopupWindow *_help;
}; 

#endif
