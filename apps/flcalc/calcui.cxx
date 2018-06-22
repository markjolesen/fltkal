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
*/

#include "calcui.h"

Fl_Double_Window* flCalc_UI::make_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(260, 25, "flCalc");
    w = o;
    o->user_data((void*)(this));
    { maths_input = new FL_CalcInput(0, 0, 260, 30, " ");
      maths_input->box(FL_DOWN_BOX);
      maths_input->color(FL_BACKGROUND2_COLOR);
      maths_input->selection_color(FL_SELECTION_COLOR);
      maths_input->labeltype(FL_NO_LABEL);
      maths_input->labelfont(0);
      maths_input->labelsize(16);
      maths_input->labelcolor(FL_FOREGROUND_COLOR);
      maths_input->textsize(16);
      maths_input->align(FL_ALIGN_LEFT);
      maths_input->when(FL_WHEN_CHANGED);
      about = new PopupWindow();
      about->text("flCalc v0.1\nCopyright 2008 Andy Le Galle\n\nflCalc uses the Fast Light Toolkit, see fltk.org\n\nflCalc is an interface for the muParser library\nsee muparser.sourceforge.net\n\nflcalc.sourceforge.net\n\nClick this window to close"); 
      maths_input->_about = about;
      help = new PopupWindow();
      help->text("History is accessed with Up and Down arrow keys\n(PgUp PgDn for first and last)\n\nAvaliable functions : \nsin\ncos\ntan\nasin\nacos\natan\nsinh\ncosh\ntanh\nlog2\nlog10\nlog\nln\nexp\nsqrt\nsign\nrint\nabs\nif\nmin\nmax\nsum\navg\n\nAvaliable constants : \npi\ne\n\n\nClick this window to close");
      maths_input->_help = help;
    } // FL_CalcInput* maths_input
    o->end();
  } // Fl_Double_Window* o
  Window = w;
  return w;
}

void flCalc_UI::show_window(int argc, char **argv) {
  Window->show(argc, argv);
}
