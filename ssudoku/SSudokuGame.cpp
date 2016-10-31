
#include "stdafx.h"
#include "SSudokuGame.h"
#include <new>
#include <random>

std::string SSudokuGame::gDigits9 = "123456789";
std::vector< std::vector<int> > SSudokuGame::gUnits9(ROW9 + COL9 + SQR9);
std::vector< std::vector<int> > SSudokuGame::gPeers9(ROW9 * COL9);
std::vector< std::vector<int> > SSudokuGame::gUnitsOfCell9(ROW9 * COL9);

const int level_given_cells[] = { 50, 36, 32, 28, 22 };

SSudokuGame::SSudokuGame(const int &rowSz, const int &colSz) : mSolved(false), mLevel(LEVEL_EASY),
						                                       mRowSz(rowSz), mColSz(colSz), 
															   mOrigCells(rowSz * colSz), mCells(rowSz * colSz)
{
}

SSudokuGame::~SSudokuGame()
{
}

void SSudokuGame::Initialize() 
{
	// initialize units
	for (int i = 0; i < ROW9; i++) {
		for (int j = 0; j < COL9; j++) {
			// initialize units
			int k = i * ROW9 + j;
			int x[3] = { i, ROW9 + j, ROW9 + COL9 + (i / 3) * 3 + j / 3 };
			for (int u = 0; u < 3; u++) {
				gUnits9[x[u]].push_back(k);
				gUnitsOfCell9[k].push_back(x[u]);
			}
		}
	}

	// initialize peers
	for (int k = 0; k < gPeers9.size(); k++) {
		for (int u = 0; u < gUnitsOfCell9[k].size(); u++) {
			for (int j = 0; j < ROW9; j++) {
				int k2 = gUnits9[gUnitsOfCell9[k][u]][j];
				if (k2 != k) gPeers9[k].push_back(k2);
			}
		}
	}
}

/* ISSudokuGame */
int SSudokuGame::Read(const std::vector< std::string > &content)
{
	// read content into mOrigCells
	if (content.size() != mRowSz) return -1;

	for (int i = 0; i < mRowSz; i++) {
		if (content[i].length() != mColSz) return -1;

		for (int j = 0; j < mColSz; j++) {
			if (gDigits9.find_first_of(content[i][j]) == std::string::npos)
				continue;

			for (int k = 0; k < gDigits9.length(); k++) {
				if (gDigits9[k] != content[i][j]) {
					mOrigCells[i * mRowSz + j].Eliminate(k);
				}
			}
		}
	}

	return 0;
}

int SSudokuGame::Solve()
{
	for (int i = 0; i < mOrigCells.size(); i++) {
		if (mOrigCells[i].Count() == 1) {
			if (!Assign(i, mOrigCells[i].Val(), mCells)) {
				return -1;
			}
		}
	}

	if (SolveF(mCells) == false) {
		return -1;
	}
	mSolved = true;
	return 0;
}

bool SSudokuGame::SolveF(std::vector< SSudokuCell > &cells)
{
	if (IsSolved(cells))
		return true;

	int idx = LeastCount(cells);

	for (int i = 0; i < gDigits9.length(); i++) {
		if (cells[idx].IsPossible(i)) {
			std::vector< SSudokuCell > cells_2(cells.size());
			CopyCells(cells, cells_2);
			if (Assign(idx, i, cells_2)) {
				if (SolveF(cells_2) == true) {
					CopyCells(cells_2, cells);
					return true;
				}
			}
		}
	}
	return false;
}

int SSudokuGame::Generate()
{
	// Create terminal pattern, Las Vegas Algorithm
	CreateTerminalPattern(mOrigCells);

	return 0;
}

int SSudokuGame::Check() const
{
	if (IsSolved(mCells) == true) {
		return 0;
	}
	return -1;
}

int SSudokuGame::Rate(int &level) const
{
	level = 0;

	//return -1 if cannot calculate level
	return 0;
}

char SSudokuGame::GetCell(const int & r, const int & c) const
{
	if((r < mRowSz) && (c < mColSz)) {
		int i = -1;
		if (mSolved && (mCells[r * mRowSz + c].Count() == 1)) {
			i = mCells[r * mRowSz + c].Val();
		}
		else if (!mSolved && (mOrigCells[r * mRowSz + c].Count() == 1)) {
			i = mOrigCells[r * mRowSz + c].Val();
		}
		if ((i >= 0) && (i < gDigits9.length()))
			return gDigits9[i];
	}

	return ' ';
}

int SSudokuGame::SetCell(const int & r, const int & c, const char & val)
{
	if (r < mRowSz && c < mColSz ) {
		// TODO: Assign(r * mRowSz + c, val, mCells);
		return 0;
	}

	return -1;
}

bool SSudokuGame::Assign(const int &idx, const int &val, std::vector< SSudokuCell > &cells)
{
	if (val < 0 || val >= gDigits9.length())
		return true;

	for (int i = 0; i < gDigits9.length(); i++) {
		if (i != val) {
			if (!Eliminate(idx, i, cells))
				return false;
		}
	}
	return true;
}

void SSudokuGame::CopyCells(std::vector< SSudokuCell > &cell_src, std::vector< SSudokuCell > &cell_dst) {
	if (cell_src.size() != cell_dst.size()) return;

	for (int i = 0; i < cell_src.size(); i++) {
		cell_dst[i] = cell_src[i];
	}
}

bool SSudokuGame::BackTracking(std::vector< SSudokuCell > &cells, std::vector< int > &givens, int pos)
{
	if (pos >= givens.size()) return true;

	int idx = givens[pos];
	for (int i = 0; i < gDigits9.size(); i++) {
		if (cells[idx].IsPossible(i)) {
			std::vector< SSudokuCell > cells_2(cells.size());
			CopyCells(cells, cells_2);
			if (Assign(idx, i, cells_2)) {
				if (BackTracking(cells_2, givens, pos+1) == true) {
					CopyCells(cells_2, cells);
					return true;
				}
			}
		}
	}

	return false;
}

bool SSudokuGame::CreateTerminalPattern(std::vector< SSudokuCell > &cells)
{
	// Las Vegas Algorithm

	// generate given number based on difficulty level
	int numGivens = rand() % (level_given_cells[mLevel - 1] - level_given_cells[mLevel]) + level_given_cells[mLevel];
	std::vector< int > givens;
	
	// generate random given cell index
	for (int i = 0; i < numGivens; i++) {
		int temp = rand() % (mRowSz * mColSz);
		givens.push_back(temp);
	}

	BackTracking(cells, givens, 0);

	return true;
}

bool SSudokuGame::Eliminate(const int &idx, const int &val, std::vector< SSudokuCell > &cells) {
	if (idx >= cells.size())
		return false;
	
	if(!cells[idx].IsPossible(val)) {
		return true;
	}

	cells[idx].Eliminate(val);

	int N = cells[idx].Count();
	if (N == 0) {
		return false;
	}
	else if (N == 1) {
		int val_temp = cells[idx].Val();
		for (int i = 0; i < gPeers9[idx].size(); i++) {
			if (!Eliminate(gPeers9[idx][i], val_temp, cells))
				return false;
		}
	}

	// Assign val to single remaining peer in a unit
	for (int i = 0; i < gUnitsOfCell9[idx].size(); i++) {
		const int x = gUnitsOfCell9[idx][i];
		int n = 0, ks;
		for (int j = 0; j < gUnits9[x].size(); j++) {
			const int p = gUnits9[x][j];
			if (cells[p].IsPossible(val)) {
				n++;
				ks = p;
			}
		}
		if (n == 0) {
			return false;
		}
		else if (n == 1 && (cells[ks].Count() > 1)) {
			if (!Assign(ks, val, cells)) {
				return false;
			}
		}
	}
	return true;
}

bool SSudokuGame::IsSolved(const std::vector< SSudokuCell > &cells) const
{
	for (int i = 0; i < cells.size(); i++ ) {
		if (cells[i].Count() != 1) {
			return false;
		}
	}

	return true;
}

int SSudokuGame::LeastCount(const std::vector< SSudokuCell > &cells) const
{
	int min = mRowSz * mColSz;
	int idx;
	for (int i = 0; i < cells.size(); i++) {
		int m = cells[i].Count();
		if ((m > 1) && (m < min)) {
			min = m;
			idx = i;
		}
	}
	return idx;
}