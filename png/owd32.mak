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
LIB=..\lib

INCLUDES=-i..\zlib

CC=wcc386

CFLAGS= -3r -mf -bt=DOS $(INCLUDES)

LIB_PNG=$(LIB)\png.lib

OBJ_PNG=&
    $(OBJ)\png.obj &
    $(OBJ)\pngset.obj &
    $(OBJ)\pngget.obj &
    $(OBJ)\pngrutil.obj &
    $(OBJ)\pngtrans.obj &
    $(OBJ)\pngwutil.obj &
    $(OBJ)\pngread.obj &
    $(OBJ)\pngrio.obj &
    $(OBJ)\pngwio.obj &
    $(OBJ)\pngwrite.obj &
    $(OBJ)\pngrtran.obj &
    $(OBJ)\pngwtran.obj &
    $(OBJ)\pngmem.obj &
    $(OBJ)\pngerror.obj &
    $(OBJ)\pngpread.obj 
    
all: $(LIB_PNG) .SYMBOLIC

$(LIB_PNG) : $(OBJ_PNG)
    wlib $@ @owd32.lbc
    
$(OBJ)\png.obj : png.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngset.obj : pngset.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngget.obj : pngget.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngrutil.obj : pngrutil.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngtrans.obj : pngtrans.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngwutil.obj : pngwutil.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngread.obj : pngread.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngrio.obj : pngrio.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngwio.obj : pngwio.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngwrite.obj : pngwrite.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngrtran.obj : pngrtran.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngwtran.obj : pngwtran.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngmem.obj : pngmem.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngerror.obj : pngerror.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\pngpread.obj : pngpread.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
