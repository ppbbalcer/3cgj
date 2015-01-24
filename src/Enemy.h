#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Character.h"
#include <time.h>

#define RANDOM_DIRECTION_CHANGE_TIME_MS 500

class Enemy : public Character
{
	clock_t _last_rand_direction;
public:
	Enemy(RTexture* texture, IMap * map);
	~Enemy(void);

	virtual int crucio(int howMuchCrucio);
	DIRECT getRandomDirection();
};

#endif
