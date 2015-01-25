#include "field.h"
#include "field_impl.h"
#include "skull.h"
#include "../Player.h"
#include "../GlobalData.h"


bool Skull::IsGolden()
{
	return GetType()==GOLDEN_SKULL;
}
Skull::Skull(bool golden, bool enabled):
	ControllerField(golden?GOLDEN_SKULL:SILVER_SKULL,0)
{

}
extern int doskey_active;
void Skull::SteppedOver(Character * who)
{
	if (IsGolden()) {
		doskey_active++;
	}
	globalAudios[BUTTON_ON].res.sound->play();
	//someone_is_here=who;
	Field::SteppedOver(who);
}
void Skull::LeftField()
{
	if (IsGolden()) {
		doskey_active--;
	}
	globalAudios[BUTTON_OFF].res.sound->play();
	//someone_is_here=0;
	Field::LeftField();
}
