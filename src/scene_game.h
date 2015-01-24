#ifndef __SCENE_GAME_H
#define __SCENE_GAME_H
#include <list>
#include "Engine/Scene.h"
#include "Engine/Engine.h"
#include "Engine/RTexture.h"
#include "Engine/Character.h"
#include "MapLogic/map.h"
class Fireball;
/**
 * scene that contains map and character
 */
class SceneGame: public Scene {
	std::list<Fireball *> fireballs;
	RTexture *_background;
	Character *_player1, *_player2;
	std::vector<Character*> _enemys;
	RTexture *_tiles;
	IMap *map;
public:
	SceneGame();
	virtual void OnLoad();
	virtual void OnFree();
	virtual void OnUpdate(int timems);
	virtual void OnRender(SDL_Renderer* renderer);
	virtual ~SceneGame();
};


#endif


