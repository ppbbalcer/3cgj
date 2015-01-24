#include "base_level.h"
#include "../GlobalData.h"
#include <stdio.h>
#include <time.h>

#define MAX_ROOM_PATH 255
#define TILE_SIZE 32

#include <iostream>
#include <fstream>
#include <string>

BaseRoom::BaseRoom(int id, int level_id) {
	this->id = id;
	this->level_id = level_id;
	char buff[MAX_ROOM_PATH];
	sprintf(buff, "Resources/levels/%u/%u.txt", level_id, id);
	map = IMap::Factory(IMap::LOADED, buff);
}

BaseRoom::~BaseRoom() {
}

void BaseRoom::render(RTexture *_tiles, SDL_Renderer* renderer) {
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
}

BaseLevel::BaseLevel(int id, int rooms_count) {
	for (int i = 0; i < rooms_count; ++i) {
		rooms.push_back(new BaseRoom(i, id));
	}
}

BaseLevel::~BaseLevel() {
	for (std::vector<BaseRoom*>::iterator itr = rooms.begin(); itr != rooms.end(); ++itr) {
		delete *itr;
	}
}

void BaseLevel::OnLoad() {
	EngineInst->setTileSize(TILE_SIZE);
	_tiles = new RTexture(globalTextures[1]);
	_tiles->setTileSizeDst(TILE_SIZE);
	_tiles->setTileSizeSrc(TILE_SIZE);
	current_room = 0;
}

void BaseLevel::OnFree() {
	current_room = -1;
	delete _tiles;
}

void BaseLevel::OnUpdate(int dt) {
	if (current_room == -1)
		return;

	//handle events
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 )
	{
		if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN  && e.key.keysym.sym == SDLK_ESCAPE) )
		{
			EngineInst->breakMainLoop();
			return;
		}
	}
}

void BaseLevel::OnRender(SDL_Renderer* renderer) {
	if (current_room == -1)
		return;

	SDL_Rect topLeftViewport; 
	topLeftViewport.x = 5; 
	topLeftViewport.y = 100; 
	topLeftViewport.w = EngineInst->screen_width(); 
	topLeftViewport.h = EngineInst->screen_height(); 
	SDL_RenderSetViewport( renderer, &topLeftViewport ); 

	rooms[current_room]->render(_tiles, renderer);
}








