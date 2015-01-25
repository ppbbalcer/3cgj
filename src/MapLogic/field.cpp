#include "field.h"
#include <cassert>
#include "field_impl.h"
#include "../Player.h"
#include "../GlobalData.h"
#include "skull.h"

int Field::assigned_field[NUM_FIELD_TYPES];

void Field::EnsureFieldIdsInitialized()
{
	static bool initialized = false;
	if (initialized) {
		return;
	}
	assigned_field[WALL_HORIZONTAL] = 5;

	assigned_field[WALL_VERTICAL] = 13;
	assigned_field[WALL_CROSS] =  02;
	assigned_field[WALL_LT] = 3;
	assigned_field[WALL_RT] = 9;
	assigned_field[WALL_LB] = 1;
	assigned_field[WALL_RB] = 4;
	assigned_field[T_LEFT] =  6;
	assigned_field[T_RIGHT] = 11;
	assigned_field[T_TOP] =  12;
	assigned_field[T_BOTTOM] =  10;
	assigned_field[FLOOR] = 7;
	assigned_field[DESK] = 7;
	assigned_field[DOOR] = 7;
	assigned_field[DOOR_VERTICAL_CLOSED] = 17;
	assigned_field[DOOR_VERTICAL_OPEN] = 16;
	assigned_field[DOOR_HORIZONTAL_CLOSED] = 14;
	assigned_field[DOOR_HORIZONTAL_OPEN] = 15;
	assigned_field[MEDKIT] = 25;
	assigned_field[INACTIVE_SKULL] = 26;
	assigned_field[SILVER_SKULL] = 45;
	assigned_field[GOLDEN_SKULL] = 44;
	assigned_field[POWERUP] = 31;
	assigned_field[SMALL_MANA_FLASK] = 36;
	assigned_field[LARGE_MANA_FLASK] = 40;
	assigned_field[SMALL_HEALTH_FLASK] = 34;
	assigned_field[LARGE_HEALTH_FLASK] = 33;
	assigned_field[EMPTY_FLASK] = 32;
	assigned_field[SWITCH_DOWN] = 38;
	assigned_field[SWITCH_UP] = 37;
	assigned_field[TRAP] = 30;
	assigned_field[STAIRS] = 46;
	assigned_field[SPIKES_ON] = 47;
	assigned_field[SPIKES_OFF] = 48;
	assigned_field[EVIL_COMPUTER] = 39;
	initialized = true;
}
int Field::GetTileId()
{
	EnsureFieldIdsInitialized();
	return assigned_field[GetType()];
}
bool Field::IsObstacle()
{
	if (someone_is_here) {
		return true;
	}
	if (GetType() == DOOR_VERTICAL_CLOSED ||
	                GetType() == DOOR_HORIZONTAL_CLOSED)
		return true;
	return (type >= WALL && type <= T_BOTTOM);
}
int doskey_active = 0;
int Field::GetType()
{
	return type;
}

void Field::SteppedOver(Character * who)
{
	if (type == POWERUP) {
		type = FLOOR;
		who->SetPowerLevel(who->GetPowerLevel() + POWERUP_VAL);
	}
	if (type == LARGE_HEALTH_FLASK && who->getType() == TYPE_PLAYER) {
		type = EMPTY_FLASK;
		who->heal(LARGE_POTION_HEAL_VAL);
		globalAudios[SLURP].res.sound->play();
	}
	if (type == SMALL_HEALTH_FLASK && who->getType() == TYPE_PLAYER) {
		type = EMPTY_FLASK;
		who->heal(SMALL_POTION_HEAL_VAL);
		globalAudios[SLURP].res.sound->play();
	}
	if (type == SMALL_MANA_FLASK && who->getType() == TYPE_PLAYER) {
		type = EMPTY_FLASK;
		Player *player = (Player *)who;
		player->restoreMana(SMALL_POTION_MANA_VAL);
		globalAudios[SLURP].res.sound->play();
	}
	if (type == LARGE_MANA_FLASK && who->getType() == TYPE_PLAYER) {
		type = EMPTY_FLASK;
		Player *player = (Player *)who;
		player->restoreMana(LARGE_POTION_MANA_VAL);
		globalAudios[SLURP].res.sound->play();
	}
	if (type == MEDKIT) {
		type = FLOOR;
		who->heal(MEDKIT_HEAL_VAL);
	}
	someone_is_here = who;
}

void Field::LeftField()
{
	someone_is_here = 0;
}

Character* Field::WhoIsHere()
{
	return someone_is_here;
}
