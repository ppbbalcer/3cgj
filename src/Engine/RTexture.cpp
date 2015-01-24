#include "RTexture.h"

RTexture::RTexture(SDL_Texture* texture, int w, int h):
	_texture(texture),
	_flip(SDL_FLIP_NONE),
	_width(w),
	_height(h),
	_x(0),
	_y(0),
	_scaleWidth(_width),
	_scaleHeight(_height),
	_tileSizeSrc(0),
	_tileSizeDst(0),
	_tileColumns(0),
	_tileRows(0),
	_tileIdx(0)
{
	SDL_assert(_texture && _width > 0 && _height > 0);
}

RTexture::RTexture(const ResourceItem &resItem):
	_texture(resItem.texture),
	_flip(SDL_FLIP_NONE),
	_width(resItem.width),
	_height(resItem.height),
	_x(0),
	_y(0),
	_scaleWidth(_width),
	_scaleHeight(_height),
	_tileSizeSrc(0),
	_tileSizeDst(0),
	_tileColumns(0),
	_tileRows(0),
	_tileIdx(0)
{
	SDL_assert(_texture && _width > 0 && _height > 0);
}

void RTexture::renderAll(SDL_Renderer* renderer, int x, int y ) {
	SDL_Rect renderQuad = { x, y, _scaleWidth, _scaleHeight};

	 if (_flip == SDL_FLIP_NONE ) {
		SDL_RenderCopy( renderer, _texture, NULL, &renderQuad );
	 } else {
		 SDL_RenderCopyEx( renderer, _texture,  NULL, &renderQuad, 0.0f, NULL, _flip );
	 }
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

void RTexture::setTileIdx(int tileIdx) {
	_tileIdx = tileIdx;
}

int RTexture::getTileIdx() {
	return _tileIdx;
}

void RTexture::renderTile(SDL_Renderer* renderer, int x, int y) {
	renderTile(renderer, x, y, _tileIdx, _flip);
}

void RTexture::renderTile(SDL_Renderer* renderer, int x, int y, int tileIdx, SDL_RendererFlip flip) {
	if( _tileColumns > 0 && _tileRows > 0 && _tileSizeDst > 0 ) {
		int row = tileIdx / _tileColumns;
		int col = tileIdx % _tileColumns;

		SDL_Rect renderQuadSrc = { col * _tileSizeSrc, row * _tileSizeSrc, _tileSizeSrc, _tileSizeSrc };
		SDL_Rect renderQuadDst = { x, y, _tileSizeDst, _tileSizeDst };

		if (_flip == SDL_FLIP_NONE ) {
			SDL_RenderCopy( renderer, _texture, &renderQuadSrc, &renderQuadDst );
		} else {
			SDL_RenderCopyEx( renderer, _texture,   &renderQuadSrc, &renderQuadDst, 0.0f, NULL, flip );
		}
	}
}

