#ifndef __FIELD_IMPL_H
#define __FIELD_IMPL_H
#include "field.h"
class Field: public IField {
	int type;
	static int assigned_field[NUM_FIELD_TYPES];
	static void EnsureFieldIdsInitialized();
public:
	Field(int f) {
		type=f;
	}
	int GetType() {
		return type;
	}
	bool IsObstacle() {
		return (type>=WALL && type <=T_BOTTOM);
	}
	int GetTileId();
	void SetType(int f)
	{
		type=f;
	}
	void SteppedOver();
	void LeftField();
};

#endif
