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

		//sort the elements in move_buffer by number of available moves
		//elements with the least number of moves go in front

		std::sort( move_buffer.begin(), move_buffer.end(), 
				
				[](MoveContainer mc1, MoveContainer mc2){
					return mc1.getNumberOfMoves() < mc2.getNumberOfMoves();
				}

		);

		for( auto mb_iter = move_buffer.begin(); mb_iter != move_buffer.end() && !solved; mb_iter++ ){

			//recurse over all the available moves in *mb_iter
					
			for(int j=0; j < mb_iter->getNumberOfMoves() && !solved; j++){
					
				Board updatedBoard = b;
				updatedBoard.setSquareValue(mb_iter->getMoveVal(j), mb_iter->getMoveRow(), mb_iter->getMoveCol());
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

		//solve an easy 9x9 sudoku

		std::vector<std::vector<int>> input = {{0,5,7,0,0,1,0,4,0},
			{0,0,6,0,0,0,2,7,0},
			{4,0,0,6,9,0,0,0,5},
			{8,0,0,4,0,0,3,0,1},
			{0,3,2,0,7,0,5,8,0},
			{1,0,5,0,0,6,0,0,2},
			{7,0,0,0,8,5,0,0,3},
			{0,9,3,0,0,0,6,0,0},
			{0,8,0,9,0,0,4,2,0}};

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
