#pragma once

#include <vector>

template<typename ValueType>

class FieldGrid {
public:
	FieldGrid();
	FieldGrid(int, int);
	int numberOfRows() const;
	int numberOfColumns() const;
	void resize(int, int);
	ValueType get(int, int) const;
	ValueType operator[][](int, int);

private:
	std::vector<std::vector<ValueType>> grid;
};