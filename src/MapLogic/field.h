#ifndef __FIELD_H
#define __FIELD_H


enum FieldType {
	EMPTY = 0,
	WALL = 2, /*!< this is transistional state during load
		   *!< - it is than supstuituted for direction
		   *!< of particular wall */
	WALL_HORIZONTAL,
	WALL_VERTICAL,
	WALL_CROSS,
	WALL_LT,
	WALL_RT,
	WALL_LB,
	WALL_RB, /* add T-shaped sections tooo.... */

	FLOOR,
	DESK,
	DOOR,
	MEDKIT
  
  
};
class IField {
public:
	// as per enum FieldType
	virtual int GetType() = 0;
	virtual bool IsObstacle() = 0;
	// other methods will be specific to certain types
};

#endif
