#include "MapLogic/field.h"
#include "MapLogic/map.h"
#include "scene_game.h"
#include "GlobalData.h"
#include <algorithm>
#include <stdio.h>

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
	RTexture *player1Texture = new RTexture(texturesScene_game[2]); 
	RTexture *player2Texture = new RTexture(texturesScene_game[2]);

	player1Texture->setPos(TILE_SIZE, TILE_SIZE);
	player2Texture->setPos(TILE_SIZE, TILE_SIZE);

	_background = new RTexture(texturesScene_game[1]);
	_player1 = new Character(player1Texture);
	_player2 = new Character(player2Texture);
	
	_tiles = new RTexture(texturesScene_game[3]);
	_tiles->setTileSizeSrc(64);
	_tiles->setTileSizeDst(TILE_SIZE);
	pcpos_before_x = pcpos_after_x = pcpos_before_y = pcpos_after_y = 1;
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

		float p1PosX = _player1->getPosX();
		float p1PosY = _player1->getPosY();
		float p2PosX = _player2->getPosX();
		float p2PosY = _player2->getPosY();

		const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

		if( currentKeyStates[ SDL_SCANCODE_DOWN ] ) {
			if ( (!map->GetFieldAt(pcpos_before_x,pcpos_before_y+1)
			      ->IsObstacle()) &&
			     (!map->GetFieldAt(pcpos_after_x,pcpos_before_y+1)
			      ->IsObstacle()) )
			{
				pcpos_after_y=pcpos_before_y+1;
			}
		}
		if( currentKeyStates[ SDL_SCANCODE_UP ] ) {
			if ( (!map->GetFieldAt(pcpos_before_x,pcpos_before_y-1)
			      ->IsObstacle()) &&
			     (!map->GetFieldAt(pcpos_after_x,pcpos_before_y-1)
			      ->IsObstacle()) ) {
				pcpos_after_y=pcpos_before_y-1;
			}
		}
		if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) {
			if ( (!map->GetFieldAt(pcpos_before_x+1,pcpos_before_y)
			      ->IsObstacle()) &&
			     (!map->GetFieldAt(pcpos_before_x+1,pcpos_after_y)
			      ->IsObstacle()) ) {
				pcpos_after_x=pcpos_before_x +1;
			}
		}
		if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) {
			if ( (!map->GetFieldAt(pcpos_before_x-1,pcpos_before_y)
			      ->IsObstacle()) &&
			     (!map->GetFieldAt(pcpos_before_x-1,pcpos_after_y)
			      ->IsObstacle()) ) {
				pcpos_after_x=pcpos_before_x -1;
			}
		}
		
		int target_y = pcpos_after_y*TILE_SIZE;
		int target_x = pcpos_after_x*TILE_SIZE;

		/* character should be moving moving down*/
		if (p1PosY>target_y) {
			p1PosY = max<int>(target_y,p1PosY-dist);
		}
		if (p1PosY<target_y) {
			p1PosY = min<int>(target_y,p1PosY+dist);
		}
		if (p1PosX>target_x) {
			p1PosX = max<int>(target_x,p1PosX-dist);
		}
		if (p1PosX<target_x) {
			p1PosX = min<int>(target_x,p1PosX+dist);
		}

		if (p1PosX==target_x)
			pcpos_before_x=pcpos_after_x;
		if (p1PosY==target_y)
			pcpos_before_y=pcpos_after_y;

		_player1->setPos(p1PosX, p1PosY);
		_player2->setPos(p2PosX, p2PosY);


		//EngineInst->font()->printTextLT(20, 20, "MSCN");
}

void SceneGame::OnRender(SDL_Renderer* renderer)
{
		//_background->render(renderer);

		int sizeDst = _tiles->getTileSizeDst();
		int tilesNums = _tiles->getTilesNums();
		//for (int i =  0 ; i<tilesNums; ++i) {
		for (int i = 0 ; i!=map->GetHeight(); i++) {
			for (int j = 0 ; j!=map->GetWidth(); ++j) {
				int field= map->GetFieldAt(j,i)->GetType();
				int tile=  map->GetFieldAt(j,i)->GetTileId();

				int col = j;// % 20 + 2;
				int row = i;// 20 + 2;
				_tiles->renderTile(renderer, col * sizeDst, row * sizeDst, tile);

			}
		}

		_tiles->renderTile(renderer, _player1->getPosX(), _player1->getPosY(), 24);
		_tiles->renderTile(renderer, _player2->getPosX(), _player2->getPosY(), 24);
}
