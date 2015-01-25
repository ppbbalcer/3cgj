#include "field.h"
#include "field_impl.h"
#include "skull.h"
#include "../Player.h"
#include "../GlobalData.h"


bool Skull::IsGolden()
{
	return GetType()==GOLDEN_SKULL;
}

int Skull::GetType()
{
	if (!enabled)
		return INACTIVE_SKULL;
	else
		return Field::GetType();
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
extern int doskey_active;
void Skull::SteppedOver(Character * who)
{
	Field::SteppedOver(who);
	if (!enabled)
		return;
	if (IsGolden()) {
		doskey_active++;
	} else {
		if (on_up)
			ActivateRemotes();
		else
			DeactivateRemotes();
	}
	globalAudios[BUTTON_ON].res.sound->play();
}
void Skull::LeftField()
{
	Field::LeftField();
	if (!enabled)
		return;
	globalAudios[BUTTON_OFF].res.sound->play();
	if (IsGolden()) {
		doskey_active--;
	} else {
		if (on_up)
			DeactivateRemotes();
		else
			ActivateRemotes();
	}
}
