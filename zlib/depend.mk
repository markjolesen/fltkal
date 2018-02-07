$(OBJ)/adler32.o: adler32.c  zutil.h \
  zlib.h zconf.h
$(OBJ)/compress.o: compress.c  \
  zlib.h zconf.h
$(OBJ)/crc32.o: crc32.c  zutil.h \
  zlib.h zconf.h crc32.h
$(OBJ)/deflate.o: deflate.c  \
  deflate.h zutil.h zlib.h zconf.h
$(OBJ)/gzclose.o: gzclose.c  \
  gzguts.h zlib.h zconf.h
$(OBJ)/gzlib.o: gzlib.c  gzguts.h \
  zlib.h zconf.h
$(OBJ)/gzread.o: gzread.c  gzguts.h \
  zlib.h zconf.h
$(OBJ)/gzwrite.o: gzwrite.c  \
  gzguts.h zlib.h zconf.h
$(OBJ)/infback.o: infback.c  zutil.h \
  zlib.h zconf.h inftrees.h inflate.h inffast.h inffixed.h
$(OBJ)/inffast.o: inffast.c  zutil.h \
  zlib.h zconf.h inftrees.h inflate.h inffast.h
$(OBJ)/inflate.o: inflate.c  zutil.h \
  zlib.h zconf.h inftrees.h inflate.h inffast.h inffixed.h
$(OBJ)/inftrees.o: inftrees.c  \
  zutil.h zlib.h zconf.h inftrees.h
$(OBJ)/trees.o: trees.c  deflate.h \
  zutil.h zlib.h zconf.h trees.h
$(OBJ)/uncompr.o: uncompr.c  zlib.h \
  zconf.h
$(OBJ)/zutil.o: zutil.c  zutil.h \
  zlib.h zconf.h gzguts.h
