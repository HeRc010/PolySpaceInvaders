/*
	A specific entity subclass for the Red UFO entity
*/

#ifndef RED_UFO_H
#define RED_UFO_H

#include "spaceinvadersentity.h"

#include <ctime>

class RedUfo : public SpaceInvadersEntity
{
public:
	RedUfo( const unsigned screen_width );
	~RedUfo();

	// overrride the update method
	void Update();

	// direction values
	enum Direction { left, right };

	// override the kill method
	void kill();

	// get the paused' state
	bool isPaused() const;

	// pause/unpause - inverts the pause state
	void togglePause();

private:
	// the direction the ufo is moving in
	Direction _current_direction;

	// is the ufos movement paused?
	bool _paused;
};

#endif RED_UFO_H