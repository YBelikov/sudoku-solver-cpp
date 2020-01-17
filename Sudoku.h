#pragma once
#include <vector>

class Solver;

class Sudoku {
private:
	std::vector<std::vector<int>> gameField;
	int check(int width, int height);
	void showStartMessage();
	Solver *solver;
	InputStreamHandler* inputHandler;

public:
	Sudoku(int width_ = 0, int height_ = 0);
	void showSizeMessage();
	void determinateSource(int);
	int getFieldWidth() const { return gameField[0].size(); }
	int getFieldHeight() const { return gameField.size(); }
	void createGameField(int);
	void start();
	void solve();
	void showSolvedGame() const;

};