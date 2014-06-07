/*
	This class stores a row of aliens, the specific alien type can be passed as a "clone object" reference
	to the constructor.
*/

#include "Polycode.h"
#include <vector>
#include "Alien.h"

class AlienRow
{
public:
	
	AlienRow( const vector<SpaceInvadersEntity*> &initial_list );

	// alternatively pass in an alien object to clone for the entire row, the starting position and the space between aliens
	AlienRow( const SpaceInvadersEntity &clone, const Vector3 &initial_pos, unsigned num_aliens, unsigned spacing );

	~AlienRow();

	// translate the row by a certain delta-movement
	void translate( const Vector3 &delta );

	// get the number of aliens in the row - do they need to be alive?... for now no
	unsigned getNumAliens() const;

	// get a reference to the current state of the aliens
	void getAliens( vector<SpaceInvadersEntity*> &list ) const;

	// does this row contain the alien?
	bool containsAlien( ScreenEntity * entity ) const;

	// remove an alien from the row
	void removeAlien( ScreenEntity * to_remove );

	// remove an alien specified by index
	void removeAlien( unsigned i );

private:
	// the number of aliens in the row
	unsigned _num_aliens;

	// list of aliens
	vector<Alien*> _aliens;
};