#ifndef __SPIKES_FIELD_H
#define __SPIKES_FIELD_H
#include <list>
#include "field.h"

class Spikes: public Field
{
protected:
	int is_on;
public:
	void Activate();
	void Deactivate();
	int GetType();
	void SteppedOver(Character * who);

	Spikes(bool _is_on)
		: Field(_is_on?SPIKES_ON:SPIKES_OFF)
	{
		is_on=_is_on;
	}
};

#endif
