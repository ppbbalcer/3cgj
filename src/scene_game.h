#ifndef __SCENE_GAME_H
#define __SCENE_GAME_H

#include "Engine/Scene.h"
#include "Engine/Engine.h"
#include "Engine/RTexture.h"
#include "Engine/Character.h"
#include "MapLogic/map.h"
/**
 * scene that contains map and character
 */
class SceneGame: public Scene {
	RTexture *_background;
	Character *_player1, *_player2;
	RTexture *_tiles;
	IMap *map;
	int pcpos_before_x;
	int pcpos_after_x;
	int pcpos_before_y;
	int pcpos_after_y;
public:
	SceneGame();
	virtual void OnLoad();
	virtual void OnFree();
	virtual void OnUpdate(int timems);
	virtual void OnRender(SDL_Renderer* renderer);
	virtual ~SceneGame();
};


#endif


