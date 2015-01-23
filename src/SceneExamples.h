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

class Scene03Object: public Scene {
public:
	virtual void OnLoad() {
		bool success = EngineInst->loadResources(texturesScene03, texturesScene03Size);

		_background = new RTexture(texturesScene03[1]);
		_player = new RTexture(texturesScene03[2]);
		_player->setPos(240, 190);

		_tiles = new RTexture(texturesScene03[3]);
		_tiles->setTileSizeSrc(32);
		_tiles->setTileSizeDst(32);

		//Load media
		if( !success )
		{
			printf( "Failed to load media Scene02Renderer !\n" );
			PAUSE();
		}

		globalAudios[1].res.sound->setVolume(0.05f);
		globalAudios[1].res.sound->play(-1, -1);
	}

	virtual void OnFree(){
		delete 	_background;
		_background = NULL;
		delete 	_player;
		_player = NULL;

		delete 	_tiles;
		_tiles = NULL;

		EngineInst->unLoadResources(texturesScene03, texturesScene03Size);
	}

	virtual void OnUpdate(int timems) {
		//Event handler
		SDL_Event e;

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			Engine::eventDebug(&e);

			//User requests quit, Press Esc
			if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN  && e.key.keysym.sym == SDLK_ESCAPE) )
			{
				//Quit the game
				EngineInst->breakMainLoop();
				return;
			}
		}

		int dist = 1.0*timems;
		int posX = _player->getPosX();
		int posY = _player->getPosY();
		int width = _player->getWidth();

		const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL ); 
		if( currentKeyStates[ SDL_SCANCODE_UP ] ) {
			globalAudios[0].res.sound->play(1, 0);
			posY -= dist;
			if(posY < 0) {
				posY = 0;
			}
		} else {
			posY += dist;
			if(posY > 190) {
				posY = 190;
			}
		}

		if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) {
			posX -= dist;
			if (posX<0) {
				posX = 0;
			}
		}

		if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) {
			posX += dist;
			if (posX > EngineInst->screen_width() - width) {
				posX = EngineInst->screen_width() - width;
			}
		}

		_player->setPos(posX, posY);

		EngineInst->font()->printfLT(100, 100, "Hello test text!!!");

	}

	virtual void OnRender(SDL_Renderer* renderer) {
		_background->render(renderer);
		_player->render(renderer);

		int sizeDst = _tiles->getTileSizeDst() + 5;
		int tilesNums = _tiles->getTilesNums();
		for (int i =  0 ; i<tilesNums; ++i) {

			int col = i % 20 + 2;
			int row = i / 20 + 2;
			

			_tiles->renderTile(renderer, col * sizeDst, row * sizeDst, i);

			EngineInst->font()->printfLT(col * sizeDst, row * sizeDst, "%i", i);

		}

	}

private:

	RTexture* _background;
	RTexture* _player;
	RTexture* _tiles;


};

#endif /* __SCENE_EXAMPLES_H__ */