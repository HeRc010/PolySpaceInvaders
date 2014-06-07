#include "Alien.h"

Alien::Alien( ScreenSprite *sprite, Vector3 *position, const unsigned &initial_HP ) : SpaceInvadersEntity( sprite, position, initial_HP )
{
	// add animations
	_sprite->addAnimation( "frame_0", "0", 1 );
	_sprite->addAnimation( "frame_1", "1", 1 );
	_sprite->playAnimation( "frame_0", 0, true );

	//
	_cur_frame = 0;
}

Alien::~Alien()
{
}

void Alien::changeAnimationFrame() {
	// increment animation frame
	++_cur_frame;
	_cur_frame %= 2;

	// for the frame string
	char buffer[256];
	itoa( _cur_frame, buffer, 10 );

	_sprite->playAnimation( String( "frame_" ) + String( buffer ), _cur_frame, true );
}

void Alien::update() {
	// change the animation frame
	changeAnimationFrame();
}