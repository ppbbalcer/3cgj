#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"

class Player : public Character
{
private:
	int _mana;
public:
	Player(RTexture* texture, IMap * map) : Character(texture, map) {};
	~Player(void);

	int getMana();
	void useMana(int howMuchMana);
	void restoreMana(int howMuchMana);

	Fireball * Shoot();
};

#endif
