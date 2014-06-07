#include "Alien.h"

class AlienOne : public Alien
{
public:
	AlienOne( Vector3 *position, const unsigned &initial_HP, ScreenSprite *sprite = ScreenSprite::ScreenSpriteFromImageFile( "Resources/Alien_1.png", 168/2, 53 ) );
	~AlienOne();

private:
	//
};