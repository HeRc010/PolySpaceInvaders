#include "AlienOne.h"

AlienOne::AlienOne( Vector3 *position, const unsigned &initial_HP, ScreenSprite *sprite ) : Alien( sprite, position, initial_HP )
{
	// add animations
	_sprite->addAnimation( "frame_0", "0", 1 );
	_sprite->addAnimation( "frame_1", "1", 1 );
	_sprite->playAnimation( "frame_0", 0, true );

	//
	_cur_frame = 0;
}

AlienOne::~AlienOne()
{
}