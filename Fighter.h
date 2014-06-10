/*
	A specific entity subclass for the player/fighter
*/

#include "SpaceInvadersEntity.h"

class Fighter : public SpaceInvadersEntity
{
public:
	Fighter( const int missile_speed );
	~Fighter();

	// override the update function
	void Update();

	// get the number of lives the player has
	unsigned getNumLives() const;

	// restore the players lives
	void restoreLives();

	// kill the fighter; play the explode frame
	void kill();

	// revive the fighter
	void revive();

	// fire a missile
	ScreenEntity * fireMissile();

	// get the missiles
	vector<ScreenSprite*> getMissiles() const;

	// remove the given missile
	void removeMissile( ScreenEntity * to_remove );

private:
	// timer for explosion
	Timer * _timer;

	// explosion duration
	unsigned _explosion_duration;

	// the number of lives the fighter has
	unsigned _num_lives;

	// the speed of the missiles
	int _missile_speed;

	// the missiles the player has fired
	vector<ScreenSprite*> _missiles;
};