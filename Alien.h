#ifndef ALIEN_H
#define ALIEN_H

#include "SpaceInvadersEntity.h"

class Alien : public SpaceInvadersEntity
{
public:
	Alien( const String &file_name, const unsigned &sprite_width, const unsigned &sprite_height, const float &explosion_duration = 1000 );

	// copy constructor - DEPRECATED
	Alien( const Alien &rhs );

	~Alien();

	// change the current animation frame
	void changeAnimationFrame();

	// get the current animation frame
	unsigned getFrame() const;

	// get explosion duration
	float getExplosionDuration() const;

	// kill the alien - set state to exploding
	void kill();

protected:
	// timer
	Timer *_timer;

	// the current animation frame
	unsigned _current_frame;

	// elapsed frames
	unsigned _elapsed_frames;

	// the duration of the explosion frame - in number of elapsed frames
	float _explosion_duration;
};

#endif ALIEN_H