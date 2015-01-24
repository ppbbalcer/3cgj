#include "GlobalData.h"

const char GlobalFontPath[] = "Resources/gabriele-bad.ttf";

ResourceItem globalTextures[] = {
	{"Resources/laughing_man_logo.png",		false, true, true, 0,		NULL, NULL, 0, 0}, //Alfa problem fixed
	{"Resources/laughing_man_logo.png",		true, true, false, 0,		NULL, NULL, 0, 0},
	{"Resources/laughing_man.bmp",			true, true, false, 0,		NULL, NULL, 0, 0},
	{"Resources/background.png",			false, true, false, 0,		NULL, NULL, 0, 0},
};

size_t globalTexturesSize = sizeof(globalTextures) / sizeof(globalTextures[0]);

class Scene* gScene = NULL;

AudioResource globalAudios[] = {
	{"Resources/audio/high.wav", AUDIO_TYPE_SOUND, NULL},
	{"Resources/audio/low.wav", AUDIO_TYPE_SOUND, NULL},
	{"Resources/audio/fireball.wav", AUDIO_TYPE_SOUND, NULL},
};
size_t globalAudiosSize = sizeof(globalAudios) / sizeof(globalAudios[0]);

ResourceItem texturesScene[] = {
	{"Resources/laughing_man_logo.png",		false, true, true, 0,		NULL, NULL, 0, 0}, //Alfa problem fixed
};

size_t texturesSceneSize = sizeof(texturesScene) / sizeof(texturesScene[0]);

ResourceItem texturesScene03[] = {
	{"Resources/laughing_man_logo.png",		false, true, true, 0,		NULL, NULL, 0, 0}, //Alfa problem fixed
	{"Resources/background.png",			false, false, true, 0,		NULL, NULL, 0, 0},
	{"Resources/foo.png",				false, false, true, 0xFFFF,	NULL, NULL, 0, 0},
	{"Resources/tiles3.png",			false, false, true, 0x0,	NULL, NULL, 0, 0},
};

size_t texturesScene03Size = sizeof(texturesScene03) / sizeof(texturesScene03[0]);

ResourceItem texturesScene_game[] = {
	{"Resources/laughing_man_logo.png",		false, true, true, 0,		NULL, NULL, 0, 0}, //Alfa problem fixed
	{"Resources/background.png",			false, false, true, 0,		NULL, NULL, 0, 0},
	{"Resources/ludek.png",				false, false, true, 0xFFFF,	NULL, NULL, 0, 0},
	{"Resources/tiles/walls.png",			false, false, true, 0x0,	NULL, NULL, 0, 0},
};
size_t texturesScene_gameSize = sizeof(texturesScene03) / sizeof(texturesScene03[0]);
