/*
	This class is for missiles
*/

#include "SpaceInvadersEntity.h"

#ifndef PLAYER_MISSILE_H
#define PLAYER_MISSILE_H

class PlayerMissile : public SpaceInvadersEntity 
{
public:
	//
	PlayerMissile( const String &file_name, const unsigned &sprite_width, const unsigned &sprite_height );
	~PlayerMissile();
private:
	//

};

#endif PLAYER_MISSILE_H