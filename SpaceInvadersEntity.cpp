#include "SpaceInvadersEntity.h"

SpaceInvadersEntity::SpaceInvadersEntity( ScreenImage *sprite, Vector3 *position, unsigned initial_HP )
	: _sprite(sprite), _position(position), _HP(initial_HP)
{
	//
	_sprite->setPosition( *_position );
	_alive = true;
}

SpaceInvadersEntity::~SpaceInvadersEntity()
{
	//
	delete _sprite;
	delete _position;
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
	_sprite->setPosition( _sprite->getPosition() + delta );
}

unsigned SpaceInvadersEntity::getHP() const {
	//
	return _HP;
}

void SpaceInvadersEntity::decHP( unsigned damage ) {
	//
	_HP -= damage;

	// if < 0 -> equals zero
	if ( _HP < 0 ) {
		_HP = 0;
		_alive = false;
	}
}

bool SpaceInvadersEntity::stillAlive() {
	//
	return _alive;
}