#include "OutputStreamHandler.h"
#include "FieldGrid.h"
#include <iostream>
#include <fstream>

using std::string;
using std::cout;


void OutputStreamHandler::sayAboutSolvingError() {
	cout << "Can't solve this puzzle\n";
}

void OutputStreamHandler::showSuccessMessage() {
	cout << "Sudoku solved!\n";

}

void OutputStreamHandler::showResult(std::ostream& os, FieldGrid<int>& field) {
	for (auto& row : field) {
		for (auto& x : row) {
			os << x;
		}
		os << '\n';
	}
}

void OutputStreamHandler::writeResultInFile(FieldGrid<int>& field) {
	string name = askAboutFileName();
	std::ofstream ofs(name.c_str(), std::ofstream::out);
	showResult(ofs, field);
	ofs.close();
}

string OutputStreamHandler::askAboutFileName() {
	cout << "Now type name of file in which result will be saved\n";
	string fileName{};
	std::cin >> fileName;
	return fileName;
}