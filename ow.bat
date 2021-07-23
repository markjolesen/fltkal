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
wmake -f owd32.mak
cd ..\..

cd make
wmake -f owd32.mak
cd ..

cd test
wmake -f owd32.mak
cd ..
