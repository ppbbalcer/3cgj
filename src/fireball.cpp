#include "fireball.h"
#include "Engine/Engine.h"
#include "Engine/Character.h"
#include <cmath>
Fireball::	Fireball(int start_x, int start_y, int _vx, int _vy)
{
	x=start_x;
	y=start_y;
	vx=_vx;
	vy=_vy;
	posX=x*EngineInst->getTileSize();
	posY=y*EngineInst->getTileSize();
}
int Fireball::updatePosition(IMap *map, int time_ms)
{
	int tile_size = EngineInst->getTileSize();
	float dist = 0.01*tile_size * time_ms;
	posX=posX+dist*vx;
	posY=posY+dist*vy;

	x=round(1.0*posX/tile_size);
	y=round(1.0*posY/tile_size);
	if (map->GetFieldAt(x,y)->IsOccupied())
	{
		Character * whoishere =
			map->GetFieldAt(x,y)->WhoIsHere();
		whoishere->crucio(20);
		// harm someone
		return 1;
	}
	if (map->GetFieldAt(x,y)->IsObstacle())
	{
		return 1;
	}
	return 0;
}

int Fireball::getPosX()
{
	return posX;
}

int Fireball::getPosY()
{
	return posY;
}
