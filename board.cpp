#include "board.h"

	/////Constructors/////
	
	Board::Board(){}

	//in initialization list: invoke the fill constructor of 'vector'
	//each entry of 'squares' is a vector of length 'dim' whose entries are constructed with the default constructor of 'Square'

	Board::Board(int value) : N(value), dim(N*N), squares(dim, std::vector<Square>(dim)) {

		num_entries = 0;
		dim_square = dim*dim;
	}

	/////Public interface/////

	int Board::getDimension() const {
		return dim;
	}

	void Board::setSquareValue(int value, int row, int col){
		if(squares[row][col].isEmpty()){
			num_entries += 1;
		}
		squares[row][col].setValue(value);
		return;
	}

	/////Some true/false properties of the board and of individual squares/////

	bool Board::isEmptySquare(int row, int col) const {
		return squares[row][col].isEmpty();
	}

	bool Board::isFull() const {
		return (num_entries == dim_square);
	}

	bool Board::valueAppearsInRow(int value, int row) const {

		bool appears = false;

		for(int i=0 ; i < dim; i++){
			if( ! squares[row][i].isEmpty() ){
				if( squares[row][i].getValue() == value ){
					appears = true;
					break;
				}
			}
		}

		return appears;
	}

	bool Board::valueAppearsInCol(int value, int col) const{

		bool appears = false;

		for(int i=0 ; i < dim; i++){
			if( ! squares[i][col].isEmpty() ){
				if( squares[i][col].getValue() == value ){
					appears = true;
					break;
				}
			}
		}

		return appears;
	}

	bool Board::valueAppearsInSmallSquare(int value, int row, int col) const{
		
		bool appears = false;

		//get the coordinates of the small square
		int x = round(row);
		int y = round(col);

		for(int i=0 ; i < N; i++){
			for(int j=0 ; j < N; j++){
				if( ! squares[x + i][y + j].isEmpty() ){
					if( squares[x + i][y + j].getValue() == value ){
						appears = true;
						break;
					}
				}
			}
			if(appears == true){break;}
		}
		return appears;
	}

	int Board::round(int i) const{
		
		int res = i % N;
		return  i - res;
	}
	
	//A square is a valid move if it is empty and if 'value' doesn't conflict with other nonempty squares.
	bool Board::isValidMove(int value, int row, int col) const {

		bool valid = true;
		valid = squares[row][col].isEmpty();

		if(valid){
			valid = (! valueAppearsInRow(value, row) ); 
		}

		if(valid){
			valid = (! valueAppearsInCol(value, col) );
		}

		if(valid){
			valid = (! valueAppearsInSmallSquare(value, row, col) );
		}

		return valid;
	}

	//A square is valid if it is either empty or its value doesn't conflict with other nonempty squares.
	bool Board::isValidSquare(int row, int col, const Square& s) const {

		bool valid = true;

		if( ! s.isEmpty() ){

			int value = s.getValue();
			Board b = *this;
			b.makeSquareEmpty(row, col);
			valid = b.isValidMove(value, row, col);
		}
		return valid;
	}

	void Board::makeSquareEmpty(int row, int col){

		if(! squares[row][col].isEmpty() ){
			squares[row][col].makeEmpty();
			num_entries -= 1;
		}
	}

	bool Board::isValidBoard() const {
		bool valid = true;	

		for( int row=0; row < dim; row++ ){

			for ( int col=0; col < dim; col++){
					
				if ( ! isValidSquare(row, col, squares[row][col]) ){
					valid = false;
					break;
		
				}
			}

			if( ! valid ){break;}
		}

		return valid;
	}

	/////Input and output/////

	void Board::read(std::vector<std::vector<int>>& s){

		for(int i = 0 ; i < dim ; i++) {
			for(int j = 0 ; j < dim ; j++) {
				if( s[i][j] == 0 ){
					makeSquareEmpty(i, j);
				} else {
					setSquareValue(s[i][j], i, j);
				}
			}
		}
		return;
	}

	std::string Board::toString() const{
		
		std::stringstream s;

		for( int row=0; row < dim; row++ ){

			for ( int col=0; col < dim; col++){
					
				if( squares[row][col].isEmpty() ) {
					s << " - ";
				}
				else {
					s << ' ' << squares[row][col].getValue() << ' ';
				}
			}

			s << '\n';
		}

		return s.str();
	}

	std::ostream& operator<<(std::ostream& out, const Board& b){
		return out << b.toString();
	}
