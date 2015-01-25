#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Character.h"
#include <time.h>
#include "Engine/AStar.h"

#define RANDOM_DIRECTION_CHANGE_TIME_MS 500

enum enemy_ai {
	ENEMY_AI_UNKNOWN,
	ENEMY_AI_DEFAULT,
	ENEMY_AI_OFF,
	ENEMY_AI_DISTANCE
};

/**
 * class represents non-player characters
 */
class Enemy : public Character
{
	//! in milliseconds
	clock_t _time_to_attack;
	clock_t _time_to_random_direction;
	//! ai instance
	enemy_ai _ai;
public:
	Enemy(RTexture* texture, IMap * map, int hp, int ai);
	~Enemy(void);
	virtual void OnRender(SDL_Renderer *renderer);

	virtual void OnUpdate(int time_ms);
	enemy_ai getAI() { return _ai; }
	virtual int crucio(int howMuchCrucio);
	DIRECT getRandomDirection();
	AStarWay_t way;
};

#endif
