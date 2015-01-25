#include "field.h"
#include "map.h"
#include "generic_map.h"
#include "door.h"
void Door::Activate()
{
	keep_open++;
	if (Field::GetType()==DOOR_VERTICAL_CLOSED)
		SetType(DOOR_VERTICAL_OPEN);
	if (Field::GetType()==DOOR_HORIZONTAL_CLOSED)
		SetType(DOOR_HORIZONTAL_OPEN);

}
void Door::Deactivate()
{
	keep_open--;	
	if (Field::GetType()==DOOR_VERTICAL_OPEN)
		SetType(DOOR_VERTICAL_CLOSED);
	if (Field::GetType()==DOOR_HORIZONTAL_OPEN)
		SetType(DOOR_HORIZONTAL_CLOSED);


}

void Door::SteppedOver(Character * who)
{
	Field::SteppedOver(who);
}

extern int doskey_active;
int Door::GetType()
{
	if (Field::GetType()==DOOR_VERTICAL_CLOSED && doskey_active)
		return DOOR_VERTICAL_OPEN;
	if (Field::GetType()==DOOR_HORIZONTAL_CLOSED && doskey_active)
		return DOOR_HORIZONTAL_OPEN;

	return Field::GetType();
}
