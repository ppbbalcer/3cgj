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
	_time_to_shot=0;
};

Player::~Player(void) {};

int Player::getMana()
{
	return _mana;
}
void Player::Win()
{
	printf("WIN");
	SetState(WON);
	_map->GetFieldAt(getPosBeforeX(), getPosBeforeY())->LeftField();

}
void Player::restoreMana(int howMuchMana)
{
	_mana += howMuchMana;
	if (_mana > MAX_MANA) {
		_mana = MAX_MANA;
	}
}
void Player::OnUpdate(int time_ms)
{
	_time_to_shot=max<int>(_time_to_shot-time_ms,
			       0);
	Character::OnUpdate(time_ms);
}

Fireball * Player::Shoot()
{
	clock_t now = clock();

	if (GetState() != ALIVE)
		return NULL;

	if (_mana - FIREBALL_MANA_COST < 0)
		return NULL;
	
	if (_time_to_shot)
		return NULL;

	_mana -= FIREBALL_MANA_COST;
	_time_to_shot=FIREBALL_MIN_DIFF_MS;

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
