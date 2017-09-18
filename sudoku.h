#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "board.h"
#include "movecontainer.h"

Board sudokuSolver(const Board& init);
static void solvePuzzle(const Board& b);
static void computeValidMoves(const Board& b, std::vector<MoveContainer>& move_buffer);

#endif
