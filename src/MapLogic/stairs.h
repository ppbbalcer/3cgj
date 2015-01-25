#ifndef __STAIRS_H
#define __STAIRS_H

#include "field.h"
#include "field_impl.h"

class Stairs: public Field {
	bool victory;
public:
	Stairs(): Field(STAIRS) {victory = false;}
	void SteppedOver(Character * who);
	/**
	 * if true, than walking up these stairs
	 * leads to winning entire game. otherwise
	 * leads just to another level
	 */
	bool GetVictory() {return victory; }
	void SetVictory() {victory=true; }
};
#endif
