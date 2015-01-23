#include "MapLogic/field.h"
#include "MapLogic/map.h"
#include "scene_game.h"
#include "GlobalData.h"
#include <algorithm>

#define TILE_SIZE 32
using namespace std;
SceneGame::SceneGame()
{
	map = IMap::Factory(IMap::LOADED, "Resources/map_example.txt");
}

SceneGame::~SceneGame()
{
	delete map;
}
void SceneGame::OnLoad()
{
	// montage *.png ../floor0.png -geometry +0x0 -tile 3x3 ../walls.png
	
	bool success = EngineInst->loadResources(texturesScene_game, texturesScene_gameSize);

	_background = new RTexture(texturesScene_game[1]);
	_player = new RTexture(texturesScene_game[2]);
	_player->setPos(TILE_SIZE,TILE_SIZE);
	
	_tiles = new RTexture(texturesScene_game[3]);
	_tiles->setTileSizeSrc(64);
	_tiles->setTileSizeDst(TILE_SIZE);
	pcpos_before_x=pcpos_after_x=pcpos_before_y=pcpos_after_y=
		1;
	//Load media
	if( !success )
	{
		printf( "Failed to load media Scene02Renderer !\n" );
		PAUSE();
	}

}

void SceneGame::OnFree()
{
		EngineInst->unLoadResources(texturesScene, texturesSceneSize);

}
#include <stdio.h>
void SceneGame::OnUpdate(int timems)
{
		//Event handler
		SDL_Event e;
		printf("X: %d->%d; XY %d->%d %d\n",
	 pcpos_before_x,
	 pcpos_after_x,
	 pcpos_before_y,
		       pcpos_after_y,
		       timems

			);
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

		float dist = 0.3*timems;
		float posX = _player->getPosX();
		float posY = _player->getPosY();
		int width = _player->getWidth();

		const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

		
		if( currentKeyStates[ SDL_SCANCODE_DOWN ] ) {
			if (!map->GetFieldAt(pcpos_before_x,pcpos_before_y+1)
			    ->IsObstacle()) {
				pcpos_after_y=pcpos_before_y+1;
			}
		}
		if( currentKeyStates[ SDL_SCANCODE_UP ] ) {
			if (!map->GetFieldAt(pcpos_before_x,pcpos_before_y-1)
			    ->IsObstacle()) {
				pcpos_after_y=pcpos_before_y-1;
			}
		}
		if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) {
			if (!map->GetFieldAt(pcpos_before_x+1,pcpos_before_y)
			    ->IsObstacle()) {
				pcpos_after_x=pcpos_before_x +1;
			}
		}
		if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) {
			if (!map->GetFieldAt(pcpos_before_x-1,pcpos_before_y)
			    ->IsObstacle()) {
				pcpos_after_x=pcpos_before_x -1;
			}
		}
		
		int target_y = pcpos_after_y*TILE_SIZE;
		int target_x = pcpos_after_x*TILE_SIZE;

		/* character should be moving moving down*/
		if (posY>target_y) {
			posY = max<int>(target_y,posY-dist);
		}
		if (posY<target_y) {
			posY = min<int>(target_y,posY+dist);
		}
		if (posX>target_x) {
			posX = max<int>(target_x,posX-dist);
		}
		if (posX<target_x) {
			posX = min<int>(target_x,posX+dist);
		}

		if (posX==target_x)
			pcpos_before_x=pcpos_after_x;
		if (posY==target_y)
			pcpos_before_y=pcpos_after_y;
		_player->setPos(posX, posY);

		//EngineInst->font()->printTextLT(20, 20, "MSCN");
}

void SceneGame::OnRender(SDL_Renderer* renderer)
{
		_background->render(renderer);

		int sizeDst = _tiles->getTileSizeDst();
		int tilesNums = _tiles->getTilesNums();
		//for (int i =  0 ; i<tilesNums; ++i) {
		for (int i = 0 ; i!=map->GetHeight(); i++) {
			for (int j = 0 ; j!=map->GetWidth(); ++j) {
				int field= map->GetFieldAt(j,i)->GetType();

				int col = j;//  % 20 + 2;
				int row = i;// / 20 + 2;
				int tile = 7;
				if (field==WALL)
					tile=4;
				_tiles->renderTile(renderer, col * sizeDst, row * sizeDst, tile);

			}
		}
//}
		_player->render(renderer);


}
