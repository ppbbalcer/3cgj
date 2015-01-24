#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(RTexture* texture, IMap * map) : Character(texture, map) {};
	~Enemy(void);
};

#endif
