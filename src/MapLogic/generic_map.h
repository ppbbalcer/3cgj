#ifndef __GENERIC_MAP
#define __GENERIC_MAP
#include <MapLogic/map.h>
#include <MapLogic/field_impl.h>


class GenericMap: public IMap {
private:
	Field** fields;
	int width;
	int height;
protected:
	/*following methods are used by implementation of specialized
	 * constructors of GeneratedMap and LoadedMap
	 */
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
		fields = new Field*[width*height];
	}
	void FreeFieldIfExists(int x, int y)
	{
		if (fields[x+y*width])
			delete fields[x+y*width];
	}
	/**
	 * @param x,y - coordinates
	 * @param field1 field to be supplied. Must be either NULL
	 *  or a valid pointer. If valid field existed before call
	 *  it is freed.
	 */
	int PlaceField(int x, int y, Field *field1)
	{
		if (fields[x+y*width]) {
			FreeFieldIfExists(x,y);
		}
		fields[x+y*width] = field1;
	}
	void DeallocateFields() {
		for (int i = 0 ; i!=width*height; ++i ) {
			if (fields[i])
				delete[] fields[i];
		}
		delete[] fields;
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
