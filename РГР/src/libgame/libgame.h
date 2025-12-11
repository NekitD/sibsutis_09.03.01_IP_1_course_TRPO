#ifndef LIBGAME_H
#define LIBGAME_H

int Bias(int z, int k, int count_z);
int NeighborCounting(bool cell, int i, int j, int count);
bool Condition(bool cell, int count);

#endif  // LIBGAME_H
