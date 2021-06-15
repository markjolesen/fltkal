cd zlib
wmake -f owd32.mak
cd ..

cd jpeg
wmake -f owd32.mak
cd ..

cd png
wmake -f owd32.mak
cd ..

cd ft2_10_4\make
wmake -f owd32.mak
cd ..\..

cd ow32svga\make
wmake -D DEBUG -f owd32.mak
cd ..\..

cd make -D DEBUG
wmake -f owd32.mak
cd ..

cd test -D DEBUG
wmake -f owd32.mak
cd ..
