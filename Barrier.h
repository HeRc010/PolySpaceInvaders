#ifndef BARRIER_H
#define BARRIER_H

#include "Block.h"

class Barrier
{
public:
	Barrier();
	~Barrier();
private:
	// the set of blocks for the barrier
	vector<Block*> _blocks;
};

#endif BARRIER_H