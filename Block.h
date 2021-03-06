/*
	A class which represents a block in the Barrier(s)
*/

#ifndef BLOCK_H
#define BLOCK_H

#include "Polycode.h"
#include "PolycodeView.h"
#include "PolyGlobals.h"

class Block : public ScreenSprite {
public:
	Block( const String &file_name, unsigned x, unsigned y, unsigned row_width );
	~Block();

	// override the update method
	void Update();

	enum Condition { condition_1, condition_2, condition_3, condition_4, destroyed };

	// get the condition of the block
	Condition getCondition() const;

	// decrement the state of the block
	void hit();

private:
	// the condition of the block
	unsigned _condition;

	// the width of the barrier in number of blocks
	unsigned _row_width;

	// the index of the block in the would-be barrier
	Vector2 _index;
};

#endif BLOCK_H