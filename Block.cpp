#include "Block.h"

Block::Block( const String &file_name, unsigned x, unsigned y, unsigned row_width )
	: ScreenSprite( file_name, 35, 35 ), _row_width( row_width )
{
	// configure animations
	/* addAnimation( "condition_0", "0", 1 );
	addAnimation( "condition_1", "1", 1 );
	addAnimation( "condition_2", "2", 1 );
	addAnimation( "condition_3", "3", 1 );

	playAnimation( "condition_0", 0, false ); */

	// compute index
	unsigned idx = x + y * _row_width;

	char buffer[256];

	itoa( idx, buffer, 10 );

	addAnimation( "base", String( buffer ), 1 );
	playAnimation( "base", idx, false );

	// add the block tag
	addTag( "block" );

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
		/* char buffer[256];

		itoa( _condition, buffer, 10 );
		playAnimation( "condition_" + String( buffer ), _condition, false ); */

		// compute the current file
		char buffer[256];

		itoa( _condition, buffer, 10 );

		String current_file = "Resources/barrier_" + String( buffer );

		if ( fileName != current_file ) {
			fileName = current_file;
		}

		playAnimation( "base", _condition, false );
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