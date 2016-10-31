#include "stdafx.h"
#include "SSudokuUtility.h"

LPCTSTR sPuzzleTypeString[MAX_PUZZLE_TYPE + 1] = {
	L"9x9 Puzzle"
};

LPCTSTR PuzzleTypeString(ePuzzleType type)
{
	return sPuzzleTypeString[type];
}

