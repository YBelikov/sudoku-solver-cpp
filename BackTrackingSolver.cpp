#include "BackTrackingSolver.h"
using std::vector;

bool BackTrackingSolver::solve(FieldGrid& field) {
	int maxNumber = sqrt(field.size());
	int row{}, col{};
	if(!findUnassignedCells(field, row, col))
	for (int i{}; i <= maxNumber; ++i) {
		if (isSafe(field, row, col, i)) {
			field[row][col] = i;
			if (solve(field)) return true;
			field[row][col] = UNASSIGNED;
		}
	}
}