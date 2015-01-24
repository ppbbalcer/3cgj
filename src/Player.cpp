#include "Player.h"
#include "GlobalData.h"

Player::~Player(void) {};

int Player::getMana()
{
	return _mana;
}
void Player::useMana(int howMuchMana)
{
	_mana -= howMuchMana;
	if (_mana < 0) {
		_mana = 0;
	}
}

void Player::restoreMana(int howMuchMana)
{
	_mana += howMuchMana;
	if (_mana > MAX_MANA) {
		_mana = MAX_MANA;
	}
}

Fireball * Player::Shoot()
{
	if (GetState() != ALIVE)
		return 0;

	globalAudios[GameSounds::FIREBALL].res.sound->play();

	return new Fireball(getPosBeforeX() + last_dir_x,
	                    getPosBeforeY() + last_dir_y,
	                    last_dir_x, last_dir_y, GetPowerLevel());
}