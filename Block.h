#ifndef BLOCK_H
#define BLOCK_H

#include "Polycode.h"
#include "PolycodeView.h"
#include "PolyGlobals.h"

class Block : public ScreenSprite {
public:
	Block( const String &file_name );
	~Block();
};

#endif BLOCK_H