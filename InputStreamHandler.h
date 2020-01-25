#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <istream>

template<typename T>
class FieldGrid;

class InputStreamHandler {
public:
	InputStreamHandler() = default;
	int getSizeInput();
	int getTypeOfSource();
	void fillField(FieldGrid<int>& field, std::istream& in);
	void openFieldFile(FieldGrid<int>& field);
	int getOutputTargetCode();
	bool restart();
	//void generateField();
private:
	int numberOfPossibleSources = 3;
	bool check();
	void showOptions();
	void showErrorMessage();
	void showSourceChoosingErrorMessage();
	bool openFile(const std::string&);
	void fileOpeningError(FieldGrid<int>&);
	void fillFieldFromFile(FieldGrid<int>&, std::ifstream& in);
};

