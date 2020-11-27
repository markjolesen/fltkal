
OBJ=..\obj
SRC=..\src
LIB=..\..\lib
INC=..\include

RM=del
AR=wlib
AS=wasm
CC=wcc386
CXX=wpp386

INCLUDES=-i$(INC) -i..\..\zlib
# DEFINES=-DFT2_BUILD_LIBRARY -DFT_CONFIG_MODULES_H="<ftmodule.h>"
DEFINES=-DFT2_BUILD_LIBRARY

AFLAGS= -d1 -3r -mf -bt=DOS $(INCLUDES) $(DEFINES)
CFLAGS= -d3 -3r -mf -bt=DOS $(INCLUDES) $(DEFINES)
CXXFLAGS= -d3 -3r -mf -bt=DOS $(INCLUDES) $(DEFINES)

LIB_FREETYPE=$(LIB)\ft2_10_4.lib

SRC_MOD= $(SRC)\base
OBJ_MOD= &
	$(OBJ)\ftinit.obj &
	$(OBJ)\ftsystem.obj &
	$(OBJ)\ftdebug.obj &
	$(OBJ)\ftglyph.obj &
	$(OBJ)\ftbitmap.obj
	
SRC_BASE= $(SRC)\base\ftbase.c
OBJ_BASE= $(SRC)\ftbase.obj

SRC_CACHE= $(SRC)\cache\ftcache.c
OBJ_CACHE= $(OBJ)\ftcache.obj

SRC_TRUETYPE= $(SRC)\truetype\truetype.c
OBJ_TRUETYPE= $(OBJ)\truetype.obj
    
SRC_SMOOTH= $(SRC)\smooth\smooth.c
OBJ_SMOOTH= $(OBJ)\smooth.obj
   
SRC_RASTER= $(SRC)\raster\raster.c
OBJ_RASTER= $(OBJ)\raster.obj

SRC_SFNT= $(SRC)\sfnt\sfnt.c
OBJ_SFNT= $(OBJ)\sfnt.obj

SRC_ZLIB= $(SRC)\gzip\ftgzip.c
OBJ_ZLIB= $(OBJ)\ftgzip.obj

OBJ_FREETYPE=&
    $(OBJ_MOD) &
    $(OBJ_BASE) &
    $(OBJ_CACHE) &
    $(OBJ_TRUETYPE) &
    $(OBJ_SMOOTH) &
    $(OBJ_RASTER) &
    $(OBJ_SFNT) &
    $(OBJ_ZLIB)

all : $(LIB_FREETYPE)

$(LIB_FREETYPE) : $(OBJ_FREETYPE)
    *$(AR) $@ $(OBJ_FREETYPE: = )
    
.c: $(SRC_MOD)
    
.c{$(OBJ)}.obj  : .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ_BASE) : $(SRC_BASE) .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ_CACHE) : $(SRC_CACHE) .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ_TRUETYPE) : $(SRC_TRUETYPE) .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ_SMOOTH) : $(SRC_SMOOTH) .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
   
$(OBJ_RASTER) : $(SRC_RASTER) .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ_SFNT) : $(SRC_SFNT) .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ_ZLIB) : $(SRC_ZLIB) .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
