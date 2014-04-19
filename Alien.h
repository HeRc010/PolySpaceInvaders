/*
	May be a depricated class
*/

#include "SpaceInvadersEntity.h"

class Alien : public SpaceInvadersEntity
{
public:
	Alien( ScreenImage *sprite, Vector3 *position, const unsigned &initial_HP );
	~Alien();

private:
	
};