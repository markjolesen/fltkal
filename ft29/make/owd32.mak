
OBJ=..\obj
SRC=..\src
LIB=..\lib
INC=..\include

RM=del
AS=wasm
CC=wcc386
CXX=wpp386

INCLUDES=-i$(INC)
#DEFINES=-DFT2_BUILD_LIBRARY -DFT_CONFIG_MODULES_H="<ftmodule.h>"
DEFINES=-DFT2_BUILD_LIBRARY 

AFLAGS= -d1 -3r -mf -bt=DOS $(INCLUDES) $(DEFINES)
CFLAGS= -d3 -3r -mf -bt=DOS $(INCLUDES) $(DEFINES)
CXXFLAGS= -d3 -3r -mf -bt=DOS $(INCLUDES) $(DEFINES)

LIB_FREETYPE=$(LIB)\freetype.lib

OBJ_BASE=&
    $(OBJ)\basepic.obj &
    $(OBJ)\ftadvanc.obj &
    $(OBJ)\ftapi.obj &
    $(OBJ)\ftbase.obj &
    $(OBJ)\ftbbox.obj &
    $(OBJ)\ftbdf.obj &
    $(OBJ)\ftbitmap.obj &
    $(OBJ)\ftcalc.obj &
    $(OBJ)\ftcid.obj &
    $(OBJ)\ftdbgmem.obj &
    $(OBJ)\ftdebug.obj &
    $(OBJ)\ftfntfmt.obj &
    $(OBJ)\ftfstype.obj &
    $(OBJ)\ftgasp.obj &
    $(OBJ)\ftgloadr.obj &
    $(OBJ)\ftglyph.obj &
    $(OBJ)\ftgxval.obj &
    $(OBJ)\fthash.obj &
    $(OBJ)\ftinit.obj &
    $(OBJ)\ftlcdfil.obj &
    $(OBJ)\ftmac.obj &
    $(OBJ)\ftmm.obj &
    $(OBJ)\ftobjs.obj &
    $(OBJ)\ftotval.obj &
    $(OBJ)\ftoutln.obj &
    $(OBJ)\ftpatent.obj &
    $(OBJ)\ftpfr.obj &
    $(OBJ)\ftpic.obj &
    $(OBJ)\ftpsprop.obj &
    $(OBJ)\ftrfork.obj &
    $(OBJ)\ftsnames.obj &
    $(OBJ)\ftstream.obj &
    $(OBJ)\ftstroke.obj &
    $(OBJ)\ftsynth.obj &
    $(OBJ)\ftsystem.obj &
    $(OBJ)\fttrigon.obj &
    $(OBJ)\fttype1.obj &
    $(OBJ)\ftutil.obj &
    $(OBJ)\ftwinfnt.obj &
    $(OBJ)\md5.obj
    
SRC_BASE=$(SRC)\base

OBJ_CACHE=&
    $(OBJ)\ftcache.obj &
    $(OBJ)\ftcbasic.obj &
    $(OBJ)\ftccache.obj &
    $(OBJ)\ftccmap.obj &
    $(OBJ)\ftcglyph.obj &
    $(OBJ)\ftcimage.obj &
    $(OBJ)\ftcmanag.obj &
    $(OBJ)\ftcmru.obj &
    $(OBJ)\ftcsbits.obj

SRC_CACHE=$(SRC)\cache

OBJ_TRUETYPE=&
    $(OBJ)\truetype.obj &
    $(OBJ)\ttdriver.obj &
    $(OBJ)\ttgload.obj &
    $(OBJ)\ttgxvar.obj &
    $(OBJ)\ttinterp.obj &
    $(OBJ)\ttobjs.obj &
    $(OBJ)\ttpic.obj &
    $(OBJ)\ttpload.obj &
    $(OBJ)\ttsubpix.obj
    
SRC_TRUETYPE=$(SRC)\truetype
    
OBJ_SMOOTH=&
    $(OBJ)\ftgrays.obj &
    $(OBJ)\ftsmooth.obj &
    $(OBJ)\ftspic.obj &
    $(OBJ)\smooth.obj
    
SRC_SMOOTH=$(SRC)\smooth
   
OBJ_RASTER=&
    $(OBJ)\ftraster.obj &
    $(OBJ)\ftrend1.obj &
    $(OBJ)\raster.obj &
    $(OBJ)\rastpic.obj
    
SRC_RASTER=$(SRC)\raster

OBJ_SFNT=&
    $(OBJ)\pngshim.obj &
    $(OBJ)\sfdriver.obj &
    $(OBJ)\sfnt.obj &
    $(OBJ)\sfntpic.obj &
    $(OBJ)\sfobjs.obj &
    $(OBJ)\ttbdf.obj &
    $(OBJ)\ttcmap.obj &
    $(OBJ)\ttkern.obj &
    $(OBJ)\ttload.obj &
    $(OBJ)\ttmtx.obj &
    $(OBJ)\ttpost.obj &
    $(OBJ)\ttsbit.obj
    
SRC_SFNT=$(SRC)\sfnt

OBJ_FREETYPE=&
    $(OBJ_BASE) &
    $(OBJ_CACHE) &
    $(OBJ_TRUETYPE) &
    $(OBJ_SMOOTH) &
    $(OBJ_RASTER) &
    $(OBJ_SFNT)

all : $(LIB_FREETYPE)

$(LIB_FREETYPE) : $(OBJ_FREETYPE)
    wlib $@ @owd32.lbc
    
# BASE

$(OBJ)\basepic.obj :  $(SRC_BASE)\basepic.c  .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftadvanc.obj : $(SRC_BASE)\ftadvanc.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftapi.obj :    $(SRC_BASE)\ftapi.c    .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<
    
$(OBJ)\ftbase.obj :   $(SRC_BASE)\ftbase.c   .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftbbox.obj :   $(SRC_BASE)\ftbbox.c   .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftbdf.obj :    $(SRC_BASE)\ftbdf.c    .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftbitmap.obj : $(SRC_BASE)\ftbitmap.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftcalc.obj :   $(SRC_BASE)\ftcalc.c   .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftcid.obj :    $(SRC_BASE)\ftcid.c    .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftdbgmem.obj : $(SRC_BASE)\ftdbgmem.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftdebug.obj :  $(SRC_BASE)\ftdebug.c  .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftfntfmt.obj : $(SRC_BASE)\ftfntfmt.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftfstype.obj : $(SRC_BASE)\ftfstype.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftgasp.obj :   $(SRC_BASE)\ftgasp.c   .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftgloadr.obj : $(SRC_BASE)\ftgloadr.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftglyph.obj :  $(SRC_BASE)\ftglyph.c  .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftgxval.obj :  $(SRC_BASE)\ftgxval.c  .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\fthash.obj :   $(SRC_BASE)\fthash.c   .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftinit.obj :   $(SRC_BASE)\ftinit.c   .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftlcdfil.obj : $(SRC_BASE)\ftlcdfil.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftmac.obj :    $(SRC_BASE)\ftmac.c    .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftmm.obj :     $(SRC_BASE)\ftmm.c     .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftobjs.obj :   $(SRC_BASE)\ftobjs.c   .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftotval.obj :  $(SRC_BASE)\ftotval.c  .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftoutln.obj :  $(SRC_BASE)\ftoutln.c  .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftpatent.obj : $(SRC_BASE)\ftpatent.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftpfr.obj :    $(SRC_BASE)\ftpfr.c    .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftpic.obj :    $(SRC_BASE)\ftpic.c    .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftpsprop.obj : $(SRC_BASE)\ftpsprop.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftrfork.obj :  $(SRC_BASE)\ftrfork.c  .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftsnames.obj : $(SRC_BASE)\ftsnames.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftstream.obj : $(SRC_BASE)\ftstream.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftstroke.obj : $(SRC_BASE)\ftstroke.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftsynth.obj :  $(SRC_BASE)\ftsynth.c  .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftsystem.obj : $(SRC_BASE)\ftsystem.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\fttrigon.obj : $(SRC_BASE)\fttrigon.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\fttype1.obj :  $(SRC_BASE)\fttype1.c  .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftutil.obj :   $(SRC_BASE)\ftutil.c   .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftwinfnt.obj : $(SRC_BASE)\ftwinfnt.c .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\md5.obj :      $(SRC_BASE)\md5.c      .AUTODEPEND 
    *$(CC) $(CFLAGS) -fo=$@ $<

# CACHE

$(OBJ)\ftcache.obj :  $(SRC_CACHE)\ftcache.c  .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftcbasic.obj : $(SRC_CACHE)\ftcbasic.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftccache.obj : $(SRC_CACHE)\ftccache.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftccmap.obj :  $(SRC_CACHE)\ftccmap.c  .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftcglyph.obj : $(SRC_CACHE)\ftcglyph.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftcimage.obj : $(SRC_CACHE)\ftcimage.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftcmanag.obj : $(SRC_CACHE)\ftcmanag.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftcmru.obj :   $(SRC_CACHE)\ftcmru.c   .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftcsbits.obj : $(SRC_CACHE)\ftcsbits.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

# TRUETYPE

$(OBJ)\truetype.obj : $(SRC_TRUETYPE)\truetype.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttdriver.obj : $(SRC_TRUETYPE)\ttdriver.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttgload.obj :  $(SRC_TRUETYPE)\ttgload.c  .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttgxvar.obj :  $(SRC_TRUETYPE)\ttgxvar.c  .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttinterp.obj : $(SRC_TRUETYPE)\ttinterp.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttobjs.obj :   $(SRC_TRUETYPE)\ttobjs.c   .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttpic.obj :    $(SRC_TRUETYPE)\ttpic.c    .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttpload.obj :  $(SRC_TRUETYPE)\ttpload.c  .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttsubpix.obj : $(SRC_TRUETYPE)\ttsubpix.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
# SMOOTH

$(OBJ)\ftgrays.obj : $(SRC_SMOOTH)\ftgrays.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftsmooth.obj : $(SRC_SMOOTH)\ftsmooth.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftspic.obj : $(SRC_SMOOTH)\ftspic.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\smooth.obj : $(SRC_SMOOTH)\smooth.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<
    
# RASTER

$(OBJ)\ftraster.obj : $(SRC_RASTER)\ftraster.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ftrend1.obj : $(SRC_RASTER)\ftrend1.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\raster.obj : $(SRC_RASTER)\raster.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\rastpic.obj : $(SRC_RASTER)\rastpic.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\pngshim.obj : $(SRC_SFNT)\pngshim.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\sfdriver.obj : $(SRC_SFNT)\sfdriver.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\sfnt.obj : $(SRC_SFNT)\sfnt.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\sfntpic.obj : $(SRC_SFNT)\sfntpic.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\sfobjs.obj : $(SRC_SFNT)\sfobjs.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttbdf.obj : $(SRC_SFNT)\ttbdf.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttcmap.obj : $(SRC_SFNT)\ttcmap.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttkern.obj : $(SRC_SFNT)\ttkern.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttload.obj : $(SRC_SFNT)\ttload.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttmtx.obj : $(SRC_SFNT)\ttmtx.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttpost.obj : $(SRC_SFNT)\ttpost.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

$(OBJ)\ttsbit.obj : $(SRC_SFNT)\ttsbit.c .AUTODEPEND
    *$(CC) $(CFLAGS) -fo=$@ $<

