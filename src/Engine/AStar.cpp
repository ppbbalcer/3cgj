#include "AStar.h"
#include <String.h>
#include <List>

#define IDXMAP(x,y) ((y) * (width) + (x))
#define IDXOBS(x,y) (((y)+1) * (width + 1) + ((x)+1))
static int statit_touchX[4] = {-1,1,0,0};
static int statit_touchY[4] = {0,0,-1,1};

enum DIRECT findAstar(int xStart, int yStart, int xEnd, int yEnd, int width, int height, funcIsObstacle func, void *data) {

	DIRECT result = DIRECT_NO_WAY;
	int* map = new int[width*height];
	int* obs = new int[(width + 2)*(height + 2)]; //Add border -1-unknow 0-ok 1-obs
	std::list<int> query;
	int i,vx,vy,vValUp,x,y,id;

	memset(obs, -1, (width + 2)*(height + 2)*sizeof(int));
	//Set borders
	for(int i=-1; i<width+1; ++i){
		obs[IDXOBS(i,-1)] = 1;
		obs[IDXOBS(i,height)] = 1;
	}
	for(int i=-1; i<height+1; ++i){
		obs[IDXOBS(-1,i)] = 1;
		obs[IDXOBS(width,i)] = 1;
	}

	memset(map, -1, width*height*sizeof(int));
	map[IDXMAP(xStart, yStart)] = 0;
	query.push_back(IDXMAP(xStart, yStart));

	while(!query.empty()) {
		vx = query.front();
		vValUp = map[vx] + 1;
		vy = vx / width;
		vx = vx % width;
		query.pop_front();
		for(i = 0; i<4; ++i) {
			x = vx + statit_touchX[i];
			y = vy + statit_touchY[i];
			id = IDXOBS(x,y);
			if(obs[id] < 0) {
				obs[id] = func(x,y,data)?1:0;
			}
			if(!obs[id]) {
				id = IDXMAP(x,y);
				if(map[id] < 0) {
					//Step5
					map[id] = vValUp;
					query.push_back(id);

					if(x == xEnd && y == yEnd) {
						goto STEP_FIND;
					}
				}
			}
		}
	}

	goto END;

STEP_FIND:
	
	query.clear();
	vx = xEnd;
	vy = yEnd;
	id = IDXMAP(xEnd, yEnd);
	vValUp = map[id] -1;
	query.push_back(id); //Dest point

	while(/*vx != xStart || vy != yStart*/vValUp > 0) {
		for(i = 0; i<4; ++i) {
			x = vx + statit_touchX[i];
			y = vy + statit_touchY[i];
			id = IDXOBS(x,y);
			if(!obs[id]) {
				id = IDXMAP(x,y);
				if(vValUp == map[id]) {
					vx = x;
					vy = y;
					--vValUp;
					query.push_back(id);
					break;
				}
			}
		}
	}

	if(!query.empty()) {
	vx = query.back();
	vy = vx / width;
	vx = vx % width;
	}


	if (xStart > vx) {
		result = DIRECT_LEFT;
	} else if (xStart < vx) {
		result = DIRECT_RIGHT;
	} else if (yStart > vy) {
		result = DIRECT_UP;
	} else if (yStart < vy) {
		result = DIRECT_DOWN;
	}

END:

	delete obs;
	delete map;
	return (DIRECT) result;
}

#undef IDXOBS
#undef IDXMAP