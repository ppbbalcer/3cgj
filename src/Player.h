#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"
#include <time.h>

class Player : public Character
{
private:
	int _mana;
	int _time_to_shot;

public:
	Player(RTexture* texture, IMap * map, int hp, int mana);
	~Player(void);
	virtual void OnUpdate(int time_ms);

	int getMana();
	void restoreMana(int howMuchMana);
	virtual int crucio(int howMuchCrucio);

	Fireball * Shoot();
};

#endif
