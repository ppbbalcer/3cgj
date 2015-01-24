#include "MapLogic/field.h"
#include "MapLogic/map.h"
#include "scene_game.h"
#include "GlobalData.h"
#include <algorithm>
#include "Engine/AStar.h"
#include <stdio.h>
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

	int tile_size = EngineInst->screen_width()/map->GetWidth();
	
	_tiles->setTileSizeDst(tile_size);
	
	
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

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (currentKeyStates[SDL_SCANCODE_DOWN]) {
			_player1->updateDirection(map, Character::ACTION_MOVE_DOWN);
		}

		if (currentKeyStates[SDL_SCANCODE_UP]) {
			_player1->updateDirection(map, Character::ACTION_MOVE_UP);
		}

		if (currentKeyStates[SDL_SCANCODE_LEFT]) {
			_player1->updateDirection(map, Character::ACTION_MOVE_LEFT);
		}

		if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
			_player1->updateDirection(map, Character::ACTION_MOVE_RIGHT);
		}

		if (currentKeyStates[SDL_SCANCODE_S]) {
			_player2->updateDirection(map, Character::ACTION_MOVE_DOWN);
		}

		if (currentKeyStates[SDL_SCANCODE_W]) {
			_player2->updateDirection(map, Character::ACTION_MOVE_UP);
		}

		if (currentKeyStates[SDL_SCANCODE_A]) {
			_player2->updateDirection(map, Character::ACTION_MOVE_LEFT);
		}

		if (currentKeyStates[SDL_SCANCODE_D]) {
			_player2->updateDirection(map, Character::ACTION_MOVE_RIGHT);
		}

		_player1->updatePosition(map, timems);
		_player2->updatePosition(map, timems);
}

void SceneGame::OnRender(SDL_Renderer* renderer)
{
	_background->render(renderer);
	int margin_top = 100;
	int margin_left = 5;
	int sizeDst = _tiles->getTileSizeDst();
	int tilesNums = _tiles->getTilesNums();
	//for (int i =  0 ; i<tilesNums; ++i) {
	srand(1);
	for (int i = 0 ; i!=map->GetHeight()-1; i++) {
		for (int j = 0 ; j!=map->GetWidth()-1; ++j) {
			int px_left = j * sizeDst+sizeDst/2 + margin_left;
			int px_top  = i * sizeDst+0.5*sizeDst + margin_top;
			_tiles->renderTile(renderer,
					   px_left,
					   px_top,
					   18+rand()%5);
		}
	}
	for (int i = 0 ; i!=map->GetHeight(); i++) {
		for (int j = 0 ; j!=map->GetWidth(); ++j) {
			int field= map->GetFieldAt(j,i)->GetType();
			int tile=  map->GetFieldAt(j,i)->GetTileId();
			if (field==IField::FLOOR)
				continue;
			int col = j* sizeDst+margin_left;
			int row = i * sizeDst +margin_top;
			_tiles->renderTile(renderer, col , row, tile);
			
		}
	}
	/*
		{ //Astar Example
			int startX = _player1->getPosBeforeX(); 
			int startY = _player1->getPosBeforeY();

			_tiles->renderTile(renderer, startX * sizeDst, startY * sizeDst, 8);

			while (startX != _player2->getPosBeforeX() || startY != _player2->getPosBeforeY()) {
				int direct = findAstar(startX, startY,_player2->getPosBeforeX(), _player2->getPosBeforeY(), map->GetWidth(), map->GetHeight(), IMap_isObstacle, map);
				if (direct == DIRECT_NO_WAY) {
					break;
				}

				if(direct & DIRECT_LEFT) {
					--startX;
				} else if(direct & DIRECT_RIGHT) {
					++startX;
				}

				if(direct & DIRECT_UP) {
					--startY;
				} else if(direct & DIRECT_DOWN) {
					++startY;
				}
				_tiles->renderTile(renderer, startX * sizeDst, startY * sizeDst, 8);
			}
		}
	*/
		if (_player1->GetState() == Character::WON &&
		    _player2->GetState() == Character::WON) {
			EngineInst->font()->printfLT(100,
			  map->GetHeight()*32+margin_top, "Both players won");
			
		} else if (_player1->GetState() == Character::WON) {
			EngineInst->font()->printfLT(100,
				     map->GetHeight()*32+margin_top, "Player 1 has left the labyrinth. Player 2 must join him so you can together win the level.");

		} else if (_player2->GetState() == Character::WON) {
			EngineInst->font()->printfLT(100,
				     map->GetHeight()*32+margin_top, "Player 2 has left the labyrinth. Player 2 must join him so you can together win the level.");

		}
		_tiles->renderTile(renderer, _player1->getPosX()+margin_left, _player1->getPosY()+margin_top, 24);
		_tiles->renderTile(renderer, _player2->getPosX()+margin_left, _player2->getPosY()+margin_top, 24);
}
