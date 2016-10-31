#pragma once

#include "stdafx.h"
#include <vector>
#include "SSudokuUtility.h"
#include "SSudokuCell.h"
#include "SSudokuBoard.h"
#include "SSudokuPuzzleMgr.h"
#include "SSudokuSerializer.h"
#include "SSudokuGenSolveEngine.h"
#include "SSudokuPuzzleMgr.h"

class CSudokuPuzzle
{
public:

	CSudokuPuzzle(ISSudokuSerializer &serializer);
	virtual ~CSudokuPuzzle();

	bool Initialize(ePuzzleType type);
	bool Generate(ePuzzleLevel level);
	ISSudokuBoard* GetBoard(void) { return mBoard; }
	bool LoadFromFile(std::string & file);
	ePuzzleLevel Rate();
	bool ResetBoard();
	bool Solve(void);
	bool Validate() const;
	
private:

	ISSudokuSerializer &mSerializer;
	ISSudokuBoard *mBoard;
	ePuzzleLevel mLevel;
};

	