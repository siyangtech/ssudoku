#pragma once

#include "SSudokuUtility.h"
#include "SSudokuPuzzle.h"
#include "SSudokuSerializer.h"
#include <string>

class CSudokuPuzzle;

class CSudokuPuzzleMgr
{
public:
	CSudokuPuzzleMgr();
	~CSudokuPuzzleMgr();

	bool Initialize();
	bool Start();

private:
	CSudokuPuzzleMgr(const CSudokuPuzzleMgr &src) {}
	CSudokuPuzzleMgr& operator=(const CSudokuPuzzleMgr &src) {}

	void Cleanup();

	CDialogEx * mPuzzleDlg;
	CSudokuPuzzle *mPuzzle;
	ISSudokuSerializer *mSerializer;
	ePuzzleType mPuzzleType;
};