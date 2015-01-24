#ifndef __FIELD_IMPL_H
#define __FIELD_IMPL_H
#include "field.h"
#include "../Engine/Character.h"
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
	int GetType();
	bool IsObstacle();
	int GetTileId();
	void SetType(int f)
	{
		type=f;
	}
	void SteppedOver(Character * who);
	void LeftField();
	bool IsOccupied() {
		return someone_is_here;
	}
	Character* WhoIsHere();

};

#endif
