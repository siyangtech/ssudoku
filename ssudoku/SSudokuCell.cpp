#include "stdafx.h"
#include "SSudokuCell.h"

CSudokuCell::CSudokuCell(byte size) : mDigits(size, true), mSize(size), mGiven(false), mDiggable(true)
{
}

int CSudokuCell::Count() const 
{
	return (int)std::count(mDigits.begin(), mDigits.end(), true);
}

void CSudokuCell::Eliminate(int i) 
{
	if (i >= 0 && i < mSize) {
		mDigits[i] = false;
	}
}

CString CSudokuCell::GetCellStr(bool filled, bool given, const std::string &charStr) const
{
	CString str("");
	if (filled && !IsFilled()) {
		return str;
	}
	if (given && !IsGiven()) {
		return str;
	}
	for (unsigned int i = 0; i < mDigits.size(); i++) {
		if (mDigits[i] == true) {
			str += charStr[i];
		}
	}
	return str;
}

bool CSudokuCell::IsPossible(int i) const 
{
	if (i >= 0 && i < mSize) {
		return mDigits[i];
	}
	return false;
}

void CSudokuCell::Reset(void)
{
	mDigits.assign(mSize, true);
	mGiven = false;
	mDiggable = true;
}

void CSudokuCell::SetVal(const int &val, bool given)
{
	Reset();
	for (int i = 0; i < mSize; i++) {
		if (i != val) {
			mDigits[i] = false;
		}
	}
	mGiven = given;
}

int CSudokuCell::Val() const
{
	for (int i = 0; i < mSize; i++) {
		if (mDigits[i] == true) {
			return i;
		}
	}
	return -1;
}