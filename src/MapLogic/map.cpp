#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "field.h"
#include "map.h"
#include "generic_map.h"
#include "switch.h"
#include "door.h"
#include "skull.h"
#include "stairs.h"
#include "spikes.h"
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
	if (!mapfile.good()) {
		assert(0);
	}
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
				new_field= new Door;
				break;
			case '[':
				new_field= new Door;
				new_field->Activate();
				break;
			case 'd':
				new_field= new Field(IField::DESK);
				break;
			case '#':
				new_field= new Spikes(true);
				break;
			case '%':
				new_field= new Spikes(false);
				break;
			case 'u':
				new_field= new Field(IField::POWERUP);
				break;
			case 'w':
				new_field= new Field(IField::WALL);
				break;
			case 'k':
				new_field= new Skull(true,true);
				break;
			case 'K':
				new_field= new Skull(false,true);
				break;
			case 's':
				new_field= new Skull(true, false);
				break;
			case 'S':
				new_field= new Skull(false, false);
				break;
			case 'U':
				new_field= new Stairs;
				break;
			case '+':
				new_field= new Field(IField::MEDKIT);
				break;
			case 'm':
				new_field= new Field(IField::SMALL_MANA_FLASK);
				break;
			case 'M':
				new_field= new Field(IField::LARGE_MANA_FLASK);
				
				break;
			case 'h':
				new_field= new Field(IField::SMALL_HEALTH_FLASK);
				break;
			case 't':
				new_field= new Field(IField::TRAP);
				break;
			case '^':
				new_field= new Switch(1);
				break;
			case 'v':
				new_field= new Switch(0);
				break;
			case 'H':
				new_field= new Field(IField::LARGE_HEALTH_FLASK);
				break;
			case 'e':
				new_field= new Field(IField::EMPTY_FLASK);
				break;
			case 'E':
				new_field= new EvilComputer;
				break;
				
			default:
				new_field= new Field(IField::EMPTY);
			}
			if (c != 'w' && c != ' ') {
				printf("Object: %c at %u %u\n", c, j, i);
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
				Door *d = (Door *)field;
				if (HasWallAt(j,i-1) && HasWallAt(j,i+1) ) // horizontal piece
					d->SetType(IField::DOOR_VERTICAL_CLOSED);
				else if (HasWallAt(j-1,i) && HasWallAt(j+1,i) ) // T junction
					d->SetType(IField::DOOR_HORIZONTAL_CLOSED);
				if (d->isOpen()){
					d->Activate();
				}
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
			else if (HasWallAt(j,i-1) || HasWallAt(j,i+1) ) // horizontal piece
				dynamic_cast <Field*>(field)->SetType(IField::WALL_VERTICAL);
			else if (HasWallAt(j-1,i) || HasWallAt(j+1,i) ) // T junction
				dynamic_cast <Field*>(field)->SetType(IField::WALL_HORIZONTAL);
		}
	}
	mapfile.close();
	params = new map_params();
	params->alpha = 140;
	params->start_hp = 100;
	params->start_mana = 100;
	SerializeOntoConsole();
	string config_path(path);
	config_path+=".conf";
	mapfile.open(config_path);
	if (!mapfile.good())
		return;
	while (!mapfile.eof()) {
		/**
		 * achtung! kein error checking! you may CTD through
		 * bugged conf file.
		 */
		string command;
		mapfile >> command;
		if (command == "start") {
			mapfile >> params->alpha >> params->start_hp >> params->start_mana;
		} else if (command == "title_string") {
			std::string title;
			while (mapfile.get()!='"') ;
			int c;
			do
			{
				c=mapfile.get();
				if (c!='"')
					title.push_back(c);
			}
			while (c!='"');
			title_string=title;
		} else if (command == "switch" || command=="controller") {
			int sw_x;
			int sw_y;
			string direction;
			int tar_x;
			int tar_y;
			mapfile >> sw_x >> sw_y >> direction >> tar_x >> tar_y;
			ControllerField * sw = dynamic_cast <ControllerField*>(
				GetFieldAt(sw_x, sw_y));
			if (!sw) {assert(0);}
			Field * tar = dynamic_cast <Field*>(
				GetFieldAt(tar_x, tar_y));
			
			sw->AssociateField(tar,direction=="up");
		} else if (command == "player1_start") {
			int x; int y;
			mapfile >> x >> y;
			p1_start = make_pair(x,y);
		} else if (command == "player2_start") {
			int x; int y;
			mapfile >> x >> y;
			p2_start = make_pair(x,y);
		} else if (command == "enemy_start") {
			enemy_definition *enemy = new enemy_definition();
			mapfile >> enemy->x >> enemy->y >> enemy->hp >> enemy->ai;
			enemies.push_back(enemy);
		} else if (command == "exit") {
			int x; int y, target;
			mapfile >> x >> y >> target;
			Door * dor = dynamic_cast <Door*>(
				GetFieldAt(x, y));
			dor->SetTargetBoard(target);
		} else if (command == "stairs") {
			int x; int y;
			string direction;
			mapfile >> x >> y >> direction;
			if (direction=="winner")
				dynamic_cast <Stairs*>(
					GetFieldAt(x, y))->SetVictory();
		}
	}
	mapfile.close();
}

const starting_pos & GenericMap::GetPlayer1Start()
{
	return p2_start;
}
const starting_pos & GenericMap::GetPlayer2Start()
{
	return p1_start;
}

const enemies_list & GenericMap::GetEnemies()
{
	return enemies;
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
 
