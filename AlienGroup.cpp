#include "AlienGroup.h"

AlienGroup::AlienGroup( const Vector3 &start_pos, const unsigned num_rows, const unsigned row_spacing, const unsigned num_row_aliens, const unsigned sprite_spacing, const int alien_speed )
	: _num_aliens( num_rows * num_row_aliens ), _speed( alien_speed )
{
	// initialize alien vectors
	Vector3 next_pos( start_pos );
	for ( unsigned r = 0; r < num_rows; ++r ) {
		//
		//_aliens.push_back( new AlienRow( *( new AlienOne() ), next_pos, num_row_aliens, sprite_spacing ) );
		vector<Alien*> new_row;
		for ( unsigned a = 0; a < num_row_aliens; ++a ) {
			//
			Alien *next_alien = new AlienOne();
			next_alien->Translate( next_pos - next_alien->getPosition() );
			next_alien->Translate( Vector3( a * sprite_spacing, 0, 0 ) );
			
			//new_row.push_back( next_alien );
			_aliens.push_back( next_alien );

			/* if ( r < 2 ) {
				new_row.push_back( new AlienOne() );
			} else if ( r < 4 ) {
				
			} else {
				
			} */
		}

		next_pos += Vector3( 0, row_spacing, 0 );
	}

	// set the current direction by default to right
	_current_dir = right;
}


AlienGroup::~AlienGroup(  )
{
	//
}

unsigned AlienGroup::getNumberOfAliens() const {
	//
	return _num_aliens;
}

void AlienGroup::getAliens( vector<Alien*> &alien_list ) const {
	//
	alien_list = _aliens;
}

void AlienGroup::translate() {
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
}

void AlienGroup::changeAnimationFrame() {
	//
	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		_aliens[i]->changeAnimationFrame();
	}
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

Alien * AlienGroup::getLeftMostAlien() {
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

Alien * AlienGroup::getRightMostAlien() {
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