/*
	A class for an entity in the clone with the following properties:
		- A visible 2D sprite
		- A position
		- HP; can be hit by a missile in-game
*/

#ifndef SPACE_INVADERS_ENTITY_H
#define SPACE_INVADERS_ENTITY_H

#include "Polycode.h"
#include "PolycodeView.h"
#include "PolyGlobals.h"

class SpaceInvadersEntity : public ScreenSprite
{
public:
	SpaceInvadersEntity( ScreenSprite *sprite, Vector3 *position = new Vector3(0,0,0), unsigned initial_HP = 0 );
	
	// copy constructor
	SpaceInvadersEntity( const SpaceInvadersEntity &rhs );

	~SpaceInvadersEntity();

	// update method
	virtual void update();

	// get the sprite
	ScreenSprite * getSprite() const;

	// get the position
	Vector3 getPosition() const;

	// translate
	void translate( const Vector3 &delta );
	
	// set the scale of the sprite - THIS MAY NOT BE NEEDED
	void setScale( const Vector3 &scale );

	// get HP
	unsigned getHP() const;

	// decrement HP?...
	void decHP( unsigned damage );

	// is the entity still alive?
	bool stillAlive() const;

	// set the alive parameter to false
	void kill();

protected:
	// sprite associated with the entity
	ScreenSprite * _sprite;

	// the position of the entity
	Vector3 * _position;

	// the entity's hit points
	unsigned _HP;

	// still alive?
	bool _alive;
};

#endif SPACE_INVADERS_ENTITY_H