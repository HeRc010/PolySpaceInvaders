/*
	This class stores a row of aliens, the specific alien type can be passed as a "clone object" reference
	to the constructor.
*/

#ifndef ALIEN_ROW_H
#define ALIEN_ROW_H

#include "Polycode.h"
#include <vector>
#include "Alien.h"

class AlienRow
{
public:
	// default constructor
	AlienRow( const vector<Alien*> &initial_list );

	// alternatively pass in an alien object to clone for the entire row, the starting position and the space between aliens
	AlienRow( const Alien &clone, const Vector3 &initial_pos, unsigned num_aliens, unsigned spacing );

	~AlienRow();

	// translate the row
	void translate( int delta );

	// get the number of aliens in the row
	unsigned getNumAliens() const;

	// get a reference to the current state of the aliens
	void getAliens( vector<Alien*> &list ) const;

	// get the left-most element of the row
	Alien * getLeftMostAlien();

	// get the right-most element of the row
	Alien * getRightMostAlien();

	// does this row contain the given alien entity?
	bool containsAlien( ScreenEntity * to_remove ) const;

	// remove the given alien entity
	void removeAlien( ScreenEntity * to_remove );

private:
	// the number of aliens in the row
	unsigned _num_aliens;

	// list of aliens
	vector<Alien*> _aliens;
};

#endif ALIEN_ROW_H