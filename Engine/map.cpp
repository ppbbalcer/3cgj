#include <Engine/map.h>
#include <cstdlib>
#include <Engine/generic_map.h>
#define MAP_WIDTH 1024
#define MAP_HEIGHT 1024
class Field : public IField {
public:
  int GetType() {
    return FLOOR;
  }
};



// a map loaded from file
class LoadedMap : public GenericMap {
public:
  LoadedMap(char * path);
  
};

// a map loaded from file
class GeneratedMap : public GenericMap     {

public:
  GeneratedMap(char * generator);
  
};


IMap * IMap::Factory(int type, char * parameter) {

  return 0;
}
