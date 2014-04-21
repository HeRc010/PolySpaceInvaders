#include "AlienRow.h"

AlienRow::AlienRow( const vector<SpaceInvadersEntity*> &initial_list ) : _aliens( initial_list )
{
	//

}

// alternative constructor - pass in a reference of the alien to clone
AlienRow::AlienRow( const SpaceInvadersEntity &clone, const Vector3 &initial_pos, unsigned num_aliens, unsigned spacing ) {
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

unsigned AlienRow::numAliens() {
	//
	return _aliens.size();
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