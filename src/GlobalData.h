#ifndef __GLOBAL_DATA_H__
#define __GLOBAL_DATA_H__
#include "Engine/Scene.h"
#include "Engine/StructsGlobal.h"

extern const char GlobalFontPath[];

extern ResourceItem globalTextures[];
extern size_t globalTexturesSize;

extern class Scene* gScenes[];
extern size_t gScenesSize;

extern AudioResource globalAudios[];
extern size_t globalAudiosSize;

extern ResourceItem texturesScene[];
extern size_t texturesSceneSize;

extern ResourceItem texturesScene03[];
extern size_t texturesScene03Size;

#endif /* __GLOBAL_DATA_H__ */