#include "Player.h"
#include "GlobalData.h"
#include "Engine/RTexture.h"

using namespace std;

Player::Player(RTexture * texture, IMap * map, int hp, int mana) : Character(texture, map)
{
	_type = TYPE_PLAYER;
	_mana = mana;
	_health = hp;
	printf("PLAYER: %u %u\n", _health, _mana);
	_last_shot_time = clock() - FIREBALL_MIN_DIFF_MS * (CLOCKS_PER_SEC / 1000);
};

Player::~Player(void) {};

int Player::getMana()
{
	return _mana;
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

	if (_mana - FIREBALL_MANA_COST < 0)
		return NULL;
	clock_t ms_since_last_shot = ((1.0 * now - _last_shot_time) / (CLOCKS_PER_SEC / 1000));
	if (ms_since_last_shot <= FIREBALL_MIN_DIFF_MS)
		return NULL;

	_mana -= FIREBALL_MANA_COST;
	_last_shot_time = now;

	globalAudios[GameSounds::FIREBALL].res.sound->play();

	return new Fireball(getPosBeforeX(),
	                    getPosBeforeY(),
	                    last_dir_x, last_dir_y,
			    GetPowerLevel(),this);
}

int Player::crucio(int howMuchCrucio)
{
	int hpRem = Character::crucio(howMuchCrucio);
	if (hpRem <= 0) {
		globalAudios[PLAYER_DEATH].res.sound->play();
	} else {
		globalAudios[PLAYER_PAIN].res.sound->play();
	}
	return hpRem;
}
