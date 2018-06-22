#Makefile for fltk_test

PROJECT= flcalc
SOURCES= main.cxx calcui.cxx calcinp.cxx muparser/parser.cpp  muparser/base.cpp muparser/bytecode.cpp muparser/callback.cpp muparser/error.cpp muparser/reader.cpp
OBJECTS= main.o calcui.o calcinp.o parser.o base.o bytecode.o callback.o error.o reader.o

$(PROJECT): $(OBJECTS)
	$(CXX)  -O2 -g $(OBJECTS) -lfltk -lfltk_forms -lXext -lX11 -lm -o $(PROJECT)
	@echo Compilation Complete

$(OBJECTS): $(SOURCES)
	@echo Compiling Sources
	$(CXX) -O2 -c $(SOURCES)

clean:
	@echo Deleting up $(OBJECTS) $(PROJECT)
	rm -f *.o
