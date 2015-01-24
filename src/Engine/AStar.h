#ifndef __ASTAR_H__
#define __ASTAR_H__

/* 
 * Handler to return that in position is obstacle 
 *  get values x, y and data from findAstar()
 */
typedef bool (*funcIsObstacle)(int, int, void*);

enum DIRECT {
	DIRECT_NO_WAY = 0,
	DIRECT_LEFT = 1,
	DIRECT_RIGHT = 2,
	DIRECT_UP = 4,
	DIRECT_DOWN = 8 
};

/* 
 *	Can return direction DIRECT_LEFT & DIRECT_UP etc. 
 */
enum DIRECT findAstar(int xStart, int yStart, int xEnd, int yEnd, int width, int height, funcIsObstacle func, void *data);

#endif /* __ASTAR_H__ */