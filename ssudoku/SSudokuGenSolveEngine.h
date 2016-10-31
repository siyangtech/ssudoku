#pragma once

#include "SSudokuUtility.h"
#include "SSudokuBoard.h"
#include "SSudokuCell.h"
#include "SSudokuPuzzle.h"

class CSudokuGenSolveEngine
{
private:
	bool _create_template(ISSudokuBoard &board, ePuzzleLevel level);
	bool _dig_holes(ISSudokuBoard &board, ePuzzleLevel level);
	bool _generate_givens(ISSudokuBoard & board, std::vector< int > &givens, int pos);
	bool _get_next_hole(ISSudokuBoard & board, eSequenceOfDigging seq, const int & cur_idx, int & next_idx);
	bool _has_unique_solution(ISSudokuBoard &board, const int & index);
	bool _propagate(ISSudokuBoard & board);
	bool _solve(ISSudokuBoard & board);
	bool _violate_restriction(ISSudokuBoard & board, ePuzzleLevel level, const int & next_idx);

public:

	CSudokuGenSolveEngine() {}
	~CSudokuGenSolveEngine() {}

	bool Generate(ISSudokuBoard & board, ePuzzleLevel level);
	int Solve(ISSudokuBoard & board);
	bool Validate(const ISSudokuBoard & board);
};

