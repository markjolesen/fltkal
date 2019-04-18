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

CC=wcc386

CFLAGS= -3r -mf -bt=DOS $(INCLUDES)

LIB_ZLIB=$(LIB)\z.lib

OBJ_ZLIB=&
    $(OBJ)\adler32.obj &
    $(OBJ)\compress.obj &
    $(OBJ)\crc32.obj &
    $(OBJ)\uncompr.obj &
    $(OBJ)\deflate.obj &
    $(OBJ)\trees.obj &
    $(OBJ)\zutil.obj &
    $(OBJ)\inflate.obj &
    $(OBJ)\inftrees.obj &
    $(OBJ)\inffast.obj &
    $(OBJ)\gzclose.obj &
    $(OBJ)\gzlib.obj &
    $(OBJ)\gzread.obj &
    $(OBJ)\gzwrite.obj &
    $(OBJ)\infback.obj 
    
all: $(LIB_ZLIB) .SYMBOLIC

$(LIB_ZLIB) : $(OBJ_ZLIB)
    wlib $@ @owd32.lbc

$(OBJ)\adler32.obj : adler32.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\compress.obj : compress.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\crc32.obj : crc32.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\uncompr.obj : uncompr.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\deflate.obj : deflate.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\trees.obj : trees.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\zutil.obj : zutil.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\inflate.obj : inflate.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\inftrees.obj : inftrees.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\inffast.obj : inffast.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\gzclose.obj : gzclose.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\gzlib.obj : gzlib.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\gzread.obj : gzread.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\gzwrite.obj : gzwrite.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\infback.obj : infback.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
