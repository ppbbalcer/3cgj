#include "Engine.h"
#include <string>

RFont::RFont(TTF_Font *font): _font(font), _frameSurface(NULL), _width(0), _height(0) /*, _x(0), _y(0)*/
{
	SDL_assert(_font);
}

RFont::~RFont()
{
	if (_frameSurface) {
		SDL_FreeSurface(_frameSurface);
		_frameSurface = NULL;
	}
}
void RFont::OnUpdate()
{
	if (_width != EngineInst->screen_width() || _height != EngineInst->screen_height()) {
		//Init, Update after resize texture layer for font
		_width = EngineInst->screen_width();
		_height = EngineInst->screen_height();
		if (_frameSurface) {
			SDL_FreeSurface(_frameSurface);
			_frameSurface = NULL;
		}

		/* SDL interprets each pixel as a 32-bit number, so our masks must depend
		   on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 rmask = 0xff000000;
		Uint32 gmask = 0x00ff0000;
		Uint32 bmask = 0x0000ff00;
		Uint32 amask = 0x000000ff;
#else
		Uint32 rmask = 0x000000ff;
		Uint32 gmask = 0x0000ff00;
		Uint32 bmask = 0x00ff0000;
		Uint32 amask = 0xff000000;
#endif

		_frameSurface = SDL_CreateRGBSurface(0, _width, _height, 32,
		                                     rmask, gmask, bmask, amask);

		if (_frameSurface == NULL) {
			fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
			PAUSE();
		}
	}

	//Clean texture for new frame
	SDL_FillRect(_frameSurface, NULL,  0x00000000);
}

void RFont::printfLT(int x, int y, const char *text, ...)
{
	va_list valist;
	char buff[1024];
	va_start(valist, text);
	vsnprintf(buff, sizeof(buff) - 1, text, valist);
	va_end(valist);

	printTextBuff(x, y, ALIGN_LEFT | ALIGN_TOP, buff);
}

void RFont::printTextBuff(int x, int y, int alignment, const char *tex)
{
	SDL_Color colorText = { 255, 255, 255, 255 };
	SDL_Color colorBorder = { 0, 0, 0, 128 };
	printTextBuff(x, y, colorText, colorBorder, 1, alignment, 1.0f, tex);
}

void RFont::printf(int x, int y, int alignment, const char *text, ...)
{
	SDL_Color colorText = { 255, 255, 255, 255 };
	SDL_Color colorBorder = { 0, 0, 0, 128 };
	va_list valist;
	char buff[1024];
	va_start(valist, text);
	vsnprintf(buff, sizeof(buff) - 1, text, valist);
	va_end(valist);
	printTextBuff(x, y, colorText, colorBorder, 1, alignment, 1.0f, buff);
}

void RFont::printf(int x, int y, SDL_Color colorText, SDL_Color colorBorder, int border, int alignment, float scale, const char *text, ...)
{
	va_list valist;
	char buff[1024];
	va_start(valist, text);
	vsnprintf(buff, sizeof(buff) - 1, text, valist);
	va_end(valist);
	printTextRAW(_font, _frameSurface, x, y, colorText, colorBorder, border, alignment, scale, text);
}

void  RFont::printTextBuff(int x, int y, SDL_Color colorText, SDL_Color colorBorder, int border, int alignment, float scale, const char *text)
{
	printTextRAW(_font, _frameSurface, x, y, colorText, colorBorder, border, alignment, scale, text);
}

void RFont::printTextRAW(TTF_Font *font, SDL_Surface* surface, int x, int y, SDL_Color colorText, SDL_Color colorBorder, int border, int alignment, float scale, const char *text)
{
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, colorText);
	SDL_Surface* textSurfaceBorder = NULL;
	if (border > 0) {
		textSurfaceBorder = TTF_RenderText_Solid(font, text, colorBorder);
	}

	if (textSurface == NULL) {
		::printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		PAUSE();
	} else {
		SDL_Rect stretchRect = {x, y, textSurface->w, textSurface->h};

		if (alignment & ALIGN_LEFT) {
			SDL_assert((alignment & ALIGN_RIGHT) == 0);
		} else if (alignment & ALIGN_RIGHT) {
			stretchRect.x -= textSurface->w;
		} else {
			stretchRect.x -= textSurface->w / 2;
		}

		if (alignment & ALIGN_TOP) {
			SDL_assert((alignment & ALIGN_BOTTOM) == 0);
		} else if (alignment & ALIGN_BOTTOM) {
			stretchRect.y -= textSurface->h;
		} else {
			stretchRect.y -= textSurface->h / 2;
		}

		if (textSurfaceBorder) {
			SDL_Rect stretchRectCpy;
			stretchRectCpy = stretchRect;
			stretchRectCpy.x -= border;
			stretchRectCpy.y -= border;
			SDL_BlitSurface(textSurfaceBorder, NULL, surface, &stretchRectCpy);

			stretchRectCpy = stretchRect;
			stretchRectCpy.x -= border;
			stretchRectCpy.y += border;
			SDL_BlitSurface(textSurfaceBorder, NULL, surface, &stretchRectCpy);

			stretchRectCpy = stretchRect;
			stretchRectCpy.x += border;
			stretchRectCpy.y -= border;
			SDL_BlitSurface(textSurfaceBorder, NULL, surface, &stretchRectCpy);

			stretchRectCpy = stretchRect;
			stretchRectCpy.x += border;
			stretchRectCpy.y += border;
			SDL_BlitSurface(textSurfaceBorder, NULL, surface, &stretchRectCpy);


			SDL_FreeSurface(textSurfaceBorder);
		}

		SDL_BlitSurface(textSurface, NULL, surface, &stretchRect);

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
}

void RFont::OnPaint(SDL_Surface* screenSurface)
{
	//SDL_BlitScaled( _frameSurface, NULL, screenSurface, NULL);
	SDL_BlitSurface(_frameSurface, NULL, screenSurface, NULL);
}

void RFont::OnRender(SDL_Renderer* renderer)
{
	SDL_Texture*  texture = SDL_CreateTextureFromSurface(renderer, _frameSurface);   //Kill Performance
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
}
