#ifndef __GENERIC_MAP
#define __GENERIC_MAP
#include <Engine/map.h>
#include <Engine/field_impl.h>


class GenericMap: public IMap {
private:
	Field** fields;
	int width;
	int height;
protected:
	void SetSize(int w, int h)
	{
		width=w;
		height=h;
	}
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
