#include "Sudoku.h"
#include "InputStreamHandler.h"
#include "BackTrackingSolver.h"
#include <iostream>

Sudoku::Sudoku(int width_ = 0, int height_ = 0) {
	inputHandler = new InputStreamHandler;
	solver = new BackTrackingSolver;
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
}

void Sudoku::createGameField(int size) {
	gameField.resize(size);
	for (auto& x : gameField) {
		x.resize(size);
	}
}

void Sudoku::determinateSource(int sourceCode) {
	switch (sourceCode) {
		case 1:
			inputHandler->fillField(gameField, std::cin);
			break;
		case 2:
			inputHandler->openFieldFile();
			break;
		case 3:
			inputHandler->generateField(gameField);
			break;
		default:
			return;
	}
 }