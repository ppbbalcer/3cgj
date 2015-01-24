#include "field.h"
#include "map.h"
#include "generic_map.h"
#include "switch.h"

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

	if (associated_field) {
		if (on_up ^ Up() )
			associated_field->Deactivate();
		else
			associated_field->Activate();
	}
	/* update the state machine */
	Field::SteppedOver(who);
}
