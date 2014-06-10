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

	// get the number of lives the player has
	unsigned getNumLives() const;

	// restore the players lives
	void restoreLives();

	// take one of the players lives
	//void takeLife();

	/*
	
	void Fighter::takeLife() {
		//
		if ( _num_lives != 0 ) --_num_lives;
	}

	*/

	// kill the fighter; play the explode frame
	void kill();

	// revive the fighter
	void revive();

private:
	//
	Timer * _timer;

	// explosion duration
	unsigned _explosion_duration;

	// the number of lives the fighter has
	unsigned _num_lives;
};