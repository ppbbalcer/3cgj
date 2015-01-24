#ifndef BASE_LEVEL_H
#define BASE_LEVEL_H

#include <vector>
#include "../Engine/Scene.h"
#include "../Engine/Engine.h"
#include "../Engine/RTexture.h"
#include "../Character.h"
#include "../MapLogic/map.h"

enum map_field {
	FIELD_UNKNOWN,
	FIELD_WALL,
	FIELD_FLOOR,
	MAX_MAP_FIELDS
};

#define MAX_WIDTH 256
#define MAX_HEIGHT 256

class BaseRoom {
public:
	BaseRoom(int id, int level_id);
	~BaseRoom();
	void render(RTexture *_tiles, SDL_Renderer *renderer);
private:
	int id;
	int level_id;
	int width;
	int height;
	IMap *map;
};

class BaseLevel : public Scene {
private:
	RTexture *_tiles;
	std::vector<BaseRoom*> rooms;
	int current_room;
	void setCurrentRoom(int room_id);
public:
	BaseLevel(int id, int rooms_count);
	virtual void OnLoad();
	virtual void OnFree();
	virtual void OnUpdate(int timems);
	virtual void OnRender(SDL_Renderer* renderer);
	virtual ~BaseLevel();
};

#endif BASE_LEVEL_H