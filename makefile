CXXFLAGS = -Wall -O2 -std=c++11

sudoku: sudoku.o square.o movecontainer.o board.o
	$(CXX) -o $@ $^ 

square.o: square.h

movecontainer.o: movecontainer.h

board.o: board.h square.h

sudoku.o: sudoku.h board.h movecontainer.h

.PHONY: clean
clean:
	rm -rf *.o sudoku
