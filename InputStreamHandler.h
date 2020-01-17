#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <istream>

class InputStreamHandler {
public:
	InputStreamHandler() = default;
	int getSizeInput();
	int getTypeOfSource();
	void fillField(std::vector<std::vector<int>>& field, std::istream& in);

private:
	int numberOfPossibleSources = 3;
	bool check();
	void showOptions();
	void showErrorMessage();
	void showSourceChoosingErrorMessage();
};

