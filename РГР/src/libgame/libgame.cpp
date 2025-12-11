#include <cstring>
#include <ctime>
#include "libgame.h"

int Bias(int z, int k, int count_z)
{
	int nz = (z + k + count_z) % count_z;
	return nz;
}

int NeighborCounting(bool cell, int i, int j, int count)
{
	if (cell && !(i == 0 && j == 0))
	{
		count++;
	}
	
	return count;
}

bool Condition(bool cell, int count)
{
	bool res;
	if (cell == true)
	{
		if (count == 2 || count == 3)
		{
			res = true;
		}
		else
		{
			res = false;
		}
	}
	else
	{
		if (count == 3)
		{
			res = true;
		}
	}
	
	return res;
}


