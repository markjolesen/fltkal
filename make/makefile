#
# "$Id: Makefile 11998 2016-09-30 21:09:59Z AlbrechtS $"
#
# Top-level makefile for the Fast Light Tool Kit (FLTK).
#
# Copyright 2017-2018 The fltkal authors
# Copyright 1998-2017 by Bill Spitzak and others.
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

ifeq (, $(shell which uname))
UNAME:=DOS
else
UNAME:= $(shell uname)
endif

ifeq ($(UNAME), DOS)
FREETYPE=/source/freetype
FREETYPEINC=$(FREETYPE)/include
ALLEGRO=/source/allegro
ALLEGROLIB=$(ALLEGRO)/lib/djgpp
ALLEGROINC=$(ALLEGRO)/include
INCLUDES=-I.. -I$(ALLEGROINC) -I$(FREETYPEINC) -I../zlib -I../png -I../jpeg
REDIRCOMMAND=redir -o $(basename $@).err -eo
else
FREETYPEINC=/usr/include/freetype2/
INCLUDES=-I.. -I$(FREETYPEINC)
endif

DEFINES=-DFL_LIBRARY -DUSE_ALLEGRO

CFLAGS=-g $(INCLUDES) $(DEFINES)
CXXFLAGS=-g $(INCLUDES) $(DEFINES)
DEPFLAGS=-MM
ARFLAGS=rvs
RANLIB=ranlib

OBJ=../obj
SRC=../src
LIB=../lib

FLTKLIB=$(LIB)/libfltk.a

FLTKOBJS=\
	$(OBJ)/abort.o \
	$(OBJ)/add_idle.o \
	$(OBJ)/adjuster.o \
	$(OBJ)/arc.o \
	$(OBJ)/box.o \
	$(OBJ)/boxoval.o \
	$(OBJ)/boxshado.o \
	$(OBJ)/boxtype.o \
	$(OBJ)/browser_.o \
	$(OBJ)/browser.o \
	$(OBJ)/browserk.o \
	$(OBJ)/browserl.o \
	$(OBJ)/btn.o \
	$(OBJ)/btnk.o \
	$(OBJ)/btnlt.o \
	$(OBJ)/btnmenu.o \
	$(OBJ)/btnret.o \
	$(OBJ)/btnro.o \
	$(OBJ)/btnrpt.o \
	$(OBJ)/chart.o \
	$(OBJ)/choice.o \
	$(OBJ)/clock.o \
	$(OBJ)/colorch.o \
	$(OBJ)/colorfn.o \
	$(OBJ)/compose.o \
	$(OBJ)/counter.o \
	$(OBJ)/cursor.o \
	$(OBJ)/curve.o \
	$(OBJ)/dial.o \
	$(OBJ)/diamond.o \
	$(OBJ)/display.o \
	$(OBJ)/dlghelp.o \
	$(OBJ)/drawpix.o \
	$(OBJ)/drvcopy.o \
	$(OBJ)/drvdev.o \
	$(OBJ)/drvgr.o \
	$(OBJ)/drvimg.o \
	$(OBJ)/drvscr.o \
	$(OBJ)/drvsys.o \
	$(OBJ)/drvwin.o \
	$(OBJ)/engraved.o \
	$(OBJ)/filebr.o \
	$(OBJ)/filech2.o \
	$(OBJ)/filech.o \
	$(OBJ)/filechn.o \
	$(OBJ)/filedir.o \
	$(OBJ)/filefltk.o \
	$(OBJ)/fl_arg.o \
	$(OBJ)/fl_ask.o \
	$(OBJ)/fl_box.o \
	$(OBJ)/fl_boxro.o \
	$(OBJ)/fl_color.o \
	$(OBJ)/fl_draw.o \
	$(OBJ)/fl_font.o \
	$(OBJ)/fl_gleam.o \
	$(OBJ)/fl_grab.o \
	$(OBJ)/fl_gtk.o \
	$(OBJ)/fl.o \
	$(OBJ)/flprintf.o \
	$(OBJ)/fl_rect.o \
	$(OBJ)/flstring.o \
	$(OBJ)/fl_uri.o \
	$(OBJ)/fl_utf8.o \
	$(OBJ)/fnabs.o \
	$(OBJ)/fnexpand.o \
	$(OBJ)/fnext.o \
	$(OBJ)/fnisdir.o \
	$(OBJ)/fnlist.o \
	$(OBJ)/fnmatch.o \
	$(OBJ)/fnsetext.o \
	$(OBJ)/group.o \
	$(OBJ)/helpview.o \
	$(OBJ)/hotspot.o \
	$(OBJ)/icon2fil.o \
	$(OBJ)/iconfile.o \
	$(OBJ)/iconize.o \
	$(OBJ)/imgbit.o \
	$(OBJ)/imgbmp.o \
	$(OBJ)/imgcore.o \
	$(OBJ)/imggif.o \
	$(OBJ)/imgjpeg.o \
	$(OBJ)/img.o \
	$(OBJ)/imgpix.o \
	$(OBJ)/imgpng.o \
	$(OBJ)/imgpnm.o \
	$(OBJ)/imgrdr.o \
	$(OBJ)/imgread.o \
	$(OBJ)/imgshare.o \
	$(OBJ)/imgtiled.o \
	$(OBJ)/imgxbm.o \
	$(OBJ)/imgxpm.o \
	$(OBJ)/inpcho.o \
	$(OBJ)/inpfile.o \
	$(OBJ)/input_.o \
	$(OBJ)/input.o \
	$(OBJ)/inpvalue.o \
	$(OBJ)/labelm.o \
	$(OBJ)/labeltyp.o \
	$(OBJ)/latin1.o \
	$(OBJ)/macroman.o \
	$(OBJ)/menuadd.o \
	$(OBJ)/menubar.o \
	$(OBJ)/menu_.o \
	$(OBJ)/menu.o \
	$(OBJ)/menuglob.o \
	$(OBJ)/numsort.o \
	$(OBJ)/outvalue.o \
	$(OBJ)/overlay.o \
	$(OBJ)/pack.o \
	$(OBJ)/plastic.o \
	$(OBJ)/pref.o \
	$(OBJ)/progress.o \
	$(OBJ)/roller.o \
	$(OBJ)/scandir.o \
	$(OBJ)/scrlarea.o \
	$(OBJ)/scrlbar.o \
	$(OBJ)/scroll.o \
	$(OBJ)/scrxywh.o \
	$(OBJ)/set_font.o \
	$(OBJ)/shortcut.o \
	$(OBJ)/slider.o \
	$(OBJ)/slvalue.o \
	$(OBJ)/spinner.o \
	$(OBJ)/symbols.o \
	$(OBJ)/syscolor.o \
	$(OBJ)/table.o \
	$(OBJ)/tablerow.o \
	$(OBJ)/tabs.o \
	$(OBJ)/terminal.o \
	$(OBJ)/textbuf.o \
	$(OBJ)/textdsp.o \
	$(OBJ)/texted.o \
	$(OBJ)/tile.o \
	$(OBJ)/tooltip.o \
	$(OBJ)/treearr.o \
	$(OBJ)/treeitem.o \
	$(OBJ)/tree.o \
	$(OBJ)/treepref.o \
	$(OBJ)/valuator.o \
	$(OBJ)/vertex.o \
	$(OBJ)/visual.o \
	$(OBJ)/widget.o \
	$(OBJ)/widgsurf.o \
	$(OBJ)/win.o \
	$(OBJ)/windbl.o \
	$(OBJ)/winmenu.o \
	$(OBJ)/winovlay.o \
	$(OBJ)/winsngl.o \
	$(OBJ)/wizard.o 
    
XUTF8OBJS=\
	$(OBJ)/case.o \
	$(OBJ)/spacing.o
    
XUTF8SRC=$(SRC)/xutf8

ALLEGRO4DRVOBJS=\
	$(OBJ)/aldrvcp.o \
	$(OBJ)/aldrvgr.o \
	$(OBJ)/aldrvimg.o \
	$(OBJ)/aldrvscr.o \
	$(OBJ)/aldrvsys.o \
	$(OBJ)/aldrvwin.o \
	$(OBJ)/algfx.o \
	$(OBJ)/drvscral.o \
	$(OBJ)/fontdir.o \
	$(OBJ)/fontft.o \
	$(OBJ)/imgconv.o \
	$(OBJ)/rgb16.o \
	$(OBJ)/rgb24cb.o \
	$(OBJ)/rgb24.o \
	$(OBJ)/rgb32.o \
	$(OBJ)/rgb8.o \
	$(OBJ)/timeout.o \
	$(OBJ)/utf8proc.o \
	$(OBJ)/util.o \
	$(OBJ)/wm.o \
	$(OBJ)/xbm.o 
    
ALLEGRO4DRVSRC=$(SRC)/drivers/allegro4

ALLOBJS=$(FLTKOBJS) $(XUTF8OBJS) $(ALLEGRO4DRVOBJS)

VPATH=$(SRC) $(ALLEGRO4DRVSRC) $(XUTF8SRC)

.PHONY: all
all : $(FLTKLIB)

$(FLTKLIB) : $(ALLOBJS)
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $(ALLOBJS)
	$(RANLIB) $@

$(OBJ)/%.o : %.c 
	$(REDIRCOMMAND) $(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ)/%.o : %.cxx
	$(REDIRCOMMAND) $(CXX) $(CXXFLAGS) -c $< -o $@
	
.PHONY: clean
clean :
	$(RM) $(FLTKOBJS)
	$(RM) $(ALLEGRO4DRVOBJS)
	$(RM) $(XUTF8OBJS)
	$(RM) $(FLTKLIB)
	$(RM) $(OBJ)/*.err
	
.PHONY: depend
depend : depend.mk

depend.mk :
	$(CC) $(CFLAGS) $(DEPFLAGS) $(SRC)/*.c > depend.mk
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(SRC)/*.cxx >> depend.mk
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(ALLEGRO4DRVSRC)/*.cxx >> depend.mk
	$(CC) $(DEPFLAGS) $(XUTF8SRC)/*.c >> depend.mk
	sed -i "s/c:.*\.ver//" depend.mk
	sed -i -re "s/(.*)\.o/$$\(OBJ\)\/\1.o/" depend.mk
	sed -i -re "s/\/usr\/include\/freetype2\//$$\(FREETYPEINC\)\//" depend.mk

-include depend.mk    
    
