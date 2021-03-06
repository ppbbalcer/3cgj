#include "field.h"
#include "field_impl.h"
#include "skull.h"
#include "../Player.h"
#include "../GlobalData.h"
#include <cassert>

bool Skull::IsGolden()
{
	return GetType()==GOLDEN_SKULL;
}

int Skull::GetType()
{
	if (enabled<=0)
		return INACTIVE_SKULL;
	else
	{
		int result=Field::GetType();
		assert(result==GOLDEN_SKULL || result==SILVER_SKULL);
		return result;
	}
}
void Skull::Activate()
{
	enabled++;
}
void Skull::Deactivate()
{
	enabled--;
}

Skull::Skull(bool golden, bool _enabled):
	ControllerField(golden?GOLDEN_SKULL:SILVER_SKULL,0)
{
	enabled=_enabled;
}
//extern int doskey_active;
void Skull::SteppedOver(Character * who)
{
	Field::SteppedOver(who);
	if ( enabled<=0)
		return;
	if (IsGolden()) {
		assoc_map->SetDoorsOpen(true);
	} else {
		ActivateRemotes();
	}
	globalAudios[BUTTON_ON].res.sound->play();
}
void Skull::LeftField()
{
	Field::LeftField();
	if (enabled<=0)
		return;
	globalAudios[BUTTON_OFF].res.sound->play();
	if (IsGolden()) {
		assoc_map->SetDoorsOpen(false);
	} else {
		DeactivateRemotes();
	}
}
