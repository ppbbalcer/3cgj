#ifndef __SCENE_MAIN_H__
#define __SCENE_MAIN_H__

#include "Engine/Scene.h"

class MainScene : public Scene {
public:
	virtual void OnLoad();
	virtual void OnFree();
	virtual void OnUpdate(int timems);
	virtual void OnRender(SDL_Renderer* renderer);

private:
	RTexture* _background;
	RTexture* _player;
	RTexture* _tiles;
};

#endif /* __SCENE_MAIN_H__ */