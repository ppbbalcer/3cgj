#ifndef __SKULL_H
#define __SKULL_H
#include "controller_field.h"

class Skull: public ControllerField {
	bool IsGolden();
	bool enabled;
public:
	Skull(bool golden, bool enabled);
	virtual void SteppedOver(Character * who);
	virtual void LeftField();
};

#endif
