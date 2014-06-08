#include "Alien.h"

Alien::Alien( const String &file_name, const unsigned &sprite_width, const unsigned &sprite_height, const float &explosion_duration )
	: SpaceInvadersEntity( file_name, sprite_width, sprite_height )
{
	// add a tag
	addTag( "alien" );

	_explosion_duration = explosion_duration;

	// initialize animations
	addAnimation( "frame_0", "0", 1 );
	addAnimation( "frame_1", "1", 1 );
	addAnimation( "explode", "2", 1 );

	playAnimation( "frame_0", 0, false );

	_current_frame = 0;
	_elapsed_frames = 0;

	// not sure why(if) this is necessary...
	_state = alive;
	_timer = 0;

	//_timer = new Timer( false, 0 );
	//_timer->Pause( true );
}

// CC
Alien::Alien( const Alien &rhs ) : SpaceInvadersEntity( rhs ) {
	//
	_current_frame = rhs.getFrame();
	_explosion_duration = rhs.getExplosionDuration();
}

Alien::~Alien()
{
	//
	if ( _timer ) delete _timer;
}

void Alien::changeAnimationFrame() {
	// if the alien is not dead
	if ( _state == alive ) {
		++_current_frame;
		_current_frame %= 2;
	
		char buffer[256];
		itoa( _current_frame, buffer, 10 );

		playAnimation( "frame_" + String( buffer ), _current_frame, false );
	} else if ( _state == exploding ) {
		// if timer not initialized; do so
		if ( !_timer ) _timer = new Timer( false, 0 );
		
		if ( (_timer->getElapsedf() * 1000) >= _explosion_duration ) {
			//
			_state = dead;
		}
	}
}

unsigned Alien::getFrame() const {
	//
	return _current_frame;
}

float Alien::getExplosionDuration() const {
	//
	return _explosion_duration;
}

void Alien::kill() {
	//
	playAnimation( "explode", 2, false );
	_state = exploding;
}