/*
	A specific entity subclass for the player/fighter
*/

#include "SpaceInvadersEntity.h"

class Fighter : public SpaceInvadersEntity
{
public:
	Fighter( ScreenSprite *sprite, Vector3 *position, const unsigned &initial_HP, const int &missile_speed );
	~Fighter();

	//
	void update();

	// get number of missiles
	unsigned getNumberOfMissiles() const;

	// get the missiles' list
	void getMissiles( vector<SpaceInvadersEntity*> &list ) const;

	// add a missile to the missile array
	void addMissile( SpaceInvadersEntity * new_missile );

	// remove the missile provided
	void removeMissile( SpaceInvadersEntity * to_remove );

	// remove missile by index
	void removeMissile( const unsigned &index );

private:
	// remove all the dead missiles from the missile list
	void removeDeadMissiles();

	// the number of missiles in the list
	unsigned _num_missiles;

	// list of missile
	vector<SpaceInvadersEntity*> _missiles;

	// the speed of the missiles
	int _missile_speed;
};