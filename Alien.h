#ifndef ALIEN_H
#define ALIEN_H

#include "SpaceInvadersEntity.h"

class Alien : public SpaceInvadersEntity
{
public:
	Alien( const String &file_name, const unsigned &sprite_width, const unsigned &sprite_height, const float &explosion_duration = 1000 );

	// copy constructor
	Alien( const Alien &rhs );

	~Alien();

	// override update function
	//void Update();

	// change the current animation frame
	void changeAnimationFrame();

	// get the current animation frame
	unsigned getFrame() const;

	// get explosion duration
	float getExplosionDuration() const;

protected:
	// timer
	//Timer *_timer;

	//
	unsigned _current_frame;

	// the duration of the explosion frame
	float _explosion_duration;
};

#endif ALIEN_H