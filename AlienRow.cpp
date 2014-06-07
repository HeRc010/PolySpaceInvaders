#include "AlienRow.h"

/*
	May be depricated.
*/
AlienRow::AlienRow( const vector<Alien*> &initial_list ) : _aliens( initial_list )
{
	//

}

// alternative constructor - pass in a reference of the alien to clone
AlienRow::AlienRow( const Alien &clone, const Vector3 &initial_pos, unsigned num_aliens, unsigned spacing ) 
	: _num_aliens( num_aliens )
{
	//
	for ( int i = 0; i < num_aliens; ++i ) {
		//
		Alien* next = new Alien( clone );

		// move to the initial position
		next->Translate( initial_pos - next->getPosition() );
		
		// shift by spacing amount
		next->Translate( Vector3( i * spacing, 0, 0 ) );

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

void AlienRow::translate( int delta ) {
	//
	for ( unsigned i = 0; i < _num_aliens; ++i ) {
		//
		_aliens[i]->Translate( Vector3( delta, 0, 0 ) );
	}
}

unsigned AlienRow::getNumAliens() const {
	//
	return _num_aliens;
}

void AlienRow::getAliens( vector<Alien*> &list ) const {
	//
	list = _aliens;
}