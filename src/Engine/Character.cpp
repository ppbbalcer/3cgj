#include "Character.h"
#include "../GlobalData.h"
#include "Engine/Engine.h"
using namespace std;

Character::Character(IMap * map, RTexture *texture)
{
	_health = MAX_HEALTH;
	_texture = texture;
	_state = ALIVE;
	_pos_after_x = 
	_pos_before_x = 
	_pos_after_y = 
	_pos_before_y = 0;
}

Character::~Character()
{
}

void Character::setPosTiles(IMap * map, int x, int y)
{
	map->GetFieldAt(_pos_before_x,_pos_before_y)
		->LeftField();
	_pos_after_x = x;
	_pos_before_x = x;
	_pos_after_y = y;
	_pos_before_y = y;
	map->GetFieldAt(_pos_after_x, _pos_before_y)
		->SteppedOver();
	setPos(x * EngineInst->getTileSize(), y * EngineInst->getTileSize());
}

int Character::getHealth()
{
	return _health;
}

int Character::crucio(int howMuchCrucio)
{
	_health = max<int>(_health - howMuchCrucio, 0);
	if (_health=0) {
		_state=DEAD;
	}
	return _health;
}
int Character::GetState() {
	return _state;
}
void Character::heal(int howMuchHeal)
{
	_health = min<int>(_health + howMuchHeal, MAX_HEALTH);
}

void Character::render(SDL_Renderer *renderer, RTexture *tiles)
{
	_texture->render(renderer);
}

void Character::setPos(int x, int y)
{
	_posX = x;
	_posY = y;
}

int Character::getPosX()
{
	return _posX;
}
int Character::getPosY()
{
	return _posY;
}

int Character::getPosBeforeX()
{
	return _pos_before_x;
}

int Character::getPosAfterX()
{
	return _pos_after_x;
}

int Character::getPosBeforeY()
{
	return _pos_before_y;
}

int Character::getPosAfterY()
{
	return _pos_after_y;
}

void Character::updateDirection(IMap *map, Action action)
{
	if (_state != ALIVE)
		return;
	if (action == ACTION_MOVE_DOWN) {
		if ((!map->GetFieldAt(_pos_before_x,_pos_before_y+1)
			->IsObstacle()) &&
			(!map->GetFieldAt(_pos_after_x,_pos_before_y+1)
			->IsObstacle()) )
		{
			_pos_after_y = _pos_before_y + 1;
		}
	}

	if (action == ACTION_MOVE_UP) {
		if ((!map->GetFieldAt(_pos_before_x,_pos_before_y-1)
			->IsObstacle()) &&
			(!map->GetFieldAt(_pos_after_x,_pos_before_y-1)
			->IsObstacle()) )
		{
			_pos_after_y = _pos_before_y - 1;
		}
	}

	if (action == ACTION_MOVE_RIGHT) {
		if ((!map->GetFieldAt(_pos_before_x+1,_pos_before_y)
			->IsObstacle()) &&
			(!map->GetFieldAt(_pos_before_x+1,_pos_after_y)
			->IsObstacle()) )
		{
			_pos_after_x = _pos_before_x + 1;
		}
	}

	if (action == ACTION_MOVE_LEFT) {
		if ((!map->GetFieldAt(_pos_before_x-1,_pos_before_y)
			->IsObstacle()) &&
			(!map->GetFieldAt(_pos_before_x-1,_pos_after_y)
			->IsObstacle()) )
		{
			_pos_after_x = _pos_before_x - 1;
		}
	}
}

void Character::updatePosition(IMap *map, int time_ms, int tile_size)
{
	//t tile_size = EngineInst->screen_width()/map->GetWidth();
	//int tile_size = 50;
	int target_y = _pos_after_y * tile_size;
	int target_x = _pos_after_x * tile_size;
	float dist = 0.3 * time_ms;
	float pos_x = getPosX();
	float pos_y = getPosY();
	if (_state != ALIVE)
		return;

	if (pos_y > target_y) {
		pos_y = max<int>(target_y, pos_y - dist);
	}
	if (pos_y < target_y) {
		pos_y = min<int>(target_y, pos_y + dist);
	}
	if (pos_x > target_x) {
		pos_x = max<int>(target_x, pos_x - dist);
	}
	if (pos_x < target_x) {
		pos_x = min<int>(target_x, pos_x + dist);
	}

	if (pos_x == target_x) {
		if (_pos_before_x != _pos_after_x) {
			map->GetFieldAt(_pos_before_x,_pos_before_y)
				->LeftField();
			map->GetFieldAt(_pos_after_x, _pos_before_y)
				->SteppedOver();
			_pos_before_x = _pos_after_x;
		}
	}
	if (pos_y == target_y){
		if (_pos_before_y != _pos_after_y) {
			map->GetFieldAt(_pos_before_x,_pos_before_y)
				->LeftField();
			map->GetFieldAt(_pos_before_x, _pos_after_y)
				->SteppedOver();
			_pos_before_y = _pos_after_y;
		}
	}

	if (_pos_before_y == 0 || _pos_before_y == map->GetHeight()-1 ||
	    _pos_before_x == 0 || _pos_before_x == map->GetWidth()-1) {
		_state = WON;
		map->GetFieldAt(_pos_before_x,_pos_before_y)
			->LeftField();
	}
	setPos(pos_x, pos_y);
}
