#ifndef __CONTROLLER_FIELD_H
#define __CONTROLLER_FIELD_H

class ControllerField: public Field
{
protected:
	Field * associated_field;

	void ActivateRemotes();
	void DeactivateRemotes();
public:
	ControllerField(int type, Field *associated=0)
		: Field(type)
	{
		associated_field=associated;

	}
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
