#include "field.h"
#include "map.h"
#include "generic_map.h"
#include "switch.h"
#include "../GlobalData.h"

bool Switch::Up() {
	if (GetType()==SWITCH_UP) {
		return true;
	} else if (GetType()==SWITCH_DOWN) {
		return false;
	} else {
		assert(0);
		return true;
	}
}

void Switch::SteppedOver(Character * who) {
	if (GetType()==SWITCH_UP) {
		SetType(SWITCH_DOWN);	
	} else if (GetType()==SWITCH_DOWN) {
		SetType(SWITCH_UP);
	} else {
		assert(0);
	}

	globalAudios[TOGGLE].res.sound->play();

		if (Up())
			ActivateRemotes();
		else
			DeactivateRemotes();
	/* update the state machine */
	Field::SteppedOver(who);
}
