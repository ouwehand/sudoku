## About

This is a sudoku solver, using a heuristic search and a simple pruning technique.

Coded by David Ouwehand. This program is released under the terms of the GNU General Public License.

## Algorithm

The basic parameter of the algorithm is N: the side of an "intermediate square" inside the sudoku board. The entire board will have size N^2 x N^2, so N^4 squares in total. Each square can be given the values 1, 2, ..., N^2. Traditional sudoku corresponds to N=3.

The heuristic works as follows: Fix a square and count the number of values that can be filled in there. Do this for the N^4 squares, and then sort the squares by the number of available moves. 

Traversal of the search tree is depth-first. The square with the least number of available moves will be tried out first, because we can expect that this leads to a solution more quickly.

At this stage we can also prune away all the other moves at the other squares (which have more moves). Indeed, we *must* plug in some value at the currently selected square (with the minimun number of available moves). If all of these values fail, then the current state of the sudoku admits no solution, and we can backtrack immediately.

## TODO

* Consider a more advanced constraint solving algorithm (backtracking or backmarking). How much can things be sped up?

* Make input more convenient (now hardcoded in sudoku.cpp).
