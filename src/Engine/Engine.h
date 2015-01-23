#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SDL.h>
#include "RFont.h"
#include "StructsGlobal.h"

class Scene;

void PAUSE();

class Engine {
public:

	static bool Create();
	static void Destroy();
	/* inline static Engine*	getInst()		{ return _engine; } */
	inline int				screen_width()	{ return 640; }
	inline int				screen_height() { return 480; }

	bool					loadTexture(ResourceItem &resItem); 
	void					unLoadTexture(ResourceItem &resItem);
	bool					loadResources(ResourceItem resources[], unsigned int size);
	void					unLoadResources(ResourceItem resources[], unsigned int size);
	bool					loadGlobalFont(const char *pathTTF, int ptSize);
	void					unLoadGlobalFont();

	inline RFont*			font() { return _font; }

	void					resetViewport();

	void					setNextScene(Scene* scene);
	void					breakMainLoop();
	void					mainLoop();
	void					showFPS(bool flag);



	static void				eventDebug(SDL_Event *e);

private:
	~Engine(){};
	Engine& operator=(const Engine&);
	Engine(const Engine&);
	Engine(){}
	/* static Engine* _engine; */

	/* Engine members */
	SDL_Window*			_window;	//The window we'll be rendering to 
	SDL_Surface*		_screenSurface;	//The surface contained by the window 
	SDL_Renderer*		_renderer;	//The window renderer 
	SDL_Rect			_viewportScreen;	//Viewport all screen

	RFont*				_font; //Global font
	Scene*				_scene;
	Scene*				_sceneNext;
	bool				_quitMainLoop;
	bool				_showFPS;

	/* Engine private functions */
	bool init();
	void close();


};

extern Engine* EngineInst;


#endif /* __ENGINE_H__ */