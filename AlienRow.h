/*
	This class stores a row of aliens, the specific alien type can be passed as a "clone object" reference
	to the constructor.
*/

#include "Polycode.h"
#include <vector>
#include "SpaceInvadersEntity.h"

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
	unsigned numAliens();

	// get a reference to the current state of the aliens
	void getAliens( vector<SpaceInvadersEntity*> &list ) const;

private:
	// list of aliens
	vector<SpaceInvadersEntity*> _aliens;
};