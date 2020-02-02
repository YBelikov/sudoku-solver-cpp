#pragma once
#include "Solver.h"
#include "ColumnNode.h"
#include <vector>


class DLXSolver : public Solver{
public:
	bool solve(FieldGrid<int>&) override; 
private:
	ColumnNode* createDLXList(FieldGrid<int>&);
	ColumnNode* chooseColumnWithMinimumSize();
	int createCellConstraints(FieldGrid<int>&, int);
	int createRowConstraints(FieldGrid<int>&, int);
	int createColumnConstraints(FieldGrid<int>&, int);
	int createBoxConstraints(FieldGrid<int>&, int);
	int indexInCoverMatrix(int, int, int);
	bool solveByCoverMatrix(FieldGrid<int>&);
	bool process(int);
	FieldGrid<int> convertToCoverMatrix();
	FieldGrid<int> createCoverMatrixForCertainGrid();
	FieldGrid<int> grid;
	int size;
	const int numberOfConstraints = 4;
	const int startingIndex = 1;
	ColumnNode* headerNode;
	void convertFromDLXListToGrid(FieldGrid<int>&);
	vector<DancingNode*> answer;
	vector<DancingNode*> result;
};