#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Character.h"
#include <time.h>

#define RANDOM_DIRECTION_CHANGE_TIME_MS 500

enum enemy_ai {
	ENEMY_AI_UNKNOWN,
	ENEMY_AI_DEFAULT,
	ENEMY_AI_OFF
};

class Enemy : public Character
{
	clock_t _last_attack_around;
	clock_t _last_rand_direction;
	enemy_ai _ai;
public:
	Enemy(RTexture* texture, IMap * map, int hp, int ai);
	~Enemy(void);

	virtual void OnUpdate(int time_ms);
	enemy_ai getAI() { return _ai; }
	virtual int crucio(int howMuchCrucio);
	DIRECT getRandomDirection();
};

#endif
