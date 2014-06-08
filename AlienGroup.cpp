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
	/* vector<Alien*> result;
	for ( unsigned i = 0; i < _num_rows; ++i ) {
		//
		const unsigned num_aliens = _aliens[i].size();
		for ( unsigned j = 0; j < num_aliens; ++j ) {
			//
			result.push_back( _aliens[i][j] );
		}
	} */

	alien_list = _aliens;
}

void AlienGroup::translate() {
	//
	switch( _current_dir ) {
	case left:
		// translate every alien by delta
		for ( unsigned i = 0; i < _num_aliens; ++i ) {
			//
			//_aliens[i]->translate( -_speed );
			/* const unsigned num_aliens = _aliens[i].size();
			for ( unsigned j = 0; j < num_aliens; ++j ) {
				//
				_aliens[i][j]->Translate( -_speed );
			} */
			_aliens[i]->Translate( Vector3( -_speed, 0, 0 ) );
		}
		break;
	case right:
		// translate every alien by delta
		for ( int i = 0; i < _num_aliens; ++i ) {
			//
			//_aliens[i]->translate( _speed );
			/* const unsigned num_aliens = _aliens[i].size();
			for ( unsigned j = 0; j < num_aliens; ++j ) {
				//
				_aliens[i][j]->Translate( _speed );
			} */
			_aliens[i]->Translate( Vector3( _speed, 0, 0 ) );
		}
		break;
	}
}

vector<Alien*> AlienGroup::getDeadAliens() {
	//
	vector<Alien*> result;
	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		/* vector<Alien*> next = _aliens[i]->getDeadAliens();
		
		vector<Alien*> temp;
		temp.reserve( result.size() + next.size() );
		temp.insert( temp.end(), result.begin(), result.end() );
		temp.insert( temp.end(), next.begin(), next.end() );

		result = temp; */
		/* const unsigned num_aliens = _aliens[i].size();
		for ( unsigned j = 0; j < num_aliens; ++j ) {
			//
			if ( _aliens[i][j]->getState() == SpaceInvadersEntity::EntityState::dead ) {
				//
				result.push_back( _aliens[i][j] );
			}
		} */
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
	/* if ( _num_rows == 0 ) return 0;

	Alien * result = _aliens[0]->getLeftMostAlien();

	Alien * temp;
	for ( unsigned i = 1; i < _num_rows; ++i ) {
		//
		temp = _aliens[i]->getLeftMostAlien();

		if ( !temp ) continue;

		if ( (temp->getPosition().x < result->getPosition().x) || ( (temp != 0) && (result == 0) ) ) {
			//
			result = temp;
		}
	} */
	
	Alien * result = 0;
	for ( unsigned i = 0; i < _num_aliens; ++i  ) {
		//
		/* const unsigned num_aliens = _aliens[i].size();
		for ( unsigned j = 0; j < num_aliens; ++j ) {
			//
			if ( ((result == 0) && (_aliens[i][j] != 0)) || (result->getPosition().x > _aliens[i][j]->getPosition().x) ) {
				//
				result = _aliens[i][j];
			} 
		} */
		if ( ((result == 0) && (_aliens[i] != 0)) || (result->getPosition().x > _aliens[i]->getPosition().x) ) {
			//
			result = _aliens[i];
		}
	}

	return result;
}

Alien * AlienGroup::getRightMostAlien() {
	//
	//if ( _num_rows == 0 ) return 0;
	//Alien * result = _aliens[0]->getRightMostAlien();
	//Alien * temp;

	Alien * result = 0;
	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		/* temp = _aliens[i]->getRightMostAlien();

		if ( !temp ) continue;

		if ( (temp->getPosition().x > result->getPosition().x) || ( (temp != 0) && (result == 0) ) ) {
			//
			result = temp;
		} */
		/* const unsigned num_aliens = _aliens[i].size();
		for ( unsigned j = 0; j < num_aliens; ++j ) {
			//
			if ( ((result == 0) && (_aliens[i][j] != 0)) || (result->getPosition().x < _aliens[i][j]->getPosition().x) ) {
				//
				result = _aliens[i][j];
			} 
		} */
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
		/* if ( _aliens[i]->containsAlien( to_kill ) ) {
			//
			_aliens[i]->killAlien( to_kill );

			return;
		} */
		/* const unsigned num_aliens = _aliens[i].size();
		for ( unsigned j = 0; j < num_aliens; ++j ) {
			//
			if ( _aliens[i][j] == to_kill ) {
				//
				_aliens[i][j]->kill();
			}
		} */
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
		/* if ( _aliens[i]->containsAlien( to_remove ) ) {
			//
			_aliens[i]->removeAlien( to_remove );

			return;
		} */
		/* const unsigned num_aliens = _aliens[i].size();
		for ( unsigned j = 0; j < num_aliens; ++j ) {
			//
			if ( _aliens[i][j] == to_remove ) {
				//
				_aliens[i].erase( _aliens[i].begin() + j );
			}
		} */
		if ( _aliens[i] == to_remove ) {
			//
			_aliens.erase( _aliens.begin() + i );
		}
	}
}