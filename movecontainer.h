#ifndef MOVECONTAINER_H
#define MOVECONTAINER_H

#include <iostream>
#include <vector>

class MoveContainer{

	//structure to hold valid values for the square at position [row][col]
	
	private:

	int row;
	int col;

	std::vector<int> values;
	
	int move_counter;

	/////Constructors/////
	
	public:

	MoveContainer(){}

	MoveContainer(int row, int col, int dim);

	/////Public interface/////
	
	public:

	void reset();

	void add(int val);

	int getNumberOfMoves() const ;

	int getMoveRow() const;

	int getMoveCol() const ;

	int getMoveVal(int i) const ;

};

/////Output/////

std::ostream& operator<<(std::ostream& out, const MoveContainer& mc);

#endif
