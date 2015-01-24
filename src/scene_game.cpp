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

	//player1Texture->setPos(TILE_SIZE, TILE_SIZE);
	//player2Texture->setPos(TILE_SIZE, TILE_SIZE);

	_background = new RTexture(texturesScene_game[1]);
	_background ->setScaleSize(1.0*EngineInst->screen_width()/_background->getWidth());
	_player1 = new Character(map,player1Texture);
	_player2 = new Character(map,player2Texture);

	_player1->setPosTiles(map,3,3);
	_player2->setPosTiles(map,4,3);

	for(int i = 0; i<5; ++i) {
		Character* enemy = new Character(map,player2Texture);
		enemy->setPosTiles(map,map->GetWidth()/2 + i, map->GetHeight()-4);
		_enemys.push_back(enemy);
	}

	
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
	for(std::vector<Character*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {
		delete *enemy;
	}
	_enemys.clear();

	//Destroy textures???

	EngineInst->unLoadResources(texturesScene, texturesSceneSize);

}

void SceneGame::OnUpdate(int timems)
{
		//Event handler
		SDL_Event e;
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//Engine::eventDebug(&e);
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

		_player1->updatePosition(map, timems,_tiles->getTileSizeDst());
		_player2->updatePosition(map, timems,_tiles->getTileSizeDst());

		for(std::vector<Character*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {
			int startX = (*enemy)->getPosBeforeX(); 
			int startY = (*enemy)->getPosBeforeY();
			AStarWay_t way1;
			AStarWay_t way2;

			DIRECT destBest = DIRECT_NO_WAY;
			DIRECT direct1 = findAstar(way1, startX, startY,_player1->getPosBeforeX(), _player1->getPosBeforeY(), map->GetWidth(), map->GetHeight(), IMap_isObstacle, map);
			DIRECT direct2 = findAstar(way2, startX, startY,_player2->getPosBeforeX(), _player2->getPosBeforeY(), map->GetWidth(), map->GetHeight(), IMap_isObstacle, map);

			if(direct1 != DIRECT_NO_WAY && direct2 == DIRECT_NO_WAY) {
				destBest = direct1;
			} else if (direct1 == DIRECT_NO_WAY && direct2 != DIRECT_NO_WAY) {
					destBest = direct2;
			} else if (direct1 != DIRECT_NO_WAY && direct2 != DIRECT_NO_WAY) {
				if(way1.size() > way2.size()) {
					destBest = direct2;
				} else {
					destBest = direct1;
				}
			}
			
			if (destBest != DIRECT_NO_WAY) {
				if (destBest == DIRECT_DOWN) {
						(*enemy)->updateDirection(map, Character::ACTION_MOVE_DOWN);
					} else if (destBest == DIRECT_UP) {
						(*enemy)->updateDirection(map, Character::ACTION_MOVE_UP);
					} else if (destBest == DIRECT_LEFT) {
						(*enemy)->updateDirection(map, Character::ACTION_MOVE_LEFT);
					} else if (destBest == DIRECT_RIGHT) {
						(*enemy)->updateDirection(map, Character::ACTION_MOVE_RIGHT);
					}
			}

			(*enemy)->updatePosition(map, timems/3,_tiles->getTileSizeDst());
		}
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
	{ //Astar Example
		int startX = _player1->getPosBeforeX(); 
		int startY = _player1->getPosBeforeY();
		AStarWay_t way;
		
		int direct = findAstar(way, startX, startY,_player2->getPosBeforeX(), _player2->getPosBeforeY(), map->GetWidth(), map->GetHeight(), IMap_isObstacle, map);
		if (direct != DIRECT_NO_WAY) {
			_tiles->renderTile(renderer, startX * sizeDst+margin_left, startY * sizeDst+margin_top, 8); //Start not exit in way
			for(AStarWay_t::iterator point = way.begin(); point != way.end(); point++) {
				int x = (*point).first;
				int y = (*point).second;
				_tiles->renderTile(renderer, x * sizeDst +margin_left, y * sizeDst+margin_top, 8);
			}
		}
		
	}


	for(std::vector<Character*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {
		
		_tiles->renderTile(renderer, (*enemy)->getPosX()+margin_left, (*enemy)->getPosY()+margin_top, 23);
	}

	/*Check victory condition*/
	if (_player1->GetState() == Character::WON &&
	    _player2->GetState() == Character::WON) {
		EngineInst->font()->printfLT(100,
					     map->GetHeight()*sizeDst+margin_top, "Both players won");
		
	} else if (_player1->GetState() == Character::WON) {
		EngineInst->font()->printfLT(100,
					     map->GetHeight()*sizeDst+margin_top, "Player 1 has left the labyrinth. Player 2 must join him so you can together win the level.");
		
	} else if (_player2->GetState() == Character::WON) {
		EngineInst->font()->printfLT(100,
					     map->GetHeight()*sizeDst+margin_top, "Player 2 has left the labyrinth. Player 2 must join him so you can together win the level.");
		
	}
	_tiles->renderTile(renderer, _player1->getPosX()+margin_left, _player1->getPosY()+margin_top, 24);
	_tiles->renderTile(renderer, _player2->getPosX()+margin_left, _player2->getPosY()+margin_top, 24);
}
