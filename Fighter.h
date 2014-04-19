#include "SpaceInvadersEntity.h"

class Fighter : public SpaceInvadersEntity
{
public:
	Fighter( ScreenImage *sprite, Vector3 *position, const unsigned &initial_HP );
	~Fighter();

private:
	
};