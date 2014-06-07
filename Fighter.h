/*
	May be a depricated class...
*/

#include "SpaceInvadersEntity.h"

class Fighter : public SpaceInvadersEntity
{
public:
	Fighter( ScreenSprite *sprite, Vector3 *position, const unsigned &initial_HP );
	~Fighter();

	//
	void update();

private:
	
};