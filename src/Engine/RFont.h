#ifndef __RENDER_FONT_H__
#define __RENDER_FONT_H__

#include <SDL.h>
#include <SDL_ttf.h>
#include <list>
#include <vector>

enum ALIGN {
	ALIGN_LEFT = 1,
	ALIGN_RIGHT = 2,
	ALIGN_TOP = 4,
	ALIGN_BOTTOM = 8,
	ALIGN_BOTTOM_WITH_PADDING = 16
};

class RFont {
public:
	RFont(TTF_Font *font);
	virtual ~RFont();
	void OnUpdate();
	void OnPaint(SDL_Surface* screenSurface);
	void OnRender(SDL_Renderer* renderer);
	TTF_Font* getFont() { return _font; }
	void clean();

	void printfLT(int x, int y, const char *text, ...);
	void printf(int x, int y, int alignment, const char *text, ...);
	void printf(int x, int y, SDL_Color colorText, SDL_Color colorBorder, int border, int alignment, float scale, const char *text, ...);
	void printTextBuff(int x, int y, int alignment, const char *tex);
	void printTextBuff(int x, int y, SDL_Color colorText, SDL_Color colorBorder, int border, int alignment, float scale, const char *text);
	void printTextRAW(TTF_Font *font, SDL_Surface* surface, int x, int y, SDL_Color colorText, SDL_Color colorBorder, int border, int alignment, float scale, const char *text);

private: 
	RFont(const RFont&);
	RFont& operator=(const RFont&);
	TTF_Font *_font;
	//int _width; 
	//int _height;
	//SDL_Surface* _frameSurface;	//The surface contained by the window 

	struct ObjDrawText {
		ObjDrawText(SDL_Surface* psurfaceText, const SDL_Rect& renderQuad):surfaceTexture(psurfaceText){renderQuads.push_back(renderQuad);};
		SDL_Surface*		surfaceTexture;
		std::list<SDL_Rect> renderQuads;
	};
	std::vector<ObjDrawText> _drawTextObjs;
};


#endif /* __RENDER_FONT_H__ */