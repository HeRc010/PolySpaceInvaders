/*
	A class for an entity in the clone. Inherits sprite properties.
	Additional properties:
	- entitiy state, one of:
		-> alive
		-> exploding
		-> dead
*/

#ifndef SPACE_INVADERS_ENTITY_H
#define SPACE_INVADERS_ENTITY_H

#include "Polycode.h"
#include "PolycodeView.h"
#include "PolyGlobals.h"

class SpaceInvadersEntity : public ScreenSprite
{
public:
	SpaceInvadersEntity( const String &file_name, const unsigned &sprite_width, const unsigned &sprite_height );
	
	// copy constructor
	SpaceInvadersEntity( const SpaceInvadersEntity &rhs );

	~SpaceInvadersEntity();

	// enumerated values for state
	enum EntityState { alive, exploding, dead };

	// get the entity's state
	EntityState getState() const;

protected:
	//
	EntityState _state;
};

#endif SPACE_INVADERS_ENTITY_H