#include "Sudoku.h"
#include "InputStreamHandler.h"
#include "BackTrackingSolver.h"
#include "OutputStreamHandler.h"
#include "FieldGrid.h"

#include <iostream>

Sudoku::Sudoku(int width_, int height_ ) {
	inputHandler = std::make_unique<InputStreamHandler>();
	solver = std::make_unique<BackTrackingSolver>();

}

void Sudoku::start() {
	showSizeMessage();
	showStartMessage();
}

void Sudoku::showSizeMessage() {
	int size = inputHandler->getSizeInput();
	createGameField(size);
}

void Sudoku::showStartMessage() {	
	int typeOfSource = inputHandler->getTypeOfSource();
	determinateSource(typeOfSource);
	solve();
}

void Sudoku::createGameField(int size) {
	gameField.resize(size);
}

void Sudoku::determinateSource(int sourceCode) {
	switch (sourceCode) {
		case 1:
			std::cout << "Here\n";
			inputHandler->fillField(gameField, std::cin);
			break;
		case 2:
			inputHandler->openFieldFile(gameField);
			break;
		case 3:
			//inputHandler->generateField(gameField);
			//it would be better to use field generator directly in this case
			break;
		default:
			return;
	}
 }

void Sudoku::solve() {
	outputHandler = std::make_unique<OutputStreamHandler>();
	if (!solver->solve(gameField)) outputHandler->sayAboutSolvingError();
	else {
		outputHandler->showSuccessMessage();
		int code = inputHandler->getOutputTargetCode();
		makeOutputTo(code);
	}
	if (inputHandler->restart()) start();
	else return;
}

void Sudoku::makeOutputTo(int code) {
	switch (code) {
	
	case 1: 
		outputHandler->showResult(std::cout, gameField);
		break;
	case 2:
		outputHandler->writeResultInFile(gameField);
	}
}