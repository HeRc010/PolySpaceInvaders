#include "Fighter.h"

Fighter::Fighter( const String &file_name, const unsigned &sprite_width, const unsigned &sprite_height, const int &missile_speed ) 
	: SpaceInvadersEntity( file_name, sprite_width, sprite_height )
{
	//
	addTag("fighter");

	_num_missiles = 0;
	_missile_speed = missile_speed;
}

Fighter::~Fighter()
{
	//

}

