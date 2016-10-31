#pragma once

#include <vector>

class CSudokuCell
{
private:
	std::vector<bool> mDigits;
	byte mSize;
	bool mGiven;
	bool mDiggable;

public:

	CSudokuCell(byte size = 9);
	~CSudokuCell() {}

	CSudokuCell& operator=(const CSudokuCell &src);
	
	int    Count() const;
	void   Eliminate(int i);
	CString GetCellStr(bool filled, bool given, const std::string &charStr) const;
	bool   IsDiggable(void) const { return mDiggable; }
	bool   IsFilled(void) const { return Count() == 1; }
	bool   IsGiven(void) const { return mGiven; }
	bool   IsPossible(int i) const;
	void   Reset(void);
	void   SetDiggable(bool diggable) { mDiggable = diggable; }
	void   SetGiven(bool given) { mGiven = given; }
	void   SetVal(const int &val, bool original = false);
	int    Val() const;
};

