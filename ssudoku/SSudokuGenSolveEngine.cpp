#include "stdafx.h"
#include "SSudokuGenSolveEngine.h"

bool CSudokuGenSolveEngine::Generate(ISSudokuBoard & board, ePuzzleLevel level)
{
	bool result = false;
	if (level == LEVEL_NONE) {
		return false;
	}

	board.ClearBoard();

	// Create terminal template
	for (int i = 0; i < NUM_TIMES_TO_TRY; i++) {
		if (_create_template(board, level) == true) {
			if (_dig_holes(board, level) == true) {
				result = true;
				break;
			}
		}
	}
	return result;
}

int CSudokuGenSolveEngine::Solve(ISSudokuBoard & board)
{
	int numSolution = 0;
	int nIter = 0;
	_solve(board, numSolution, nIter, true);

	if (numSolution > 0) {
		int numSolution2 = 0;
		nIter = 0;
		if (_solve(board, numSolution2, nIter, false) == false) {
			return numSolution2;
		}
		TRACE(traceAppMsg, 0, "numIter=%d\n", nIter);
	}
	return numSolution;
}

bool CSudokuGenSolveEngine::Validate(const ISSudokuBoard & board)
{
	return board.IsValid();
}

bool CSudokuGenSolveEngine::_create_template(ISSudokuBoard &board, ePuzzleLevel level)
{
	bool result = false;

	if (level == LEVEL_NONE) {
		return false;
	}

	// generate template with fixed givens
	int numGivens = GENERATE_NUM_GIVENS;
	std::vector< int > givens;

	// get current time, use it as rand() seed
	DWORD after, before = GetTickCount();

	srand((unsigned int)before); 

	while (true) {
		// generate random given cell index
		for (int i = 0; i < numGivens; i++) {
			int temp = rand() % (board.GetNumCells());
			givens.push_back(temp);
		}
		int numS = 0;
		int nIter = 0;
		if (_generate_givens(board, givens, 0) == true) {
			if (_solve(board, numS, nIter, false) == true) {
				result = true;
				break;
			}
		}

		after = GetTickCount();
		if ((after - before) > GENERATE_GIVENS_TIMER) {
			result = false;
			break;
		}

		// try another time
		board.ClearBoard();
	}

	return result;
}

bool CSudokuGenSolveEngine::_dig_holes(ISSudokuBoard &board, ePuzzleLevel level)
{
	bool result = true;
	if (level == LEVEL_NONE) {
		return false;
	}

	// number of holes
	int numGivens = rand() % (board.GetGivenBoundary((ePuzzleLevel)((int)level - 1)) - board.GetGivenBoundary(level)) + board.GetGivenBoundary(level);
	int numHoles = board.GetNumCells() - numGivens;

	// determine sequence of digging holes
	eSequenceOfDigging seq = SEQ_RANDOM;
	switch (level) {
	case LEVEL_EASY:
		seq = SEQ_RANDOM;
		break;
	case LEVEL_MEDIUM:
		seq = SEQ_JUMPING_ONE;
		break;
	case LEVEL_DIFFICULT:
		seq = SEQ_S;
		break;
	case LEVEL_EVIL:
		seq = SEQ_LR_TB;
		break;
	default:
		return false;
	}
	
	// dig numHoles holes
	int cur_idx = -1;
	int next_idx = -1;
	int vcount = 0;
	int ucount = 0;
	while ((board.CountDiggable() >= numHoles) && 
		   _get_next_hole(board, seq, cur_idx, next_idx) ) {
		
		// check restriction
		if (!_violate_restriction(board, level, next_idx)) {
			// check uniqueness
			if (_has_unique_solution(board, next_idx)) {
				int preVal;
				if (board.DigCell(next_idx, preVal)) {
					board.SetDiggable(next_idx, false);
					if (--numHoles == 0) {
						break;
					}
				}
			}
			else {
				board.SetDiggable(next_idx, false);
				ucount++;
			}
		}
		else {
			board.SetDiggable(next_idx, false);
			vcount++;
		}
		cur_idx = next_idx;
		if (level >= LEVEL_MEDIUM && numHoles < 10) {
			seq = SEQ_LR_TB;
		}
		TRACE(traceAppMsg, 0, "numHoles=%d countDiggable=%d ucount=%d vcount=%d\n", 
			numHoles, board.CountDiggable(), ucount, vcount);
	}

	if (numHoles == 0) {
		_propagate(board);
		board.Prun();
		return true;
	}
	else {
		return false;
	}
}

bool CSudokuGenSolveEngine::_get_next_hole(ISSudokuBoard & board, eSequenceOfDigging seq, const int & cur_idx, int & next_idx)
{
	bool result = false;
	int row, col;
	switch (seq) {
	case SEQ_LR_TB:
		// find next diggable one
		if (cur_idx < 0) {
			next_idx = 0;
			return true;
		}
		next_idx = cur_idx + 1;
		while (next_idx < board.GetNumCells()) {
			if (board.IsDiggable(next_idx)) {
				return true;
			}
			next_idx++;
		}
		// Reached the end, restart with next available cell from beginning
		for (int i = 0; i < board.GetNumCells(); i++) {
			if (board.IsDiggable(i)) {
				next_idx = i;
				return true;
			}
		}
		return false;
	case SEQ_S:
		if (cur_idx < 0) {
			next_idx = 0;
			return true;
		}
		next_idx = cur_idx;
		do {
			row = next_idx / board.GetBoardSize();
			col = next_idx % board.GetBoardSize();
			// find next diggable one
			if ((row % 2) == 0) { // even row
				if (col < board.GetBoardSize()) {
					// move right
					next_idx++;
				}
				else {
					// move down
					next_idx += board.GetBoardSize();
				}
			}
			else {
				if (col > 0) {
					// move left
					next_idx--;
				}
				else {
					next_idx += board.GetBoardSize();
				}
			}
			if (board.IsDiggable(next_idx)) {
				return true;
			}
		} while (next_idx < board.GetNumCells());

		// Reached the end, restart with next available cell from beginning
		for (int i = 0; i < board.GetNumCells(); i++) {
			if (board.IsDiggable(i)) {
				next_idx = i;
				return true;
			}
		}
		return false;
	case SEQ_JUMPING_ONE:
		if (cur_idx < 0) {
			next_idx = 0;
			return true;
		}
		next_idx = cur_idx;
		do {
			row = next_idx / board.GetBoardSize();
			col = next_idx - row * board.GetBoardSize();
			// find next diggable one
			if ((row % 2) == 0) { // even row
				if (col < (board.GetBoardSize() - 1)) {
					// move right two
					next_idx += 2;
				}
				else {
					// move down, left
					next_idx += board.GetBoardSize();
					next_idx--;
				}
			}
			else { // odd row
				if (col > 1) {
					// move left
					next_idx -= 2;
				}
				else {
					// move down left
					next_idx += board.GetBoardSize();
					next_idx--;
				}
			}
			if (board.IsDiggable(next_idx)) {
				return true;
			}
		} while (next_idx < board.GetNumCells());

		// Reached the end, restart with next available cell from beginning
		for (int i = 0; i < board.GetNumCells(); i++) {
			if (board.IsDiggable(i)) {
				next_idx = i;
				return true;
			}
		}
		return false;
	case SEQ_RANDOM:
		while (board.CountDiggable()) {
			next_idx = rand() % board.GetNumCells();
			if (board.IsDiggable(next_idx)) {
				return true;
			}
		}
		return false;
	default:
		return false;
	}
	return result;
}

bool CSudokuGenSolveEngine::_generate_givens(ISSudokuBoard & board, std::vector< int > &givens, int pos)
{
	if (pos >= givens.size()) {
		return true;
	}

	int idx = givens[pos];
	ISSudokuBoard *board2 = board.Duplicate();
	if (board2 == NULL) {
		return false;
	}

	bool result = false;

	// start time
	DWORD after, before = GetTickCount();
	while (true) {
		// randomly choose a digits
		int i = rand() % board.GetBoardSize();
		if (board.IsPossible(idx, i)) {
			board2->Copy(board);
			if (board2->Assign(idx, i)) {
				if (_generate_givens(*board2, givens, pos + 1) == true) {
					board.Copy(*board2);
					result = true;
					break;
				}
			}
		}
		after = GetTickCount();
		if ((after - before) > 100) { // abount 100 millisecond
			break;
		}
	}

	if (board2) {
		delete board2;
	}

	return result;
}

bool CSudokuGenSolveEngine::_has_unique_solution(ISSudokuBoard &board, const int & index)
{
	int preVal;
	bool result = true;

	ISSudokuBoard *l_board = board.Duplicate();
	if (l_board == NULL) {
		return false;
	}
	
	if (l_board->DigCell(index, preVal)) {
		l_board->Prun();
		int numS = 0;
		int nIter = 0;
		if (_solve(*l_board, numS, nIter, true) == true) {
			if (numS > 1) {
				result = false;
			}
		}
		else {
			result = false;
		}
	}
	else {
		result = false;
	}

	if (l_board) {
		delete l_board;
	}
	return result;
}

bool CSudokuGenSolveEngine::_propagate(ISSudokuBoard & board)
{
	board.Propagate(PROPG_SWITCH_DIGIT);
	board.Propagate(PROPG_SWITCH_COL);
	return true;
}

bool CSudokuGenSolveEngine::_solve(ISSudokuBoard & board, int & numSolution, int &nIter, const bool & checkUnique)
{
	if (board.IsSolved()) {
		numSolution++;
		return true;
	}

	nIter++;

	int idx = board.LeastCount();
	if (idx == -1) {
		// all cells are filled, but not valid
		return false;
	}

	ISSudokuBoard *board2 = board.Duplicate();
	if (board2 == NULL) {
		return false;
	}
	for (int i = 0; i < board.GetBoardSize(); i++) {
		if (board.IsPossible(idx, i)) {
			board2->Copy(board);
			if (board2->Assign(idx, i) == true) {
				if (_solve(*board2, numSolution, nIter, checkUnique) == true) {
					if (!checkUnique) {
						board.Copy(*board2);
						delete board2;
						return true;
					}
				}
			}
		}
	}
	if (board2) {
		delete board2;
	}
	return false;
}

bool CSudokuGenSolveEngine::_violate_restriction(ISSudokuBoard & board, ePuzzleLevel level, const int & next_idx)
{
	return board.ViolateLowerUnitBoundary(next_idx, level);
}
