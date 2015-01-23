#ifndef __RENDER_TEXTURE_H__
#define __RENDER_TEXTURE_H__

#include "StructsGlobal.h"

class RTexture {
public:
	RTexture(SDL_Texture* texture, int w, int h):_texture(texture), _width(w), _height(h), _x(0), _y(0) {
		SDL_assert(_texture && _width > 0 && _height > 0);
	}

	RTexture(const ResourceItem &resItem):_texture(resItem.texture), _width(resItem.width), _height(resItem.height), _x(0), _y(0)  {
		SDL_assert(_texture && _width > 0 && _height > 0);
	}

	void setPos( int x, int y ) { 
		_x = x;
		_y = y;
	}

	int getPosX() {
		return _x;
	}

	int getPosY() {
		return _y;
	}

	inline void render(SDL_Renderer* renderer) {
		renderRaw(renderer, _x, _y);
	}

	void renderRaw(SDL_Renderer* renderer, int x, int y ) {
		 SDL_Rect renderQuad = { x, y, _width, _height }; 
		 SDL_RenderCopy( renderer, _texture, NULL, &renderQuad );
	}

	//Gets image dimensions 
	int getWidth() {
		return _width;
	}

	int getHeight() {
		return _height;
	}

private: 

	//The actual hardware texture 
	SDL_Texture* _texture; //Image dimensions 
	int _width; 
	int _height;
	int _x; 
	int _y;
};


#endif /* __RENDER_TEXTURE_H__ */