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
	PlayerMissile( const String &file_name = "Resources/player_missile.png", const unsigned &sprite_width = 3, const unsigned &sprite_height = 15 );
	~PlayerMissile();
private:
	//

};

#endif PLAYER_MISSILE_H