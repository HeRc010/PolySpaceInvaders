#include "SpaceInvadersEntity.h"

SpaceInvadersEntity::SpaceInvadersEntity( ScreenImage *sprite, Vector3 *position, const unsigned &initial_HP ) 
	: _sprite(sprite), _position(position), _HP(initial_HP)
{
	//
	_sprite->setPosition( *_position );
}

SpaceInvadersEntity::~SpaceInvadersEntity()
{
}

ScreenImage * SpaceInvadersEntity::getSprite() {
	//
	return _sprite;
}

Vector3 SpaceInvadersEntity::getPosition() const {
	//
	return *_position;
}

void SpaceInvadersEntity::translate( const Vector3 &delta ) {
	//
	*_position += delta;
}

unsigned SpaceInvadersEntity::getHP() const {
	//
	return _HP;
}

void SpaceInvadersEntity::decHP( unsigned damage ) {
	//
	_HP -= damage;

	// if < 0 -> equals zero
	_HP = MAX( 0, _HP );
}