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

#include "main.h"
#include "calcui.h"

int main(int argc, char **argv) {
  flCalc_UI *ui = new flCalc_UI();
  ui->make_window();
  ui->show_window(argc,argv);
  Fl::run();
  delete ui;
  return 0;
}

