#ifndef __RENDER_TEXTURE_H__
#define __RENDER_TEXTURE_H__

#include "StructsGlobal.h"

class RTexture {
public:
	RTexture(SDL_Texture* texture, int w, int h);
	RTexture(const ResourceItem &resItem);

	inline void		setPos( int x, int y );
	inline int		getPosX();
	inline int		getPosY();
	inline void		render(SDL_Renderer* renderer);
	void			renderAll(SDL_Renderer* renderer, int x, int y );
	inline int		getWidth();
	inline int		getHeight();

	void			setTileSizeSrc(int size); //Size in file
	void			setTileSizeDst(int size); //Size on screen
	int				getTileSizeSrc();
	int				getTileSizeDst();
	int				getTilesNums();
	void			renderTile(SDL_Renderer* renderer, int x, int y, int tileIdx );

private: 

	//The actual hardware texture 
	SDL_Texture* _texture; //Image dimensions 
	int _width; 
	int _height;
	int _x; 
	int _y;

	int _tileSizeSrc;
	int _tileSizeDst;
	int _tileColumns;
	int _tileRows;
	
};

void RTexture::setPos( int x, int y ) { 
	_x = x;
	_y = y;
}

int RTexture::getPosX() {
	return _x;
}

int RTexture::getPosY() {
	return _y;
}

int RTexture::getWidth() {
	return _width;
}
int RTexture::getHeight() {
	return _height;
}

void RTexture::render(SDL_Renderer* renderer) {
	renderAll(renderer, _x, _y);
}

#endif /* __RENDER_TEXTURE_H__ */
