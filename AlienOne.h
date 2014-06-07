#ifndef ALIEN_ONE_H
#define ALIEN_ONE_H

#include "Alien.h"

class AlienOne : public Alien
{
public:
	AlienOne( Vector3 *position, const unsigned &initial_HP, const float &explosion_duration, const Vector3 &scale, ScreenSprite *sprite = ScreenSprite::ScreenSpriteFromImageFile( "Resources/Alien_1_test.png", 84, 53 ) );
	~AlienOne();

private:
	//
};

#endif ALIEN_ONE_H