#include <Engine/map.h>
#include <cstdlib>
#include <Engine/field.h>
#include <Engine/generic_map.h>
/* following constants define width and height of map in tiles */
#define MAP_WIDTH 6
#define MAP_HEIGHT 6

// a map loaded from file
class LoadedMap : public GenericMap {
public:
	LoadedMap(const char * path);
  
};
LoadedMap::LoadedMap(const char * path) {
	SetSize( MAP_WIDTH, MAP_HEIGHT );
	AllocateFields();
	for (int i = 0 ; i!=MAP_WIDTH; i++) {
		for (int j = 0 ; j!=MAP_HEIGHT; ++j) {
			if (i==2)
				PlaceField(i,j,new Field(WALL));
			else
				PlaceField(i,j,new Field(FLOOR));
		}
	}
}

// a map loaded from file
class GeneratedMap : public GenericMap     {

public:
	GeneratedMap(char * const generator);
  
};


IMap * IMap::Factory(int type, const char * parameter) {
	return new LoadedMap("foo");
}
