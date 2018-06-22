#Makefile for flcalc windows cygwin

PROJECT= flcalc
SOURCES= main.cxx calcui.cxx calcinp.cxx muparser/parser.cpp  muparser/base.cpp muparser/bytecode.cpp muparser/callback.cpp muparser/error.cpp muparser/reader.cpp
OBJECTS= main.o calcui.o calcinp.o parser.o base.o bytecode.o callback.o error.o reader.o

$(PROJECT): $(OBJECTS)
	$(CXX) -O2 -mwindows -DWIN32 -mno-cygwin $(OBJECTS) -lmingw32 -lfltk -lfltk_forms -lm -lole32 -luuid -lcomctl32 -lwsock32 -mwindows -mno-cygwin -o $(PROJECT)
	@echo Compilation Complete

$(OBJECTS): $(SOURCES)
	@echo Compiling Sources
	$(CXX) -O2 -Wall -pedantic -c $(SOURCES)

clean:
	@echo Deleting up $(OBJECTS) $(PROJECT)
	rm -f *.o
