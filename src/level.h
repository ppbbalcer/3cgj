#ifndef LEVEL_H
#define LEVEL_H
#include "scene_game.h"
#include <map>

#define INITIAL_LEVEL_SCENE 0

typedef std::map<int, SceneGame*> scenes_map_t;

class Level {
private:
	int id;
	int current_scene;
	scenes_map_t scenes;
public:
	Level(int id);
	~Level();
	void setCurrentScene(int scene_id);
	void resetCurrent();
	SceneGame* getCurrentScene(); 
	int getId() { return id; }
};

#endif