#ifndef ALIEN_GROUP_H
#define ALIEN_GROUP_H

#include "AlienRow.h"
#include "AlienOne.h"

class AlienGroup
{
public:
	//
	AlienGroup( const Vector3 &start_pos, const unsigned num_rows, const unsigned row_spacing, const unsigned num_row_aliens, const unsigned sprite_spacing, const int alien_speed );

	~AlienGroup(  );

	// direction values
	enum Direction { left, right };

	// get the number of rows
	unsigned getNumberOfRows() const;

	// get the aliens
	void getAliens( vector<AlienRow*> &alien_list ) const;

	// translate the aliens
	void translate();

	// get current direction
	Direction getCurrentDirection() const;

	// reverse the direction of the row
	void reverseDirection();

	// get the left-most element of the group
	Alien * getLeftMostAlien();

	// get the right-most element of the group
	Alien * getRightMostAlien();

	// remove the given alien entity
	void removeAlien( ScreenEntity * to_remove );

private:
	// the current direction
	Direction _current_dir;

	// the aliens' speed
	int _speed;

	// the number of rows
	unsigned _num_rows;

	// the set of alien rows
	vector<AlienRow*> _aliens;
};

#endif ALIEN_GROUP_H