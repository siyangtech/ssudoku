#pragma once
#include "SSudokuUtility.h"
#include "SSudokuCell.h"
#include <string>
#include <vector>

class ISSudokuBoard
{
public:
	virtual ~ISSudokuBoard() {}
	virtual bool Assign(const int & index, const int & val) = 0;
	virtual void ClearBoard(void) = 0;
	virtual void Copy(const ISSudokuBoard &board) = 0;
	virtual int CountDiggable(void) = 0;
	virtual bool DigCell(const int & index, int & preVal) = 0;
	virtual bool Eliminate(const int & index, const int & val) = 0;
	virtual ISSudokuBoard* Duplicate() = 0;
	virtual CString GetCell(const int &row, const int &col, bool isGiven) const = 0;
	virtual int GetBoardSize(void) const = 0;
	virtual int GetGivenBoundary(ePuzzleLevel level) const = 0; 
	virtual int GetLowerBoundaryPerUnit(ePuzzleLevel level) const = 0; 
	virtual eSequenceOfDigging GetPuzzleDigPattern(ePuzzleLevel level) const = 0;
	virtual int GetNumCells(void) const = 0;
	virtual bool IsDiggable(const int & index) const = 0;
	virtual bool IsFilled(const int & index) const = 0;
	virtual bool IsGiven(const int & index) const = 0;
	virtual bool IsLoaded() const = 0;
	virtual bool Initialize(void) = 0;
	virtual bool IsPossible(const int & index, const int & val) const = 0;
	virtual bool IsSolved(void) const = 0;
	virtual bool IsValid(void) const = 0;
	virtual int  LeastCount(void) const = 0;
	virtual bool LoadBoard(const std::string &content) = 0;
	virtual void Propagate(ePropagateType type) = 0;
	virtual void Prun(void) = 0;
	virtual ePuzzleLevel Rate(void) = 0;
	virtual void SetGiven(const int & index, bool given) = 0;
	virtual void SetDiggable(const int & index, bool diggabe) = 0;
	virtual bool SetVal(const int & index, const int & val) = 0;
	virtual bool ViolateLowerUnitBoundary(const int & index, const ePuzzleLevel & level) const = 0;
};

class CSudokuBoard9x9 : ISSudokuBoard
{
private:
	static const byte CSudokuBoard9x9::gBoardSize = 9;
	static const byte CSudokuBoard9x9::gNumUnits = 27; // 9*3
	static const byte CSudokuBoard9x9::gNumCells = 81; // 9*9
	static const byte CSudokuBoard9x9::gNumPeers = 81; // 9*9
	static const byte CSudokuBoard9x9::gNumUnitsOfCell = 3;
	static const std::string CSudokuBoard9x9::gDigits;

	static std::vector< std::vector<int> > gUnits;
	static std::vector< std::vector<int> > gPeers;
	static std::vector< std::vector<int> > gUnitsOfCell;
	static bool gInitialized;
	static int gPuzzleGivenBoundary[MAX_PUZZLE_LEVEL + 1];
	static int gPuzzleLowerBoundaryPerUnit[MAX_PUZZLE_LEVEL + 1];
	static eSequenceOfDigging gPuzzleDigPattern[MAX_PUZZLE_LEVEL + 1];

	enum sState {
		sUninitialized,
		sInitialized,
		sLoaded,
		sSolved
	};

	CSudokuCell **mCellsP;
	sState mState;

	void ChangeState(sState newState);

public:

	CSudokuBoard9x9();
	virtual ~CSudokuBoard9x9();

	CSudokuBoard9x9(const CSudokuBoard9x9 &src);
	CSudokuBoard9x9& operator=(const CSudokuBoard9x9 &src);

	virtual bool Assign(const int & index, const int & val);
	virtual void ClearBoard(void); 
	virtual void Copy(const ISSudokuBoard &board);
	virtual int CountDiggable(void);
	virtual bool DigCell(const int & index, int & preVal);
	virtual bool Eliminate(const int & index, const int & val);
	virtual ISSudokuBoard* Duplicate();
	virtual CString GetCell(const int &row, const int &col, bool isGiven) const;
	virtual int GetBoardSize(void) const { return gBoardSize; }
	virtual int GetGivenBoundary(ePuzzleLevel level) const { return gPuzzleGivenBoundary[level]; }
	virtual int GetLowerBoundaryPerUnit(ePuzzleLevel level) const {
		return gPuzzleLowerBoundaryPerUnit[level];
	}
	virtual eSequenceOfDigging GetPuzzleDigPattern(ePuzzleLevel level) const {
		return gPuzzleDigPattern[level];
	}
	virtual int GetNumCells(void) const { return gNumCells; }
	virtual bool Initialize(void);
	virtual bool IsDiggable(const int & index) const;
	virtual bool IsFilled(const int & index) const;
	virtual bool IsGiven(const int & index) const;
	virtual bool IsLoaded(void) const { return (mState == sLoaded); }
	virtual bool IsPossible(const int & index, const int & val) const;
	virtual bool IsSolved(void) const;
	virtual bool IsValid(void) const;
	virtual int  LeastCount(void) const;
	virtual bool LoadBoard(const std::string &content);
	virtual void Propagate(ePropagateType type);
	virtual void Prun(void);
	virtual ePuzzleLevel Rate(void);
	virtual void SetGiven(const int & index, bool given);
	virtual void SetDiggable(const int & index, bool diggabe);
	virtual bool SetVal(const int & index, const int & val);
	virtual bool ViolateLowerUnitBoundary(const int & index, const ePuzzleLevel & level) const;

	static void PrepareBoard();
};

