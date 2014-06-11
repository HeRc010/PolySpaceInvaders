#ifndef BLOCK_H
#define BLOCK_H

#include "Polycode.h"
#include "PolycodeView.h"
#include "PolyGlobals.h"

class Block : public ScreenSprite {
public:
	Block( const String &file_name, unsigned x, unsigned y );
	~Block();

	enum Condition { state_1, state_2, state_3, state_4, dead };

	// get the condition of the block
	Condition getCondition() const;

private:
	// the condition of the block
	Condition _condition;

	// the index of the block in the would-be barrier
	Vector2 _index;
};

#endif BLOCK_H