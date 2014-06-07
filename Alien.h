#ifndef ALIEN_H
#define ALIEN_H

#include "SpaceInvadersEntity.h"

class Alien : public SpaceInvadersEntity
{
public:
	Alien( ScreenSprite *sprite, Vector3 *position, const unsigned &initial_HP, const float &explosion_duration );

	// copy constructor
	Alien( const Alien &rhs );

	~Alien();

	// change the current animation frame, bounds: [0, 1]
	void changeAnimationFrame();

	// get the current frame
	unsigned getCurrentFrame() const;

	// override the update function
	void update();

protected:
	// timer
	Timer *_timer;

	// the current animation frame
	unsigned _cur_frame;

	// the duration of the explosion frame
	float _explosion_duration;
};

#endif ALIEN_H