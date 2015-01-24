#include "Character.h"

using namespace std;

Character::Character(RTexture *texture)
{
	_health = MAX_HEALTH;
	_texture = texture;
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