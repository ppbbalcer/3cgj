#ifndef __MAP_H
#define __MAP_H
#include "MapLogic/field.h"

class IMap {
  
public:
	enum MapType {
		GENERATED=1, // not implemented
		LOADED=2
	};
	/**
	 * @param type type of map to be factored (as per enum MapType)
	 * @param parameter - parameter as per map time. probably a path
	 * @return pointer to a map. If failed to generate, 0 is returned
	 *   and an exception is thrown
	 */
	static IMap *Factory(int type, const char *parameter);
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
