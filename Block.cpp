#include "Block.h"

Block::Block( const String &file_name, unsigned x, unsigned y )
	: ScreenSprite( file_name )
{
	//
	_condition = state_1;
	_index = Vector2( x, y );
}


Block::~Block()
{
}

Block::Condition Block::getCondition() const {
	//
	return _condition;
}