#include "movecontainer.h"

	/////Constructors/////
	
	MoveContainer::MoveContainer(int row, int col, int dim): 
	values(dim, 0)
	{
		this->row = row;
		this->col = col;
		move_counter = 0;
	}

	/////Public interface/////

	void MoveContainer::reset(){
		move_counter = 0;
		return;
	}

	void MoveContainer::add(int val){
		values[move_counter] = val;
		move_counter += 1;
		return;
	}

	int MoveContainer::getNumberOfMoves() const {
		return move_counter;
	}

	int MoveContainer::getMoveRow() const {
		return row;
	}

	int MoveContainer::getMoveCol() const {
		return col;
	}

	int MoveContainer::getMoveVal(int i) const {
		return values[i];
	}

/////Output/////

std::ostream& operator<<(std::ostream& out, const MoveContainer& mc){
		
	out << "row, col = " << mc.getMoveRow() << ", " << mc.getMoveCol() << ": ";
	int number_of_moves = mc.getNumberOfMoves();

	if (number_of_moves == 0){

		out<< "Empty";

	} else {

		for( int i = 0; i < number_of_moves; i++ ){
					
			out << mc.getMoveVal(i) << " ";
		}
	}
	return out;
}
