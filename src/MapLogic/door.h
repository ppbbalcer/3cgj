#ifndef __DOOR_H
#define __DOOR_H

class Door: public Field {
	int keep_open;
public:
	Door():Field(DOOR) {keep_open=0;}
	virtual void Activate();
	virtual void Deactivate();
	int GetType();
	void SteppedOver(Character * who);
};

#endif
