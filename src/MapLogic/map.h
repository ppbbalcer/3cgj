#ifndef __MAP_H
#define __MAP_H
#include "field.h"
#include <utility>
#include <list>

struct enemy_definition {
	int x;
	int y;
	int hp;
	int ai;
};

struct map_params {
	int alpha;
	int start_mana;
	int start_hp;
};

typedef std::pair<int,int> starting_pos;
typedef std::list<starting_pos> start_list;
typedef std::list<enemy_definition*> enemies_list;

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

	virtual const starting_pos & GetPlayer1Start() =0;
	virtual const starting_pos & GetPlayer2Start() =0;
	virtual const enemies_list & GetEnemies() = 0;
	virtual map_params* getParams() = 0;
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
