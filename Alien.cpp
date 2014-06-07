#include "Alien.h"

Alien::Alien( const String &file_name, const unsigned &sprite_width, const unsigned &sprite_height, const float &explosion_duration )
	: SpaceInvadersEntity( file_name, sprite_width, sprite_height )
{
	// add a tag
	addTag( "alien" );

	_explosion_duration = explosion_duration;
}

// CC
Alien::Alien( const Alien &rhs ) : SpaceInvadersEntity( rhs ) {
	//
}

Alien::~Alien()
{
	//
	if ( _timer ) delete _timer;
}