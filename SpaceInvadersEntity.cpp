#include "SpaceInvadersEntity.h"

SpaceInvadersEntity::SpaceInvadersEntity( ScreenSprite *sprite, Vector3 *position, unsigned initial_HP )
	: _sprite(sprite), _position(position), _HP(initial_HP)
{
	//
	_sprite->setPosition( *_position );
	_alive = true;
}

// CC
SpaceInvadersEntity::SpaceInvadersEntity( const SpaceInvadersEntity &rhs ) {
	// create new instances of the pointer content
	_sprite = new ScreenSprite( *( rhs.getSprite() ) );
	_position = new Vector3( rhs.getPosition() );

	_HP = rhs.getHP();
	_alive = rhs.stillAlive();
}

SpaceInvadersEntity::~SpaceInvadersEntity()
{
	//
	delete _sprite;
	delete _position;
}

ScreenSprite * SpaceInvadersEntity::getSprite() const {
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

bool SpaceInvadersEntity::stillAlive() const {
	//
	return _alive;
}