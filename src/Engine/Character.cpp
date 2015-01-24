#include "Character.h"
#include "../GlobalData.h"

using namespace std;

Character::Character(RTexture *texture)
{
	_health = MAX_HEALTH;
	_texture = texture;
	_pos_after_x = 1;
	_pos_before_x = 1;
	_pos_after_y = 1;
	_pos_before_y = 1;
}

int Character::getHealth()
{
	return _health;
}

int Character::crucio(int howMuchCrucio)
{
	_health = max<int>(_health - howMuchCrucio, 0);
	return _health;
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
	_texture->setPos(x, y);
}

int Character::getPosX()
{
	return _texture->getPosX();
}
int Character::getPosY()
{
	return _texture->getPosY();
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

void Character::updatePosition(int time_ms)
{
	int target_y = _pos_after_y * TILE_SIZE;
	int target_x = _pos_after_x * TILE_SIZE;
	float dist = 0.3 * time_ms;
	float pos_x = getPosX();
	float pos_y = getPosY();

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

	if (pos_x == target_x)
		_pos_before_x = _pos_after_x;	
	if (pos_y == target_y)
		_pos_before_y = _pos_after_y;	

	setPos(pos_x, pos_y);
}