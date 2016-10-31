
#include "stdafx.h"
#include "SSudokuPuzzle.h"
#include <new>
#include <random>

const int level_given_cells[] = { 50, 36, 32, 28, 22 };

CSudokuPuzzle::CSudokuPuzzle(ISSudokuSerializer &serializer) : mBoard(NULL), mSerializer(serializer), mLevel(LEVEL_NONE)
{
}

CSudokuPuzzle::~CSudokuPuzzle()
{
	if (mBoard) {
		delete mBoard;
		mBoard = NULL;
	}
}

bool CSudokuPuzzle::Initialize(ePuzzleType type)
{
	switch (type) {
	case s9x9:
		mBoard = (ISSudokuBoard*) new CSudokuBoard9x9();
		if (mBoard == NULL) {
			return false;
		}
		if (!mBoard->Initialize()) {
			delete mBoard;
			mBoard = NULL;
			return false;
		}
		break;
	default:
		break;
	}

	return true;
}

bool CSudokuPuzzle::LoadFromFile(std::string & file)
{
	if (!mBoard || !mSerializer.FileToBoard(file, *mBoard)) {
		return false;
	}

	return true;
}

bool CSudokuPuzzle::Solve()
{
	CSudokuGenSolveEngine engine;
	if (mBoard && (engine.Solve(*mBoard) > 0)) {
		return true;
	}
	return false;
}

bool CSudokuPuzzle::Generate(ePuzzleLevel level)
{
	CSudokuGenSolveEngine engine;
	if (mBoard && engine.Generate(*mBoard, level)) {
		mLevel = level;
		return true;
	}

	return false;
}

ePuzzleLevel CSudokuPuzzle::Rate()
{
	if (mBoard) {
		mLevel = mBoard->Rate();
	}
	return mLevel;
}

bool CSudokuPuzzle::ResetBoard()
{
	if (mBoard) {
		mBoard->ClearBoard();
		return true;
	}
	return false;
}

bool CSudokuPuzzle::Validate() const
{
	if (mBoard && (mBoard->IsValid() == true)) {
		return true;
	}
	return false;
}