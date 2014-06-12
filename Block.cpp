#include "Block.h"

Block::Block( const String &file_name, unsigned x, unsigned y )
	: ScreenSprite( file_name, 35, 35 )
{
	// configure animations
	addAnimation( "condition_0", "0", 1 );
	addAnimation( "condition_1", "1", 1 );
	addAnimation( "condition_2", "2", 1 );
	addAnimation( "condition_3", "3", 1 );

	playAnimation( "condition_0", 0, false );

	// add the block tag
	addTag("block");

	//
	_condition = 0;
	_index = Vector2( x, y );
}


Block::~Block()
{
}

void Block::Update() {
	//
	ScreenSprite::Update();

	// if not destroyed, play the appropriate state frame
	if ( Condition( _condition ) != destroyed ) {
		//
		char buffer[256];

		itoa( _condition, buffer, 10 );
		playAnimation( "condition_" + String( buffer ), _condition, false );
	}
}

Block::Condition Block::getCondition() const {
	//
	return Condition( _condition );
}

void Block::hit() {
	//
	_condition = ++_condition % 5;
}