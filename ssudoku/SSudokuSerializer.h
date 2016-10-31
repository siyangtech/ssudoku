#pragma once

#include "SSudokuBoard.h"

class ISSudokuSerializer
{
public:
	virtual ~ISSudokuSerializer() {}

	virtual bool FileToBoard(const std::string & name, ISSudokuBoard &board) = 0;
	virtual bool BoardToFile(const std::string & name, const ISSudokuBoard &board) = 0;

};

class CSudokuPuzzleMgr;

class CSudokuSerializerText : public ISSudokuSerializer
{
public:
	explicit CSudokuSerializerText(CSudokuPuzzleMgr *mgr) : mMgr(mgr) {}
	~CSudokuSerializerText(){}

	virtual bool FileToBoard(const std::string & name, ISSudokuBoard &board);
	virtual bool BoardToFile(const std::string & name, const ISSudokuBoard &board);

private:

	CSudokuPuzzleMgr *mMgr;
};