#include "RTexture.h"

RTexture::RTexture(SDL_Texture* texture, int w, int h):
	_texture(texture),
	_width(w),
	_height(h),
	_x(0),
	_y(0),
	_tileSizeSrc(0),
	_tileSizeDst(0),
	_tileColumns(0),
	_tileRows(0)
{
	SDL_assert(_texture && _width > 0 && _height > 0);
}

RTexture::RTexture(const ResourceItem &resItem):
	_texture(resItem.texture),
	_width(resItem.width),
	_height(resItem.height),
	_x(0),
	_y(0),
	_tileSizeSrc(0),
	_tileSizeDst(0),
	_tileColumns(0),
	_tileRows(0)
{
	SDL_assert(_texture && _width > 0 && _height > 0);
}

void RTexture::renderAll(SDL_Renderer* renderer, int x, int y ) {
	SDL_Rect renderQuad = { x, y, _width, _height };
	SDL_RenderCopy( renderer, _texture, NULL, &renderQuad );
}

void RTexture::setTileSizeSrc(int size) {
	_tileSizeSrc = size;
	if(_tileSizeSrc > 0 ) {
		_tileColumns = _width / _tileSizeSrc;
		_tileRows = _height / _tileSizeSrc;
	} else {
		_tileColumns = 0;
		_tileRows = 0;
	}
}

void RTexture::setTileSizeDst(int size) {
	_tileSizeDst = size;
}

int RTexture::getTileSizeSrc() {
	return _tileSizeSrc;
}

int RTexture::getTileSizeDst() {
	return _tileSizeDst;
}

int RTexture::getTilesNums() {
	return _tileColumns * _tileRows;
}

void RTexture::renderTile(SDL_Renderer* renderer, int x, int y, int tileIdx ) {
	if( _tileColumns > 0 && _tileRows > 0 && _tileSizeDst > 0 ) {
		int row = tileIdx / _tileColumns;
		int col = tileIdx % _tileColumns;

		SDL_Rect renderQuadSrc = { col * _tileSizeSrc, row * _tileSizeSrc, _tileSizeSrc, _tileSizeSrc };
		SDL_Rect renderQuadDst = { x, y, _tileSizeDst, _tileSizeDst };
		SDL_RenderCopy( renderer, _texture, &renderQuadSrc, &renderQuadDst );

	}
}
