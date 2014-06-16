#include "AlienGroup.h"

AlienGroup::AlienGroup( const Vector3 &start_pos, const unsigned num_rows, const unsigned row_spacing, const unsigned num_row_aliens, const unsigned sprite_spacing, const int alien_speed, const unsigned missile_speed )
	: _num_aliens( num_rows * num_row_aliens ), _num_aliens_per_row( num_row_aliens ), _speed( alien_speed ), _missile_speed( missile_speed )
{
	// initialize alien vectors
	Vector3 next_pos( start_pos );
	for ( unsigned r = 0; r < num_rows; ++r ) {
		//
		vector<Alien*> new_row;
		for ( unsigned a = 0; a < num_row_aliens; ++a ) {
			//
			Alien * next_alien = 0;
			if ( r < 1 ) {
				//
				next_alien = new AlienThree();
			} else if ( r < 3 ) {
				//
				next_alien = new AlienTwo();
			} else {
				//
				next_alien = new AlienOne();
			}

			next_alien->Translate( next_pos - next_alien->getPosition() );
			next_alien->Translate( Vector3( a * sprite_spacing, 0, 0 ) );
			
			_aliens.push_back( next_alien );
		}

		next_pos += Vector3( 0, row_spacing, 0 );
	}

	// set the current direction by default to right
	_current_dir = right;

	// initialize the audio set
	unsigned _sound_idx = 0;
	for ( unsigned i = 0; i < 4; ++i ) {
		//
		char buffer[256];

		itoa( i + 1, buffer, 10 );

		_audio.push_back( new Sound( "Resources/Audio/fastinvader" + String( buffer ) + "/fastinvader" + String( buffer ) + ".wav" ) );
	}
}


AlienGroup::~AlienGroup(  )
{
	//
}

void AlienGroup::update() {
	// translate all the missiles
	const unsigned num_missiles = _missiles.size();
	for ( unsigned i = 0; i < num_missiles; ++i ) {
		//
		_missiles[i]->Translate( Vector3( 0, _missile_speed, 0 ) );
	}
}

AlienGroup::Direction AlienGroup::getCurrentDirection() const {
	//
	return _current_dir;
}

void AlienGroup::reverseDirection() {
	//
	switch ( _current_dir ) {
	case left:
		_current_dir = right;
		break;
	case right:
		_current_dir = left;
		break;
	}
}

unsigned AlienGroup::getNumberOfAliens() const {
	//
	return _num_aliens;
}

void AlienGroup::getAliens( vector<Alien*> &alien_list ) const {
	//
	alien_list = _aliens;
}

void AlienGroup::shift() {
	//
	switch( _current_dir ) {
	case left:
		// translate every alien by delta
		for ( unsigned i = 0; i < _num_aliens; ++i ) {
			//
			_aliens[i]->Translate( Vector3( -_speed, 0, 0 ) );
		}
		break;
	case right:
		// translate every alien by delta
		for ( int i = 0; i < _num_aliens; ++i ) {
			//
			_aliens[i]->Translate( Vector3( _speed, 0, 0 ) );
		}
		break;
	}

	// play the appropriate audio
	++_sound_idx %= 4;
	_audio[ _sound_idx ]->Play();
}

void AlienGroup::translate( const Vector3 &delta ) {
	//
	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		_aliens[i]->Translate( delta );
	}
}

void AlienGroup::changeAnimationFrame() {
	//
	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		_aliens[i]->changeAnimationFrame();
	}
}

Alien * AlienGroup::getLeftMostAlien() const {
	//
	Alien * result = 0;
	for ( unsigned i = 0; i < _num_aliens; ++i  ) {
		//
		if ( ((result == 0) && (_aliens[i] != 0)) || (result->getPosition().x > _aliens[i]->getPosition().x) ) {
			//
			result = _aliens[i];
		}
	}

	return result;
}

Alien * AlienGroup::getRightMostAlien() const {
	//
	Alien * result = 0;
	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		if ( ((result == 0) && (_aliens[i] != 0)) || (result->getPosition().x < _aliens[i]->getPosition().x) ) {
			//
			result = _aliens[i];
		}
	}

	return result;
}

vector<Alien*> AlienGroup::getDeadAliens() {
	//
	vector<Alien*> result;
	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		if ( _aliens[i]->getState() == SpaceInvadersEntity::EntityState::dead ) {
			//
			result.push_back( _aliens[i] );
		}
	}

	return result;
}

void AlienGroup::killAlien( ScreenEntity * to_kill ) {
	//
	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		if ( _aliens[i] == to_kill ) {
			//
			_aliens[i]->kill();
		}
	}
}

void AlienGroup::removeAlien( ScreenEntity * to_remove ) {
	//
	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		if ( _aliens[i] == to_remove ) {
			//
			_aliens.erase( _aliens.begin() + i );
			--_num_aliens;
		}
	}
}

vector<Alien*> AlienGroup::getLowestAliens() const {
	// find the lowest aliens
	vector<Alien*> result( _num_aliens_per_row, 0 );

	// calculate the difference between the left-most and right-most enitity
	unsigned diff = getRightMostAlien()->getPosition().x - getLeftMostAlien()->getPosition().x;

	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		// calculate the difference between the entity and the left-most entity
		unsigned current_diff = _aliens[i]->getPosition().x - getLeftMostAlien()->getPosition().x;
		
		unsigned col_idx ;
		if ( current_diff == 0 ) {
			//
			col_idx = 0;
		} else {
			col_idx = floorf( float( diff ) / current_diff );
		}

		if ( (!result[col_idx]) || (result[col_idx]->getPosition().y < _aliens[i]->getPosition().y) ) {
			//
			result[col_idx] = _aliens[i];
		}
	}

	return result;
}

ScreenSprite* AlienGroup::fireMissile() {
	//
	if ( _num_aliens == 0 ) return 0;

	vector<Alien*> lowest_aliens = getLowestAliens();

	// remove any null elements
	const int num_aliens = lowest_aliens.size();
	for ( int i = num_aliens - 1; i >= 0; --i ) {
		//
		if ( !lowest_aliens[i] ) lowest_aliens.erase( lowest_aliens.begin() + i );
	}

	// seed the random number generator
	srand( time(NULL) );

	// fire a missile from a random alien
	unsigned idx = rand() % lowest_aliens.size();

	ScreenSprite * new_missile = ScreenSprite::ScreenSpriteFromImageFile( "Resources/alien_missile.png", 20, 39 );
	new_missile->setPosition( lowest_aliens[ idx ]->getPosition() + Vector3( 0, new_missile->getHeight(), 0 ) );
	new_missile->setScale( Vector3( 0.5, 0.5, 0 ) );

	// animations
	new_missile->addAnimation( "default", "0,1,2,3,4", 0.2 );
	new_missile->playAnimation( "default", 0, false );

	new_missile->addTag("a_missile");

	_missiles.push_back( new_missile );

	return new_missile;
}

vector<ScreenSprite*> AlienGroup::getMissiles() const {
	//
	return _missiles;
}

void AlienGroup::removeMissile( ScreenEntity * to_remove ) {
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