#include "MapLogic/field.h"
#include "MapLogic/map.h"
#include "scene_game.h"
#include "GlobalData.h"
#include <algorithm>
#include "Engine/AStar.h"
#include <stdio.h>
#include "fireball.h"
#include "Enemy.h"
#include "KeyMap.h"
#include "level.h"
#include "MapLogic/door.h"
using namespace std;

#define MAX_ROOM_PATH 255
#define HEARTBEAT_BASE_INTERVAL 2000
#define HEARTBEAT_MIN_INTERVAL 500

/* looking for obstacles*/
bool IMap_isObstacle(int x, int y, void* objMap)
{
	if (((IMap*)objMap)->GetFieldAt(x, y)->IsOccupied())
		return false;
	return ((IMap*)objMap)->GetFieldAt(x, y)->IsObstacle();
}

SceneGame::SceneGame(Level *level, int room_id)
{
	this->room_id = room_id;
	this->level = level;
	this->heartbeat_tempo = 0;
	char buff[MAX_ROOM_PATH];
	sprintf(buff, "Resources/levels/%u/%u.txt", level->getId(), room_id);
	map = IMap::Factory(IMap::LOADED, buff);
}

SceneGame::~SceneGame()
{
	delete map;
}
SDL_Rect SceneGame::GetDefaultViewport()
{
#define MARGIN_TOP 100
#define MARGIN_BOTTOM 60
#define MARGIN_LEFT 5
#define MARGIN_RIGHT 5
	
	SDL_Rect topLeftViewport;
	topLeftViewport.x = MARGIN_LEFT;
	topLeftViewport.y = MARGIN_TOP;
	topLeftViewport.w = EngineInst->screen_width()-MARGIN_LEFT-MARGIN_RIGHT;
	topLeftViewport.h = EngineInst->screen_height()-MARGIN_TOP-MARGIN_BOTTOM;
	return topLeftViewport;
}
void SceneGame::OnLoad()
{
	// montage *.png ../floor0.png -geometry +0x0 -tile 3x3 ../walls.png
	SDL_Rect dvp=GetDefaultViewport();

	int tile_size = std::min<int>(dvp.w / map->GetWidth(),
				 dvp.h/map->GetHeight());

	EngineInst->setTileSize(tile_size);

	bool success = EngineInst->loadResources(texturesScene_game, texturesScene_gameSize);
	/*RTexture *player1Texture = new RTexture(texturesScene_game[2]);
	RTexture *player2Texture = new RTexture(texturesScene_game[2]);*/

	//player1Texture->setPos(TILE_SIZE, TILE_SIZE);
	//player2Texture->setPos(TILE_SIZE, TILE_SIZE);
	int tileSizeSrc = 64;

	RTexture *tmpTexture;
	_background = new RTexture(texturesScene_game[1]);
	_background ->setScaleSize(1.0f * EngineInst->screen_width() / _background->getWidth());

	tmpTexture = new RTexture(texturesScene_game[3]);
	tmpTexture->setTileSizeSrc(tileSizeSrc);
	tmpTexture->setTileSizeDst(tile_size);
	tmpTexture->setTileIdx(24);
	_player1 = new Player(tmpTexture, map);

	tmpTexture = new RTexture(texturesScene_game[3]);
	tmpTexture->setTileSizeSrc(tileSizeSrc);
	tmpTexture->setTileSizeDst(tile_size);
	tmpTexture->setTileIdx(27);
	_player2 = new Player(tmpTexture, map);

	_player1->setPosTiles(map->GetPlayer1Start().first,
			      map->GetPlayer1Start().second);
	_player2->setPosTiles(map->GetPlayer2Start().first,
			      map->GetPlayer2Start().second);

	const enemies_list &ens = map->GetEnemies();

	//int i=0;
	for (enemies_list::const_iterator it=ens.begin() ; it!=ens.end();
	     ++it)
	{
		tmpTexture = new RTexture(texturesScene_game[3]);
		tmpTexture->setTileSizeSrc(tileSizeSrc);
		tmpTexture->setTileSizeDst(tile_size);
		tmpTexture->setTileIdx(23);
		Enemy* enemy = new Enemy(tmpTexture, map, (*it)->hp, (*it)->ai);
		enemy->setPosTiles((*it)->x, (*it)->y);
		_enemys.push_back(enemy);
	}

	_tiles = new RTexture(texturesScene_game[3]);
	_tiles->setTileSizeSrc(tileSizeSrc);
	_tiles->setTileSizeDst(tile_size);

	_arrayShadowW = map->GetWidth();
	_arrayShadowH = map->GetHeight();
	_arrayShadow = new int[_arrayShadowW*_arrayShadowH*sizeof(_arrayShadowH)];

	//Load media
	if (!success) {
		printf("Failed to load media Scene02Renderer !\n");
		PAUSE();
	}
	globalAudios[HEARTBEAT].res.sound->setVolume(0.2f);
	globalAudios[HEARTBEAT].res.sound->play(-1, 0, HEARTBEAT_BASE_INTERVAL);
}

extern int doskey_active;

void SceneGame::OnFree()
{
	for (std::vector<Enemy*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {
		delete *enemy;
	}
	_enemys.clear();
	delete _arrayShadow;
	_arrayShadow = NULL;

	//Destroy textures???
	doskey_active = 0;

	globalAudios[HEARTBEAT].res.sound->stop();

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
		_player1->updateDirection(DIRECT_DOWN);
	}

	if (currentKeyStates[PLAYER_1_MOVE_UP]) {
		_player1->updateDirection(DIRECT_UP);
	}

	if (currentKeyStates[PLAYER_1_MOVE_LEFT]) {
		_player1->updateDirection(DIRECT_LEFT);
	}

	if (currentKeyStates[PLAYER_1_MOVE_RIGHT]) {
		_player1->updateDirection(DIRECT_RIGHT);
	}

	if (currentKeyStates[PLAYER_1_SHOOT]) {
		Fireball * fb = _player1->Shoot();
		if (fb)
			fireballs.push_back(fb);
	}

	if (currentKeyStates[PLAYER_2_MOVE_DOWN]) {
		_player2->updateDirection(DIRECT_DOWN);
	}

	if (currentKeyStates[PLAYER_2_MOVE_UP]) {
		_player2->updateDirection(DIRECT_UP);
	}

	if (currentKeyStates[PLAYER_2_MOVE_LEFT]) {
		_player2->updateDirection(DIRECT_LEFT);
	}

	if (currentKeyStates[PLAYER_2_MOVE_RIGHT]) {
		_player2->updateDirection(DIRECT_RIGHT);
	}

	if (currentKeyStates[PLAYER_2_SHOOT]) {
		Fireball * fb = _player2->Shoot();
		if (fb)
			fireballs.push_back(fb);
	}

	_player1->OnUpdate(timems);
	_player2->OnUpdate(timems);
}

void SceneGame::updateEnemies(int timems)
{
	for (std::vector<Enemy*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {
		(*enemy)->OnUpdate(timems / 3);
		if ((*enemy)->getAI() == ENEMY_AI_OFF)
			continue;
		int startX = (*enemy)->getPosBeforeX();
		int startY = (*enemy)->getPosBeforeY();
		AStarWay_t way1;
		AStarWay_t way2;

		int maxSteps = 0;
		DIRECT destBest = DIRECT_NO_WAY;
		DIRECT direct1 = DIRECT_NO_WAY;
		DIRECT direct2 = DIRECT_NO_WAY;

		int distQuad = EngineInst->getTileSize()*EngineInst->getTileSize()*6*6;
		int distX = _player1->getPosX() - (*enemy)->getPosX();
		int distY = _player1->getPosY() - (*enemy)->getPosY();

		//if(distX*distX + distY*distY <= distQuad ) {
			direct1 = findAstar(way1, maxSteps, startX, startY, _player1->getPosBeforeX(), _player1->getPosBeforeY(), map->GetWidth(), map->GetHeight(), IMap_isObstacle, map);
		//}

		distX = _player2->getPosX() - (*enemy)->getPosX();
		distY = _player2->getPosY() - (*enemy)->getPosY();
		//if(distX*distX + distY*distY <= distQuad ) {
			direct2 = findAstar(way2, maxSteps,  startX, startY, _player2->getPosBeforeX(), _player2->getPosBeforeY(), map->GetWidth(), map->GetHeight(), IMap_isObstacle, map);
		//}

		if (heartbeat_tempo == 0 && ((way1.size() != 0 && way1.size() < 10 ) || (way2.size() != 0 && way2.size() < 10))) {
			heartbeat_tempo = 50;
			globalAudios[HEARTBEAT].res.sound->setDelay(HEARTBEAT_MIN_INTERVAL);
		} else if (heartbeat_tempo != 0) {
			heartbeat_tempo--;
			if (heartbeat_tempo == 0)
				globalAudios[HEARTBEAT].res.sound->setDelay(HEARTBEAT_BASE_INTERVAL);
		}

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
		} else {
			destBest = (*enemy)->getRandomDirection();
		}

		if (destBest != DIRECT_NO_WAY) {
			if (destBest == DIRECT_DOWN) {
				(*enemy)->updateDirection(DIRECT_DOWN);
			} else if (destBest == DIRECT_UP) {
				(*enemy)->updateDirection(DIRECT_UP);
			} else if (destBest == DIRECT_LEFT) {
				(*enemy)->updateDirection(DIRECT_LEFT);
			} else if (destBest == DIRECT_RIGHT) {
				(*enemy)->updateDirection(DIRECT_RIGHT);
			}
		}

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
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
			level->resetCurrent();
			return;
		}
	}
	globalAudios[HEARTBEAT].res.sound->update(timems);
	updatePlayers(timems);
	updateFireballs(timems);
	updateEnemies(timems);
	updateShadows();
}

void SceneGame::updateShadowsObj4(int centerTiltX, int centerTiltY) 
{
	int radius = 4;
	int alfa,xx,yy;
	int idx;
	for(int y=-radius; y<=radius; ++y) {
		for(int x=-radius; x<=radius; ++x) {
			alfa = calcCircleAlfaRadius4[x+radius][y+radius];
			if(alfa > 0) {
				xx = x + centerTiltX;
				yy = y + centerTiltY;
				if(xx >= 0 && xx < _arrayShadowW && yy >= 0 && yy < _arrayShadowH) {
					idx = yy*_arrayShadowW + xx;
					_arrayShadow[idx] += alfa;
					if(_arrayShadow[idx] > 255) {
						_arrayShadow[idx] = 255;
					}
				}
			}
		}
	}
}

void SceneGame::updateShadowsObj6(int centerTiltX, int centerTiltY) 
{
	int radius = 6;
	int alfa,xx,yy;
	int idx;
	for(int y=-radius; y<=radius; ++y) {
		for(int x=-radius; x<=radius; ++x) {
			alfa = calcCircleAlfaRadius6[x+radius][y+radius];
			if(alfa > 0) {
				xx = x + centerTiltX;
				yy = y + centerTiltY;
				if(xx >= 0 && xx < _arrayShadowW && yy >= 0 && yy < _arrayShadowH) {
					idx = yy*_arrayShadowW + xx;
					_arrayShadow[idx] += alfa;
					if(_arrayShadow[idx] > 255) {
						_arrayShadow[idx] = 255;
					}
				}
			}
		}
	}
}

void SceneGame::updateShadows()
{
	memset(_arrayShadow, 00, _arrayShadowW*_arrayShadowH*sizeof(_arrayShadowH));

	updateShadowsObj6(_player1->getPosAfterX(), _player1->getPosAfterY());
	updateShadowsObj6(_player2->getPosAfterX(), _player2->getPosAfterY());
	
	for (int i = 0 ; i != map->GetHeight(); i++) {
		for (int j = 0 ; j != map->GetWidth(); ++j) {
			int field = map->GetFieldAt(j, i)->GetType();
			//int tile =  map->GetFieldAt(j, i)->GetTileId();
			if (field == IField::MEDKIT || field == IField::DOSKEY || field == IField::POWERUP) {
				updateShadowsObj4(j, i);
			}

		}
	}
	
}


void SceneGame::OnRenderShadow(SDL_Renderer* renderer) {
	
	int tileSize = EngineInst->getTileSize();
	int alfa;
	for (int y = 0 ; y < _arrayShadowH; ++y) {
		for (int x = 0 ;x< _arrayShadowW; ++x) {
			alfa = 255 - _arrayShadow[y*_arrayShadowW + x];
			if (alfa >140)
			{
				alfa = 140;
			}
			_tiles->setAlpha(alfa);
			_tiles->renderTile(renderer, x*tileSize, y*tileSize, 35, SDL_FLIP_NONE);
		}
	}

	_tiles->setAlpha(255);

}

static unsigned long _next = 1;

static int _rand(void)
{
	_next = _next * 1103515245 + 12345;
	return((unsigned)(_next/65536) % 32768);
}

void _srand(unsigned seed) {
	_next = seed;
}

void SceneGame::OnRenderMap(SDL_Renderer* renderer) {
	int tileSize = EngineInst->getTileSize();
	int tilesNums = _tiles->getTilesNums();

	_srand(1);

	/*Render background*/
	for (int i = 0 ; i != map->GetHeight(); i++) {
		for (int j = 0 ; j != map->GetWidth(); ++j) {
			int px_left = j * tileSize;
			int px_top  = i * tileSize;
			_tiles->renderTile(renderer,
			                   px_left,
			                   px_top,
			                   18 + _rand() % 5, SDL_FLIP_NONE);
		}
	}
	/*Render actual mapiles*/
	for (int i = 0 ; i != map->GetHeight(); i++) {
		for (int j = 0 ; j != map->GetWidth(); ++j) {
			int field = map->GetFieldAt(j, i)->GetType();
			int tile =  map->GetFieldAt(j, i)->GetTileId();
			if (field == IField::FLOOR)
				continue;
			int col = j * tileSize;
			int row = i * tileSize;
			_tiles->renderTile(renderer, col , row, tile, SDL_FLIP_NONE);

		}
	}
	#define MARGIN_TOP 41
	#define MARGIN_CORNER 42
	#define MARGIN_LEFT 43
	for (int i = 0 ; i != map->GetHeight(); i++) {
		//left and right column
		int col = 0 * tileSize;
		int row = i * tileSize;
		_tiles->renderTile(renderer, col , row, MARGIN_LEFT, SDL_FLIP_NONE);
		col = (map->GetWidth()-1)*tileSize;
		_tiles->renderTile(renderer, col , row, MARGIN_LEFT, SDL_FLIP_HORIZONTAL);	
	}
	for (int j = 0 ; j != map->GetWidth(); ++j) {
		// top and bottom line0
		int col = j * tileSize;
		int row = 0;
		_tiles->renderTile(renderer, col , row, MARGIN_TOP, SDL_FLIP_NONE);
		row = (map->GetHeight()-1)*tileSize;
		_tiles->renderTile(renderer, col , row, MARGIN_TOP, SDL_FLIP_VERTICAL);	
	}
}


void SceneGame::OnRender(SDL_Renderer* renderer)
{
	// _background->render(renderer);

	int tileSize = EngineInst->getTileSize();

	SDL_Rect topLeftViewport=GetDefaultViewport();
	int map_width=map->GetWidth()*EngineInst->getTileSize();
	if (topLeftViewport.w>map_width) {
		int excess_width = topLeftViewport.w-map_width;
		topLeftViewport.w-=excess_width;
		topLeftViewport.x+=excess_width/2;
	}
	SDL_RenderSetViewport(renderer, &topLeftViewport);
	OnRenderMap(renderer);




	
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
	//for (std::vector<Character*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {
	//	if ((*enemy)->GetState() == Character::ALIVE)
	//		(*enemy)->OnRenderCircle(renderer, 4, 7);
	//}
	//_player1->OnRenderCircle(renderer, 4, 7);


	for (std::vector<Enemy*>::iterator enemy = _enemys.begin(); enemy != _enemys.end(); ++enemy) {
		if ((*enemy)->GetState() == Character::ALIVE)
			(*enemy)->OnRender(renderer);
	}


	/* render fireballs */
	for (std::list<Fireball*>::iterator it = fireballs.begin();
	                it != fireballs.end(); ++it) {
		int sprite;
		if ((*it)->GetPowerLevel() > 30)
			sprite = 29;
		else
			sprite = 28;
		_tiles->renderTile(renderer, (*it)->getPosX(), (*it)->getPosY(), sprite, SDL_FLIP_NONE);
	}
	/* check loss condition */
	if (_player1->GetState() == Character::DEAD ||
	                _player2->GetState() == Character::DEAD) {
		EngineInst->font()->printfLT(100,
		                             map->GetHeight()*tileSize, "You lost!");
		EngineInst->font()->printfLT(100,
		                             (map->GetHeight()*tileSize)+30, "Press R to try again");
	}
	/*Check victory condition*/
	else if (_player1->GetState() == Character::WON &&
	                _player2->GetState() == Character::WON) {
		EngineInst->font()->printfLT(100,
		                             map->GetHeight()*tileSize, "Both players won");
		Door * dor = dynamic_cast <Door*>(
			map->GetFieldAt(_player1->getPosAfterX(),
					_player1->getPosAfterY()));
		//room_id + 1
		level->setCurrentScene(dor->GetTargetBoard());
	} else if (_player1->GetState() == Character::WON) {
		EngineInst->font()->printfLT(100,
			map->GetHeight()*tileSize, "Player 1 has left the screen. Player 2 must join him so you can win the level together.");
	} else if (_player2->GetState() == Character::WON) {
		EngineInst->font()->printfLT(100,
			map->GetHeight()*tileSize, "Player 2 has left the screen. Player 2 must join him so you can win the level together.");
	}

	_player1->OnRender(renderer);
	_player2->OnRender(renderer);


	OnRenderShadow(renderer);

	// Render top bar
	SDL_Rect veryTopBar;
	int playerBarXPadding = 20;
	int playerBarHeight = 20;
	int paddingBetweenBars = 5;

	veryTopBar.x = 0;
	veryTopBar.y = 20;
	veryTopBar.w = EngineInst->screen_width();
	veryTopBar.h = 50;

	SDL_RenderSetViewport(renderer, &veryTopBar);

	SDL_Rect p1_hp_rect = { playerBarXPadding, 0, _player1->getHealth() * 2, playerBarHeight};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &p1_hp_rect);

	SDL_Rect p1_mana_rect = { playerBarXPadding, playerBarHeight + paddingBetweenBars, _player1->getMana() * 2, playerBarHeight};
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &p1_mana_rect);

	SDL_Rect p2_hp_rect = { EngineInst->screen_width() - playerBarXPadding - _player2->getHealth() * 2, 0, _player2->getHealth() * 2, playerBarHeight};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &p2_hp_rect);

	SDL_Rect p2_mana_rect = { EngineInst->screen_width() - playerBarXPadding - _player2->getMana() * 2, playerBarHeight + paddingBetweenBars, _player2->getMana() * 2, playerBarHeight};;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &p2_mana_rect);
}
