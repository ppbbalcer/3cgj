#include <MapLogic/map.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <MapLogic/field.h>
#include <MapLogic/generic_map.h>
#include <fstream>
/* following constants define width and height of map in tiles */
using namespace std;
/*
 * a map loaded from file
 */
class LoadedMap : public GenericMap {
private:
	/**
	 * mainly for tracing (checking if map was deserialized correctly)
	 * but in future it may be useful for map editor as part of 
	 * actual serializer
	 */
	void SerializeOntoConsole();
public:
	/**
	 * @param path to text file containing actual map
	 */
	LoadedMap(const char * path);
	virtual ~LoadedMap();
};//end of class LoadedMap

LoadedMap::LoadedMap(const char * path) {
	ifstream mapfile;
	mapfile.open(path);
	// check result

	// before allocating determine actual width and height of the map
	int w=0;
	int h=0;
	int cur_line_w=0;
	while (!mapfile.eof()) {
		char c;
		c = mapfile.get();
		if (c==10) {
			h++;	
			w=max<int>(w,cur_line_w);
			cur_line_w=0;
		} else {
			cur_line_w++;
		}
	}
	cout << "w=" << w << " h=" << h << endl;
	cout << mapfile.tellg() << endl;
	mapfile.close();
	mapfile.open(path);
	cout << mapfile.tellg() << endl;	
	SetSize( w,h );
	AllocateFields();
	for (int i = 0 ; i!=GetHeight(); i++) {
		for (int j = 0 ; j!=GetWidth(); ++j) {
			Field * new_field = 0;
			char c = mapfile.get();
			switch(c) {
			case ' ':
				new_field= new Field(FLOOR);
				break;
			case '|':
				new_field= new Field(DOOR);
				break;
			case 'd':
				new_field= new Field(DESK);
				break;
			case 'w':
				new_field= new Field(WALL);
				break;
			default:
				new_field= new Field(EMPTY);
			}
			PlaceField(j,i,new_field);

		}
		mapfile.get(); //consume endline character
	}
	mapfile.close();
	SerializeOntoConsole();
}

void LoadedMap::SerializeOntoConsole()
{
	ostream & stream = cout;
	for (int i = 0 ; i!=GetHeight(); i++) {
		for (int j = 0 ; j!=GetWidth(); ++j) {
			int field= GetFieldAt(j,i)->GetType();
			stream << (field==WALL?'w':'_');
		}
		stream << endl;
	}
}
LoadedMap::~LoadedMap() {
	DeallocateFields();
}
// a map loaded from file
class GeneratedMap : public GenericMap     {

public:
	GeneratedMap(char * const generator);
  
};


IMap * IMap::Factory(int type, const char * parameter) {
	return new LoadedMap(parameter);
}
