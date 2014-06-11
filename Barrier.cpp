#include "Barrier.h"

Barrier::Barrier( unsigned num_blocks, unsigned num_blocks_row )
	: _num_blocks_row( num_blocks_row )
{
	//
}


Barrier::~Barrier()
{
}

vector<Block*> Barrier::getBlocks() const {
	//
	return _blocks;
}