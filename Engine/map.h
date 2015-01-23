#ifndef __MAP_H
#define __MAP_H
/* following constants define width and height of map in tiles */

enum FieldType {
  EMPTY = 0,
  WALL = 2,
  FLOOR,
  DESK,
  
  
};
class IField {
public:
  // as per enum FieldType
  virtual int GetType() = 0;
};



class IMap {
  
 public:
  /**
   * @param type type of map to be factored (as per enum MapType)
   * @param parameter - parameter as per map time. probably a path
   * @return pointer to a map. If failed to generate, 0 is returned
   *   and an exception is thrown
   */
  static IMap * Factory(int type, char * parameter);
  /**
   * @return in fields
   */
  virtual int GetWidth() = 0;
  /**
   *
   * @return in fields
   */
  virtual int GetHeight() = 0;
  /**
   * @param x,y field position (0-n)
   */
  virtual IField* GetFieldAt(int x, int y) = 0;
  virtual ~IMap() {};
};



#endif
