#ifndef __SCENE_EXAMPLES_H__
#define __SCENE_EXAMPLES_H__

#include "GlobalData.h"
#include <stdio.h>
#include <string>
#include "Engine/Scene.h"
#include "Engine/Engine.h"
#include "Engine/RTexture.h"

class SceneInit: public Scene {
public:
	virtual void OnLoad() {
		_drawType = DrawType_Paint;
		bool success = EngineInst->loadResources(texturesScene, texturesSceneSize);
		//Load media
		if( !success )
		{
			printf( "Failed to load media SceneInit !\n" );
			PAUSE();
		}

		_progress = 0;

		int dist = 20;

		_stretchRect.x = 0;
		_stretchRect.y = 0;
		_stretchRect.w = EngineInst->screen_width(); 
		_stretchRect.h = EngineInst->screen_height();
		if(EngineInst->screen_width() > EngineInst->screen_height()) {
			int diff = EngineInst->screen_width() - EngineInst->screen_height();
			_stretchRect.x += diff/2;
			_stretchRect.w -= diff;
		} else if(EngineInst->screen_height() > EngineInst->screen_width()) {
			int diff = EngineInst->screen_height() - EngineInst->screen_width();
			_stretchRect.y += diff/2;
			_stretchRect.h -= diff;
		}
		_stretchRect.x += dist; 
		_stretchRect.y += dist; 
		_stretchRect.w -= dist*2; 
		_stretchRect.h -= dist*2;
	};

	virtual void OnFree(){
		EngineInst->unLoadResources(texturesScene, texturesSceneSize);
	};

	virtual void OnUpdate(int timems) {
		//Event handler
		SDL_Event e;
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN  && e.key.keysym.sym == SDLK_ESCAPE) )
			{
				//Quit the game
				EngineInst->breakMainLoop();
			} else if( e.type == SDL_KEYDOWN )
			{
				//Change scene
				//EngineInst->setNextScene(gScenes[1]);
			}
		}

		//SDL_Delay( 20 );
		_progress += timems;
		if (_progress >= 1500) {
			//Change scene
			//EngineInst->setNextScene(gScenes[1]);

		}


	};
	virtual void OnPaint(SDL_Surface* screenSurface) {
		int fill = (int)((255.0f* _progress)/1500.0f);
		if(fill > 255) {
			fill = 255;
		}
		SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, fill, fill, fill ) );

		//Apply the image stretched 
		SDL_BlitScaled(  texturesScene[0].surface, NULL, screenSurface, &_stretchRect );
	};

private:
	int _progress;
	SDL_Rect _stretchRect; 

};

class Scene01Image: public Scene {
public:
	virtual void OnLoad() {
		_drawType = DrawType_Paint;
		bool success = EngineInst->loadResources(texturesScene, texturesSceneSize);
		//Load media
		if( !success )
		{
			printf( "Failed to load media Scene01Image !\n" );
			PAUSE();
		}
		timer = 0;
	};

	virtual void OnFree(){
		EngineInst->unLoadResources(texturesScene, texturesSceneSize);
	};
	virtual void OnUpdate(int timems) {
		//Event handler
		SDL_Event e;

		timer += 1;
		//if(timer > 400) {
		//		//Change scene
		//		EngineInst->setNextScene(gScenes[4]);
		//}

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			Engine::eventDebug(&e);

			//User requests quit, Press Esc
			if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN  && e.key.keysym.sym == SDLK_ESCAPE) )
			{
				//Quit the game
				EngineInst->breakMainLoop();
				//EngineInst->setNextScene(gScenes[2]);
			} else if( e.type == SDL_KEYDOWN )
			{
				//Change scene
				//EngineInst->setNextScene(gScenes[4]);
			}

		}
	};
	virtual void OnPaint(SDL_Surface* screenSurface) {
		//Apply the image
		SDL_BlitSurface( texturesScene[0].surface, NULL, screenSurface, NULL );
		//{
		//	int dist = 50;
		//	SDL_Rect stretchRect; 
		//	stretchRect.x = dist; 
		//	stretchRect.y = dist; 
		//	stretchRect.w = EngineInst->screen_width() - 2*dist; 
		//	stretchRect.h = EngineInst->screen_height() - 2*dist; 
		//	//Apply the image stretched 
		//	SDL_BlitScaled( gHelloWorld, NULL, gScreenSurface, &stretchRect );
		//}
	};

private:
	int timer;
};

class Scene02Renderer: public Scene {
public:
	virtual void OnLoad() {
		timer = 0;
		bool success = EngineInst->loadResources(texturesScene,texturesSceneSize);
		//Load media
		if( !success )
		{
			printf( "Failed to load media Scene02Renderer !\n" );
			PAUSE();
		}

	}

	virtual void OnFree(){
		EngineInst->unLoadResources(texturesScene, texturesSceneSize);
	}

	virtual void OnUpdate(int timems) {
		//Event handler
		SDL_Event e;

		timer += 1;
		//if(timer > 400) {
		//		//Change scene
		//		EngineInst->setNextScene(gScenes[5]);
		//}

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			Engine::eventDebug(&e);

			//User requests quit, Press Esc
			if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN  && e.key.keysym.sym == SDLK_ESCAPE) )
			{

				//Quit the game
				EngineInst->breakMainLoop();
			} else if( e.type == SDL_KEYDOWN )
			{
				//Change scene
				//EngineInst->setNextScene(gScenes[5]);
			}
		}
	};
	virtual void OnRender(SDL_Renderer* renderer) {
		SDL_RenderCopy(renderer, texturesScene[0].texture, NULL, NULL ); //Update screen 

		 //Top left corner viewport 
		SDL_Rect topLeftViewport; 
		topLeftViewport.x = 0; 
		topLeftViewport.y = 0; 
		topLeftViewport.w = EngineInst->screen_width() / 2; 
		topLeftViewport.h = EngineInst->screen_height() / 2; 
		SDL_RenderSetViewport( renderer, &topLeftViewport ); 
		//Render texture to screen 
		SDL_RenderCopy( renderer, texturesScene[0].texture, NULL, NULL );
		topLeftViewport.x = EngineInst->screen_width() / 2; ; 
		SDL_RenderSetViewport( renderer, &topLeftViewport ); 
		//Render texture to screen 
		SDL_RenderCopy( renderer, texturesScene[0].texture, NULL, NULL );

		EngineInst->resetViewport();

		 //Render red filled quad 
		SDL_Rect fillRect = { EngineInst->screen_width() / 4, EngineInst->screen_height() / 4, EngineInst->screen_width() / 2, EngineInst->screen_height() / 2 }; 
		SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF ); 
		SDL_RenderFillRect( renderer, &fillRect );

		//Render green outlined quad 
		SDL_Rect outlineRect = { EngineInst->screen_width() / 6, EngineInst->screen_height() / 6, EngineInst->screen_width() * 2 / 3, EngineInst->screen_height() * 2 / 3 }; 
		SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF ); 
		SDL_RenderDrawRect( renderer, &outlineRect );


		//Draw blue horizontal line 
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF ); 
		SDL_RenderDrawLine( renderer, 0, EngineInst->screen_height() / 2, EngineInst->screen_width(), EngineInst->screen_height() / 2 );

		//Draw vertical line of yellow dots 
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF ); 
		for( int i = 0; i < EngineInst->screen_height(); i += 4 ) { 
			SDL_RenderDrawPoint( renderer, EngineInst->screen_width() / 2, i ); 
		}

	};

private:
	int timer;

};

#endif /* __SCENE_EXAMPLES_H__ */