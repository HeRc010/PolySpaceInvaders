/*
	A class for an entity in the clone with the following properties:
		- A visible 2D sprite
		- A position
		- HP; can be hit by a missile in-game
*/

#include "Polycode.h"
#include "PolycodeView.h"
#include "PolyGlobals.h"

class SpaceInvadersEntity
{
public:
	SpaceInvadersEntity( ScreenImage *sprite, Vector3 *position, const unsigned &initial_HP );
	~SpaceInvadersEntity();

	// get the sprite
	ScreenImage * getSprite();

	// get the position
	Vector3 getPosition() const;

	// translate
	void translate( const Vector3 &delta );

	// get HP
	unsigned getHP() const;

	// decrement HP?...
	void decHP( unsigned damage );

private:
	// sprite associated with the entity
	ScreenImage * _sprite;

	// the position of the entity
	Vector3 * _position;

	// the entity's hit points
	unsigned _HP;
};