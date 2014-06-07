/*
	A specific entity subclass for the player/fighter
*/

#include "SpaceInvadersEntity.h"
#include "PlayerMissile.h"

class Fighter : public SpaceInvadersEntity
{
public:
	Fighter( const String &file_name, const unsigned &sprite_width, const unsigned &sprite_height, const int &missile_speed );
	~Fighter();

private:
	// the speed of the missiles
	int _missile_speed;

	// the number of missiles in the list
	unsigned _num_missiles;

	// a list of the missiles
	vector<PlayerMissile*> _missiles;
};