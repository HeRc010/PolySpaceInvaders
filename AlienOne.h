#ifndef ALIEN_ONE_H
#define ALIEN_ONE_H

#include "Alien.h"

class AlienOne : public Alien
{
public:
	AlienOne( const String &file_name = "Resources/Alien_One.png", const unsigned &sprite_width = 84, const unsigned &sprite_height = 53 );
	~AlienOne();

private:
	//
};

#endif ALIEN_ONE_H