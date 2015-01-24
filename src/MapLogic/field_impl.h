#ifndef __FIELD_IMPL_H
#define __FIELD_IMPL_H
#include "field.h"
class Field: public IField {
	int type;
	int someone_is_here;
	static int assigned_field[NUM_FIELD_TYPES];
	static void EnsureFieldIdsInitialized();
public:
	Field(int f) {
		someone_is_here=false;
		type=f;
	}
	int GetType();
	bool IsObstacle();
	int GetTileId();
	void SetType(int f)
	{
		type=f;
	}
	void SteppedOver();
	void LeftField();
	bool IsOccupied() {
		return someone_is_here;
	}
};

#endif
