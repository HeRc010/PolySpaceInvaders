#ifndef BARRIER_H
#define BARRIER_H

#include "Block.h"

class Barrier {
public:
	// these elements may not be needed in the constructor if they're static
	Barrier( const Vector3 &start_pos, unsigned num_blocks, unsigned num_blocks_row, unsigned barrier_idx );
	~Barrier();

	// get the number of blocks
	unsigned getNumBlocks() const;

	// get the blocks
	vector<Block*> getBlocks() const;
	
	// change the state of the given block
	void Barrier::hitBlock( Block * to_hit );

	// get destroyed blocks
	vector<Block*> getDestroyedBlocks() const;

	// remove the given block
	void removeBlock( Block * to_remove );

private:
	// the index of the barrier
	String _barrier_idx;

	// the number of blocks in the barrier
	unsigned _num_blocks;

	// the number of blocks per row
	unsigned _num_blocks_row;

	// the set of blocks for the barrier
	vector<Block*> _blocks;

	// the set of blocks which have been destroyed
	vector<Block*> _destroyed_blocks;
};

#endif BARRIER_H