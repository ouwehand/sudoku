//    Copyright (C) 2017  David Ouwehand
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "sudoku.h"
	
	//Some global variables and a helper function

	static bool solved;
	static int dim;
	static Board solvedBoard;

	Board sudokuSolver(const Board& init){
		
		dim = init.getDimension();
		solved = false;

		solvePuzzle(init);
		
		//Note: there is no mechanism to test whether 'init' is a solvable board
		//If 'init' is not solvable then 'solvedBoard' will just be the instance of 'Board' that's initialized with the default constructor
		return solvedBoard;
	}
	
	static void solvePuzzle(const Board& b){

		std::vector<MoveContainer> move_buffer;

		//If the board is solved then we are done
		if( b.isFull()) { 	
			solvedBoard = b;
			solved = true;
			return;
		}
		
		//Compute all the valid moves

		computeValidMoves(b, move_buffer);

		//find the element in move_buffer with the
		//minimal nonzero number of available moves
		//(if there are any moves left at all)
		
		bool moves_left = false;
		int min_moves = std::numeric_limits<int>::max();
		int min_moves_index = 0;

		for(size_t i=0; i < move_buffer.size(); i++){
			int num_moves = move_buffer[i].getNumberOfMoves();

			if(num_moves > 0 && num_moves < min_moves){
				moves_left = true;
				min_moves = num_moves;
				min_moves_index = i;
			}
		}

		//try out all available values at the square
		//with the least number of available moves
		
		if(moves_left){
			
			int row = move_buffer[min_moves_index].getMoveRow();
			int col = move_buffer[min_moves_index].getMoveCol();

			for(int j=0; j < min_moves && !solved; j++){

				Board updatedBoard = b;
				updatedBoard.setSquareValue(move_buffer[min_moves_index].getMoveVal(j), row, col);
				solvePuzzle(updatedBoard);
			}
		} 
		return;
	}


	//gets a list of available moves
	static void computeValidMoves(const Board& b, std::vector<MoveContainer>& move_buffer){
		
		move_buffer.clear();
		move_buffer.reserve(dim*dim);

		for( int row = 0; row < dim; row++ ){
			for( int col = 0; col < dim; col++ ){
				move_buffer.emplace_back(row, col, dim);
			}
		}

		for( auto mb_iter = move_buffer.begin(); mb_iter != move_buffer.end() ; mb_iter++ ){

			for( int value = 1; value <= dim; value++ ){

				if( b.isValidMove(value, mb_iter->getMoveRow(), mb_iter->getMoveCol()) ){

					mb_iter->add(value);
				}
			}
		}

		return;
	}


	static void test1(){

		//solve an empty 4x4 board

		Board b(2);
		b = sudokuSolver(b);
		std::cout << b;
		std::cout << b.isValidBoard() << '\n';
		return;
	}

	static void test2(){

		//solve a 9x9 sudoku

		std::vector<std::vector<int>> input = 
			{{8,0,3,0,2,9,7,1,6},
			{0,0,6,0,1,8,5,0,4},
			{0,0,0,0,6,0,0,0,8},
			{0,0,5,0,4,6,0,8,0},
			{7,0,9,0,3,5,6,4,2},
			{0,6,0,0,9,0,1,0,5},
			{6,0,0,0,7,0,0,5,1},
			{0,0,1,6,5,0,8,0,0},
			{5,0,0,9,8,1,4,6,3}};

		Board b(3);
		b.read(input);
		if(! b.isValidBoard()){
			std::cout << "Input board is not valid\n";
		}

		std::cout << b << "\n\n";

		b = sudokuSolver(b);
		std::cout << b;
		std::cout << b.isValidBoard() << '\n';
		return;
	}
	

	int main(int argc, char** argv){
		
		test2();
		return 0;
	} 
