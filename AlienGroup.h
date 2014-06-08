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
	unsigned getNumberOfAliens() const;

	// get the aliens
	void getAliens( vector<Alien*> &alien_list ) const;

	// translate the aliens
	void translate();

	// change the animation frame for the aliens
	void changeAnimationFrame();

	// get the list of aliens which need to be removed
	vector<Alien*> getDeadAliens();

	// get current direction
	Direction getCurrentDirection() const;

	// reverse the direction of the row
	void reverseDirection();

	// get the left-most element of the group
	Alien * getLeftMostAlien();

	// get the right-most element of the group
	Alien * getRightMostAlien();

	// kill the given alien
	void killAlien( ScreenEntity * to_kill );

	// remove the given alien entity
	void removeAlien( ScreenEntity * to_remove );

private:
	// the current direction
	Direction _current_dir;

	// the aliens' speed
	int _speed;

	// the number of aliens
	unsigned _num_aliens;
	
	// the set of aliens
	vector<Alien*> _aliens;
};

#endif ALIEN_GROUP_H