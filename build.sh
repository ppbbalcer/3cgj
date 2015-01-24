for i in `find . -name '*.o'` ; do
    rm $i
done

for i in `find . -name '*.cpp'` ; do
    echo COMPILE $i
     g++ -g $i -o `echo $i | sed 's/.cpp/.o/'` -Isrc  -I/usr/include/SDL2/ -c -std=gnu++11 -DFULLSCREEN
done
echo LINK
g++ src/*.o src/*/*.o -lSDL2 -lSDL2_mixer `sdl-config --libs`  -lSDL2_ttf -lSDL2_image -lpng -lz -o whatdowedonow 
