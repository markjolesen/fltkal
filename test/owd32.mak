
SYSTEM=dos4g

CXX=wpp386

OBJ=..\obj
BIN=..\bin
LIB=..\lib

LIB_ZLIB=$(LIB)\z.lib
LIB_PNG=$(LIB)\png.lib
LIB_JPEG=$(LIB)\jpeg.lib
LIB_FLTK=$(LIB)\fltk.lib
LIB_FT=..\lib\ft2_10_4.lib
LIB_OW32SVGA=..\lib\ow32svga.lib

LIBS=&
    $(LIB_FLTK), &
    $(LIB_OW32SVGA), &
    $(LIB_FT), &
    $(LIB_JPEG), &
    $(LIB_PNG), &
    $(LIB_ZLIB)

DEFINES=-DUSE_OWD32

INCLUDES=-i.. -i..\ft131

CXXFLAGS=-3r -mf -bt=DOS $(DEBUG) $(INCLUDES) $(DEFINES)

EXES=&
    $(BIN)\omenubar.exe &
    $(BIN)\ohello.exe  &
    $(BIN)\otree.exe &
    $(BIN)\oinput.exe 
    
all : $(EXES) .SYMBOLIC

$(BIN)\ohello.exe : $(OBJ)\ohello.obj 
    *wlink NAME $^@ DEBUG ALL SYSTEM $(SYSTEM) FILE $< LIBRARY $(LIBS)
    
$(BIN)\otree.exe : $(OBJ)\otree.obj 
    *wlink NAME $^@ DEBUG ALL SYSTEM $(SYSTEM) FILE $< LIBRARY $(LIBS)
    
$(BIN)\omenubar.exe : $(OBJ)\omenubar.obj 
    *wlink NAME $^@ DEBUG ALL SYSTEM $(SYSTEM) FILE $< LIBRARY $(LIBS)
    
$(BIN)\oinput.exe : $(OBJ)\oinput.obj 
    *wlink NAME $^@ DEBUG ALL SYSTEM $(SYSTEM) FILE $< LIBRARY $(LIBS)

$(OBJ)\ohello.obj : thello.cxx .AUTODEPEND
    $(CXX) $(CXXFLAGS) -fo=$^@ $<

$(OBJ)\otree.obj : ttree.cxx .AUTODEPEND
    $(CXX) $(CXXFLAGS) -fo=$^@ $<
    
$(OBJ)\omenubar.obj : tmenubar.cxx .AUTODEPEND
    $(CXX) $(CXXFLAGS) -fo=$^@ $<
    
$(OBJ)\oinput.obj : tinput.cxx .AUTODEPEND
    $(CXX) $(CXXFLAGS) -fo=$^@ $<

