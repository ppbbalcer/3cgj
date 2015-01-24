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
	Player(RTexture* texture, IMap * map) : Character(texture, map) { _last_shot_time = clock() - FIREBALL_MIN_DIFF_MS * (CLOCKS_PER_SEC / 1000); };
	~Player(void);

	int getMana();
	void useMana(int howMuchMana);
	void restoreMana(int howMuchMana);

	Fireball * Shoot();
};

#endif
