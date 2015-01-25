#ifndef __SKULL_H
#define __SKULL_H
#include "controller_field.h"

class Skull: public ControllerField {
	bool IsGolden();
	int enabled;
public:
	Skull(bool golden, bool enabled);
	virtual void Activate();
	virtual void Deactivate();
	virtual int GetType();
	virtual void SteppedOver(Character * who);
	virtual void LeftField();
};

#endif
