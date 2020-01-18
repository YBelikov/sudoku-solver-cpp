#pragma once
#include "FieldGrid.h" 
#include "Solver.h"
#include <vector>

using std::vector;

class BackTrackingSolver : public Solver{
public:
	 bool solve(FieldGrid<int>& field) override;
private:
    const int UNASSIGNED = 0;
    bool inRow(FieldGrid<int>&, int, int);
    bool inColumn(FieldGrid<int>&, int, int);
    bool inBox(FieldGrid<int>&, int, int, int);
    bool findUnassignedCells(FieldGrid<int>&, int&, int&);
    bool isSafe(FieldGrid<int>&, int, int, int);
};
