/*
	A class which represents the group of aliens
*/

#ifndef ALIEN_GROUP_H
#define ALIEN_GROUP_H

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "AlienOne.h"
#include "AlienTwo.h"
#include "AlienThree.h"

class AlienGroup
{
public:
	//
	AlienGroup( const Vector3 &start_pos, const unsigned num_rows, const unsigned row_spacing, const unsigned num_row_aliens, const unsigned sprite_spacing, const int alien_speed, const unsigned missile_speed );

	~AlienGroup();

	// function to be called every frame
	void update();

	// direction values
	enum Direction { left, right };

	// get current direction
	Direction getCurrentDirection() const;

	// reverse the direction of the rows
	void reverseDirection();

	// get the number of rows
	unsigned getNumberOfAliens() const;

	// get the aliens
	void getAliens( vector<Alien*> &alien_list ) const;

	// shift the aliens to the left or right
	void shift();

	// translate the aliens
	void translate( const Vector3 &delta );

	// change the animation frame for the aliens
	void changeAnimationFrame();

	// get the left-most alien of the group
	Alien * getLeftMostAlien() const;

	// get the right-most alien of the group
	Alien * getRightMostAlien() const;

	// get the list of aliens which need to be removed
	vector<Alien*> getDeadAliens();

	// kill the given alien
	void killAlien( ScreenEntity * to_kill );

	// remove the given alien entity
	void removeAlien( ScreenEntity * to_remove );

	// fire a missile
	ScreenSprite * fireMissile();

	// get the set of missiles
	vector<ScreenSprite*> getMissiles() const;

	// remove the given missile
	void removeMissile( ScreenEntity * to_remove );

private:
	// get the lowest aliens in each column
	vector<Alien*> getLowestAliens() const;

	// the current direction
	Direction _current_dir;

	// the aliens' speed
	int _speed;

	// the number of aliens
	unsigned _num_aliens;
	
	// the set of aliens
	vector<Alien*> _aliens;

	// the number of aliens per row - initially
	unsigned _num_aliens_per_row;

	// the speed of the missiles
	unsigned _missile_speed;

	// the set of missiles the aliens have fired
	vector<ScreenSprite*> _missiles;

	// the current index of the sound in the audio set
	unsigned _sound_idx;

	// the set of audio for alien shifts
	vector<Sound*> _audio;
};

#endif ALIEN_GROUP_H