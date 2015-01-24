#ifndef __FIREBALL_H
#define __FIREBALL_H
#include "MapLogic/map.h"
class Fireball {
	int x; // in tiles
	int y;
	int vx;
	int vy;
	int posX; // in pixels (margin not included)
	int posY;
public:
	Fireball(int start_x, int start_y, int _vx, int _vy);

	/**
	 * Attempt to update position
	 * @return return code of 1 warrants removal of this particular
	 * fireball object. It either hit the wall and can be discarded
	 * or it hit its proper target and should be discarded.
	 */
	int updatePosition(IMap *map, int time_ms);

	int getPosX();
	int getPosY();
};

#endif
