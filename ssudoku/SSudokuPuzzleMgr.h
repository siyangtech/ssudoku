#pragma once

#include "SSudokuUtility.h"
#include "SSudokuPuzzle.h"
#include "SSudokuSerializer.h"
#include <string>

class CSudokuPuzzle;

class CSudokuPuzzleMgr
{
public:
	explicit CSudokuPuzzleMgr();
	~CSudokuPuzzleMgr();

	bool Initialize();
	bool Start();

private:
	void Cleanup();

	CDialogEx * mPuzzleDlg;
	CSudokuPuzzle *mPuzzle;
	ISSudokuSerializer *mSerializer;
	ePuzzleType mPuzzleType;
};