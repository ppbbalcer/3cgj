#ifndef __CONTROLLER_FIELD_H
#define __CONTROLLER_FIELD_H
#include <list>

class ControllerField: public Field
{
protected:
	struct association {
		Field * associated_field;
		bool on_up;
	};
	typedef std::list<association> assoc_list_type;
	assoc_list_type assoc_list;
	void ActivateRemotes();
	void DeactivateRemotes();
public:
	ControllerField(int type, Field *associated=0)
		: Field(type)
	{
		
	}
	/**
	 *
	 * @param on_up determines whenever object will be activated on
	 * "up" position of switch or on "down" position
	 */
	void AssociateField(Field * associated, bool on_up);
};

#endif
