#include "Barrier.h"

Barrier::Barrier( const Vector3 &start_pos, unsigned num_blocks, unsigned num_blocks_row, unsigned barrier_index )
	: _num_blocks_row( num_blocks_row ), _num_blocks( num_blocks - 2 )
{
	// define the barrier index member
	char idx_buff[256];

	itoa( barrier_index, idx_buff, 10 );

	_barrier_idx = "barrier_" + String( idx_buff );

	// initialize the blocks
	Vector3 next_pos( start_pos );
	for ( unsigned i = 0; i < num_blocks / _num_blocks_row; ++i ) {
		//
		for ( unsigned j = 0; j < _num_blocks_row; ++j ) {
			// skip two of the blocks on the bottom
			if ( ( (i == 2) && (j == 1) ) || ( (i == 2) && (j == 2) ) ) continue;

			char i_buff[256];
			char j_buff[256];

			itoa( i, i_buff, 10 );
			itoa( j, j_buff, 10 );

			//Block * next_block = new Block( "Resources/barrier_" + String( j_buff ) + "_" + String( i_buff ) + "_test.png" , j, i, _num_blocks_row );
			Block * next_block = new Block( "Resources/barrier_0.png", j, i, _num_blocks_row );

			next_block->Translate( next_pos + Vector3( next_block->getWidth() * j, 0, 0 ) );

			next_block->addTag( _barrier_idx );

			_blocks.push_back( next_block );
		}

		next_pos += Vector3( 0, 35, 0 );
	}
}


Barrier::~Barrier()
{
	//
}

unsigned Barrier::getNumBlocks() const {
	//
	return _num_blocks;
}

vector<Block*> Barrier::getBlocks() const {
	//
	return _blocks;
}

void Barrier::hitBlock( ScreenEntity * to_hit ) {
	//
	for ( unsigned i = 0; i < _num_blocks; ++i ) {
		//
		if ( _blocks[i] == to_hit ) {
			//
			_blocks[i]->hit();

			if ( _blocks[i]->getCondition() == Block::Condition::destroyed ) {
				// place the block in the destroyed array
				_destroyed_blocks.push_back( _blocks[i] );
			}

			return;
		}
	}
}

vector<Block*> Barrier::getDestroyedBlocks() const {
	//
	return _destroyed_blocks;
}

void Barrier::removeBlock( Block * to_remove ) {
	//
	for ( unsigned i = 0; i < _num_blocks; ++i ) {
		//
		if ( _blocks[i] == to_remove ) {
			//
			_blocks.erase( _blocks.begin() + i );
			--_num_blocks;

			return;
		}
	}

	const unsigned num_destroyed_blocks = _destroyed_blocks.size();
	for ( unsigned i = 0; i < num_destroyed_blocks ; ++i ) {
		//
		if ( _destroyed_blocks[i] == to_remove ) {
			_destroyed_blocks.erase( _destroyed_blocks.begin() + i );
			return;
		}
	}
}