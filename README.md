## About

This is a sudoku solver, using a simple heuristic search approach.

Coded by David Ouwehand. This program is released under the terms of the GNU General Public License.

## Algorithm

The basic parameter of the algorithm is N: the side of a small square. The entire board will have size N^2 x N^2, so N^4 squares in total. Each square can be given the values 1, 2, ..., N^2. Traditional sudoku corresponds to N=3.

The heuristic works as follows: Fix a square and count the number of values that can be filled in there. Do this for the N^4 squares, and then sort the squares by the number of available moves. 

Traversal of the search tree is depth-first. The square with the least number of available moves will be tried out first, then the square with the second least moves, etc. 

Memory footprint per node is O(N^6), since at most N^2 values can be stored for each of the N^4 squares. Since the search tree has depth N^4, the total memory consumption is O(N^10).


## TODO

* Combine heuristic search with a constraint solving algorithm (backtracking or backmarking).

* Make input more convenient (now hardcoded in sudoku.cpp).
