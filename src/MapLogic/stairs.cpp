#include "../Character.h"
#include "../Player.h"
#include "stairs.h"
void Stairs::SteppedOver(Character * who)
{
	Player * pc = dynamic_cast<Player*>(who);
	if (!pc) return;
	pc->Win();
}
