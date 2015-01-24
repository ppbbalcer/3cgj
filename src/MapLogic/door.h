#ifndef __DOOR_H
#define __DOOR_H
#include "field.h"
#include "field_impl.h"

class Door: public Field {
	int keep_open;
	int target_board;
public:
	Door():Field(DOOR) {keep_open=0;target_board=-1;}
	virtual void Activate();
	virtual void Deactivate();
	int isOpen() { return keep_open; }
	int GetType();
	void SteppedOver(Character * who);
	int GetTargetBoard() { return target_board; }
	void SetTargetBoard(int b) {target_board=b;}
};

#endif
