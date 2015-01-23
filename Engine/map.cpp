#include <Engine/map.h>

#define MAP_WIDTH 1024
#define MAP_HEIGHT 1024
#include <cstdlib>
class Field : public IField {
  
};

class GenericMap: public IMap {
private:
  Field** fields;
  int width;
  int height;
protected:
  /**
   * allocate fields
   */
  int AllocateFields()
  {
     fields = (Field**)calloc(width*height,sizeof(void*));
  }
  int PlaceField(int x, int y, Field * field1)
  {
     fields[x+y*width] = field1;
  }
  void DeallocateFields() {
  for (int i = 0 ; i!=width*height; ++i ) {
  if (fields[ i])
    free(fields[i]);
    }

  }
public:
  IField* GetFieldAt(int x, int y) {
  return fields[x+y*width];
  }
  GenericMap()
  {
    width = 0;
    height = 0;
    fields = 0;
  }
  int GetWidth() {
    return width;
  }
  int GetHeight() {
    return height;
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
