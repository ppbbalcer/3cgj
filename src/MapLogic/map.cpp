#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "field.h"
#include "map.h"
#include "generic_map.h"
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
				new_field= new Field(IField::FLOOR);
				break;
			case '|':
				new_field= new Field(IField::DOOR);
				break;
			case 'd':
				new_field= new Field(IField::DESK);
				break;
			case 'w':
				new_field= new Field(IField::WALL);
				break;
			default:
				new_field= new Field(IField::EMPTY);
			}
			PlaceField(j,i,new_field);

		}
		mapfile.get(); //consume endline character
	}

	/* replace fields of type "wall" for wall of appropriate 
	 * orientation */
	for (int i = 0 ; i!=GetHeight(); i++) {
		for (int j = 0 ; j!=GetWidth(); ++j) {
			IField * field = GetFieldAt(j,i);
			if (field->GetType() == IField::DOOR) {
				if (HasWallAt(j,i-1) && HasWallAt(j,i+1) ) // horizontal piece
					dynamic_cast <Field*>(field)->SetType(IField::DOOR_VERTICAL_CLOSED);
				else if (HasWallAt(j-1,i) && HasWallAt(j+1,i) ) // T junction
					dynamic_cast <Field*>(field)->SetType(IField::DOOR_HORIZONTAL_CLOSED);
			}
			if (field->GetType() != IField::WALL)
				continue;
			if (HasWallAt(j,i-1) && HasWallAt(j,i+1) && HasWallAt(j+1,i) && HasWallAt(j-1,i) ) // cross
				dynamic_cast <Field*>(field)->SetType(IField::WALL_CROSS);
			else if (HasWallAt(j,i+1) && HasWallAt(j+1,i) && HasWallAt(j-1,i) ) // T junction without top
				dynamic_cast <Field*>(field)->SetType(IField::T_BOTTOM);
			else if (HasWallAt(j,i-1) && HasWallAt(j+1,i) && HasWallAt(j-1,i) ) // T junction without bottom
				 dynamic_cast <Field*>(field)->SetType(IField::T_TOP);
			else if (HasWallAt(j,i-1) && HasWallAt(j,i+1) && HasWallAt(j-1,i) ) // T junction without right piece
				dynamic_cast <Field*>(field)->SetType(IField::T_LEFT);
			else if (HasWallAt(j,i-1) && HasWallAt(j,i+1) && HasWallAt(j+1,i) ) // T junction
				dynamic_cast <Field*>(field)->SetType(IField::T_RIGHT);
			else if (HasWallAt(j,i+1) && HasWallAt(j+1,i) ) // L rb
				dynamic_cast <Field*>(field)->SetType(IField::WALL_RB);
			else if (HasWallAt(j,i-1)  && HasWallAt(j-1,i) ) // L lt
				 dynamic_cast <Field*>(field)->SetType(IField::WALL_LT);
			else if (HasWallAt(j,i+1) && HasWallAt(j-1,i) ) // L lb
				dynamic_cast <Field*>(field)->SetType(IField::WALL_LB);
			else if (HasWallAt(j,i-1)  && HasWallAt(j+1,i) ) // L rt
				dynamic_cast <Field*>(field)->SetType(IField::WALL_RT);
			else if (HasWallAt(j,i-1) && HasWallAt(j,i+1) ) // horizontal piece
				dynamic_cast <Field*>(field)->SetType(IField::WALL_VERTICAL);
			else if (HasWallAt(j-1,i) && HasWallAt(j+1,i) ) // T junction
				dynamic_cast <Field*>(field)->SetType(IField::WALL_HORIZONTAL);
		}
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
			stream << (field==IField::WALL?'w':'_');
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
 
