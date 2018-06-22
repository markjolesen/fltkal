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


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "main.h"
#include "calcinp.h"

#if !defined(__DJGPP__)
#include <FL/fl_ask.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu.H>
#else
#include <fl/fl_ask.h>
#include <fl/fl.h>
#include <fl/win.h>
#include <fl/menu.h>
#endif

void handle_menu(Fl_Widget *w, void *v);

FL_CalcInput::FL_CalcInput(int x, int y, int w, int h, const char *label = 0)
 : Fl_Input (x,y,w,h,label) {
  p = new Parser;
  p->DefineConst("pi", 3.1415926535897932384626433832795028841971693993751058209749445923078164062f);
  p->DefineConst("e", 2.718281828459045f);
  hist_pos = 0;
}

int FL_CalcInput::handle(int event)
{
switch(event) {
  case FL_KEYBOARD:
    if ((Fl::event_key()==FL_Enter)||(Fl::event_key()==FL_KP_Enter)) {
      
	p->SetExpr(this->value());
	try
	  {
	    stringstream s;
	    s << p->Eval();
	    history.push_back(this->value());
	    hist_pos = history.size();
	    this->value(s.str().c_str());
	  }
	catch (Parser::exception_type &e)
	  {
	    stringstream s;
	    s << e.GetMsg() << endl;
	    fl_message(s.str().c_str());
	    return 1;
	  }
            
      return 1;
    }
    else if (Fl::event_key()==FL_Up) {
      if (!history.empty()){
	hist_pos--;
	if (hist_pos<0) { hist_pos=0; }
	this->value(history.at(hist_pos).c_str());
	return 1;
      }
    }
    else if (Fl::event_key()==FL_Down) {
      if (!history.empty()){
	hist_pos++;
	if (hist_pos>history.size()-1) { hist_pos=history.size()-1;  return 1; }
	this->value(history.at(hist_pos).c_str());
	return 1;
      }
    }
    else if (Fl::event_key()==FL_Page_Down) {
      if (!history.empty()){
	hist_pos = history.size()-1;
	this->value(history.at(hist_pos).c_str());
	return 1;
      }
    }
    else if (Fl::event_key()==FL_Page_Up) {
      if (!history.empty()){
	hist_pos = 0;
	this->value(history.at(hist_pos).c_str());
	return 1;
      }
    }
    else 
    {
      return Fl_Input::handle(event);
    }
 case FL_PUSH:
   if ( Fl::event_button()!=1)
     {
       right_click(this, NULL);
       return 1;
     }
   else return Fl_Input::handle(event);
  default:
    return Fl_Input::handle(event);
  }
}

void FL_CalcInput::right_click(FL_CalcInput *w, void *v)
{
  Fl_Menu_Item rclick_menu[] = {
        { "Undo",  0, handle_menu, (void*)1 },
        { "Cut",  0, handle_menu, (void*)2 },
	{ "Copy", 0, handle_menu, (void*)3 },
	{ "Paste", 0, handle_menu, (void*)4 },
	//{ "-", 0, handle_menu, (void*)5 },
        { "Help",  0, handle_menu, (void*)6 },
        { "About",  0, handle_menu, (void*)7 },
	//{ "-",0, handle_menu, (void*)8 },
	{ "Exit", 0, handle_menu, (void*)9 },
        { 0 }
    };

  const Fl_Menu_Item *m = rclick_menu->popup(Fl::event_x(), Fl::event_y(),0, 0, 0);
  if ( m ) m->do_callback(w, m->user_data());
  return;
}


void handle_menu(Fl_Widget *w, void *v) 
{
  if(!w || !v) return;

  FL_CalcInput *a = (FL_CalcInput*)w;

  switch((long)v)
  {
  case 1: a->undo(); break;
  case 2: a->copy(1); a->cut(); break;
  case 3: a->copy(1); break;
  case 4: Fl::paste(*w); break;
  case 5: break;
  case 6: if(a->_help) a->_help->popup(); break;
  case 7: if(a->_about) a->_about->popup(); break;
  case 8: break;
  case 9: exit(0); break;
  }
}
