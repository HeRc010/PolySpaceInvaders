#ifndef BARRIER_H
#define BARRIER_H

#include "Block.h"

class Barrier
{
public:
	Barrier( unsigned num_blocks, unsigned num_blocks_row );
	~Barrier();

	// get the blocks
	vector<Block*> getBlocks() const;

private:
	// the number of blocks per row
	unsigned _num_blocks_row;

	// the set of blocks for the barrier
	vector<Block*> _blocks;
};

#endif BARRIER_H