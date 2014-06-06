/*
	May be a depricated class
*/

#include "SpaceInvadersEntity.h"

class Alien : public SpaceInvadersEntity
{
public:
	Alien( ScreenSprite *sprite, Vector3 *position, const unsigned &initial_HP );
	~Alien();

private:
	
};