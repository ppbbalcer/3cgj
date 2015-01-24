#ifndef __GENERIC_MAP
#define __GENERIC_MAP
#include "map.h"
#include "field_impl.h"
#include <cstring>

class GenericMap: public IMap {
private:
	Field** fields;
	int width;
	int height;
protected:
	starting_pos p1_start;
	starting_pos p2_start;
	start_list enemies_start;
protected:

	virtual const starting_pos & GetPlayer1Start();
	virtual const starting_pos & GetPlayer2Start();
	virtual const start_list & GetEnemiesStart();

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
		memset(fields, 0, sizeof(Field**)*width*height);
		return 0;
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
		return 0;
	}
	void DeallocateFields() {
		for (int i = 0 ; i!=width*height; ++i ) {
			if (fields[i])
				delete[] fields[i];
		}
		delete[] fields;
	}
	bool HasWallAt(int x, int y)
	{
		if (x<0) return false;
		if (y<0) return false;
		if (x>=GetWidth()) return false;
		if (y>=GetHeight()) return false;
		IField * field = GetFieldAt(x,y);
		if (!field) return false;
		if (field->GetType() <=IField::T_BOTTOM &&
		    field->GetType() >=IField::WALL)
			return true;
		if (field->GetType() <= IField::DOOR_VERTICAL_OPEN &&
		    field->GetType() >= IField::DOOR)
			return true;
		return false;
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
