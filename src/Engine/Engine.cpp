#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Engine.h"
#include "Scene.h"


void PAUSE() {
#ifdef WIN32
	system("pause");
#else
	system("read");
#endif
}

float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
 
	if(number < 1.0f) {
		return 1.0f;
	}

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//      y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
 
	return 1.0f/y;
}


#define GAME_TITLE "WHAT DO WE DO NOW?"
#define _engine EngineInst

Engine* EngineInst = NULL;

bool Engine::Create() {
	SDL_assert(_engine == NULL);
	_engine = new Engine();
	return _engine->init();
}

void Engine::Destroy() {
	SDL_assert(_engine != NULL);
	_engine->close();
	delete _engine;
	_engine = NULL;
}
int Engine::screen_width()
{
	//int display_count = 0, display_index = 0, mode_index = 0;
	//SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
	//SDL_GetDisplayMode(display_index, mode_index, &mode);
	//return mode.w;
	return 800;
}
int Engine::screen_height()
{
	int display_count = 0, display_index = 0, mode_index = 0;
	//SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
	//SDL_GetDisplayMode(display_index, mode_index, &mode);
	//return mode.h;
	return 600;
}


bool Engine::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { 
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError()); 
		return false; 
	}

	_window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, EngineInst->screen_width(), EngineInst->screen_height(), SDL_WINDOW_SHOWN);
	if (_window == NULL) { 
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError()); 
		return false; 
	}
	//SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
		
	
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == NULL) { 
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError()); 
		return false; 
	}

	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF); 

	if (!(IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG) ) { 
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() ); 
		return false; 
	}

	_screenSurface = SDL_GetWindowSurface( _window ); 
	
	if (TTF_Init() == -1) { 
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError()); 
		return false; 
	} 

	_audio = new AudioEngine();

	_viewportScreen.x = 0; 
	_viewportScreen.y = 0; 
	_viewportScreen.w = screen_width(); 
	_viewportScreen.h = screen_height(); 

	_scene = NULL;
	_sceneNext = NULL;
	_font = NULL;
	_showFPS = false;

	return true;
}

void Engine::close() {
	unLoadGlobalFont();

	SDL_DestroyRenderer( _renderer );
	SDL_DestroyWindow( _window );

	_window = NULL;
	_renderer = NULL;
	_screenSurface = NULL;

	delete _audio;

	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

void Engine::resetViewport() {
	SDL_RenderSetViewport(_renderer, &_viewportScreen); 
}

bool Engine::loadResources(ResourceItem resources[], unsigned int size) {
	bool result = true;
	for (unsigned i=0; i<size && result; ++i) {
		result &= loadTexture(resources[i]);
	}
	return result;
}

void Engine::unLoadResources(ResourceItem resources[], unsigned int size) {
	for (unsigned i=0; i<size; ++i) {
		unLoadTexture(resources[i]);
	}
}

bool Engine::loadAudioResources(AudioResource resources[], unsigned int size) {
	bool result = true;

	for (unsigned i = 0; i < size; ++i) {
		switch(resources[i].type) {
		case AUDIO_TYPE_SOUND:
			resources[i].res.sound = _audio->loadSound(resources[i].path);
			break;
		case AUDIO_TYPE_MUSIC:
			resources[i].res.music = _audio->loadMusic(resources[i].path);
			break;
		}
		result &= resources[i].res.sound != NULL;
	}
	return result;
}

void Engine::unloadAudioResources(AudioResource resources[], unsigned int size) {
}

/* 
 * Load image at specified path 
 */
bool Engine::loadTexture(ResourceItem &resItem) 
{ 
	SDL_assert(resItem.surface == NULL && resItem.texture == NULL);
	bool success = true; 
	SDL_Surface* loadedSurface = IMG_Load(resItem.path); 
	
	if (loadedSurface == NULL) { 
		printf("Unable to load image %s! SDL Error: %s\n", resItem.path, SDL_GetError()); 
		success = false;
		PAUSE();
	} else {
		resItem.width = loadedSurface->w;
		resItem.height = loadedSurface->h;

		if (resItem.optLoadTexture) {

			if(resItem.optTextureColorKeyRGB) {
				//Color key image 
				SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, (resItem.optTextureColorKeyRGB&0xFF0000)>>16, (resItem.optTextureColorKeyRGB&0xFF00)>>8, resItem.optTextureColorKeyRGB & 0xFF ) );
			}

			//Create texture from surface pixels 
			resItem.texture = SDL_CreateTextureFromSurface(_renderer, loadedSurface); 
			if (resItem.texture  == NULL) {
				printf("Unable to create texture from %s! SDL Error: %s\n", resItem.path, SDL_GetError()); 
				success = false;
				PAUSE();
			} 
		}

		if (resItem.optLoadSurface) {
			if(resItem.optOptymalize) {
				//Convert surface to screen format, optimized image 
				resItem.surface = SDL_ConvertSurface(loadedSurface, _screenSurface->format, NULL);
				if (resItem.surface == NULL) { 
					printf("Unable to optimize image %s! SDL Error: %s\n", resItem.path, SDL_GetError()); 
					success = false;
					PAUSE();
				}
			} else {
				resItem.surface = loadedSurface;
			}
		}

		if (loadedSurface && (resItem.surface == NULL || loadedSurface != resItem.surface)) {
			SDL_FreeSurface(loadedSurface);
		}
	}

	return success; 
}

void Engine::unLoadTexture(ResourceItem &resItem) {
	if (resItem.surface) {
		SDL_FreeSurface( resItem.surface );
		resItem.surface = NULL;
	}
	if (resItem.texture) {
		SDL_DestroyTexture( resItem.texture );
		resItem.texture = NULL;
	}
}

bool Engine::loadGlobalFont(const char *pathTTF, int ptSize) {
	SDL_assert(_font == NULL);
	bool success = true; 
	TTF_Font* font = TTF_OpenFont(pathTTF, ptSize);

	if (font == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError()); 
		success = false; 
		PAUSE();
	} else { 
		_font = new RFont(font);
	} 
	return success;
}

void Engine::unLoadGlobalFont() {
	if(_font) {
		TTF_CloseFont(_font->getFont());
		delete _font;
		_font = NULL;
	}
}

void Engine::setNextScene(Scene* scene) {
	_sceneNext = scene;
}

void Engine::breakMainLoop() {
	_quitMainLoop = true;
}

void Engine::showFPS(bool flag)
{
	_showFPS = flag;
}

void Engine::mainLoop() {
	_quitMainLoop = false;
	
	if (_scene == NULL) {
		if (_sceneNext != NULL) {
			_scene = _sceneNext;
			_sceneNext = NULL;
			_scene->OnLoadBase();
		}
		else {
			_quitMainLoop = true;
		}
	}

	Uint32 time = SDL_GetTicks();

	//While application is running
	while (!_quitMainLoop)
	{
		Uint32 timeNew = SDL_GetTicks();
		Uint32 delta = timeNew - time;
		if (delta == 0) {
			delta = 1;
		}
		time = timeNew;

		if (_font) {
			_font->OnUpdate();
		}
	
		_scene->OnUpdate(delta);

		//Change scene
		if (_sceneNext) {
			_scene->OnFreeBase();
			_scene = _sceneNext;
			_sceneNext = NULL;
			_scene->OnLoadBase();
			time = SDL_GetTicks();
			continue;
		}

		if (_font && _showFPS) {
			_font->printf(screen_width(), 0, ALIGN_RIGHT | ALIGN_TOP, "FPS: %.2f", 1000.0f/delta);
		}

		if (_scene->getDrawType() == Scene::DrawType_Paint) {
			//Draw 2D
			//Clean screen
			SDL_FillRect( _screenSurface, NULL, SDL_MapRGB( _screenSurface->format, 0x00, 0x00, 0x00 ) );

			_scene->OnPaint(_screenSurface);
	
			if (_font) {
				_font->OnPaint(_screenSurface);
			}
			//Update the surface
			SDL_UpdateWindowSurface( _window );
		} else {
			//Draw 3D Accl
			//Clear screen 
			resetViewport();
			SDL_SetRenderDrawColor( _renderer, 0x20, 0x20, 0x20, 0xFF ); 
			SDL_RenderClear( _renderer ); //Render texture to screen 

			_scene->OnRender(_renderer);

			if (_font) {
				resetViewport();
				_font->OnRender(_renderer);
			}

			SDL_RenderPresent( _renderer );

			//In the main loop after the event loop, we call SDL_RenderClear. This function fills the screen with the color that was last set with SDL_SetRenderDrawColor.
			//With the screen cleared, we render the texture with SDL_RenderCopy. With the texture rendered, we still have to update the screen, but since we're not using SDL_Surfaces to render we can't use SDL_UpdateWindowSurface. Instead we have to use SDL_RenderPresent. 
		}
	}

	_scene->OnFreeBase();
	_scene = NULL;
}

void Engine::eventDebug(SDL_Event *e)
{
	if (e->type == SDL_QUIT) {
		printf("Recive event SDL_QUIT !!! Bye!\n");
	} else if (e->type == SDL_KEYDOWN || e->type == SDL_KEYUP) {
		printf("Recive SDL_KeyboardEvent: Type: %s ", (e->type == SDL_KEYDOWN)? "SDL_KEYDOWN":"SDL_KEYUP"); 
		printf("State: %s ", (e->key.state == SDL_PRESSED)? "SDL_PRESSED":"SDL_RELEASED");
		printf("Repeat: %i ", e->key.repeat);
		if( e->key.keysym.sym == SDLK_UP ) { printf("Key: SDLK_UP");} 
		else if( e->key.keysym.sym == SDLK_DOWN ) { printf("Key: SDLK_DOWN"); } 
		else if( e->key.keysym.sym == SDLK_LEFT ) { printf("Key: SDLK_LEFT"); } 
		else if( e->key.keysym.sym == SDLK_RIGHT ) { printf("Key: SDLK_RIGHT");	}
		else {
			printf("Key: %i",e->key.keysym.sym);  
		}
			
		printf("\n");
	} else {
		printf("Recive Unknown Event: Type: %i Key: %i, Text: %i\n", e->type, e->key,  e->text);
	}
}
