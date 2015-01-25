#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Engine/RTexture.h"
#include <unordered_map>
#include "MapLogic/map.h"
#include "fireball.h"

#define MAX_HEALTH 100
#define MAX_MANA 100
#define DEFAULT_POWER_LEVEL 25;
#define SMALL_POTION_MANA_VAL 25
#define LARGE_POTION_MANA_VAL 50
#define SMALL_POTION_HEAL_VAL 25
#define LARGE_POTION_HEAL_VAL 50
#define MEDKIT_HEAL_VAL MAX_HEALTH
#define POWERUP_VAL 20

#define FIREBALL_MANA_COST 10
#define FIREBALL_MIN_DIFF_MS 500

enum CharacterType {
	TYPE_UNKNOWN,
	TYPE_ENEMY,
	TYPE_PLAYER,
	MAX_PLAYER_TYPE
};

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
	/**
	 * Unforgivable curse ;-) Inflicit damage on character
	 * @param howMuchCrucio amount of HPs to remove
	 */
	virtual int crucio(int howMuchCrucio);
	void heal(int howMuchHeal);
	virtual void Win();
	void OnRenderCircle(SDL_Renderer *renderer, int radius, int tileIdx);
	virtual void OnRender(SDL_Renderer *renderer);
	void renderAvatar(SDL_Renderer *renderer, int x, int y, SDL_RendererFlip flip);
	void setPosTiles(int x, int y);
	/* strength of damage dealt by character*/
	int GetPowerLevel();
	int SetPowerLevel(int x);

	/* in pixels */
	float getPosX();
	float getPosY();
	/* following four routines return position in TILES */
	/* position FROM which character is moving */
	int getPosBeforeX();
	int getPosAfterX();
	/* position to which character is moving */
	int getPosBeforeY();
	int getPosAfterY();
	/* if position TO equals FROM, character is NOT moving */
	
	void updateDirection(DIRECT directMove);
	virtual void OnUpdate(int time_ms);
	CharacterType getType() { return _type; }

protected:
	RTexture *_texture;
	int power_level;

	IMap * _map;
	void SetState(int state)
	{
		_state=state;
	}
private:
	void setPos(float x, float y);
	int _speed;
	int _state;
	float _posX;
	float _posY;
	int _pos_before_x;
	int _pos_after_x;
	int _pos_before_y;
	int _pos_after_y;

protected:
	int last_dir_x;
	int last_dir_y;
	CharacterType _type;
	int _health;

};

#endif
