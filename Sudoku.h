#pragma once
#include <vector>
#include <memory>

class Solver;
class InputStreamHandler;
class OutputStreamHandler;

template<typename T>
class FieldGrid;

class Sudoku {

public:
	Sudoku(int width_ = 0, int height_ = 0);
	void showSizeMessage();
	void determinateSource(int);
	int getFieldWidth() const { return gameField.numberOfColumns(); }
	int getFieldHeight() const { return gameField.numberOfRows(); }
	void createGameField(int);
	void start();
	void solve();
	void showSolvedGame() const;

private:
	FieldGrid<int> gameField;
	int check(int width, int height);
	void showStartMessage();
	void makeOutputTo(int);
	std::unique_ptr<Solver> solver;
	std::unique_ptr<InputStreamHandler> inputHandler;
	std::unique_ptr<OutputStreamHandler> outputHandler;
};