#ifndef __STAIRS_H
#define __STAIRS_H

#include "field.h"
#include "field_impl.h"

class Stairs: public Field {
public:
	Stairs(): Field(STAIRS) {}
	void SteppedOver(Character * who);

};
#endif
