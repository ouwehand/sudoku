#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>

class Square{
	
	private:

	bool is_empty;
	int value;

	/////Constructors/////
	
	public:

	Square();

	Square(int i);

	/////Public interface/////
	
	public:

	void setValue(int i);

	int getValue() const;

	bool isEmpty() const;

	void makeEmpty();

};

/////Output/////

std::ostream& operator<<(std::ostream& out, const Square& s);

#endif
