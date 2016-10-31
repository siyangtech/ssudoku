#pragma once
#include "stdafx.h"
#include "ISSudokuGame.h"
#include <vector>
#include "SSudokuCell.h"


class SSudokuSerializerText;
class SSudokuGenerator;

class SSudokuGame : public ISSudokuGame
{
	friend class SSudokuSerializerText;
	friend class SSudokuGenerator;
public:
	SSudokuGame(const int &rowSz, const int &colSz);
	virtual ~SSudokuGame();

	static void Initialize();
	
	virtual int Read(const std::vector< std::string > &content);
	virtual int Solve();
	virtual int Check() const;
	virtual int Generate();
	virtual int Rate(int &level) const;
	virtual char GetCell(const int & r, const int & c) const;
	virtual int SetCell(const int & r, const int & c, const char &val);
	virtual int GetRowSize() const { return mRowSz; }
	virtual int GetColSize() const { return mColSz; }
	
private:
	
	enum SudokuLevel {
		LEVEL_NONE,
		LEVEL_EXTREMELY_EASY,
		LEVEL_EASY,
		LEVEL_MEDIUM,
		LEVEL_DIFFICULT,
		LEVEL_EVIL
	};

	bool Assign(const int & index, const int & val, std::vector< SSudokuCell > &cells);
	void CopyCells(std::vector< SSudokuCell > &cell_src, std::vector< SSudokuCell > &cell_dst);
	bool CreateTerminalPattern(std::vector< SSudokuCell > &cells);
	bool Eliminate(const int & index, const int & val, std::vector< SSudokuCell > &cells);
	bool IsSolved(const std::vector< SSudokuCell > &cells) const;
	int  LeastCount(const std::vector< SSudokuCell > &cells) const;

	bool SolveF(std::vector< SSudokuCell > &cells);
	bool BackTracking(std::vector< SSudokuCell > &cells, std::vector< int > &givens, int pos);
	
	std::vector< SSudokuCell > mOrigCells;
	std::vector< SSudokuCell > mCells;
	bool mSolved;
	SudokuLevel mLevel;

	static std::string gDigits9;
	static std::vector< std::vector<int> > gUnits9;
	static std::vector< std::vector<int> > gPeers9;
	static std::vector< std::vector<int> > gUnitsOfCell9;

	int mRowSz;
	int mColSz;
};

	