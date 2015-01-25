#include "../Character.h"
#include "field.h"
#include "field_impl.h"
#include "spikes.h"

int Spikes::GetType()
{
	if (is_on>0)
		return SPIKES_ON;
	else
		return SPIKES_OFF;
}
void Spikes::SteppedOver(Character * who)
{
	if (is_on>0)
		who->crucio(20);
	Field::SteppedOver(who);
}

void Spikes::Activate()
{
	is_on++;
}
void Spikes::Deactivate()
{
	is_on--;
}
