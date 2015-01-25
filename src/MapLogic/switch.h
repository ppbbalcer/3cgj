#ifndef __SWITCH_H
#define __SWITCH_H
#include "controller_field.h"

class Switch: public ControllerField {
	bool on_up;
	/* check state */
	bool Up();
public:
Switch(bool initially_up, Field *associated=0)
	:
	ControllerField(initially_up?SWITCH_UP:SWITCH_DOWN,associated) {
		on_up=true;
	}
	virtual void SteppedOver(Character * who);
};

#endif
