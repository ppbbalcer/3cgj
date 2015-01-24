#ifndef OBJECT_H
#define OBJECT_H

#include <SDL_render.h>
#include "Engine\RTexture.h"
#include "Character.h"

class Object {
public:
	virtual void update(int dt) = 0;
	virtual void onAction(Character *player) = 0;
	virtual void render(SDL_Renderer *renderer, RTexture *tex) = 0;
};


class RoomDoor : Object {
	void update(int dt);
	void onAction(Character *player);
	void render(SDL_Renderer *renderer, RTexture *tex);
};

#endif OBJECT_H