#include "Alien.h"

Alien::Alien( const String &file_name, const unsigned &sprite_width, const unsigned &sprite_height, const float &explosion_duration )
	: SpaceInvadersEntity( file_name, sprite_width, sprite_height )
{
	// scale the sprite
	setScale( Vector3( 0.75, 0.75, 0 ) ); 

	// add a tag
	addTag( "alien" );

	// initialize animations
	addAnimation( "frame_0", "0", 1 );
	addAnimation( "frame_1", "1", 1 );
	addAnimation( "explode", "2", 1 );

	playAnimation( "frame_0", 0, false );

	_timer = 0;
	_current_frame = 0;
	_explosion_duration = explosion_duration;
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

void Alien::Update() {
	// call the base update function - to update the animations normally
	ScreenSprite::Update();

	// if the alien is exploding; if past the explosion duration; kill the alien
	if ( _state == exploding ) {
		// if timer not initialized; do so
		if ( !_timer ) _timer = new Timer( false, 0 );
		
		if ( (_timer->getElapsedf() * 1000) >= _explosion_duration ) {
			//
			_state = dead;
		}
	}
}

void Alien::changeAnimationFrame() {
	// if the alien is not dead
	if ( _state == alive ) {
		++_current_frame;
		_current_frame %= 2;
	
		char buffer[256];
		itoa( _current_frame, buffer, 10 );

		playAnimation( "frame_" + String( buffer ), _current_frame, false );
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