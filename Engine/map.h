#ifndef __MAP_H
#define __MAP_H
/* following constants define width and height of map in tiles */

class Field {

};
class Map {
 private:
  
  
 public:
  int GetWidth();
  int GetHeight();
  Field* GetFieldAt();
};

#endif
