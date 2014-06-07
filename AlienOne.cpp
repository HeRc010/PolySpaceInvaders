#include "AlienOne.h"

AlienOne::AlienOne( Vector3 *position, const unsigned &initial_HP, const float &explosion_duration, ScreenSprite *sprite ) : Alien( sprite, position, initial_HP, explosion_duration  )
{
}

AlienOne::~AlienOne()
{
}