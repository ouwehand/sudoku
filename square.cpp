#include "square.h"

	/////Constructors/////
	
	Square::Square(){
		is_empty = true;
		value = 0;
	}

	Square::Square(int i){
		is_empty = false;
		value = i;
	}

	/////Public interface/////

	void Square::setValue(int i){
		value = i;
		is_empty = false;
		return;
	}

	int Square::getValue() const {
		if( is_empty ){
			std::cout << "Trying to get value of an empty square \n";
		}
		return value;
	}

	bool Square::isEmpty() const {
		return is_empty;
	}

	void Square::makeEmpty(){
		is_empty = true;
	}

	/////Output method/////
	
	std::ostream& operator<<(std::ostream& out, const Square& s){

		if( s.isEmpty() ){
			return out << "Empty";
		} else {
			return out << "Not empty, value = " << s.getValue();
		}
	}


