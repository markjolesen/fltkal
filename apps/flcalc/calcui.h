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

#ifndef flCalc_UI_h
#define flCalc_UI_h

#if !defined(__DJGPP__)
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#else
#include <fl/fl.h>
#include <fl/windbl.h>
#endif

#include "calcinp.h"

class flCalc_UI {
public:
  Fl_Double_Window* make_window();
  FL_CalcInput *maths_input;
  PopupWindow *about;
  PopupWindow *help;
  void show_window(int argc, char **argv);
  Fl_Double_Window *Window; 
};
#endif
