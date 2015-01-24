#ifndef __ASTAR_H__
#define __ASTAR_H__
#include <list>

/* 
 * Handler to return that in position is obstacle 
 *  get values x, y and data from findAstar()
 */
typedef bool (*funcIsObstacle)(int, int, void*);
typedef std::pair<int,int> AStartPoint_t;
typedef std::list<AStartPoint_t> AStarWay_t;

enum DIRECT {
	DIRECT_NO_WAY = 0,
	DIRECT_LEFT = 1,
	DIRECT_RIGHT = 2,
	DIRECT_UP = 4,
	DIRECT_DOWN = 8 
};

bool IMap_isObstacle(int x, int y, void* objMap);

/* 
 *	Can return direction DIRECT_LEFT & DIRECT_UP etc. 
 */
enum DIRECT findAstar(AStarWay_t &way, int xStart, int yStart, int xEnd, int yEnd, int width, int height, funcIsObstacle func, void *data);

#endif /* __ASTAR_H__ */
