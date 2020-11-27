# makefile
#
# License CC0 PUBLIC DOMAIN
#
# To the extent possible under law, Mark J. Olesen has waived all copyright 
# and related or neighboring rights to ow32svga Library. This work is published 
# from: United States.

INCLUDES=-i..\include
DEFINES=

OBJ=..\obj
SRC=..\src
LIB=..\..\lib
INC=..\include

RM=del
AS=wasm
CC=wcc386
CXX=wpp386

AFLAGS= -3r -mf -bt=DOS -d1 $(INCLUDES) $(DEFINES)
CFLAGS= -3r -mf -bt=DOS -d3 $(INCLUDES) $(DEFINES)
CXXFLAGS= -3r -mf -bt=DOS -d3 $(INCLUDES) $(DEFINES)

LIBOW32SVGA=$(LIB)\ow32svga.lib

OBJS=&
    $(OBJ)\bitmap.obj &
    $(OBJ)\bitmap_.obj &
    $(OBJ)\clip_.obj &
    $(OBJ)\cursor_.obj &
    $(OBJ)\display.obj &
    $(OBJ)\dpmi_.obj &
    $(OBJ)\image.obj &
    $(OBJ)\image_.obj &
    $(OBJ)\line.obj &
    $(OBJ)\mouse_.obj &
    $(OBJ)\vbe_.obj &
    $(OBJ)\vbe.obj
	
OBJ_CURSORS=&
    $(OBJ)\xarrow_.obj &
    $(OBJ)\xcrossh_.obj &
    $(OBJ)\xe_.obj &
    $(OBJ)\xew_.obj &
    $(OBJ)\xhand_.obj &
    $(OBJ)\xhelp_.obj &
    $(OBJ)\xinsert_.obj &
    $(OBJ)\xmove_.obj &
    $(OBJ)\xn_.obj &
    $(OBJ)\xne_.obj &
    $(OBJ)\xnesw_.obj &
    $(OBJ)\xns_.obj &
    $(OBJ)\xnw_.obj &
    $(OBJ)\xnwse_.obj &
    $(OBJ)\xs_.obj &
    $(OBJ)\xse_.obj &
    $(OBJ)\xsw_.obj &
    $(OBJ)\xw_.obj &
    $(OBJ)\xwait_.obj
    
SRC_CURSORS=$(SRC)\cursors
	
all : $(LIBOW32SVGA) .SYMBOlIC

$(LIBOW32SVGA) : $(OBJS) $(OBJ_CURSORS)
        wlib $@ @owd32.lbc
	
$(OBJ)\clip_.obj : $(SRC)\clip_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\cursor_.obj : $(SRC)\cursor_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\cursors_.obj : $(SRC)\cursors_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<

$(OBJ)\vbe_.obj : $(SRC)\vbe_.asm  .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\dpmi_.obj : $(SRC)\dpmi_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\image_.obj : $(SRC)\image_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\mouse_.obj : $(SRC)\mouse_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\bitmap.obj : $(SRC)\bitmap.c .AUTODEPEND
        *$(CC) $(CFLAGS) -fo=$@ $<
	
$(OBJ)\bitmap_.obj : $(SRC)\bitmap_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\vbe.obj : $(SRC)\vbe.c .AUTODEPEND
        *$(CC) $(CFLAGS) -fo=$@ $<
	
$(OBJ)\display.obj : $(SRC)\display.c .AUTODEPEND
        *$(CC) $(CFLAGS) -fo=$@ $<
	
$(OBJ)\image.obj : $(SRC)\image.c .AUTODEPEND
        *$(CC) $(CFLAGS) -fo=$@ $<
	
$(OBJ)\line.obj : $(SRC)\line.c .AUTODEPEND
        *$(CC) $(CFLAGS) -fo=$@ $<
	
$(OBJ)\xarrow_.obj : $(SRC_CURSORS)\xarrow_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xcrossh_.obj : $(SRC_CURSORS)\xcrossh_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xe_.obj : $(SRC_CURSORS)\xe_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xew_.obj : $(SRC_CURSORS)\xew_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xhand_.obj : $(SRC_CURSORS)\xhand_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xhelp_.obj : $(SRC_CURSORS)\xhelp_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xinsert_.obj : $(SRC_CURSORS)\xinsert_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xmove_.obj : $(SRC_CURSORS)\xmove_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xn_.obj : $(SRC_CURSORS)\xn_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xne_.obj : $(SRC_CURSORS)\xne_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xnesw_.obj : $(SRC_CURSORS)\xnesw_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xns_.obj : $(SRC_CURSORS)\xns_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xnw_.obj : $(SRC_CURSORS)\xnw_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xnwse_.obj : $(SRC_CURSORS)\xnwse_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xs_.obj : $(SRC_CURSORS)\xs_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xse_.obj : $(SRC_CURSORS)\xse_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xsw_.obj : $(SRC_CURSORS)\xsw_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xw_.obj : $(SRC_CURSORS)\xw_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
	
$(OBJ)\xwait_.obj : $(SRC_CURSORS)\xwait_.asm .AUTODEPEND
        *$(AS) $(AFLAGS) -fo=$@ $<
