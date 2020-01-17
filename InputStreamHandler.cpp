#include "InputStreamHandler.h"

using std::cout;
using std::cin;
using std::vector;
using std::istream;

int InputStreamHandler::getSizeInput() {
	cout << "Hello, user!\n" << "Now you should say me grid of which size would you like to solve: ";
	int size{};
	cin >> size;
	if (size <= 0) {
		showErrorMessage();
	}
	return size;
}

int InputStreamHandler::getTypeOfSource() {
	
	cout << "You have 3 options of input: \n"
		<< "\t1.Console\n" << "\t 2.File\n" << "\t 3.Random generated grid\n";
	int source{};
	cin >> source;
	if (source <= 0 || source > numberOfPossibleSources) {
		showSourceChoosingErrorMessage();
	}
	return source;
}

void InputStreamHandler::fillField(vector<vector<int>>& field, istream& in) {
	
	for (auto& row : field) {
		std::istream_iterator<int> eos;
		std::istream_iterator<int> it(in);
		while (it != eos) {
			row.push_back(*it);
		}
	}
}

void InputStreamHandler::showErrorMessage() {
	std::cout << "Error! Size should be postive number! Try again\n";
	getSizeInput();
}

void InputStreamHandler::showSourceChoosingErrorMessage() {
	cout << "Error!\n" << "You have only " << numberOfPossibleSources << " choices\n"
		"Try again\n";
	getTypeOfSource();
}