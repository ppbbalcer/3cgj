#include "Enemy.h"
#include "GlobalData.h"

Enemy::~Enemy(void) {};

int Enemy::crucio(int howMuchCrucio)
{
	int hpRem = Character::crucio(howMuchCrucio);
	if (hpRem <= 0) {
		globalAudios[ENEMY_DEATH].res.sound->play();
	}
	return hpRem;
}