#ifndef __ASTAR_H__
#define __ASTAR_H__
#include <list>
#include "StructsGlobal.h"

/* 
 * Handler to return that in position is obstacle 
 *  get values x, y and data from findAstar()
 */
typedef bool (*funcIsObstacle)(int, int, void*);
typedef std::pair<int,int> AStartPoint_t;
typedef std::list<AStartPoint_t> AStarWay_t;

/* 
 *	Can return direction DIRECT_LEFT & DIRECT_UP etc. 
 */
enum DIRECT findAstar(AStarWay_t &way, int maxSteps, int xStart, int yStart, int xEnd, int yEnd, int width, int height, funcIsObstacle func, void *data);

#endif /* __ASTAR_H__ */
