#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include "ctest.h"
}
#include "libgame.h"

CTEST(game_logic, test1)
{

	int real = Bias(10, -1, 5);
	
	int exp = 4;
	ASSERT_EQUAL(exp, real);
}

CTEST(game_logic, test2)
{
	bool cell = true;
	int count = 0;
	int i = 1, j = 1;

	count = NeighborCounting(cell, i, j, count);
	
	int expected = 1;
	
	ASSERT_EQUAL(expected, count);
}

CTEST(game_logic, test3)
{
	bool cell = true;
	int count = 3;
	
	bool result = Condition(cell, count);
	
	ASSERT_EQUAL(1, result);
}

CTEST(game_logic, test1un)
{

	int real = Bias(10, -1, 5);
	
	int exp = 0;
	ASSERT_NOT_EQUAL(exp, real);
}

CTEST(game_logic, test2un)
{
	bool cell = false;
	int count = 0;
	int i = 1, j = 1;

	count = NeighborCounting(cell, i, j, count);
	
	int expected = 1;
	
	ASSERT_NOT_EQUAL(expected, count);
}

CTEST(game_logic, test3un)
{
	bool cell = true;
	int count = 3;
	
	bool result = Condition(cell, count);
	
	ASSERT_NOT_EQUAL(0, result);
}

