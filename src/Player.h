#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"
#include <time.h>

class Player : public Character
{
private:
	int _mana;
	clock_t _last_shot_time;

public:
	Player(RTexture* texture, IMap * map, int hp, int mana);
	~Player(void);

	int getMana();
	void restoreMana(int howMuchMana);
	virtual int crucio(int howMuchCrucio);

	Fireball * Shoot();
};

#endif
