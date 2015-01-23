for i in `find . -name '*.cpp'` ; do
     g++ -g $i -o `echo $i | sed 's/.cpp/.o/'` -I. -I/usr/include/SDL2/ -c
done
g++ */*.o -lSDL2  `sdl-config --libs`  -lSDL2_ttf -lSDL2_image -lpng -lz -o whatdowedonow
