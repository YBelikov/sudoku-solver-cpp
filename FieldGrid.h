#pragma once

#include <vector>

using std::vector;

template<typename ValueType>
class FieldGrid {
public:

	using const_iterator = typename vector<vector<ValueType>>::const_iterator;
	using iterator = typename vector<vector<ValueType>>::iterator;

	FieldGrid();
	FieldGrid(int, int);
	int numberOfRows() const;
	int numberOfColumns() const;
	void resize(int, int);
	void resize(int);
	ValueType& operator()(int, int);
	iterator begin() { return grid.begin(); }
	iterator end() { return grid.end(); }
	const_iterator cbegin() const { return grid.cbegin(); }
	const_iterator cend() const { return grid.cend(); }

private:
	vector<vector<ValueType>> grid;
};

template<typename ValueType>
FieldGrid<ValueType>::FieldGrid() {

}

template<typename ValueType>
FieldGrid<ValueType>::FieldGrid(int rows, int columns) {
	for (int i : rows) {
		grid.push_back(vector<ValueType>(columns));
	}
}

template<typename ValueType>
void FieldGrid<ValueType>::resize(int rows, int columns) {
	grid.resize(rows);
	for (auto& row : grid) {
		row.resize(columns);
	}
}

template<typename ValueType>
void FieldGrid<ValueType>::resize(int size) {
	grid.resize(size);
	for (auto& row : grid) {
		row.resize(size);
	}
}

template<typename ValueType>
ValueType& FieldGrid<ValueType>::operator()(int row, int column){
	return grid[row][column];
}

template<typename ValueType>
int FieldGrid<ValueType>::numberOfColumns() const {
	return grid[0].size();
}

template<typename ValueType>
int FieldGrid<ValueType>::numberOfRows() const {
	return grid.size();
}





