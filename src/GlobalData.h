#ifndef __GLOBAL_DATA_H__
#define __GLOBAL_DATA_H__
#include "Engine/Scene.h"
#include "Engine/StructsGlobal.h"

extern int calcCircleAlfaRadius4[9][9];

extern const char GlobalFontPath[];

extern ResourceItem globalTextures[];
extern size_t globalTexturesSize;

extern class Scene* gScene;
extern size_t gScenesSize;

enum GameSounds {
	CLICK_ON = 0,
	CLICK_OFF = 1,
	FIREBALL = 2,
	SLURP = 3,
	HEARTBEAT = 4
};

extern AudioResource globalAudios[];
extern size_t globalAudiosSize;

extern ResourceItem texturesScene[];
extern size_t texturesSceneSize;

extern ResourceItem texturesScene03[];
extern size_t texturesScene03Size;
extern ResourceItem texturesScene_game[];
extern size_t texturesScene_gameSize;

#endif /* __GLOBAL_DATA_H__ */
