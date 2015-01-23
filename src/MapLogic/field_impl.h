#ifndef __FIELD_IMPL_H
#define __FIELD_IMPL_H
class Field: public IField {
	int type;
public:
	Field(int f) {
		type=f;
	}
	int GetType() {
		return type;
	}
	bool IsObstacle() {
		return type==WALL;
	}
};

#endif
