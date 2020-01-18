#include "BackTrackingSolver.h"
using std::vector;

bool BackTrackingSolver::solve(FieldGrid<int>& field) {
	int maxNumberInGrid = field.size();
	int row{}, col{};
	if (!findUnassignedCells(field, row, col)) return true;
	for (int i{}; i <= maxNumberInGrid; ++i) {
		if (isSafe(field, row, col, i)) {
			field[row][col] = i;
			if (solve(field)) return true;
			field[row][col] = UNASSIGNED;
		}
	}
	return false;

}

bool BackTrackingSolver::findUnassignedCells(FieldGrid<int>& field, int& row, int& column) {
	int gridSize = field.size();
	for (row = 0; row < gridSize; ++row) {
		for (column = 0; column < gridSize; ++column) {
			if (field[row][column] == UNASSIGNED) return true;
		}
	}
	return false;
}

bool BackTrackingSolver::inRow(FieldGrid<int>& field, int row, int number) {
	int gridSize = field.size();
	for (int column = 0; column < gridSize; ++column) {
		if (field[row][column] == number) return true;
	}
	return false;
}

bool BackTrackingSolver::inColumn(FieldGrid<int>& field, int column, int number) {
	int gridSize = field.size();
	for (int row = 0; row < gridSize; ++row) {
		if (field[row][column] == number) return true;
	}
	return false;
}

bool BackTrackingSolver::inBox(FieldGrid<int>& field, int boxStartingRow, int boxStartingColumn, int number) {
	int boxSize = int(sqrt(field.size()));
	for (int row = 0; row < boxSize; ++row) {
		for (int column = 0; column < boxSize; ++column) {
			if (field[boxStartingRow + row][boxStartingColumn + column] == number) return true;
		}
	}
	return false;
}

bool BackTrackingSolver::isSafe(FieldGrid<int>& field, int row, int column, int number) {
	int boxSize = int(sqrt(field.size()));
	return !inColumn(field, column, number) && !inRow(field, row, number) && !inBox(field, row - row % boxSize, column -
		column % boxSize, number) && (field[row][column] == UNASSIGNED);
}