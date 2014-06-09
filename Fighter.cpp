#include "Fighter.h"

Fighter::Fighter(  )
	: SpaceInvadersEntity( "Resources/fighter_1_test.png", 85, 53 )
{
	//
	addTag("fighter");

	addAnimation( "frame_0", "0", 1 );
	addAnimation( "explode", "1", 1 );

	playAnimation( "frame_0", 0, false );

	// set the explosion duration
	_explosion_duration = 1000;

	_timer = new Timer( false, 0 );

	_timer->Pause( true );
}

Fighter::~Fighter()
{
	//

}

void Fighter::Update() {
	// call the base update function - to update the animations normally
	ScreenSprite::Update();

	//
	if ( _state == exploding ) {
		//
		if ( _timer->isPaused() ) {
			_timer->Pause( false );
			_timer->Reset();
		}

		if ( (_timer->getElapsedf() * 1000) > _explosion_duration ) {
			//
			_state = dead;
		}
	}
}

void Fighter::kill() {
	//
	_state = exploding;
	playAnimation( "explode", 1, false );
}

void Fighter::revive() {
	//
	_state = alive;
	playAnimation( "frame_0", 0, false );

	_timer->Pause( true );
}
