#pragma once
#include <vector>
#include "FieldGrid.h"

class Solver {
public:
	virtual bool solve(FieldGrid<int>&) = 0;
};
