#pragma once
#include <ostream>
#include <string>

template<typename T>
class FieldGrid;


class OutputStreamHandler {
public:

	void sayAboutSolvingError();
	void showResult(std::ostream&, FieldGrid<int>&);
	void showSuccessMessage();
	void writeResultInFile(FieldGrid<int>&);
private:
	std::string askAboutFileName();
};