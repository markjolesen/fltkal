# License

    Copyright (C) 2018 The fltkal authors

    Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
    or any later version published by the Free Software Foundation;
    with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
    A copy of the license is included in the section entitled "GNU
    Free Documentation License"

# DJGPP

[DJGPP Installing](http://www.delorie.com/djgpp/doc/ug/intro/installing-djgpp.html)

```
http://www.delorie.com/djgpp/doc/ug/intro/installing-djgpp.html
```

[unzip](ftp://ftp.delorie.com/pub/djgpp/current/unzip32.exe) 

```
ftp://ftp.delorie.com/pub/djgpp/current/unzip32.exe
```

Following are the DJGPP software tools used to build fltkal and Allegro.

[DJGPP V2](ftp://ftp.delorie.com/pub/djgpp/current/v2/)

```
ftp://ftp.delorie.com/pub/djgpp/current/v2/
```

* djdev205.zip

[DJGPP V2GNU](ftp://ftp.delorie.com/pub/djgpp/current/v2gnu/) 

```
ftp://ftp.delorie.com/pub/djgpp/current/v2gnu/
```

* bnu2291b.zip
* fil41br2.zip
* gcc346b.zip
* gpp346b.zip
* mak421b.zip
* sed44b.zip
* txi413br3.zip (optional)
* gdb771b.zip (optional)

# Allegro 4

[Allegro 4.2.3.1](https://github.com/liballeg/allegro5/releases/download/v4-2-3-1/all4231.zip) 

```
https://github.com/liballeg/allegro5/releases/download/v4-2-3-1/all4231.zip
```

These instructions assume Allegro was unpacked into c:\source.

```
cd \source\allegro
fix.bat djgpp
make UNIX_TOOLS=1
```

# fltkal

The source tree for fltk is as follows:

```
fltkal
├── bin
├── doc
├── fl
├── jpeg
├── lib
├── make
├── obj
├── png
├── src
│   ├── cursors
│   ├── drivers
│   │   └── allegro4
│   └── xutf8
│       └── headers
├── test
│   └── pixmaps
└── zlib
```

fltkal requires Allegro, jpeg, png and zlib libraries.  As can be seen
above, the jpeg, png, and zlib sources come bundled with fltkal. To
compile, run make in zlib, png, and jpeg subdirectories. Following,
run make in the make directory.

```
cd \source\fltkal\zlib
make
cd ..\png
make
cd ..\jpeg
make
cd ..\make
make
```

Object files are placed into the obj directory and libraries are placed
into the lib directory.  Once the libraries have been compiled, the test
programs can be built. The makefile assumes the Allegro library is in
the \source directory.  The programs are placed into the bin directory.

```
cd c:\source\fltkal\test
make
```

# Applications

## hello.cxx

```
#include <fl/fl.h>
#include <fl/win.h>
#include <fl/box.h>

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(340,180);
  Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");
  box->box(FL_UP_BOX);
  box->labelfont(FL_BOLD+FL_ITALIC);
  box->labelsize(36);
  box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
```

Compiling applications requires setting up the include search
path. Linking requires setting the library search path and libraries
that will be linked.

```
INCLUDES=-I /source/allegro/include -I /source/fltkal
LIBPATH=-L /source/allegro/lib/djgpp -L /source/fltkal/lib
LIBS=-l fltk -l alleg -l png -l jpeg -l z
```

## compiling

```
gcc -o hello.o -c hello.cxx -I /source/allegro/include -I /source/fltkal
```

## linking

```
gcc -o hello.exe hello.o -L /source/allegro/lib/djgpp -L /source/fltkal/lib -l fltk -l alleg -l png -l jpeg -l z
```

## makefile

NOTE: DOS command line has a limit of 127 characters. It is advantegous
to use DJGPP makefiles that do not impose such limits.

```
INCLUDES=-I /source/allegro/include -I /source/fltkal
LIBPATH=-L /source/allegro/lib/djgpp -L /source/fltkal/lib
LIBS=-l fltk -l alleg -l png -l jpeg -l z

OBJS= hello.o

hello.exe : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBPATH) $(LIBS)

%.o : %.cxx
	$(CXX) $(INCLUDES) -c $< -o $@ 

```

# Porting

To port your application, simply include the normal FLTK headers and compile for the specific platform.

```
#if !defined(__DJGPP__)
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#else
#include <fl/fl.h>
#include <fl/win.h>
#include <fl/box.h>
#endif
```

See FLTK [Basics](http://www.fltk.org/doc-1.1/basics.html) for more information.

