#include "MapLogic/field.h"
#include "MapLogic/map.h"
#include "scene_game.h"
#include "GlobalData.h"
#include <algorithm>
#include "Engine/AStar.h"
#include <stdio.h>
#include "fireball.h"
#include "KeyMap.h"

using namespace std;

/* looking for obstacles*/
bool IMap_isObstacle(int x, int y, void* objMap)
{

	if (((IMap*)objMap)->GetFieldAt(x, y)->IsOccupied())
		return false;
	return ((IMap*)objMap)->GetFieldAt(x, y)->IsObstacle();
}

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
	int tile_size = EngineInst->screen_width() / map->GetWidth();
	EngineInst->setTileSize(tile_size);
	
	bool success = EngineInst->loadResources(texturesScene_game, texturesScene_gameSize);
	/*RTexture *player1Texture = new RTexture(texturesScene_game[2]);
	RTexture *player2Texture = new RTexture(texturesScene_game[2]);*/

	//player1Texture->setPos(TILE_SIZE, TILE_SIZE);
	//player2Texture->setPos(TILE_SIZE, TILE_SIZE);
	int tileSizeSrc = 64;

	RTexture *tmpTexture;

	_background = new RTexture(texturesScene_game[1]);
	_background ->setScaleSize(1.0 * EngineInst->screen_width() / _background->getWidth());

	tmpTexture = new RTexture(texturesScene_game[3]);
	tmpTexture->setTileSizeSrc(tileSizeSrc);
	tmpTexture->setTileSizeDst(tile_size);
	tmpTexture->setTileIdx(24);
	_player1 = new Character(tmpTexture, map);

	tmpTexture = new RTexture(texturesScene_game[3]);
	tmpTexture->setTileSizeSrc(tileSizeSrc);
	tmpTexture->setTileSizeDst(tile_size);
	tmpTexture->setTileIdx(27);
	_player2 = new Character(tmpTexture, map);

	_player1->setPosTiles(map, 3, 3);
	_player2->setPosTiles(map, 4, 3);

	for (int i = 0; i < 5; ++i) {
		tmpTexture = new RTexture(texturesScene_game[3]);
		tmpTexture->setTileSizeSrc(tileSizeSrc);
		tmpTexture->setTileSizeDst(tile_size);
		tmpTexture->setTileIdx(23);
		Character* enemy = new Character(tmpTexture, map);
		enemy->setPosTiles(map, map->GetWidth() - 2, map->GetHeight() - 2 - i);
		_enemys.push_back(enemy);
	}

	_tiles = new RTexture(texturesScene_game[3]);
	_tiles->setTileSizeSrc(tileSizeSrc);
	_tiles->setTileSizeDst(tile_size);

	//Load media
	if (!success) {
		printf("Failed to load media Scene02Renderer !\n");
		PAUSE();
	}

}

void SceneGame::OnFree()
{
	for (std::vector<Character*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {
		delete *enemy;
	}
	_enemys.clear();

	//Destroy textures???

	EngineInst->unLoadResources(texturesScene, texturesSceneSize);

}

void SceneGame::updateFireballs(int timems)
{
	for (std::list<Fireball*>::iterator it = fireballs.begin(); it != fireballs.end();) {
		if ((*it)->updatePosition(map, timems)) {
			delete *it;
			it = fireballs.erase(it);
		} else {
			it++;
		}
	}
}

void SceneGame::updatePlayers(int timems)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[PLAYER_1_MOVE_DOWN]) {
		_player1->updateDirection(map, DIRECT_DOWN);
	}

	if (currentKeyStates[PLAYER_1_MOVE_UP]) {
		_player1->updateDirection(map, DIRECT_UP);
	}

	if (currentKeyStates[PLAYER_1_MOVE_LEFT]) {
		_player1->updateDirection(map, DIRECT_LEFT);
	}

	if (currentKeyStates[PLAYER_1_MOVE_RIGHT]) {
		_player1->updateDirection(map, DIRECT_RIGHT);
	}

	if (currentKeyStates[PLAYER_1_SHOOT]) {
		Fireball * fb = _player1->Shoot();
		if (fb)
			fireballs.push_back(fb);
	}

	if (currentKeyStates[PLAYER_2_MOVE_DOWN]) {
		_player2->updateDirection(map, DIRECT_DOWN);
	}

	if (currentKeyStates[PLAYER_2_MOVE_UP]) {
		_player2->updateDirection(map, DIRECT_UP);
	}

	if (currentKeyStates[PLAYER_2_MOVE_LEFT]) {
		_player2->updateDirection(map, DIRECT_LEFT);
	}

	if (currentKeyStates[PLAYER_2_MOVE_RIGHT]) {
		_player2->updateDirection(map, DIRECT_RIGHT);
	}

// <<<<<<< HEAD
		// _player1->updatePosition(map, timems,_tiles->getTileSizeDst());
		// _player2->updatePosition(map, timems,_tiles->getTileSizeDst());
		// for(std::list<Fireball*>::iterator it = fireballs.begin();
		    // it != fireballs.end(); ++it) {
			// if ( (*it)->updatePosition(map,timems) ) {
				// std::list<Fireball*>::iterator next=it;
				// next++;
				// delete *it;
				// fireballs.erase(it);
				// it=next;
			// }
		// }

		// //int enemys = _enemys.size();
		// //calc_enemy_timer += timems;
		// //calc_enemy_last = 0;
		// //int tipePerOne = /*period to update all enemys*/1000 /enemys;
		// //int enemysToUpdate = calc_enemy_timer/tipePerOne + 3;
		// //calc_enemy_timer = calc_enemy_timer%tipePerOne;

		// //int enemy_start = -1;
		// //int enemy_stop = -1;
		// //if(enemysToUpdate > 0) {
		// //	enemy_start = calc_enemy_last + 1;
		// //	enemy_stop = (enemy_start + enemysToUpdate -1)%enemys;
		// //	enemy_start %= enemys;
		// //	calc_enemy_last = enemy_stop;
		// //}

		// //int index = 0;
		// for(std::vector<Character*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {

			// /*if((index >= enemy_start && index <= enemy_stop) || (index <= enemy_start && index >= enemy_stop)) {*/
				// int startX = (*enemy)->getPosBeforeX(); 
				// int startY = (*enemy)->getPosBeforeY();
				// AStarWay_t way1;
				// AStarWay_t way2;

				// DIRECT destBest = DIRECT_NO_WAY;
				// DIRECT direct1 = findAstar(way1, 5, startX, startY,_player1->getPosBeforeX(), _player1->getPosBeforeY(), map->GetWidth(), map->GetHeight(), IMap_isObstacle, map);
				// DIRECT direct2 = findAstar(way2, 5, startX, startY,_player2->getPosBeforeX(), _player2->getPosBeforeY(), map->GetWidth(), map->GetHeight(), IMap_isObstacle, map);

				// if(direct1 != DIRECT_NO_WAY && direct2 == DIRECT_NO_WAY) {
					// destBest = direct1;
				// } else if (direct1 == DIRECT_NO_WAY && direct2 != DIRECT_NO_WAY) {
						// destBest = direct2;
				// } else if (direct1 != DIRECT_NO_WAY && direct2 != DIRECT_NO_WAY) {
					// if(way1.size() > way2.size()) {
						// destBest = direct2;
					// } else {
						// destBest = direct1;
					// }
				// }
			
				// if (destBest != DIRECT_NO_WAY) {
					// if (destBest == DIRECT_DOWN) {
							// (*enemy)->updateDirection(map, Character::ACTION_MOVE_DOWN);
						// } else if (destBest == DIRECT_UP) {
							// (*enemy)->updateDirection(map, Character::ACTION_MOVE_UP);
						// } else if (destBest == DIRECT_LEFT) {
							// (*enemy)->updateDirection(map, Character::ACTION_MOVE_LEFT);
						// } else if (destBest == DIRECT_RIGHT) {
							// (*enemy)->updateDirection(map, Character::ACTION_MOVE_RIGHT);
						// }
				// }
			// /*}
			// index++;*/

	if (currentKeyStates[PLAYER_2_SHOOT]) {
		Fireball * fb = _player2->Shoot();
		if (fb)
			fireballs.push_back(fb);
	}

	_player1->updatePosition(map, timems);
	_player2->updatePosition(map, timems);
}

void SceneGame::updateEnemies(int timems)
{
	for (std::vector<Character*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {
		int startX = (*enemy)->getPosBeforeX();
		int startY = (*enemy)->getPosBeforeY();
		AStarWay_t way1;
		AStarWay_t way2;

		int maxSteps = 5;
		DIRECT destBest = DIRECT_NO_WAY;
		DIRECT direct1 = findAstar(way1, maxSteps, startX, startY, _player1->getPosBeforeX(), _player1->getPosBeforeY(), map->GetWidth(), map->GetHeight(), IMap_isObstacle, map);
		DIRECT direct2 = findAstar(way2,maxSteps,  startX, startY, _player2->getPosBeforeX(), _player2->getPosBeforeY(), map->GetWidth(), map->GetHeight(), IMap_isObstacle, map);

		if (direct1 != DIRECT_NO_WAY && direct2 == DIRECT_NO_WAY) {
			destBest = direct1;
		} else if (direct1 == DIRECT_NO_WAY && direct2 != DIRECT_NO_WAY) {
			destBest = direct2;
		} else if (direct1 != DIRECT_NO_WAY && direct2 != DIRECT_NO_WAY) {
			if (way1.size() > way2.size()) {
				destBest = direct2;
			} else {
				destBest = direct1;
			}
		}

		if (destBest != DIRECT_NO_WAY) {
			if (destBest == DIRECT_DOWN) {
				(*enemy)->updateDirection(map, DIRECT_DOWN);
			} else if (destBest == DIRECT_UP) {
				(*enemy)->updateDirection(map, DIRECT_UP);
			} else if (destBest == DIRECT_LEFT) {
				(*enemy)->updateDirection(map, DIRECT_LEFT);
			} else if (destBest == DIRECT_RIGHT) {
				(*enemy)->updateDirection(map, DIRECT_RIGHT);
			}
		}

		(*enemy)->updatePosition(map, timems / 3);
	}
}

void SceneGame::OnUpdate(int timems)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN  && e.key.keysym.sym == SDLK_ESCAPE)) {
			EngineInst->breakMainLoop();
			return;
		}
	}

	updatePlayers(timems);
	updateFireballs(timems);
	updateEnemies(timems);
}

void SceneGame::OnRender(SDL_Renderer* renderer)
{
	_background->render(renderer);

	SDL_Rect topLeftViewport;
	topLeftViewport.x = 5;
	topLeftViewport.y = 100;
	topLeftViewport.w = EngineInst->screen_width();
	topLeftViewport.h = EngineInst->screen_height();
	SDL_RenderSetViewport(renderer, &topLeftViewport);

	int sizeDst = _tiles->getTileSizeDst();
	int tilesNums = _tiles->getTilesNums();
	//for (int i =  0 ; i<tilesNums; ++i) {
	srand(1);
	
	/*Render background*/
	for (int i = 0 ; i != map->GetHeight() - 1; i++) {
		for (int j = 0 ; j != map->GetWidth() - 1; ++j) {
			int px_left = j * sizeDst + sizeDst / 2;
			int px_top  = i * sizeDst + 0.5 * sizeDst;
			_tiles->renderTile(renderer,
			                   px_left,
			                   px_top,
			                   18 + rand() % 5, SDL_FLIP_NONE);
		}
	}
	/*Render actual mapiles*/
	for (int i = 0 ; i != map->GetHeight(); i++) {
		for (int j = 0 ; j != map->GetWidth(); ++j) {
			int field = map->GetFieldAt(j, i)->GetType();
			int tile =  map->GetFieldAt(j, i)->GetTileId();
			if (field == IField::FLOOR)
				continue;
			int col = j * sizeDst;
			int row = i * sizeDst;
			_tiles->renderTile(renderer, col , row, tile, SDL_FLIP_NONE);

		}
	}
	//{ //Astar Example
	//	int startX = _player1->getPosBeforeX();
	//	int startY = _player1->getPosBeforeY();
	//	AStarWay_t way;
	//
	//	int direct = findAstar(way, startX, startY,_player2->getPosBeforeX(), _player2->getPosBeforeY(), map->GetWidth(), map->GetHeight(), IMap_isObstacle, map);
	//	if (direct != DIRECT_NO_WAY) {
	//		_tiles->renderTile(renderer, startX * sizeDst+margin_left, startY * sizeDst+margin_top, 8); //Start not exit in way
	//		for(AStarWay_t::iterator point = way.begin(); point != way.end(); point++) {
	//			int x = (*point).first;
	//			int y = (*point).second;
	//			_tiles->renderTile(renderer, x * sizeDst +margin_left, y * sizeDst+margin_top, 8);
	//		}
	//	}
	//
	//}

	
	/*render enemies */
	for (std::vector<Character*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {
		if ((*enemy)->GetState() == Character::ALIVE)
			(*enemy)->OnRenderCircle(renderer, 4, 7);
	}

	for (std::vector<Character*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {
		if ((*enemy)->GetState() == Character::ALIVE)
			(*enemy)->OnRender(renderer);
	}
	/* render fireballs */
	for (std::list<Fireball*>::iterator it = fireballs.begin();
	                it != fireballs.end(); ++it) {
		int sprite;
		if ( (*it)->GetPowerLevel() >30)
			sprite= 29;
		else
			sprite=28;
		_tiles->renderTile(renderer, (*it)->getPosX(), (*it)->getPosY(), sprite, SDL_FLIP_NONE);
	}
	/* check loss condition */
	if (_player1->GetState() == Character::DEAD ||
	                _player2->GetState() == Character::DEAD) {
		EngineInst->font()->printfLT(100,
		                             map->GetHeight()*sizeDst, "You lost!");
		
	}
	/*Check victory condition*/
	else if (_player1->GetState() == Character::WON &&
	                _player2->GetState() == Character::WON) {
		EngineInst->font()->printfLT(100,
		                             map->GetHeight()*sizeDst, "Both players won");

	} else if (_player1->GetState() == Character::WON) {
		EngineInst->font()->printfLT(100,
		                             map->GetHeight()*sizeDst, "Player 1 has left the labyrinth. Player 2 must join him so you can together win the level.");

	} else if (_player2->GetState() == Character::WON) {
		EngineInst->font()->printfLT(100,
		                             map->GetHeight()*sizeDst, "Player 2 has left the labyrinth. Player 2 must join him so you can together win the level.");

	}

	_player1->OnRenderCircle(renderer, 4, 7);

	_player1->OnRender(renderer);

	_player2->OnRender(renderer);

}
