#ifndef __FIELD_H
#define __FIELD_H
class Character;
class IField {
public:

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
	
		T_LEFT,
		T_RIGHT,
		T_TOP,
		T_BOTTOM,
	
		FLOOR,
		DESK,
		DOOR,
		DOOR_HORIZONTAL_CLOSED,
		DOOR_VERTICAL_CLOSED,
		DOOR_HORIZONTAL_OPEN,
		DOOR_VERTICAL_OPEN,
		MEDKIT,
		DOSKEY, /* dos computer that opens doors */
		POWERUP,
		SMALL_MANA_FLASK,
		LARGE_MANA_FLASK,
		SMALL_HEALTH_FLASK,
		LARGE_HEALTH_FLASK,
		EMPTY_FLASK,

		NUM_FIELD_TYPES
  
	};
// as per enum FieldType
	virtual int GetType() = 0;
	virtual bool IsObstacle() = 0;
	/**
	 * Get id of tile on corresponding bitmap
	 */
	virtual int GetTileId()=0;
	// other methods will be specific to certain types
	virtual void SteppedOver(Character *who)=0;
	virtual void LeftField()=0;
	virtual bool IsOccupied()=0;
	virtual Character* WhoIsHere()=0;

};

#endif
