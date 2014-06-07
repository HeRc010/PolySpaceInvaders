#include "SpaceInvadersEntity.h"

class Alien : public SpaceInvadersEntity
{
public:
	Alien( ScreenSprite *sprite, Vector3 *position, const unsigned &initial_HP );
	~Alien();

	// change the current animation frame, bounds: [0, 1]
	void changeAnimationFrame();

	// override the update function
	void update();

protected:
	// the current animation frame
	unsigned _cur_frame;
};