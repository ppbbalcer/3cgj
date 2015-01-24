#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"

class Player : public Character
{
public:
	Player(RTexture* texture, IMap * map) : Character(texture, map) {};
	~Player(void);
};

#endif
