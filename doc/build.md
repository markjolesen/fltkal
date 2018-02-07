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

[unzip](ftp://ftp.delorie.com/pub/djgpp/current/unzip32.exe)

Following are the DJGPP software tools used to build fltkal and Allegro.

[DJGPP V2](ftp://ftp.delorie.com/pub/djgpp/current/v2/)

* djdev205.zip

[DJGPP V2GNU](ftp://ftp.delorie.com/pub/djgpp/current/v2gnu/)

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

These instructions assume Allegro was unpacked into C:\SOURCE.

```
cd C:\SOURCE\ALLEGRO
fix.bat djgpp
make UNIX\_TOOLS=1
```

ftp://ftp.delorie.com/pub/djgpp/current/v2tk/allegro/
all422ar2.zip


 


