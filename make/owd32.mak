#
# Copyright 2019 The fltkal authors
# 
#                               FLTK License
#                             December 11, 2001
#  
#  The FLTK library and included programs are provided under the terms
#  of the GNU Library General Public License (LGPL) with the following
#  exceptions:
#  
#      1. Modifications to the FLTK configure script, config
#         header file, and makefiles by themselves to support
#         a specific platform do not constitute a modified or
#         derivative work.
#  
#        The authors do request that such modifications be
#        contributed to the FLTK project - send all contributions
#        through the "Software Trouble Report" on the following page:
#   
#             http://www.fltk.org/str.php
#  
#      2. Widgets that are subclassed from FLTK widgets do not
#         constitute a derivative work.
#  
#      3. Static linking of applications and widgets to the
#         FLTK library does not constitute a derivative work
#         and does not require the author to provide source
#         code for the application or widget, use the shared
#         FLTK libraries, or link their applications or
#         widgets against a user-supplied version of FLTK.
#  
#         If you link the application or widget to a modified
#         version of FLTK, then the changes to FLTK must be
#         provided under the terms of the LGPL in sections
#         1, 2, and 4.
#  
#      4. You do not have to provide a copy of the FLTK license
#         with programs that are linked to the FLTK library, nor
#         do you have to identify the FLTK license in your
#         program or documentation as required by section 6
#         of the LGPL.
#  
#         However, programs must still identify their use of FLTK.
#         The following example statement can be included in user
#         documentation to satisfy this requirement:
#  
#             [program/widget] is based in part on the work of
#             the FLTK project (http://www.fltk.org).
#  
#      This library is free software; you can redistribute it and/or
#      modify it under the terms of the GNU Library General Public
#      License as published by the Free Software Foundation; either
#      version 2 of the License, or (at your option) any later version.
#  
#      This library is distributed in the hope that it will be useful,
#      but WITHOUT ANY WARRANTY; without even the implied warranty of
#      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#      Library General Public License for more details.
#  
#      You should have received a copy of the GNU Library General Public
#      License along with FLTK.  If not, see <http://www.gnu.org/licenses/>.
# 

OBJ=..\obj
SRC=..\src
LIB=..\lib

ZLIB=..\zlib
INC_ZLIB=-i$(ZLIB)

PNG=..\png
INC_PNG=-i$(PNG)

JPEG=..\jpeg
INC_JPEG=-i$(JPEG)

TTF=..\ft29
INC_TTF=-i$(TTF)\include

OW32SVGA=..\ow32svga
INC_OW32SVGA=-i$(OW32SVGA)\include

INCLUDES=-i.. $(INC_TTF) $(INC_OW32SVGA) $(INC_ZLIB) $(INC_PNG) $(INC_JPEG)

DEFINES=-DFL_LIBRARY -DUSE_OWD32

RM=del
AS=wasm
CC=wcc386
CXX=wpp386

AFLAGS= -3r -mf -bt=DOS -d1 $(INCLUDES) $(DEFINES)
CFLAGS= -3r -mf -bt=DOS -d3 $(INCLUDES) $(DEFINES)
CXXFLAGS= -3r -mf -bt=DOS -d3 $(INCLUDES) $(DEFINES)

LIB_FLTK=$(LIB)\fltk.lib

OBJ_FLTK=&
    $(OBJ)\abort.obj &
    $(OBJ)\add_idle.obj &
    $(OBJ)\adjuster.obj &
    $(OBJ)\arc.obj &
    $(OBJ)\box.obj &
    $(OBJ)\boxoval.obj &
    $(OBJ)\boxshado.obj &
    $(OBJ)\boxtype.obj &
    $(OBJ)\browser_.obj &
    $(OBJ)\browser.obj &
    $(OBJ)\browserk.obj &
    $(OBJ)\browserl.obj &
    $(OBJ)\btn.obj &
    $(OBJ)\btnk.obj &
    $(OBJ)\btnlt.obj &
    $(OBJ)\btnmenu.obj &
    $(OBJ)\btnret.obj &
    $(OBJ)\btnro.obj &
    $(OBJ)\btnrpt.obj &
    $(OBJ)\chart.obj &
    $(OBJ)\choice.obj &
    $(OBJ)\cleanup.obj &
    $(OBJ)\clock.obj &
    $(OBJ)\colorch.obj &
    $(OBJ)\colorfn.obj &
    $(OBJ)\compose.obj &
    $(OBJ)\counter.obj &
    $(OBJ)\owcursor.obj &
    $(OBJ)\curve.obj &
    $(OBJ)\dial.obj &
    $(OBJ)\diamond.obj &
    $(OBJ)\display.obj &
    $(OBJ)\dlghelp.obj &
    $(OBJ)\drawpix.obj &
    $(OBJ)\drvcopy.obj &
    $(OBJ)\drvdev.obj &
    $(OBJ)\drvgr.obj &
    $(OBJ)\drvimg.obj &
    $(OBJ)\drvscr.obj &
    $(OBJ)\drvsys.obj &
    $(OBJ)\drvwin.obj &
    $(OBJ)\engraved.obj &
    $(OBJ)\filebr.obj &
    $(OBJ)\filech2.obj &
    $(OBJ)\filech.obj &
    $(OBJ)\filechn.obj &
    $(OBJ)\filedir.obj &
    $(OBJ)\filefltk.obj &
    $(OBJ)\fl_arg.obj &
    $(OBJ)\fl_ask.obj &
    $(OBJ)\fl_box.obj &
    $(OBJ)\fl_boxro.obj &
    $(OBJ)\fl_color.obj &
    $(OBJ)\fl_draw.obj &
    $(OBJ)\fl_font.obj &
    $(OBJ)\fl_gleam.obj &
    $(OBJ)\fl_grab.obj &
    $(OBJ)\fl_gtk.obj &
    $(OBJ)\fl.obj &
    $(OBJ)\flprintf.obj &
    $(OBJ)\fl_rect.obj &
    $(OBJ)\flstring.obj &
    $(OBJ)\fl_uri.obj &
    $(OBJ)\fl_utf8.obj &
    $(OBJ)\fnabs.obj &
    $(OBJ)\fnexpand.obj &
    $(OBJ)\fnext.obj &
    $(OBJ)\fnisdir.obj &
    $(OBJ)\fnlist.obj &
    $(OBJ)\fnmatch.obj &
    $(OBJ)\fnsetext.obj &
    $(OBJ)\group.obj &
    $(OBJ)\helpview.obj &
    $(OBJ)\hotspot.obj &
    $(OBJ)\icon2fil.obj &
    $(OBJ)\iconfile.obj &
    $(OBJ)\iconize.obj &
    $(OBJ)\imgbit.obj &
    $(OBJ)\imgbmp.obj &
    $(OBJ)\imgcore.obj &
    $(OBJ)\imggif.obj &
    $(OBJ)\imgjpeg.obj &
    $(OBJ)\img.obj &
    $(OBJ)\imgpix.obj &
    $(OBJ)\imgpng.obj &
    $(OBJ)\imgpnm.obj &
    $(OBJ)\imgread.obj &
    $(OBJ)\imgshare.obj &
    $(OBJ)\imgtiled.obj &
    $(OBJ)\imgxbm.obj &
    $(OBJ)\imgxpm.obj &
    $(OBJ)\inpcho.obj &
    $(OBJ)\inpfile.obj &
    $(OBJ)\input_.obj &
    $(OBJ)\input.obj &
    $(OBJ)\inpvalue.obj &
    $(OBJ)\labelm.obj &
    $(OBJ)\labeltyp.obj &
    $(OBJ)\latin1.obj &
    $(OBJ)\macroman.obj &
    $(OBJ)\menuadd.obj &
    $(OBJ)\menubar.obj &
    $(OBJ)\menu_.obj &
    $(OBJ)\menu.obj &
    $(OBJ)\menuglob.obj &
    $(OBJ)\numsort.obj &
    $(OBJ)\outvalue.obj &
    $(OBJ)\overlay.obj &
    $(OBJ)\pack.obj &
    $(OBJ)\plastic.obj &
    $(OBJ)\pref.obj &
    $(OBJ)\progress.obj &
    $(OBJ)\rint.obj &
    $(OBJ)\roller.obj &
    $(OBJ)\scandir.obj &
    $(OBJ)\scrlarea.obj &
    $(OBJ)\scrlbar.obj &
    $(OBJ)\scroll.obj &
    $(OBJ)\scrxywh.obj &
    $(OBJ)\set_font.obj &
    $(OBJ)\shortcut.obj &
    $(OBJ)\slider.obj &
    $(OBJ)\slvalue.obj &
    $(OBJ)\spinner.obj &
    $(OBJ)\symbols.obj &
    $(OBJ)\syscolor.obj &
    $(OBJ)\table.obj &
    $(OBJ)\tablerow.obj &
    $(OBJ)\tabs.obj &
    $(OBJ)\terminal.obj &
    $(OBJ)\textbuf.obj &
    $(OBJ)\textdsp.obj &
    $(OBJ)\texted.obj &
    $(OBJ)\tile.obj &
    $(OBJ)\tooltip.obj &
    $(OBJ)\treearr.obj &
    $(OBJ)\treeitem.obj &
    $(OBJ)\tree.obj &
    $(OBJ)\treepref.obj &
    $(OBJ)\valuator.obj &
    $(OBJ)\vertex.obj &
    $(OBJ)\visual.obj &
    $(OBJ)\widget.obj &
    $(OBJ)\widgsurf.obj &
    $(OBJ)\win.obj &
    $(OBJ)\windbl.obj &
    $(OBJ)\winmenu.obj &
    $(OBJ)\winovlay.obj &
    $(OBJ)\winsngl.obj &
    $(OBJ)\wizard.obj 
	
SRC_FLTK=$(SRC)

OBJ_OW32DRV= &
    $(OBJ)\aldrvcp.obj &
    $(OBJ)\aldrvgr.obj &
    $(OBJ)\aldrvimg.obj &
    $(OBJ)\aldrvscr.obj &
    $(OBJ)\aldrvsys.obj &
    $(OBJ)\aldrvwin.obj &
    $(OBJ)\drvscrow.obj &
    $(OBJ)\fontdir.obj &
    $(OBJ)\fontft.obj &
    $(OBJ)\rgb24cb.obj &
    $(OBJ)\timeout.obj &
    $(OBJ)\utf8proc.obj &
    $(OBJ)\util.obj &
    $(OBJ)\wm.obj
	
SRC_OW32DRV=$(SRC)\drivers\allegro4
    
OBJ_XUTF8=&
    $(OBJ)\case.obj &
    $(OBJ)\spacing.obj
    
SRC_XUTF8=$(SRC)\xutf8

OBJ_ALL=$(OBJ_FLTK) $(OBJ_OW32DRV) $(OBJ_XUTF8)

all : $(LIB_FLTK)

$(LIB_FLTK) : $(OBJ_ALL)
    wlib $@ @owd32.lbc

$(OBJ)\abort.obj : $(SRC_FLTK)\abort.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\add_idle.obj : $(SRC_FLTK)\add_idle.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\adjuster.obj : $(SRC_FLTK)\adjuster.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\arc.obj : $(SRC_FLTK)\arc.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\box.obj : $(SRC_FLTK)\box.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\boxoval.obj : $(SRC_FLTK)\boxoval.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\boxshado.obj : $(SRC_FLTK)\boxshado.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\boxtype.obj : $(SRC_FLTK)\boxtype.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\browser_.obj : $(SRC_FLTK)\browser_.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\browser.obj : $(SRC_FLTK)\browser.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\browserk.obj : $(SRC_FLTK)\browserk.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\browserl.obj : $(SRC_FLTK)\browserl.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\btn.obj : $(SRC_FLTK)\btn.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\btnk.obj : $(SRC_FLTK)\btnk.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\btnlt.obj : $(SRC_FLTK)\btnlt.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\btnmenu.obj : $(SRC_FLTK)\btnmenu.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\btnret.obj : $(SRC_FLTK)\btnret.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\btnro.obj : $(SRC_FLTK)\btnro.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\btnrpt.obj : $(SRC_FLTK)\btnrpt.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\chart.obj : $(SRC_FLTK)\chart.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\choice.obj : $(SRC_FLTK)\choice.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\cleanup.obj : $(SRC_FLTK)\cleanup.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\clock.obj : $(SRC_FLTK)\clock.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\colorch.obj : $(SRC_FLTK)\colorch.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\colorfn.obj : $(SRC_FLTK)\colorfn.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\compose.obj : $(SRC_FLTK)\compose.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\counter.obj : $(SRC_FLTK)\counter.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\owcursor.obj : $(SRC_FLTK)\owcursor.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\curve.obj : $(SRC_FLTK)\curve.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\dial.obj : $(SRC_FLTK)\dial.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\diamond.obj : $(SRC_FLTK)\diamond.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\display.obj : $(SRC_FLTK)\display.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\dlghelp.obj : $(SRC_FLTK)\dlghelp.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\drawpix.obj : $(SRC_FLTK)\drawpix.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\drvcopy.obj : $(SRC_FLTK)\drvcopy.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\drvdev.obj : $(SRC_FLTK)\drvdev.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\drvgr.obj : $(SRC_FLTK)\drvgr.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\drvimg.obj : $(SRC_FLTK)\drvimg.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\drvscr.obj : $(SRC_FLTK)\drvscr.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\drvsys.obj : $(SRC_FLTK)\drvsys.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\drvwin.obj : $(SRC_FLTK)\drvwin.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\engraved.obj : $(SRC_FLTK)\engraved.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\filebr.obj : $(SRC_FLTK)\filebr.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\filech2.obj : $(SRC_FLTK)\filech2.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\filech.obj : $(SRC_FLTK)\filech.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\filechn.obj : $(SRC_FLTK)\filechn.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\filedir.obj : $(SRC_FLTK)\filedir.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\filefltk.obj : $(SRC_FLTK)\filefltk.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl_arg.obj : $(SRC_FLTK)\fl_arg.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl_ask.obj : $(SRC_FLTK)\fl_ask.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl_box.obj : $(SRC_FLTK)\fl_box.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl_boxro.obj : $(SRC_FLTK)\fl_boxro.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl_color.obj : $(SRC_FLTK)\fl_color.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl_draw.obj : $(SRC_FLTK)\fl_draw.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl_font.obj : $(SRC_FLTK)\fl_font.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl_gleam.obj : $(SRC_FLTK)\fl_gleam.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl_grab.obj : $(SRC_FLTK)\fl_grab.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl_gtk.obj : $(SRC_FLTK)\fl_gtk.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl.obj : $(SRC_FLTK)\fl.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\flprintf.obj : $(SRC_FLTK)\flprintf.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\fl_rect.obj : $(SRC_FLTK)\fl_rect.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\flstring.obj : $(SRC_FLTK)\flstring.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\fl_uri.obj : $(SRC_FLTK)\fl_uri.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fl_utf8.obj : $(SRC_FLTK)\fl_utf8.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fnabs.obj : $(SRC_FLTK)\fnabs.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fnexpand.obj : $(SRC_FLTK)\fnexpand.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fnext.obj : $(SRC_FLTK)\fnext.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fnisdir.obj : $(SRC_FLTK)\fnisdir.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fnlist.obj : $(SRC_FLTK)\fnlist.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fnmatch.obj : $(SRC_FLTK)\fnmatch.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fnsetext.obj : $(SRC_FLTK)\fnsetext.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\group.obj : $(SRC_FLTK)\group.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\helpview.obj : $(SRC_FLTK)\helpview.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\hotspot.obj : $(SRC_FLTK)\hotspot.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\icon2fil.obj : $(SRC_FLTK)\icon2fil.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\iconfile.obj : $(SRC_FLTK)\iconfile.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\iconize.obj : $(SRC_FLTK)\iconize.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgbit.obj : $(SRC_FLTK)\imgbit.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgbmp.obj : $(SRC_FLTK)\imgbmp.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgcore.obj : $(SRC_FLTK)\imgcore.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imggif.obj : $(SRC_FLTK)\imggif.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgjpeg.obj : $(SRC_FLTK)\imgjpeg.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\img.obj : $(SRC_FLTK)\img.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgpix.obj : $(SRC_FLTK)\imgpix.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgpng.obj : $(SRC_FLTK)\imgpng.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgpnm.obj : $(SRC_FLTK)\imgpnm.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgread.obj : $(SRC_FLTK)\imgread.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgshare.obj : $(SRC_FLTK)\imgshare.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgtiled.obj : $(SRC_FLTK)\imgtiled.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgxbm.obj : $(SRC_FLTK)\imgxbm.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\imgxpm.obj : $(SRC_FLTK)\imgxpm.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\inpcho.obj : $(SRC_FLTK)\inpcho.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\inpfile.obj : $(SRC_FLTK)\inpfile.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\input_.obj : $(SRC_FLTK)\input_.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\input.obj : $(SRC_FLTK)\input.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\inpvalue.obj : $(SRC_FLTK)\inpvalue.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\labelm.obj : $(SRC_FLTK)\labelm.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\labeltyp.obj : $(SRC_FLTK)\labeltyp.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\latin1.obj : $(SRC_FLTK)\latin1.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\macroman.obj : $(SRC_FLTK)\macroman.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\menuadd.obj : $(SRC_FLTK)\menuadd.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\menubar.obj : $(SRC_FLTK)\menubar.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\menu_.obj : $(SRC_FLTK)\menu_.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\menu.obj : $(SRC_FLTK)\menu.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\menuglob.obj : $(SRC_FLTK)\menuglob.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\numsort.obj : $(SRC_FLTK)\numsort.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\outvalue.obj : $(SRC_FLTK)\outvalue.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\overlay.obj : $(SRC_FLTK)\overlay.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\pack.obj : $(SRC_FLTK)\pack.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\plastic.obj : $(SRC_FLTK)\plastic.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\pref.obj : $(SRC_FLTK)\pref.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\progress.obj : $(SRC_FLTK)\progress.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\rint.obj : $(SRC_FLTK)\rint.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\roller.obj : $(SRC_FLTK)\roller.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\scandir.obj : $(SRC_FLTK)\scandir.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\scrlarea.obj : $(SRC_FLTK)\scrlarea.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\scrlbar.obj : $(SRC_FLTK)\scrlbar.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\scroll.obj : $(SRC_FLTK)\scroll.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\scrxywh.obj : $(SRC_FLTK)\scrxywh.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\set_font.obj : $(SRC_FLTK)\set_font.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\shortcut.obj : $(SRC_FLTK)\shortcut.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\slider.obj : $(SRC_FLTK)\slider.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\slvalue.obj : $(SRC_FLTK)\slvalue.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\spinner.obj : $(SRC_FLTK)\spinner.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\symbols.obj : $(SRC_FLTK)\symbols.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\syscolor.obj : $(SRC_FLTK)\syscolor.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\table.obj : $(SRC_FLTK)\table.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\tablerow.obj : $(SRC_FLTK)\tablerow.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\tabs.obj : $(SRC_FLTK)\tabs.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\terminal.obj : $(SRC_FLTK)\terminal.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\textbuf.obj : $(SRC_FLTK)\textbuf.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\textdsp.obj : $(SRC_FLTK)\textdsp.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\texted.obj : $(SRC_FLTK)\texted.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\tile.obj : $(SRC_FLTK)\tile.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\tooltip.obj : $(SRC_FLTK)\tooltip.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\treearr.obj : $(SRC_FLTK)\treearr.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\treeitem.obj : $(SRC_FLTK)\treeitem.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\tree.obj : $(SRC_FLTK)\tree.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\treepref.obj : $(SRC_FLTK)\treepref.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\valuator.obj : $(SRC_FLTK)\valuator.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\vertex.obj : $(SRC_FLTK)\vertex.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\visual.obj : $(SRC_FLTK)\visual.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\widget.obj : $(SRC_FLTK)\widget.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\widgsurf.obj : $(SRC_FLTK)\widgsurf.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\win.obj : $(SRC_FLTK)\win.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\windbl.obj : $(SRC_FLTK)\windbl.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\winmenu.obj : $(SRC_FLTK)\winmenu.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\winovlay.obj : $(SRC_FLTK)\winovlay.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\winsngl.obj : $(SRC_FLTK)\winsngl.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\wizard.obj : $(SRC_FLTK)\wizard.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\case.obj : $(SRC_XUTF8)\case.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\spacing.obj : $(SRC_XUTF8)\spacing.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\aldrvcp.obj : $(SRC_OW32DRV)\aldrvcp.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\aldrvgr.obj : $(SRC_OW32DRV)\aldrvgr.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\aldrvimg.obj : $(SRC_OW32DRV)\aldrvimg.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\aldrvscr.obj : $(SRC_OW32DRV)\aldrvscr.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\aldrvsys.obj : $(SRC_OW32DRV)\aldrvsys.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\aldrvwin.obj : $(SRC_OW32DRV)\aldrvwin.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\drvscrow.obj : $(SRC_OW32DRV)\drvscrow.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\fontdir.obj : $(SRC_OW32DRV)\fontdir.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<

$(OBJ)\fontft.obj : $(SRC_OW32DRV)\fontft.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\rgb24cb.obj : $(SRC_OW32DRV)\rgb24cb.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\timeout.obj : $(SRC_OW32DRV)\timeout.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<

$(OBJ)\utf8proc.obj : $(SRC_OW32DRV)\utf8proc.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\util.obj : $(SRC_OW32DRV)\util.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
$(OBJ)\wm.obj : $(SRC_OW32DRV)\wm.cxx .AUTODEPEND
    *$(CXX) $(CXXFLAGS) -fo=$@ $<
    
