#include "stdafx.h"
#include "SSudokuBoard.h"
#include <set>

const std::string CSudokuBoard9x9::gDigits = { "123456789" };
std::vector< std::vector<int> > CSudokuBoard9x9::gUnits(gNumUnits);
std::vector< std::vector<int> > CSudokuBoard9x9::gPeers(gNumPeers);
std::vector< std::vector<int> > CSudokuBoard9x9::gUnitsOfCell(gNumCells);
bool CSudokuBoard9x9::gInitialized = false;
int CSudokuBoard9x9::gPuzzleGivenBoundary[MAX_PUZZLE_LEVEL + 1] = { 50, 36, 32, 28, 22 };
int CSudokuBoard9x9::gPuzzleLowerBoundaryPerUnit[MAX_PUZZLE_LEVEL + 1] = { 7, 4, 3, 2, 0 };
eSequenceOfDigging CSudokuBoard9x9::gPuzzleDigPattern[MAX_PUZZLE_LEVEL + 1] = { SEQ_RANDOM, SEQ_RANDOM, SEQ_JUMPING_ONE, SEQ_S, SEQ_LR_TB };

CSudokuBoard9x9::CSudokuBoard9x9() : mCellsP(NULL), mState(sUninitialized)
{
	if (!gInitialized) {
		CSudokuBoard9x9::PrepareBoard();
		gInitialized = true;
	}
}

CSudokuBoard9x9::~CSudokuBoard9x9()
{
	if (mCellsP) {
		for (int i = 0; i < gNumCells; i++) {
			if (mCellsP[i]) {
				delete mCellsP[i];
			}
		}
		delete mCellsP;
		mCellsP = NULL;
	}
}

void CSudokuBoard9x9::PrepareBoard() 
{
	// initialize units
	for (int i = 0; i < gBoardSize; i++) {
		for (int j = 0; j < gBoardSize; j++) {
			// initialize units
			int k = i * gBoardSize + j;
			int x[3] = { i, gBoardSize + j, gBoardSize + gBoardSize + (i / 3) * 3 + j / 3 };
			for (int u = 0; u < 3; u++) {
				gUnits[x[u]].push_back(k);
				gUnitsOfCell[k].push_back(x[u]);
			}
		}
	}

	// initialize peers
	for (int i = 0; i < gNumPeers; i++) {
		for (int u = 0; u < gNumUnitsOfCell; u++) {
			for (int j = 0; j < gBoardSize; j++) {
				int k = gUnits[gUnitsOfCell[i][u]][j];
				if (k != i) gPeers[i].push_back(k);
			}
		}
	}
}

CSudokuBoard9x9::CSudokuBoard9x9(const CSudokuBoard9x9 &src)
{
	Initialize();

	// copy cells
	if (mCellsP && src.mCellsP) {
		for (int i = 0; i < gNumCells; i++) {
			if (mCellsP[i] && src.mCellsP[i]) {
				*mCellsP[i] = *src.mCellsP[i];
			}
		}
	}
	mState = src.mState;

}

CSudokuBoard9x9& CSudokuBoard9x9::operator=(const CSudokuBoard9x9 &src)
{
	Initialize();

	// copy cells
	if (mCellsP && src.mCellsP) {
		for (int i = 0; i < gNumCells; i++) {
			if (mCellsP[i] && src.mCellsP[i]) {
				*mCellsP[i] = *src.mCellsP[i];
			}
		}
	}
	mState = src.mState;

	return *this;
}

bool CSudokuBoard9x9::Assign(const int & index, const int & val)
{
	if (val < 0 || val >= gBoardSize)
		return false;
	if (index < 0 || index >= gNumCells) {
		return false;
	}
	for (int i = 0; i < gBoardSize; i++) {
		if (i != val) {
			if (!Eliminate(index, i)) {
				return false;
			}
		}
	}
	
	return true;
}

void CSudokuBoard9x9::ChangeState(sState newState)
{
	mState = newState;
}

void CSudokuBoard9x9::ClearBoard(void)
{
	if (mCellsP)
	{
		for (int i = 0; i < gNumCells; i++) {
			if (mCellsP[i]) {
				mCellsP[i]->Reset();
			}
		}
	}
	ChangeState(sInitialized);
}

void CSudokuBoard9x9::Copy(const ISSudokuBoard &board)
{
	*this = (const CSudokuBoard9x9&)board;
}

int CSudokuBoard9x9::CountDiggable(void)
{
	int sum = 0;
	if (mCellsP)
	{
		for (int i = 0; i < gNumCells; i++)
		{
			if (mCellsP[i] && mCellsP[i]->IsDiggable())
			{
				sum++;
			}
		}
	}
	return sum;
}

bool CSudokuBoard9x9::DigCell(const int & index, int & preVal)
{
	if (index < 0 || index >= gNumCells)
		return false;
	if (mCellsP && mCellsP[index] && mCellsP[index]->IsDiggable())
	{
		preVal = mCellsP[index]->Val();
		mCellsP[index]->Reset();
		return true;
	}
	return false;
}

ISSudokuBoard* CSudokuBoard9x9::Duplicate()
{
	CSudokuBoard9x9 *board = new CSudokuBoard9x9();
	if (board == NULL) {
		TRACE(traceAppMsg, 0, "Failed to allocate memory!!!!!!!!");
	}
	*board = *this;
	return board;
}

bool CSudokuBoard9x9::Eliminate(const int & index, const int & val)
{
	if (index < 0 || index >= gNumCells)
		return false;

	if (!mCellsP[index]->IsPossible(val)) {
		return true;
	}

	mCellsP[index]->Eliminate(val);

	int N = mCellsP[index]->Count();
	if (N == 0) {
		return false;
	}
	else if (N == 1) {
		int val_temp = mCellsP[index]->Val();
		for (int i = 0; i < gPeers[index].size(); i++) {
			int k = gPeers[index][i];
			if (!Eliminate(k, val_temp))
				return false;
		}
	}

	// Assign val to single remaining peer in a unit
	for (int i = 0; i < gUnitsOfCell[index].size(); i++) {
		const int x = gUnitsOfCell[index][i];
		int n = 0, ks;
		for (int j = 0; j < gUnits[x].size(); j++) {
			const int p = gUnits[x][j];
			if (mCellsP[p]->IsPossible(val)) {
				n++;
				ks = p;
			}
		}
		if (n == 0) {
			return false;
		}
		else if (n == 1 && (mCellsP[ks]->Count() > 1)) {
			if (!Assign(ks, val)) {
				return false;
			}
		}
	}

	return true;
}

CString CSudokuBoard9x9::GetCell(const int &row, const int &col, bool isGiven) const
{
	int idx = row * gBoardSize + col;

	if (mCellsP && mCellsP[idx] && (idx < gNumCells)) {
		return mCellsP[idx]->GetCellStr(isGiven, isGiven, gDigits);
	}
	return CString("");
}

bool CSudokuBoard9x9::IsDiggable(const int & index) const
{
	if (index < 0 || index >= gNumCells) {
		return false;
	}
	if (mCellsP && mCellsP[index]) {
		return mCellsP[index]->IsDiggable();
	}
	return false;
}

bool CSudokuBoard9x9::IsFilled(const int & index) const
{
	if (index < 0 || index >= gNumCells) {
		return false;
	}
	if (mCellsP && mCellsP[index]) {
		return mCellsP[index]->IsFilled();
	}
	return false;
}

bool CSudokuBoard9x9::IsGiven(const int & index) const
{
	if (index < 0 || index >= gNumCells) {
		return false;
	}
	if (mCellsP && mCellsP[index]) {
		return mCellsP[index]->IsGiven();
	}
	return false;
}

bool CSudokuBoard9x9::Initialize(void)
{
	if (mState != sUninitialized) return true;

	mCellsP = new CSudokuCell*[gNumCells];
	if (!mCellsP) return false;

	for (int i = 0; i < gNumCells; i++) {
		mCellsP[i] = new CSudokuCell(gBoardSize);
		if (!mCellsP[i]) return false;
	}

	CSudokuCell cell(gBoardSize);
	//TRACE(traceAppMsg, 0, "sizeofCell=%d bool=%d\n", sizeof(cell), sizeof(r));

	ChangeState(sInitialized);
	return true;
}

bool CSudokuBoard9x9::IsPossible(const int & index, const int & val) const
{ 
	if (mState == sUninitialized) return false;
	if (index < 0 || index >= gNumCells) return false;

	return mCellsP[index]->IsPossible(val); 
}

bool CSudokuBoard9x9::IsSolved(void) const
{
	for (int i = 0; i < gNumCells; i++) {
		if (!mCellsP[i]->IsFilled()) {
			return false;
		}
	}

	return IsValid();
}

bool CSudokuBoard9x9::IsValid(void) const
{
	if (mState == sUninitialized) {
		return false;
	}
	// make sure there is no duplicate in each unit
	for (int i = 0; i < gNumUnits; i++) {
		std::vector<int> temp;
		for (int j = 0; j < gUnits[i].size(); j++) {
			int idx = gUnits[i][j];
			if (mCellsP[idx] && mCellsP[idx]->IsFilled()) {
				int val = mCellsP[idx]->Val();
				for (int k = 0; k < temp.size(); k++) {
					if (temp[k] == val) {
						return false;
					}
				}
				temp.push_back(val);
			}
		}
	}
	return true;
}

int CSudokuBoard9x9::LeastCount(void) const
{
	int min = gNumCells;
	int idx = -1;
	for (int i = 0; i < gNumCells; i++) {
		int m = mCellsP[i]->Count();
		if ((m > 1) && (m < min)) {
			min = m;
			idx = i;
		}
	}
	return idx;
}

bool CSudokuBoard9x9::LoadBoard(const std::string &content)
{
	if (content.size() != gNumCells) return false;

	// reset the board
	ClearBoard();

	for (int i = 0; i < gNumCells; i++) {
		size_t pos = gDigits.find_first_of(content[i]);
		if (pos == std::string::npos)
			continue;
		mCellsP[i]->SetGiven(true);
		Assign(i, (int)pos);
	}

	ChangeState(sLoaded);
	return true;
}

void CSudokuBoard9x9::Propagate(ePropagateType type)
{
	if (mState == sUninitialized){
		return;
	}
	int col2;
	int d1, d2;
	switch (type) {
	case PROPG_SWITCH_DIGIT:
		d1 = rand() % gBoardSize;
		d2 = rand() % gBoardSize;
		if (d1 != d2) {
			for (int i = 0; i < gNumCells; i++) {
				if (mCellsP && mCellsP[i]) {
					if (mCellsP[i]->IsFilled()) {
						if (mCellsP[i]->Val() == d1) {
							mCellsP[i]->SetVal(d2);
						}
						else if (mCellsP[i]->Val() == d2) {
							mCellsP[i]->SetVal(d1);
						}
					}
				}
			}
		}
		break;
	case PROPG_SWITCH_COL:
		col2 = rand() % gNumUnitsOfCell;
		col2 = col2 * 3; // col can be 0,3,6
		for (int i = 0; i < gNumCells; i++) {
			int col = i % gBoardSize;
			if (col == col2) {
				CSudokuCell *temp = mCellsP[i];
				mCellsP[i] = mCellsP[i+2];
				mCellsP[i+2] = temp;
			}
		}
		break;
	case PROPG_ROTATE:
	default:
		break;
	}
}

void CSudokuBoard9x9::Prun(void) {
	if(!mCellsP) {
		return;
	}
	std::string str;
	for (int i = 0; i < gNumCells; i++) {
		if (mCellsP[i]) {
			if (mCellsP[i]->IsFilled()) {
				int val = mCellsP[i]->Val();
				str += gDigits[val];
			}
			else {
				str += '.';
			}
		}
	}
	LoadBoard(str);
}

ePuzzleLevel CSudokuBoard9x9::Rate(void)
{
	if (mState < sLoaded) {
		return LEVEL_NONE;
	}

	tPuzzleRate rate;
	int level1, level2, level;
	
	rate.nGivens = 0;
	// count givens
	for (int i = 0; i < gNumCells; i++) {
		if (mCellsP && mCellsP[i]) {
			if (mCellsP[i]->IsGiven()) {
				rate.nGivens++;
			}
		}
	}

	for (int i = 0; i < MAX_PUZZLE_LEVEL; i++) {
		if (rate.nGivens < gPuzzleGivenBoundary[i]) {
			level1 = i + 1;
		}
	}

	// count lowest givens per units
	// make sure there is no duplicate in each unit
	rate.nMinGivensPerUnits = gBoardSize;
	for (int i = 0; i < gNumUnits; i++) {
		int temp = 0;
		for (int j = 0; j < gUnits[i].size(); j++) {
			int idx = gUnits[i][j];
			if (mCellsP[idx] && mCellsP[idx]->IsGiven()) {
				temp++;
			}
		}
		if (temp < rate.nMinGivensPerUnits) {
			rate.nMinGivensPerUnits = temp;
		}
	}

	for (int i = 0; i < MAX_PUZZLE_LEVEL; i++) {
		if (rate.nMinGivensPerUnits < gPuzzleLowerBoundaryPerUnit[i]) {
			level2 = i + 1;
		}
	}
	level = (int)((double)level1*0.7 + (double)level2*0.3);
	return (ePuzzleLevel)level1;
}

void CSudokuBoard9x9::SetGiven(const int & index, bool given)
{
	if (index < 0 || index >= gNumCells) {
		return;
	}
	if (mCellsP && mCellsP[index]) {
		mCellsP[index]->SetGiven(given);
	}
}

void CSudokuBoard9x9::SetDiggable(const int & index, bool diggable)
{
	if (index < 0 || index >= gNumCells) {
		return;
	}
	if (mCellsP && mCellsP[index]) {
		mCellsP[index]->SetDiggable(diggable);
	}
}

bool CSudokuBoard9x9::SetVal(const int & index, const int & val)
{
	if (index < 0 || index >= gNumCells) {
		return false;
	}
	if (val < 0 || val >= gBoardSize) {
		return false;
	}
	if (mCellsP && mCellsP[index]) {
		mCellsP[index]->SetVal(val);
	}
	return true;
}

bool CSudokuBoard9x9::ViolateLowerUnitBoundary(const int & index, const ePuzzleLevel & level) const
{
	if (mCellsP == NULL) {
		return false;
	}

	// check whether reach lower boundary of difficulty level
	int lower_b = GetLowerBoundaryPerUnit(level);

	for (int i = 0; i < gUnitsOfCell[index].size(); i++) {
		int uIdx = gUnitsOfCell[index][i];
		int count = 0;
		for (int j = 0; j < gUnits[uIdx].size(); j++) {
			int k = gUnits[uIdx][j];
			if (mCellsP[k] && mCellsP[k]->IsFilled()) {
				count++;
			}
		}
		if (count <= lower_b) {
			return true;
		}
	}
	return false;
}