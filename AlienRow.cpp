#include "AlienRow.h"

/*
	May be depricated.
*/
AlienRow::AlienRow( const vector<SpaceInvadersEntity*> &initial_list ) : _aliens( initial_list )
{
	//

}

// alternative constructor - pass in a reference of the alien to clone
AlienRow::AlienRow( const SpaceInvadersEntity &clone, const Vector3 &initial_pos, unsigned num_aliens, unsigned spacing ) : _num_aliens( num_aliens ) {
	//
	for ( int i = 0; i < num_aliens; ++i ) {
		//
		SpaceInvadersEntity* next = new SpaceInvadersEntity( clone );

		// move to the initial position
		next->translate( initial_pos - next->getPosition() );
		
		// shift by spacing amount
		next->translate( Vector3( i * spacing, 0, 0 ) );

		_aliens.push_back( next );
	}
}

AlienRow::~AlienRow()
{
	//
	for ( int i = 0; i < _aliens.size(); ++i ) {
		//
		delete _aliens[i];
	}
}

unsigned AlienRow::getNumAliens() {
	//
	return _num_aliens;
}

void AlienRow::getAliens( vector<SpaceInvadersEntity*> &list ) const {
	//
	list = _aliens;
}

void AlienRow::translate( const Vector3 &delta ) {
	// translate every alien by delta
	for ( int i = 0; i < _aliens.size(); ++i ) {
		//
		_aliens[i]->translate( delta );
	}
}

bool AlienRow::containsAlien( ScreenEntity * entity ) const {
	//
	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		if ( entity == _aliens[i]->getSprite() ) return true;
	}

	return false;
}

/*
	NOTE: the assertion check might not be necessary... in the app class; the function checks if the row contains the alien first...
*/
void AlienRow::removeAlien( ScreenEntity * to_remove ) {
	// failsafe
	assert( containsAlien( to_remove ) );

	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		if ( to_remove == _aliens[i]->getSprite() ) {
			_aliens.erase( _aliens.begin() + i );
			--_num_aliens;
			break;
		}
	}
}

void AlienRow::removeAlien( unsigned i ) {
	//
	_aliens.erase( _aliens.begin() + i );
}