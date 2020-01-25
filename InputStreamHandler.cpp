#include "InputStreamHandler.h"
#include <fstream>
#include "FieldGrid.h"

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
		<< "\t1.Console\n" << "\t2.File\n" << "\t3.Random generated grid\n";
	int source{};
	cin >> source;
	if (source <= 0 || source > numberOfPossibleSources) {
		showSourceChoosingErrorMessage();
	}
	return source;
}

void InputStreamHandler::fillField(FieldGrid<int>& field, istream& in) {
	for (auto& row : field) {
		for (auto& x : row) {
			in >> x;
		}
	}
}

void InputStreamHandler::showErrorMessage() {
	std::cout << "Error! Size should be positive number! Try again\n";
	getSizeInput();
}

void InputStreamHandler::showSourceChoosingErrorMessage() {
	cout << "Error!\n" << "You have only " << numberOfPossibleSources << " choices\n"
		"Try again\n";
	getTypeOfSource();
}

void InputStreamHandler::openFieldFile(FieldGrid<int>& field) {
	cout << "Ok, now you should type name of file, you'd like to use as starting field: \n";
	std::string fieldFile{};
	cin >> fieldFile;
	std::ifstream in(fieldFile.c_str());
	if (!in)
		fileOpeningError(field);
	else
		fillFieldFromFile(field, in);

}

void InputStreamHandler::fileOpeningError(FieldGrid<int>& field) {
	cout << "Opening file error\nTry again!";
	openFieldFile(field);
}

void InputStreamHandler::fillFieldFromFile(FieldGrid<int>& field, std::ifstream& in) {
	for (auto& row : field) {
		for (auto& x : row) {
			in >> x;
		}
	}
		in.close();
}

int InputStreamHandler::getOutputTargetCode() {
	cout << "Now you have 2 options of output:\n1. Console\n2. File\n";
	int code{};
	cin >> code;
	return code;
}

bool InputStreamHandler::restart() {
	cout << "Would you like to solve more sudoku? Type Y to continue and N for exit\n";
	char answer{};
	cin >> answer;
	return answer == 'Y';
}