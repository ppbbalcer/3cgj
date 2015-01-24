#include "RTexture.h"
#include <unordered_map>
#include "../MapLogic/map.h"

#define MAX_HEALTH 100

class Fireball;
class Character
{
public:
	enum Action {
		ACTION_MOVE_UP = 0,
		ACTION_MOVE_DOWN,
		ACTION_MOVE_RIGHT,
		ACTION_MOVE_LEFT,
		ACTION_USE,
		ACTION_SHOT,
		ACTION_END
	};
	enum State {
		ALIVE = 1,
		DEAD,
		WON /* not playing now, because player has left the labyrinth */
	};
	Character(IMap * map, RTexture *texture);
	~Character();

	/**
	 * DEAD, ALIVE or WON
	 */
	int GetState();
	int getHealth();
	int crucio(int howMuchCrucio);
	void heal(int howMuchHeal);

	void render(SDL_Renderer *renderer, RTexture *tiles);
	void setPosTiles(IMap *map, int x, int y);
	int getPosX();
	int getPosY();

	Fireball * Shoot();
	void updateDirection(IMap *map, Action action);
	void updatePosition(IMap *map, int time_ms, int tile_size);
	int getPosBeforeX();
	int getPosAfterX();
	int getPosBeforeY();
	int getPosAfterY();
	int getDirRight() {return _dirRight;}

private:
	IMap * map;
	void setPos(int x, int y);
	RTexture *_texture;
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


	bool _dirRight;
};
