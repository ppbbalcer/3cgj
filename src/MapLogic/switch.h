#ifndef __SWITCH_H
#define __SWITCH_H

class Switch: public Field {
	Field * associated_field;
	bool Up();
public:
Switch(bool initially_up, Field *associated=0)
	:
	Field(initially_up?SWITCH_UP:SWITCH_DOWN) {
		associated_field=associated;
	}
	virtual void SteppedOver(Character * who);
};

#endif
