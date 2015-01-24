#ifndef __FIELD_IMPL_H
#define __FIELD_IMPL_H
#include "field.h"
#include <cassert>
#include "../Character.h"
class Field: public IField {
	int type;
	Character* someone_is_here;
	static int assigned_field[NUM_FIELD_TYPES];
	static void EnsureFieldIdsInitialized();
public:
	Field(int f) {
		someone_is_here=NULL;
		type=f;
	}
	virtual int GetType();
	virtual bool IsObstacle();
	virtual int GetTileId();
	virtual void SetType(int f)
	{
		type=f;
	}
	virtual void SteppedOver(Character * who);
	virtual void LeftField();
	virtual bool IsOccupied() {
		return someone_is_here != NULL;
	}
	virtual Character* WhoIsHere();

	virtual void Activate() {}
	virtual void Deactivate() {}
};

class EvilComputer: public Field {
	bool running;
	bool time_to_next_fb;
public:
	EvilComputer() : Field(EVIL_COMPUTER)
		{
			time_to_next_fb;
			running=false;
		}
	
};
#endif
