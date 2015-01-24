#include "Character.h"
#include "GlobalData.h"
#include "Engine/Engine.h"
#include "fireball.h"

using namespace std;

Character::Character(RTexture* texture, IMap * map)
{
	_texture = texture;
	power_level=DEFAULT_POWER_LEVEL;
	_map = map;
	_health = MAX_HEALTH;
	_state = ALIVE;
	_pos_after_x =
	        _pos_before_x =
	                _pos_after_y =
	                        _pos_before_y = 0;
	last_dir_x = 1;
	last_dir_y = 0;
}

Character::~Character()
{
	delete _texture;
	_texture = NULL;
}

void Character::setPosTiles(int x, int y)
{
	_map->GetFieldAt(_pos_before_x, _pos_before_y)->LeftField();
	_pos_after_x = x;
	_pos_before_x = x;
	_pos_after_y = y;
	_pos_before_y = y;
	_map->GetFieldAt(_pos_after_x, _pos_before_y)->SteppedOver(this);
	setPos(x * EngineInst->getTileSize(), y * EngineInst->getTileSize());
}

int Character::getHealth()
{
	return _health;
}

int Character::crucio(int howMuchCrucio)
{
	_health = max<int>(_health - howMuchCrucio, 0);
	printf("crucio! %d\n", _health);
	if (_health == 0) {
		_state = DEAD;
		_map->GetFieldAt(_pos_before_x, _pos_before_y)->LeftField();
	}
	return _health;
}

int Character::GetState()
{
	return _state;
}

void Character::heal(int howMuchHeal)
{
	_health = min<int>(_health + howMuchHeal, MAX_HEALTH);
}

int Character::GetPowerLevel()
{
	return power_level;
}
int Character::SetPowerLevel(int x)
{
	return (power_level=x);
}

void Character::OnRenderCircle(SDL_Renderer *renderer, int radius, int tileIdx)
{
	int title_size = 23;

	if(radius == 4) {
		int cx = getPosX();
		int cy = getPosY();

	//	if(_pos_before_x == _pos_after_x && _pos_before_y == _pos_after_y) {
			int alfa;
			for(int x=-radius; x<=radius; ++x) {
				for(int y=-radius; y<=radius; ++y) {
					
					int tx = (cx/title_size)+x;
					int ty = (cy/title_size)+y;
					if (tx < 0 || tx >= (_map)->GetWidth()) continue;
					if (ty < 0 || ty >= (_map)->GetHeight()) continue;

					if( (_map)->GetFieldAt(tx, ty)->IsObstacle()) {
						continue;
					}
					alfa = calcCircleAlfaRadius4[x+radius][y+radius];
					if(alfa > 0) {
						_texture->setAlpha( alfa );

						_texture->renderTile(renderer, cx + x*title_size, cy + y*title_size, tileIdx, SDL_FLIP_NONE);	
					}
				}
			}
	/*	} else {



		}
*/


	}else {
		printf("No calculated Radius\n");
		PAUSE();
	}
	_texture->setAlpha( 255 );


}

void Character::OnRender(SDL_Renderer *renderer)
{
	if (GetState()==DEAD) {
		_texture->renderTile(renderer, getPosX(), getPosY(), 30, SDL_FLIP_NONE);
	} else {
		_texture->renderTile(renderer, getPosX(), getPosY());
	}
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

void Character::updateDirection(DIRECT directMove)
{
	if (_state != ALIVE)
		return;

	switch (directMove) {
	case DIRECT_DOWN:
		if ((!_map->GetFieldAt(_pos_before_x, _pos_before_y + 1)->IsObstacle()) &&
		                (!_map->GetFieldAt(_pos_after_x, _pos_before_y + 1)->IsObstacle())) {
			_pos_after_y = _pos_before_y + 1;
		}
		break;

	case DIRECT_UP:
		if ((!_map->GetFieldAt(_pos_before_x, _pos_before_y - 1)->IsObstacle()) &&
		                (!_map->GetFieldAt(_pos_after_x, _pos_before_y - 1)->IsObstacle())) {
			_pos_after_y = _pos_before_y - 1;
		}
		break;

	case DIRECT_RIGHT:
		if ((!_map->GetFieldAt(_pos_before_x + 1, _pos_before_y)->IsObstacle()) &&
		                (!_map->GetFieldAt(_pos_before_x + 1, _pos_after_y)->IsObstacle())) {
			_pos_after_x = _pos_before_x + 1;
		}
		break;

	case DIRECT_LEFT:
		if ((!_map->GetFieldAt(_pos_before_x - 1, _pos_before_y)->IsObstacle()) &&
		                (!_map->GetFieldAt(_pos_before_x - 1, _pos_after_y)->IsObstacle())) {
			_pos_after_x = _pos_before_x - 1;
		}
		break;

	default:
		printf("Unrecognized direction %d given\n", directMove);
		break;
	}
}

void Character::OnUpdate(int time_ms)
{
	int tile_size = EngineInst->getTileSize();
	int target_y = _pos_after_y * tile_size;
	int target_x = _pos_after_x * tile_size;
	int dist = tile_size * time_ms / 100;
	int pos_x = getPosX();
	int pos_y = getPosY();

	if (_state != ALIVE)
		return;

	if (pos_y > target_y) {
		last_dir_y = -1;
		last_dir_x = 0;
		pos_y = max<int>(target_y, pos_y - dist);
	}
	if (pos_y < target_y) {
		last_dir_y = 1;
		last_dir_x = 0;
		pos_y = min<int>(target_y, pos_y + dist);
	}
	if (pos_x > target_x) {
		_texture->setFlip(SDL_FLIP_HORIZONTAL);
		last_dir_y = 0;
		last_dir_x = -1;
		pos_x = max<int>(target_x, pos_x - dist);
	}
	if (pos_x < target_x) {
		_texture->setFlip(SDL_FLIP_NONE);
		last_dir_y = 0;
		last_dir_x = +1;
		pos_x = min<int>(target_x, pos_x + dist);
	}

	if (pos_x == target_x) {
		if (_pos_before_x != _pos_after_x) {
			_map->GetFieldAt(_pos_before_x, _pos_before_y)->LeftField();
			_map->GetFieldAt(_pos_after_x, _pos_before_y)->SteppedOver(this);
			_pos_before_x = _pos_after_x;
		}
	}

	if (pos_y == target_y) {
		if (_pos_before_y != _pos_after_y) {
			_map->GetFieldAt(_pos_before_x, _pos_before_y)
			->LeftField();
			_map->GetFieldAt(_pos_before_x, _pos_after_y)
			->SteppedOver(this);
			_pos_before_y = _pos_after_y;
		}
	}

	if (_pos_before_y == 0 || _pos_before_y == _map->GetHeight() - 1 ||
	                _pos_before_x == 0 || _pos_before_x == _map->GetWidth() - 1) {
		_state = WON;
		_map->GetFieldAt(_pos_before_x, _pos_before_y)->LeftField();
	}
	setPos(pos_x, pos_y);
}
