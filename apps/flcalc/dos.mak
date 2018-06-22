#Makefile for fltk_test

LIBPATHS=-L ../../lib

ifeq (, $(shell which uname))
UNAME:=DOS
else
UNAME:= $(shell uname)
endif

ifeq ($(UNAME), DOS)
ALLEGRO=/source/allegro
ALLEGROLIB=$(ALLEGRO)/lib/djgpp
ALLEGROINC=$(ALLEGRO)/include
REDIRCOMMAND=redir -o $(basename $@).err -eo
LIBPATHS+= -L $(ALLEGROLIB)
DEFINES=
else
DEFINES=-D__DJGPP__
endif

INCLUDES=-I../../
CXXFLAGS=-g -ggdb $(INCLUDES) $(DEFINES)
LIBS= $(LIBPATHS) -l fltk -l alleg -l png -l jpeg -l z

PROJECT= flcalc
SOURCES= main.cxx calcui.cxx calcinp.cxx muparser/parser.cpp  muparser/base.cpp muparser/bytecode.cpp muparser/callback.cpp muparser/error.cpp muparser/reader.cpp
OBJECTS= main.o calcui.o calcinp.o parser.o base.o bytecode.o callback.o error.o reader.o

$(PROJECT): $(OBJECTS)
	$(CXX)  -O2 -g $(OBJECTS) $(LIBS) -o $(PROJECT)
	@echo Compilation Complete

$(OBJECTS): $(SOURCES)
	@echo Compiling Sources
	$(CXX) $(CXXFLAGS) -O2 -c $(SOURCES)

clean:
	@echo Deleting up $(OBJECTS) $(PROJECT)
	rm -f *.o
