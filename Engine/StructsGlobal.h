#ifndef __STRUCTS_GLOBAL_H__
#define __STRUCTS_GLOBAL_H__

#include <SDL.h>
#include <SDL_image.h>

struct ResourceItem {
	/* Configure part */
	const char*		path;
	const bool		optOptymalize;
	const bool		optLoadSurface;
	const bool		optLoadTexture;
	const Uint32	optTextureColorKeyRGB; //Set for texture if value other that 0
	
	/* Loaded part */
	SDL_Surface* surface;
	SDL_Texture* texture;
	int width;
	int height;
};

#endif /* __STRUCTS_GLOBAL_H__ */