#include "Fighter.h"

Fighter::Fighter( const int missile_speed )
	: SpaceInvadersEntity( "Resources/fighter_1_test.png", 85, 53 ), _missile_speed( missile_speed )
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

	_num_lives = 3;
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

	// update the missiles
	const unsigned num_missiles = _missiles.size();
	for ( unsigned i = 0; i < num_missiles; ++i ) {
		//
		_missiles[i]->Translate( Vector3( 0, -_missile_speed, 0 ) );
	}
}

unsigned Fighter::getNumLives() const {
	//
	return _num_lives;
}

void Fighter::restoreLives() {
	//
	_num_lives = 3;
}

void Fighter::kill() {
	//
	_state = exploding;
	playAnimation( "explode", 1, false );

	--_num_lives;
}

void Fighter::revive() {
	//
	_state = alive;
	playAnimation( "frame_0", 0, false );

	_timer->Pause( true );
}

ScreenEntity * Fighter::fireMissile() {
	//
	ScreenSprite * new_missile = ScreenSprite::ScreenSpriteFromImageFile( "Resources/player_missile.png", 3, 15 );
	new_missile->setScale( Vector3( 1, 1, 0 ) );
	new_missile->Translate( getPosition() + Vector3( 0, - ( (new_missile->getHeight()*2) * new_missile->getScale().y ), 0 ) );
	new_missile->addTag("p_missile");

	_missiles.push_back( new_missile );

	return new_missile;
}

vector<ScreenSprite*> Fighter::getMissiles() const {
	//
	return _missiles;
}

void Fighter::removeMissile( ScreenEntity * to_remove ) {
	//
	const unsigned num_missiles = _missiles.size();
	for ( unsigned i = 0; i < num_missiles; ++i ) {
		//
		if ( _missiles[i] == to_remove ) {
			_missiles.erase( _missiles.begin() + i );
			break;
		}
	}
}