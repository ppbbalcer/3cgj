#ifndef __GENERIC_MAP
#define __GENERIC_MAP
#include <Engine/map.h>
class Field : public IField {
public:
	int GetType() {
		return FLOOR;
	}
};



class GenericMap: public IMap {
private:
	Field** fields;
	int width;
	int height;
protected:
	/**
	 * allocate fields
	 */
	int AllocateFields()
	{
		fields = (Field**)calloc(width*height,sizeof(void*));
	}
	int PlaceField(int x, int y, Field * field1)
	{
		fields[x+y*width] = field1;
	}
	void DeallocateFields() {
		for (int i = 0 ; i!=width*height; ++i ) {
			if (fields[ i])
				free(fields[i]);
		}

	}
public:
	IField* GetFieldAt(int x, int y) {
		return fields[x+y*width];
	}
	GenericMap()
	{
		width = 0;
		height = 0;
		fields = 0;
	}
	int GetWidth() {
		return width;
	}
	int GetHeight() {
		return height;
	}

};
#endif
