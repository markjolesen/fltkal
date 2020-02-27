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

CFLAGS= -3r -mf -bt=DOS 

LIB_JPEG=$(LIB)\jpeg.lib

OBJ_JPEG=&
    $(OBJ)\jaricom.obj &
    $(OBJ)\jcapimin.obj &
    $(OBJ)\jcapistd.obj &
    $(OBJ)\jcarith.obj &
    $(OBJ)\jccoefct.obj &
    $(OBJ)\jccolor.obj &
    $(OBJ)\jcdctmgr.obj &
    $(OBJ)\jchuff.obj &
    $(OBJ)\jcinit.obj &
    $(OBJ)\jcmainct.obj &
    $(OBJ)\jcmarker.obj &
    $(OBJ)\jcmaster.obj &
    $(OBJ)\jcomapi.obj &
    $(OBJ)\jcparam.obj &
    $(OBJ)\jcprepct.obj &
    $(OBJ)\jcsample.obj &
    $(OBJ)\jctrans.obj &
    $(OBJ)\jdapimin.obj &
    $(OBJ)\jdapistd.obj &
    $(OBJ)\jdarith.obj &
    $(OBJ)\jdatadst.obj &
    $(OBJ)\jdatasrc.obj &
    $(OBJ)\jdcoefct.obj &
    $(OBJ)\jdcolor.obj &
    $(OBJ)\jddctmgr.obj &
    $(OBJ)\jdhuff.obj &
    $(OBJ)\jdinput.obj &
    $(OBJ)\jdmainct.obj &
    $(OBJ)\jdmarker.obj &
    $(OBJ)\jdmaster.obj &
    $(OBJ)\jdmerge.obj &
    $(OBJ)\jdpostct.obj &
    $(OBJ)\jdsample.obj &
    $(OBJ)\jdtrans.obj &
    $(OBJ)\jerror.obj &
    $(OBJ)\jfdctflt.obj &
    $(OBJ)\jfdctfst.obj &
    $(OBJ)\jfdctint.obj &
    $(OBJ)\jidctflt.obj &
    $(OBJ)\jidctfst.obj &
    $(OBJ)\jidctint.obj &
    $(OBJ)\jmemmgr.obj &
    $(OBJ)\jmemnobs.obj &
    $(OBJ)\jquant1.obj &
    $(OBJ)\jquant2.obj &
    $(OBJ)\jutils.obj
    
all: $(LIB_JPEG)

$(LIB_JPEG) : $(OBJ_JPEG)
    wlib $@ @owd32.lbc
    
$(OBJ)\jaricom.obj : jaricom.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcapimin.obj : jcapimin.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcapistd.obj : jcapistd.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcarith.obj : jcarith.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jccoefct.obj : jccoefct.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jccolor.obj : jccolor.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcdctmgr.obj : jcdctmgr.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jchuff.obj : jchuff.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcinit.obj : jcinit.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcmainct.obj : jcmainct.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcmarker.obj : jcmarker.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcmaster.obj : jcmaster.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcomapi.obj : jcomapi.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcparam.obj : jcparam.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcprepct.obj : jcprepct.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jcsample.obj : jcsample.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jctrans.obj : jctrans.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdapimin.obj : jdapimin.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdapistd.obj : jdapistd.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdarith.obj : jdarith.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdatadst.obj : jdatadst.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdatasrc.obj : jdatasrc.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdcoefct.obj : jdcoefct.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdcolor.obj : jdcolor.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jddctmgr.obj : jddctmgr.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdhuff.obj : jdhuff.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdinput.obj : jdinput.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdmainct.obj : jdmainct.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdmarker.obj : jdmarker.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdmaster.obj : jdmaster.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdmerge.obj : jdmerge.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdpostct.obj : jdpostct.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdsample.obj : jdsample.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jdtrans.obj : jdtrans.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jerror.obj : jerror.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jfdctflt.obj : jfdctflt.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jfdctfst.obj : jfdctfst.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jfdctint.obj : jfdctint.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jidctflt.obj : jidctflt.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jidctfst.obj : jidctfst.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jidctint.obj : jidctint.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jmemmgr.obj : jmemmgr.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jmemnobs.obj : jmemnobs.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jquant1.obj : jquant1.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jquant2.obj : jquant2.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\jutils.obj : jutils.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
