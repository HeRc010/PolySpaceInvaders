#include "Alien.h"

Alien::Alien( ScreenSprite *sprite, Vector3 *position, const unsigned &initial_HP, const float &explosion_duration ) : SpaceInvadersEntity( sprite, position, initial_HP )
{
	// add animations
	_sprite->addAnimation( "frame_0", "0", 1 );
	_sprite->addAnimation( "frame_1", "1", 1 );
	_sprite->addAnimation( "explosion", "2", 1 );
	_sprite->playAnimation( "frame_0", 0, false );

	// add a tag
	_sprite->addTag( "alien" );

	// initialize parameters
	_cur_frame = 0;
	_explosion_duration = explosion_duration;
}

// CC
Alien::Alien( const Alien &rhs ) : SpaceInvadersEntity( rhs ) {
	//
	_cur_frame = rhs.getCurrentFrame();
}

Alien::~Alien()
{
	//
	if ( _timer ) delete _timer;
}

void Alien::changeAnimationFrame() {
	// increment animation frame
	++_cur_frame;
	_cur_frame %= 2;

	// for the frame string
	char buffer[256];
	itoa( _cur_frame, buffer, 10 );

	_sprite->playAnimation( String( "frame_" ) + String( buffer ), _cur_frame, false );
}

unsigned Alien::getCurrentFrame() const {
	//
	return _cur_frame;
}

void Alien::update() {
	// display the explosion sprite if dead; but still "alive"
	// otherwise update the animation frame
	if ( (_HP == 0) && _alive ) {
		//
		if ( _timer == NULL ) _timer = new Timer( false, 0 );

		if ( (_timer->getElapsedf() * 1000) < _explosion_duration ) {
			//
			_sprite->playAnimation( "explosion", 2, false );
		} else {
			//
			_alive = false;
		}
	} else {
		// change the animation frame
		changeAnimationFrame();
	}
}