#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SDL.h>
#include "Audio.h"
#include "RFont.h"
#include "StructsGlobal.h"
#include <string>
class Scene;

void PAUSE();
float Q_rsqrt( float number );

class Engine {
public:

	static bool Create();
	static void Destroy();
	int screen_width();
	int screen_height();
	void setTileSize(int ts)
	{
		_tile_size=ts;
	}
	int getTileSize()
	{
		return _tile_size;
	}
	void setStatusLine(const char *line);
	void clearStatusLine();
	bool loadTexture(ResourceItem &resItem); 
	void unLoadTexture(ResourceItem &resItem);
	bool loadResources(ResourceItem resources[], unsigned int size);
	void unLoadResources(ResourceItem resources[], unsigned int size);
	bool loadAudioResources(AudioResource resources[], unsigned int size);
	void unloadAudioResources(AudioResource resources[], unsigned int size);
	bool loadGlobalFont(const char *pathTTF, int ptSize);
	void unLoadGlobalFont();
	inline RFont* font() { return _font; }
	void resetViewport();
	void setNextScene(Scene* scene);
	void breakMainLoop();
	void mainLoop();
	void showFPS(bool flag);
	static void eventDebug(SDL_Event *e);

private:
	~Engine(){}
	Engine& operator=(const Engine&);
	Engine(const Engine&);
	Engine(){}
	int _tile_size;
	/* Engine members */
	std::string status_line;
	SDL_Window* _window;		//The window we'll be rendering to 
	SDL_Surface* _screenSurface;		//The surface contained by the window 
	SDL_Renderer* _renderer;		//The window renderer 
	SDL_Rect _viewportScreen;	//Viewport all screen

	RFont* _font;			//Global font
	Scene* _scene;
	Scene* _sceneNext;
	bool _quitMainLoop;
	bool _showFPS;
	AudioEngine *_audio;

	bool init();
	void close();
};

extern Engine* EngineInst;


#endif /* __ENGINE_H__ */
