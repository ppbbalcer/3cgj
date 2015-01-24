#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Engine/RTexture.h"
#include <unordered_map>
#include "MapLogic/map.h"

#define MAX_HEALTH 100

class Fireball;
class Character
{
public:
	enum Action {
		ACTION_NONE,
		ACTION_USE,
		ACTION_SHOT,
		ACTION_END
	};
	enum State {
		ALIVE = 1,
		DEAD,
		WON /* not playing now, because player has left the labyrinth */
	};
	Character(RTexture* texture, IMap * map);
	~Character();

	/**
	 * DEAD, ALIVE or WON
	 */
	int GetState();
	int getHealth();
	int crucio(int howMuchCrucio);
	void heal(int howMuchHeal);

	
	void OnRenderCircle(SDL_Renderer *renderer, int radius, int tileIdx);
	void OnRender(SDL_Renderer *renderer);
	void setPosTiles(int x, int y);

	int getPosX();
	int getPosY();
	int getPosBeforeX();
	int getPosAfterX();
	int getPosBeforeY();
	int getPosAfterY();

	/*
	
	int getPosX();
	int getPosY();
	int getPosTilesX();
	int getPosTilesX();
	DIRECT getActualDirect();
	float getMoveProgress(); /*0.0f to 1.0f*/


	Fireball * Shoot();
	void updateDirection(DIRECT directMove);
	void OnUpdate(int time_ms);

private:
	RTexture *_texture;

	IMap * _map;
	void setPos(int x, int y);
	int _health;
	int _speed;
	int _state;
	int last_dir_x;
	int last_dir_y;
	float _posX;
	float _posY;
	int _pos_before_x;
	int _pos_after_x;
	int _pos_before_y;
	int _pos_after_y;
};

#endif
