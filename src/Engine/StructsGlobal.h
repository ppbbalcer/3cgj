#ifndef __STRUCTS_GLOBAL_H__
#define __STRUCTS_GLOBAL_H__

#include <SDL.h>
#include <SDL_image.h>
#include "Audio.h"

enum DIRECT {
	DIRECT_NO_WAY = 0,
	DIRECT_LEFT = 1,
	DIRECT_RIGHT = 2,
	DIRECT_UP = 4,
	DIRECT_DOWN = 8 
};

struct ResourceItem {
	/* Configure part */
	const char*		path;
	const bool		optOptymalize;
	const bool		optLoadSurface;
	const bool		optLoadTexture;
	const Uint32		optTextureColorKeyRGB; //Set for texture if value other that 0

	/* Loaded part */
	SDL_Surface* surface;
	SDL_Texture* texture;
	int width;
	int height;
};

enum audioType {
	AUDIO_TYPE_SOUND,
	AUDIO_TYPE_MUSIC,
	END_AUDIO_TYPE
};

struct AudioResource {
	const char *path;
	enum audioType type;
	union {
		AudioSound *sound;
		AudioMusic *music;
	} res ;
};

#endif /* __STRUCTS_GLOBAL_H__ */