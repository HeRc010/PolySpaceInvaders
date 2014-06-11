#include "RedUfo.h"

RedUfo::RedUfo( const unsigned screen_width )
	: SpaceInvadersEntity( "Resources/red_ufo.png", 155, 68 )
{
	//
	setScale( Vector3( 0.5, 0.5, 0 ) );
	
	// randomly choose which side to approach from
	srand( time(0) );

	_current_direction = Direction( rand() % 2 );

	switch ( _current_direction ) {
	case left:
		// start on the right
		Translate( Vector3( screen_width - getWidth() + 10, 100, 0 ) - getPosition() );
		break;
	case right:
		Translate( Vector3( getWidth() + 10, 100, 0 ) - getPosition() );
		break;
	}

	addTag("redUFO");
}


RedUfo::~RedUfo()
{
	//
}

void RedUfo::Update() {
	//
	if ( !_paused ) {
		ScreenSprite::Update();

		switch ( _current_direction ) {
		case left:
			Translate( Vector3( -3, 0, 0 ) );
			break;
		case right:
			Translate( Vector3( 3, 0, 0 ) );
			break;
		}
	}
}

void RedUfo::kill() {
	//

}

bool RedUfo::isPaused() const {
	//
	return _paused;
}

void RedUfo::togglePause() {
	//
	_paused = !_paused;
}