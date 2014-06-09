/*
	A specific entity subclass for the player/fighter
*/

#include "SpaceInvadersEntity.h"

class Fighter : public SpaceInvadersEntity
{
public:
	Fighter();
	~Fighter();

	// override the update function
	void Update();

	// kill the fighter; play the explode frame
	void kill();

	// revive the fighter
	void revive();

private:
	//
	Timer * _timer;

	// explosion duration
	unsigned _explosion_duration;
};