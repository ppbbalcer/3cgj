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
	load(buff);
}

char map_field_chars[MAX_MAP_FIELDS] = {0, 'w', ' '};

void BaseRoom::load(const char *path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		PAUSE();
		return;
	}
	std::string line;
	height = 0;
	while(std::getline(file, line)) {
		width = line.length();
		for (int i = 0; i < width; ++i) {
			char c = line[i];
			enum map_field field = MAX_MAP_FIELDS;
			for (int n = 0; n < MAX_MAP_FIELDS; ++n) {
				if (map_field_chars[n] == c) {
					field = (enum map_field)n;
					break;
				}
			}
			if (field == MAX_MAP_FIELDS) {
				PAUSE();
				return;
			}
			map[height][i] = field;
		}
		height++;
	}

	file.close();
}

BaseRoom::~BaseRoom() {
}

#define MAX_FLOORS 3
int floors[MAX_FLOORS] = {6, 7, 8};

#define MAX_WALLS 2
int walls[MAX_WALLS] = {4, 5};

void BaseRoom::render(RTexture *_tiles, SDL_Renderer* renderer) {
	int sizeDst = _tiles->getTileSizeDst();
	int tilesNums = _tiles->getTilesNums();
	srand(id + level_id);

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int tile = -1;
			switch (map[i][j]) {
			case FIELD_FLOOR:
				tile = floors[rand()%MAX_FLOORS];
				break;
			case FIELD_WALL:
				tile = walls[rand()%MAX_WALLS];
				break;
			case FIELD_UNKNOWN:
			default:
				break;
			}
			if (tile != -1) {
				int col = j * sizeDst;
				int row = i * sizeDst;
				_tiles->renderTile(renderer, col , row, tile, SDL_FLIP_NONE);
			}
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
	_tiles = new RTexture(globalTextures[0]);
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








