#include "../Character.h"
#include "field.h"
#include "field_impl.h"
#include "spikes.h"

#define SPIKE_DMG_LEVEL 20

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
		who->crucio(SPIKE_DMG_LEVEL);
	Field::SteppedOver(who);
}

void Spikes::Activate()
{
	is_on++;
	if (is_on==1 && WhoIsHere()) {
		WhoIsHere()->crucio(SPIKE_DMG_LEVEL);
	}	
}
void Spikes::Deactivate()
{
	is_on--;
}
