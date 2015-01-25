#include "level.h"

Level::Level(int id, int initial_scene) {
	this->id = id;
	this->initial_scene = initial_scene;
	current_scene = -1;
}

Level::~Level() {
	for (scenes_map_t::iterator itr = scenes.begin(); itr != scenes.end(); ++itr) {
		delete itr->second;
	}
	scenes.clear();
}

SceneGame* Level::getCurrentScene() {
	if (current_scene == -1) //first run
		setCurrentScene(initial_scene);
	return scenes[current_scene];
}
void Level::setId(int i) {
	if (i==id)
		return;
	id=i;
	scenes.clear();
}

void Level::setCurrentScene(int scene_id) {
	if (scenes.find(scene_id) == scenes.end()) {
		scenes[scene_id] = new SceneGame(this, scene_id);
	}
	current_scene = scene_id;
	EngineInst->setNextScene(getCurrentScene());
}

void Level::resetCurrent() {
	scenes[current_scene]->OnFreeBase();
	delete scenes[current_scene];
	scenes.erase(current_scene);
	setCurrentScene(current_scene);
}
