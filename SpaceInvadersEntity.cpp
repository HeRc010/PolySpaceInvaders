#include "SpaceInvadersEntity.h"

SpaceInvadersEntity::SpaceInvadersEntity( const String &file_name, const unsigned &sprite_width, const unsigned &sprite_height )
	: ScreenSprite( *( ScreenSprite::ScreenSpriteFromImageFile( file_name, sprite_width, sprite_height ) ) )
{
	//
	_state = alive;
}

// CC
SpaceInvadersEntity::SpaceInvadersEntity( const SpaceInvadersEntity &rhs ) : ScreenSprite( rhs ) {
	//
	
}

SpaceInvadersEntity::~SpaceInvadersEntity()
{
	//

}

SpaceInvadersEntity::EntityState SpaceInvadersEntity::getState() const {
	//
	return _state;
}