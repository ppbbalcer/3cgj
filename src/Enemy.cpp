#include "Enemy.h"
#include "GlobalData.h"

Enemy::Enemy(RTexture *texture, IMap *map, int hp, int ai) : Character(texture, map)
{
	_type = TYPE_ENEMY;
	_last_rand_direction = 0;
	_health = hp;
	_ai = (enemy_ai)ai;
}

Enemy::~Enemy(void) {};

int Enemy::crucio(int howMuchCrucio)
{
	int hpRem = Character::crucio(howMuchCrucio);
	if (hpRem <= 0) {
		globalAudios[ENEMY_DEATH].res.sound->play();
	}
	return hpRem;
}

DIRECT Enemy::getRandomDirection()
{
	clock_t now = clock();
	if (((1.0 * now - _last_rand_direction) / (CLOCKS_PER_SEC / 1000)) <= RANDOM_DIRECTION_CHANGE_TIME_MS) {
		return DIRECT_NO_WAY;
	}

	_last_rand_direction = now;
	return (static_cast<DIRECT>((rand() % (DIRECT_END - 1)) + 1));
}
