#ifndef __SWITCH_H
#define __SWITCH_H

class Switch: public Field {
	Field * associated_field;
	bool on_up;
	/* check state */
	bool Up();
public:
Switch(bool initially_up, Field *associated=0)
	:
	Field(initially_up?SWITCH_UP:SWITCH_DOWN) {
		associated_field=associated;
		on_up=true;
	}
	virtual void SteppedOver(Character * who);
	/**
	 *
	 * @param on_up determines whenever object will be activated on
	 * "up" position of switch or on "down" position
	 */
	void AssociateField(Field * associated, bool on_up) {
		associated_field=associated;
	}
};

#endif
