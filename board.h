#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <sstream>
#include <vector>
#include "square.h"

class Board{
	
	private:

	int N;
	int dim;
	int dim_square;

	std::vector<std::vector<Square>> squares;

	int num_entries;

	/////Constructors/////
	
	public:

	Board();

	Board(int value);

	/////Public interface/////
	
	public:

	int getDimension() const;

	void setSquareValue(int value, int row, int col);

	/////Some true/false properties of the board and of individual squares/////

	bool isEmptySquare(int row, int col) const;

	bool isFull() const;

	bool valueAppearsInRow(int value, int row) const;

	bool valueAppearsInCol(int value, int col) const;

	bool valueAppearsInSmallSquare(int value, int row, int col) const;
	
	bool isValidMove(int value, int row, int col) const;

	bool isValidBoard() const;

	/////Internal methods/////
	
	private:

	int round(int i) const;

	bool isValidSquare(int row, int col, const Square& s) const;

	void makeSquareEmpty(int row, int col);

	/////Input and output/////
	
	public:

	void read(std::vector<std::vector<int>>& s);

	std::string toString() const;

};

std::ostream& operator<<(std::ostream& out, const Board& b);


#endif
