#include "Player.h"
#include "GlobalData.h"

using namespace std;

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
	clock_t now = clock();

	if (GetState() != ALIVE)
		return NULL;

	if (((1.0 * now - _last_shot_time) / (CLOCKS_PER_SEC / 1000)) <= FIREBALL_MIN_DIFF_MS)
		return NULL;

	_last_shot_time = now;

	globalAudios[GameSounds::FIREBALL].res.sound->play();

	return new Fireball(getPosBeforeX() + last_dir_x,
	                    getPosBeforeY() + last_dir_y,
	                    last_dir_x, last_dir_y, GetPowerLevel());
}
