#include "DLXSolver.h"
#include <string>
#include <iostream>

bool DLXSolver::solve(FieldGrid<int>& grid_) {
	grid = grid_;
	size = grid.numberOfColumns();
	FieldGrid<int> coverMatrix = createCoverMatrixForCertainGrid();
	if (solveByCoverMatrix(coverMatrix)) {
		convertFromDLXListToGrid(grid_);
		return true;
	}
	return false;
}

int DLXSolver::indexInCoverMatrix(int row, int column, int number) {
	return (row - 1) * grid.numberOfColumns() * grid.numberOfRows() + (column - 1) * grid.numberOfColumns() + (number - 1);
}

FieldGrid<int> DLXSolver::convertToCoverMatrix() {
	FieldGrid<int> coverMatrix;
	coverMatrix.resize(grid.numberOfRows() * grid.numberOfRows() * grid.numberOfRows());
	for (auto& row : coverMatrix) {
		row.resize(grid.numberOfColumns() * grid.numberOfRows() * numberOfConstraints);
	}
	int header{};
	header = createCellConstraints(coverMatrix, header);
	header = createRowConstraints(coverMatrix, header);
	header = createColumnConstraints(coverMatrix, header);
	createBoxConstraints(coverMatrix, header);
	return coverMatrix;
}

int DLXSolver::createCellConstraints(FieldGrid<int>& matrix, int header) {
	for (int row = startingIndex; row <= size; ++row) {
		for (int column = startingIndex; column <= size; ++column, ++header) {
			for (int number = startingIndex; number <= size; ++number) {
				int index = indexInCoverMatrix(row, column, number);
				matrix(index, header) = 1;
			}
		}
	}
	return header;
}

int DLXSolver::createRowConstraints(FieldGrid<int>& matrix, int header) {
	for (int row = startingIndex; row <= size; ++row) {
		for (int number = startingIndex; number <= size; ++number, ++header) {
			for (int column = startingIndex; column <= size; ++column) {
				int index = indexInCoverMatrix(row, column, number);
				matrix(index, header) = 1;
			}
		}
	}
	return header;
}

int DLXSolver::createColumnConstraints(FieldGrid<int>& matrix, int header) {
	for (int column = startingIndex; column <= size; ++column) {
		for (int n = startingIndex; n <= size; ++n, ++header) {
			for (int row = startingIndex; row <= size; ++row) {
				int index = indexInCoverMatrix(row, column, n);
				matrix(index, header) = 1;
			}
		}
	}
	return header;
}

int DLXSolver::createBoxConstraints(FieldGrid<int>& matrix, int header) {
	int boxSize = int(sqrt(size));
	for (int row = startingIndex; row <= size; row += boxSize) {
		for (int column = startingIndex; column <= size; column += boxSize) {
			for (int n = startingIndex; n <= size; n++, header++) {
				for (int rowDelta = 0; rowDelta < boxSize; rowDelta++) {
					for (int columnDelta = 0; columnDelta < boxSize; columnDelta++) {
						int index = indexInCoverMatrix(row + rowDelta, column + columnDelta, n);
						matrix(index, header) = 1;
					}
				}
			}
		}
	}
	return header;
}

FieldGrid<int> DLXSolver::createCoverMatrixForCertainGrid() {
	FieldGrid<int> coverMatrix = convertToCoverMatrix();
	for (int row = startingIndex; row <= size; ++row) {
		for (int column = startingIndex; column <= size; ++column) {
			int numberInCell = grid(row - 1, column - 1);
			if (numberInCell) {
				for (int n = 1; n <= grid.numberOfColumns(); ++n) {
					if (n != numberInCell) {
						int index = indexInCoverMatrix(row, column, n);
						std::fill(coverMatrix[index].begin(), coverMatrix[index].end(), 0);
					}
				}
			}
		}
	}
	return coverMatrix;
}

bool DLXSolver::solveByCoverMatrix(FieldGrid<int>& matrix) {
	headerNode = createDLXList(matrix);
	return process(0);
}

bool DLXSolver::process(int stage) {
	if (headerNode->right == headerNode) {
		std::swap(answer, result);
		return true;
	}
	else {
		ColumnNode* column = chooseColumnWithMinimumSize();
		column->cover();
		for (DancingNode* node = column->bottom; node != column; node = node->bottom) {
			answer.push_back(node);
			for (DancingNode* j = node->right; j != node; j = j->right) {
				j->column->cover();
			}
			process(stage + 1);
			column = node->column;

			for (DancingNode* j = node->left; j != node; j = j->left) {
				j->column->uncover();
			}
		}
		column->uncover();
		return true;
	}
}

ColumnNode* DLXSolver::createDLXList(FieldGrid<int>& matrix) {
	vector<ColumnNode*> columnNodes;
	ColumnNode* header = new ColumnNode(std::string("header"));
	for (int i = 0; i < matrix.numberOfColumns(); ++i) {
		ColumnNode* column = new ColumnNode(std::to_string(i));
		columnNodes.push_back(column);
		header = static_cast<ColumnNode*>(header->linkRight(column));
	}
	header = header->right->column;
	for (auto& row : matrix) {
		DancingNode* previous = nullptr;
		for (int i = 0; i < matrix.numberOfColumns(); ++i) {
			if (row[i] == 1) {
				ColumnNode* column = columnNodes[i];
				DancingNode* newNode = new DancingNode(column);
				if (previous == nullptr) previous = newNode;
				column->top->linkDown(newNode);
				previous = previous->linkRight(newNode);
				++column->size;
			}
		}
	}
	header->size = matrix.numberOfColumns();
	return header;
}

ColumnNode* DLXSolver::chooseColumnWithMinimumSize() {
	
	ColumnNode* header = headerNode;
	ColumnNode* minColumn = headerNode->right->column;
	header = header->right->right->column;
	do {
		if (header->size < minColumn->size) {
			minColumn = header;
		}
		header = header->right->column;
	} while (header != headerNode);
	
	return minColumn;
}

void DLXSolver::convertFromDLXListToGrid(FieldGrid<int>& grid) {
	for (auto& n : result) {
		DancingNode* rcNode = n;
		int min = stoi(rcNode->column->name);

		for (DancingNode* tmp = n->right; tmp != n; tmp = tmp->right) {
			int val = std::stoi(tmp->column->name);
			if (val < min) {
				min = val;
				rcNode = tmp;
			}
		}
		int ans1 = std::stoi(rcNode->column->name);
		int ans2 = std::stoi(rcNode->right->column->name);
		int row = ans1 / size;
		int column = ans1 % size;
		int number = (ans2 % size) + 1;
		grid(row, column) = number;
	}
}